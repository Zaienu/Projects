using System.Collections.Generic;
using Entities_Core_Scripts;
using Helper;
using UnityEditor;
using UnityEngine;

namespace Editor.Tools_Scripts.Data_Management
{
    public class EntityManager : ScriptableObject
    {
        private float[] stats = new float[4];
        private Relations[] relationships = new Relations[3]{ new(), new(), new() };
        private List<string> behaviours = new();
        private EntityData entityData;
        
        private void SetData(string _path, string _tag)
        {
            entityData.Stats = stats.Copy();
            entityData.Relationships = relationships.Copy();
            entityData.Behaviours = behaviours.Copy();
            EditorUtility.SetDirty(entityData);
            AssetDatabase.SaveAssets();
            AssetDatabase.Refresh();
        }

        private void CreateFolder(string _parent, string _name)
        {
            AssetDatabase.CreateFolder(_parent, _name);
            AssetDatabase.SaveAssets();
            AssetDatabase.Refresh();
        }

        private bool CheckFolderValidity(string _path)
        {
            return AssetDatabase.IsValidFolder(_path);
        }

        private bool CheckFileValidity(string _path, string _name)
        {
            string assetPath = string.Concat(_path + _name + ".asset");
            return AssetDatabase.LoadAssetAtPath<EntityData>(assetPath);
        }

        private void CreateFile(string _path, string _name)
        {
            string assetPath = string.Concat(_path + _name + ".asset");
            
            EntityData data = CreateInstance<EntityData>();
            AssetDatabase.CreateAsset(data, assetPath);
            
            Relations[] tempRelationships = relationships.Copy();
            float[] tempStats = stats.Copy();
            List<string> tempBehaviours = behaviours.Copy();
            
            entityData = data;
            relationships = tempRelationships;
            stats = tempStats;
            behaviours = tempBehaviours;
        }
        
        private void CreateEntityData(string _path, string _name, string _pFolder, string _nFolder)
        {
            if (!CheckFolderValidity(_path))
            {
                CreateFolder(_pFolder, _nFolder);
            }

            if (!CheckFileValidity(_path, _name))
            {
                CreateFile(_path, _name);
            }
            
            AssetDatabase.SaveAssets();
            AssetDatabase.Refresh();
        }
        
        public bool FindEntityData(string _path, string _tag)
        {
            string assetPath = string.Concat(_path + _tag + ".asset");

            if (!CheckFileValidity(_path, _tag))
            {
                return false;
            }

            if (!AssetDatabase.LoadAssetAtPath<EntityData>(assetPath))
            {
                return false;
            }

            return true;
        }

        public void LoadEntityData(string _path, string _tag)
        {
            string assetPath = string.Concat(_path + _tag + ".asset");
            EntityData = AssetDatabase.LoadAssetAtPath<EntityData>(assetPath);
        }

        public void SaveStats(string _path, string _tag)
        {
            if (!FindEntityData(_path, _tag))
            {
                CreateEntityData(_path, _tag, "Assets", "Entities Data");
            } 
            SetData(_path, _tag);
        }

        public EntityData EntityData
        {
            get => entityData;
            set
            {
                entityData = value;
                Relationships = entityData.Relationships.Copy();
                Stats = entityData.Stats.Copy();
                Behaviours = entityData.Behaviours.Copy();
            }
        }

        public Relations[] Relationships
        {
            get => relationships;
            private set => relationships = value;
        }

        public float[] Stats
        {
            get => stats;
            set => stats = value;
        }

        public List<string> Behaviours
        {
            get => behaviours;
            set => behaviours = value;
        }
    }
}