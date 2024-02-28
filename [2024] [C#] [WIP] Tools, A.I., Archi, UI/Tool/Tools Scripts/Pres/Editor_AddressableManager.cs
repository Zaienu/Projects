using System;
using System.Collections.Generic;
using UnityEditor;
using UnityEditor.AddressableAssets;
using UnityEditor.AddressableAssets.Settings;
using UnityEditor.AddressableAssets.Settings.GroupSchemas;
using UnityEngine.AddressableAssets;
using UnityEngine.ResourceManagement.AsyncOperations;
using UnityEngine.ResourceManagement.ResourceLocations;

namespace Editor.Tools_Scripts.Pres
{
    public class Editor_AddressableManager<T>
    {
        private T asset;
        public event Action OnLoaded;
        public event Action OnNotFound;

        private AddressableAssetGroup CreateAssetGroup(AddressableAssetSettings _settings, string _group)
        {
            return _settings.CreateGroup(_group, false, false, true, null, typeof(BundledAssetGroupSchema));
        }

        private bool CheckSettings(out AddressableAssetSettings _settings)
        {
            _settings = AddressableAssetSettingsDefaultObject.Settings;
            if (!_settings)
            {
                return false;
            }

            return true;
        }

        private void CreateGroup(out AddressableAssetGroup _group, AddressableAssetSettings _settings,
            string _groupName)
        {
            _group = _settings.FindGroup(_groupName);
            if (!_group)
            {
                _group = CreateAssetGroup(_settings, _groupName);
            }
        }

        private bool SearchKey(AddressableAssetGroup _group, string _key)
        {
            foreach (AddressableAssetEntry entry in _group.entries)
            {
                if (entry.address == _key)
                {
                    return true;
                }
            }

            return false;
        }

        public void CreateAddressable(string _path, string _key, string _groupName)
        {
            if (!CheckSettings(out AddressableAssetSettings settings))
            {
                return;
            }

            CreateGroup(out AddressableAssetGroup group, settings, _groupName);

            if (SearchKey(group, _key))
            {
                return;
            }

            //Refactor
            string guid = AssetDatabase.AssetPathToGUID(_path);
            if (string.IsNullOrEmpty(guid))
            {
                return;
            }

            AddressableAssetEntry newEntry = settings.CreateOrMoveEntry(guid, group);
            newEntry.address = _key;

            settings.SetDirty(AddressableAssetSettings.ModificationEvent.EntryMoved, newEntry, true);
            
            AssetDatabase.SaveAssets();
            AssetDatabase.Refresh();
            
            FindEntityData(_key);
        }

        private EditorApplication.CallbackFunction currentUpdateAction;
        
        public void FindEntityData(string _tag)
        {
            var handle = Addressables.LoadResourceLocationsAsync(_tag);
            currentUpdateAction = () => CheckEntityDataPresence(handle, _tag);
            EditorApplication.update += currentUpdateAction;
        }

        private void CheckEntityDataPresence(AsyncOperationHandle<IList<IResourceLocation>> _list, string _tag)
        {
            if (_list.IsDone)
            {
                EditorApplication.update -= currentUpdateAction;
                
                if (_list.Status == AsyncOperationStatus.Succeeded)
                {
                    var locations = _list.Result;
                    
                    if (locations is { Count: > 0 })
                    {
                        var handle = Addressables.LoadAssetAsync<T>(_tag);
                        currentUpdateAction = () => OnEntityDataLoaded(handle, _tag);
                        EditorApplication.update += currentUpdateAction;
                    }
                    else
                    {
                        asset = default;
                        OnNotFound?.Invoke();
                    }
                    Addressables.Release(_list);
                }
            }
        }

        private void OnEntityDataLoaded(AsyncOperationHandle<T> _asset, string _tag)
        {
            if (_asset.IsDone)
            {
                EditorApplication.update -= currentUpdateAction;
                currentUpdateAction = null;
                
                if (_asset.Status == AsyncOperationStatus.Succeeded)
                {
                    asset = _asset.Result;
                    OnLoaded?.Invoke();
                }
                Addressables.Release(_asset);
            }
        }

        public T Asset => asset;
    }
}