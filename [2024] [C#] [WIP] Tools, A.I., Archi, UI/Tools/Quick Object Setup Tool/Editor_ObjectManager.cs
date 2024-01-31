using System;
using System.Collections.Generic;
using Obstacles_Core_Scripts;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;
using Button = UnityEngine.UIElements.Button;
using Utility;

namespace Editor.Tool_Scripts.Quick_Object_Setup_Tool
{
    enum TYPE
    {
        ENTITY,
        OBSTACLE,
    }

    public class Editor_ObjectManager : EditorWindow
    {
        [SerializeField] private VisualTreeAsset UXML_UI;
        [SerializeField] private ObjectManager objectManager;

        //Menu Tab Attribute
        [MenuItem("Window/I.A.I.T./Quick Object Setup Tool")]
        public static void InitWindow()
        {
            EditorWindow window = GetWindow<Editor_ObjectManager>();
            window.titleContent = new GUIContent("Quick Object Setup Tool");
            window.minSize = new Vector2(625, 360);
            window.maxSize = new Vector2(625, 360);
        }

        public void CreateGUI()
        {
            if (!Application.isEditor)
            {
                return;
            }

            UXML_UI.CloneTree();

            TemplateContainer container = UXML_UI.Instantiate();
            rootVisualElement.Add(container);

            #region Get Visual Elements

            #region Apply Buttons

            //Configure Entity Button
            Button CE_Button = rootVisualElement.Q<Button>(null, "CE_Button");

            //Configure Obstacle Button
            Button CO_Button = rootVisualElement.Q<Button>(null, "CO_Button");

            #endregion

            #region Tag List

            //Entities Tag List
            ListView ET_List = rootVisualElement.Q<ListView>(null, "ET_List");
            //Entities Tag List Add Button
            VisualElement ETL_AddButton = rootVisualElement.Q<VisualElement>(null, "ETL_AddButton");
            //Entities Tag List Subtract Button
            VisualElement ETL_SubButton = rootVisualElement.Q<VisualElement>(null, "ETL_SubButton");

            //Obstacles Tag List
            ListView OT_List = rootVisualElement.Q<ListView>(null, "OT_List");
            //Obstacles Tag List Add Button
            VisualElement OTL_AddButton = rootVisualElement.Q<VisualElement>(null, "OTL_AddButton");
            //Obstacles Tag List Subtract Button
            VisualElement OTL_SubButton = rootVisualElement.Q<VisualElement>(null, "OTL_SubButton");

            #endregion
            
            #region Layer Selectors

            //Entities Layer Field
            LayerField ELayer_Field = rootVisualElement.Q<LayerField>(null, "ELayer_Field");

            //Obstacles Layer Field
            LayerField OLayer_Field = rootVisualElement.Q<LayerField>(null, "OLayer_Field");
            
            #endregion

            #endregion

            #region Buttons Functions

            #region Apply Parameters

            #region Entities

            CE_Button.RegisterCallback<ClickEvent>(Configure_Entities);
            CE_Button.SetEnabled(false);
            if (objectManager.Entities_Layer != "Default" && objectManager.Entities_Tags.Count > 0)
            {
                CE_Button.SetEnabled(true);
            }
            
            void Configure_Entities(EventBase _evt)
            {
                objectManager.Configure_Entities();
            }

            #endregion

            #region Obstacles

            CO_Button.RegisterCallback<ClickEvent>(Configure_Obstacles);
            CO_Button.SetEnabled(false);
            if (objectManager.Obstacles_Layer != "Default" && objectManager.Obstacles_Tags.Count > 0)
            {
                CO_Button.SetEnabled(true);
            }
            
            void Configure_Obstacles(EventBase _evt)
            {
                ObstacleManager.Obstacle_List.Clear();
                objectManager.Configure_Obstacles();
            }

            #endregion

            #endregion

            #region Manage List

            //List Delegates
            Func<VisualElement> makeItem = null;
            Action<VisualElement, int> bindEntityItem = null;
            Action<VisualElement, int> bindObstacleItem = null;
            Action<VisualElement, int> unbindEntityItem = null;
            Action<VisualElement, int> unbindObstacleItem = null;
            Action<VisualElement> destroyItem = null;

            //Assign Functions to buttons
            ETL_AddButton.RegisterCallback<ClickEvent>(AddTagItemTo_Entity);
            ETL_SubButton.RegisterCallback<ClickEvent>(SubTagItemTo_Entity);

            OTL_AddButton.RegisterCallback<ClickEvent>(AddTagItemTo_Obstacle);
            OTL_SubButton.RegisterCallback<ClickEvent>(SubTagItemTo_Obstacle);

            //Item Size
            StyleLength itemWidth = ET_List.parent.style.width;
            StyleLength itemHeight = ET_List.style.height.value.Divide(5);

            #region Tag List Functions

            makeItem = () =>
            {
                TagField item = new TagField();

                //Style
                item.style.width = itemWidth;
                item.style.height = itemHeight;

                //Value
                item.value = "Untagged";

                return item;
            };

            #region Entity

            bindEntityItem = (_element, _index) =>
            {
                //Check Whether the element is a TagField and is valid
                TagField toBind = _element as TagField;
                if (toBind == null)
                {
                    return;
                }

                //Set Value according to list index
                toBind.SetValueWithoutNotify(objectManager.Entities_Tags[_index]);

                //Bind the Function that will modify the value when it is changed in UI
                toBind.RegisterCallback<ChangeEvent<string>>(_evt => OnTagFieldValueChanged(_evt, _index, TYPE.ENTITY));
            };

            unbindEntityItem = (_element, _index) =>
            {
                //Check Whether the element is a TagField and is valid
                TagField toUnbind = _element as TagField;
                if (toUnbind == null)
                {
                    return;
                }

                //Set Basic Value
                toUnbind.SetValueWithoutNotify("Untagged");

                //Unregister the Callback to avoid any double registrations
                toUnbind.UnregisterCallback<ChangeEvent<string>>(_evt =>
                    OnTagFieldValueChanged(_evt, _index, TYPE.ENTITY));
            };

            #endregion

            #region Obstacle

            bindObstacleItem = (_element, _index) =>
            {
                //Check Whether the element is a TagField and is valid
                TagField toBind = _element as TagField;
                if (toBind == null)
                {
                    return;
                }

                //Set Value according to list index
                toBind.SetValueWithoutNotify(objectManager.Obstacles_Tags[_index]);

                //Bind the Function that will modify the value when it is changed in UI
                toBind.RegisterCallback<ChangeEvent<string>>(
                    _evt => OnTagFieldValueChanged(_evt, _index, TYPE.OBSTACLE));
            };

            unbindObstacleItem = (_element, _index) =>
            {
                //Check Whether the element is a TagField and is valid
                TagField toUnbind = _element as TagField;
                if (toUnbind == null)
                {
                    return;
                }

                //Set Basic Value
                toUnbind.SetValueWithoutNotify("Untagged");

                //Unregister the Callback to avoid any double registrations
                toUnbind.UnregisterCallback<ChangeEvent<string>>(_evt =>
                    OnTagFieldValueChanged(_evt, _index, TYPE.OBSTACLE));
            };

            #endregion

            destroyItem = (_element) =>
            {
                TagField toRemove = _element as TagField;
                if (toRemove == null)
                {
                    return;
                }
            };

            //Link each TextField to its TagList value
            void OnTagFieldValueChanged(ChangeEvent<string> _evt, int _index, TYPE _type)
            {
                if (_type == TYPE.ENTITY)
                {
                    objectManager.Entities_Tags[_index] = _evt.newValue.ToString();
                }
                else if (_type == TYPE.OBSTACLE)
                {
                    objectManager.Obstacles_Tags[_index] = _evt.newValue.ToString();
                }
            }

            #endregion

            //Setup ET_List
            ET_List.makeItem = makeItem;
            ET_List.bindItem = bindEntityItem;
            ET_List.unbindItem = unbindEntityItem;
            ET_List.destroyItem = destroyItem;
            ET_List.selectionType = SelectionType.None;
            ET_List.itemsSource = objectManager.Entities_Tags;
            ET_List.style.height = 5 * itemHeight.value.value;
            ET_List.showBoundCollectionSize = false;

            //Setup OT_List
            OT_List.makeItem = makeItem;
            OT_List.bindItem = bindObstacleItem;
            OT_List.unbindItem = unbindObstacleItem;
            OT_List.destroyItem = destroyItem;
            OT_List.selectionType = SelectionType.None;
            OT_List.itemsSource = objectManager.Obstacles_Tags;
            OT_List.style.height = 5 * itemHeight.value.value;
            OT_List.showBoundCollectionSize = false;

            //Add an Element to the List
            void AddTagItemTo_Entity(EventBase _evt)
            {
                objectManager.Entities_Tags.Add("Untagged");
                if (ELayer_Field.value != LayerMask.NameToLayer("Default"))
                {
                    CE_Button.SetEnabled(true);
                }
                //Update in real time the List
                ET_List.Rebuild();
            }

            //Sub an Element to the List
            void SubTagItemTo_Entity(EventBase _evt)
            {
                if (objectManager.Entities_Tags.Count <= 0) { return; }

                if (objectManager.Entities_Tags.Count == 1) { CE_Button.SetEnabled(false); }

                int index = objectManager.Entities_Tags.Count - 1;
                objectManager.Entities_Tags.RemoveAt(index);

                //Update in real time the List
                ET_List.Rebuild();
            }

            //Add an Element to the List
            void AddTagItemTo_Obstacle(EventBase _evt)
            {
                objectManager.Obstacles_Tags.Add("Untagged");
                if (OLayer_Field.value != LayerMask.NameToLayer("Default"))
                {
                    CO_Button.SetEnabled(true);
                }
                //Update in real time the List
                OT_List.Rebuild();
            }

            //Sub an Element to the List
            void SubTagItemTo_Obstacle(EventBase _evt)
            {
                if (objectManager.Entities_Tags.Count <= 0) { return; }
                
                if (objectManager.Entities_Tags.Count == 1) { CO_Button.SetEnabled(false); }
                
                int index = objectManager.Obstacles_Tags.Count - 1;
                objectManager.Obstacles_Tags.RemoveAt(index);

                //Update in real time the List
                OT_List.Rebuild();
            }

            #endregion

            #region Layer Fields

            //Entities
            ELayer_Field.value = LayerMask.NameToLayer(objectManager.Entities_Layer);
            ELayer_Field.RegisterCallback<ChangeEvent<int>>(_evt => OnLayerValueChanged(_evt, TYPE.ENTITY));

            //Obstacles
            OLayer_Field.value = LayerMask.NameToLayer(objectManager.Obstacles_Layer);
            OLayer_Field.RegisterCallback<ChangeEvent<int>>(_evt => OnLayerValueChanged(_evt, TYPE.OBSTACLE));

            void OnLayerValueChanged(ChangeEvent<int> _evt, TYPE _type)
            {
                if (_type == TYPE.ENTITY)
                {
                    objectManager.Entities_Layer = LayerMask.LayerToName(_evt.newValue);
                    CE_Button.SetEnabled(false);
                    if (objectManager.Entities_Layer != "Default" && objectManager.Entities_Tags.Count > 0)
                    {
                        CE_Button.SetEnabled(true);
                    }
                }
                else if (_type == TYPE.OBSTACLE)
                {
                    objectManager.Obstacles_Layer = LayerMask.LayerToName(_evt.newValue);
                    CO_Button.SetEnabled(false);
                    if (objectManager.Obstacles_Layer != "Default" && objectManager.Obstacles_Tags.Count > 0)
                    {
                        CO_Button.SetEnabled(true);
                    }
                }
            }

            #endregion

            #endregion
        }
    }
}