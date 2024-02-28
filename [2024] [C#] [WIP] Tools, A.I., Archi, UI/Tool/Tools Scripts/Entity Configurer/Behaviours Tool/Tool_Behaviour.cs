using System;
using System.Collections.Generic;
using Entities_Core_Scripts;
using Helper;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;
using Button = UnityEngine.UIElements.Button;
using EntityManager = Editor.Tools_Scripts.Data_Management.EntityManager;

namespace Editor.Tools_Scripts.Entity_Configurer.Behaviours_Tool
{
    public class Tool_Behaviours : EditorWindow
    {
        
        [SerializeField] private VisualTreeAsset UXML_UI;
        [SerializeField] private VisualTreeAsset TagBox;
        [SerializeField] private EntityManager EManager;

        private readonly ListView[] tagLists = new ListView[3];
        private readonly Slider[] statSliders = new Slider[4];

        //Menu Tab Attribute
        [MenuItem("Window/I.A.I.T./Entity Configurer/Behaviour Tool")]
        public static void InitWindow()
        {
            EditorWindow window = GetWindow<Tool_Behaviours>();
            window.titleContent = new GUIContent("Behaviour Tool");
            window.minSize = new Vector2(530, 530);
            window.maxSize = new Vector2(530, 530);
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
            
            DropdownField Entity_Tag = rootVisualElement.Q<DropdownField>(null, "Entity_Tag");
            
            //ENEMIES
            ListView Enemies_List = rootVisualElement.Q<ListView>(null, "Enemies_List");
            Button ELS_Button = rootVisualElement.Q<Button>(null, "ELS_Button");
            Button ELA_Button = rootVisualElement.Q<Button>(null, "ELA_Button");

            //NEUTRAL
            ListView Neutral_List = rootVisualElement.Q<ListView>(null, "Neutral_List");
            Button NLS_Button = rootVisualElement.Q<Button>(null, "NLS_Button");
            Button NLA_Button = rootVisualElement.Q<Button>(null, "NLA_Button");

            //ALLIES
            ListView Allies_List = rootVisualElement.Q<ListView>(null, "Allies_List");
            Button ALS_Button = rootVisualElement.Q<Button>(null, "ALS_Button");
            Button ALA_Button = rootVisualElement.Q<Button>(null, "ALA_Button");

            Button Save_Button = rootVisualElement.Q<Button>(null, "Save_Button");
            
            tagLists[(int)ENTITY_TYPES.Allies] = Allies_List;
            tagLists[(int)ENTITY_TYPES.Neutral] = Neutral_List;
            tagLists[(int)ENTITY_TYPES.Enemies] = Enemies_List;
            
                        //Item Size
            int itemHeight = 30;
            int itemWidth = 123;
            
            void SetData()
            {
                //Update List ??
            }

            //Works
            void ResetData()
            {
                EManager.Relationships.Clear();
                EManager.Stats.Clear();
            }

            void CheckExistingData()
            {
                if (!EManager.FindEntityData("Assets/Entities Data/", Entity_Tag.value))
                {
                    ResetData();
                    return;
                }

                EManager.LoadEntityData("Assets/Entities Data/", Entity_Tag.value);
                SetData();
            }
            
            //Assign Functions to buttons
            Entity_Tag.RegisterCallback<ChangeEvent<string>>(ChangeTag);

            void ChangeTag(EventBase _evt)
            {
                ResetData();
                CheckExistingData();
                // InitLists();
            }
            
            //List Delegates
            Func<VisualElement> makeItem = null;
            Action<VisualElement, int> bindItem = null;
            Action<VisualElement, int> unbindItem = null;
            Action<VisualElement> destroyItem = null;
            
            ELA_Button.RegisterCallback<ClickEvent>(_evt => AddTagItem(_evt, ENTITY_TYPES.Enemies));
            ELS_Button.RegisterCallback<ClickEvent>(_evt => SubTagItem(_evt, ENTITY_TYPES.Enemies));

            NLA_Button.RegisterCallback<ClickEvent>(_evt => AddTagItem(_evt, ENTITY_TYPES.Neutral));
            NLS_Button.RegisterCallback<ClickEvent>(_evt => SubTagItem(_evt, ENTITY_TYPES.Neutral));

            ALA_Button.RegisterCallback<ClickEvent>(_evt => AddTagItem(_evt, ENTITY_TYPES.Allies));
            ALS_Button.RegisterCallback<ClickEvent>(_evt => SubTagItem(_evt, ENTITY_TYPES.Allies));

            Save_Button.RegisterCallback<ClickEvent>(SaveData);
            

            //Add an Element to the List
            void AddTagItem(EventBase _evt, ENTITY_TYPES _type)
            {
                EManager.Relationships[(int)_type].list.Add("Untagged");
                // if (ELayer_Field.value != LayerMask.NameToLayer("Default"))
                // {
                //     CE_Button.SetEnabled(true);
                // }

                //Update in real time the List
                tagLists[(int)_type].Rebuild();
            }

            //Sub an Element to the List
            void SubTagItem(EventBase _evt, ENTITY_TYPES _type)
            {
                if (EManager.Relationships[(int)_type].list.Count <= 0)
                {
                    return;
                }

                //if (relationships[(int)_type].Count == 1) { Save_Button.SetEnabled(false); }

                int index = EManager.Relationships[(int)_type].list.Count - 1;
                EManager.Relationships[(int)_type].list.RemoveAt(index);

                //Update in real time the List
                tagLists[(int)_type].Rebuild();
            }

            void RemoveGroupBox(EventBase _evt, Button _element)
            {
                //Get the TagBox element
                VisualElement rootTagBox = _element.parent.parent;

                //Get the TagBox's ID and Type in the Hierarchy
                int index = rootTagBox.parent.IndexOf(rootTagBox);
                ENTITY_TYPES type = DetermineType(rootTagBox);

                //Remove the bound data at the correct index
                //and rebuild to reflect changes
                EManager.Relationships[(int)type].list.RemoveAt(index);
                tagLists[(int)type].Rebuild();
            }

            GroupBox CloneGroupBox()
            {
                //Clone TagBox_UXML and find the TagBox Item
                VisualElement root = TagBox.CloneTree();
                return root.Q<GroupBox>(null, "TagBox_Root");
            }

            ListView FindContainingListView(VisualElement _element)
            {
                //Search through the parent element if one is a ListView
                VisualElement current = _element;
                while (current != null)
                {
                    if (current is ListView listView)
                    {
                        return listView;
                    }

                    current = current.parent;
                }

                return null; // Return null if the ListView is not found
            }

            ENTITY_TYPES DetermineType(VisualElement _element)
            {
                ListView list = FindContainingListView(_element);

                if (list.ClassListContains("Enemies_List"))
                {
                    return ENTITY_TYPES.Enemies;
                }

                if (list.ClassListContains("Neutral_List"))
                {
                    return ENTITY_TYPES.Neutral;
                }

                if (list.ClassListContains("Allies_List"))
                {
                    return ENTITY_TYPES.Allies;
                }

                return 0;
            }

            void SaveData(EventBase _evt)
            {
                EManager.SaveStats("Assets/Entities Data/", Entity_Tag.value);
            }

            //Link each TextField to its TagList value
            void OnTagFieldValueChanged(ChangeEvent<string> _evt, int _index, ENTITY_TYPES _type)
            {
                EManager.Relationships[(int)_type].list[_index] = _evt.newValue.ToString();
            }

            makeItem = () =>
            {
                //Value
                GroupBox groupBox = CloneGroupBox();
                
                DropdownField tagField = groupBox.Q<DropdownField>(null, "Tag_Field");
                tagField.choices = new List<string>() { "1", "2", "3" };
                tagField.value = "Untagged";

                Button button = groupBox.Q<Button>(null, "Tag_Button");
                button.RegisterCallback<ClickEvent>(_evt => RemoveGroupBox(_evt, button));

                return groupBox;
            };

            bindItem = (_element, _index) =>
            {
                //Check Whether the element is a TagField and is valid
                DropdownField toBind = _element.Q<DropdownField>(null, "Tag_Field");
                toBind.choices = new List<string>() { "1", "2", "3" };
                // toBind.value = toBind.choices[0];
                if (toBind == null)
                {
                    return;
                }

                ENTITY_TYPES type = DetermineType(_element);

                //Set Value according to list index
                toBind.SetValueWithoutNotify(EManager.Relationships[(int)type].list[_index]);
                
                // //Bind the Function that will modify the value when it is changed in UI
                toBind.RegisterCallback<ChangeEvent<string>>(_evt => OnTagFieldValueChanged(_evt, _index, type));
            };

            unbindItem = (_element, _index) =>
            {
                //Check Whether the element is a TagField and is valid
                DropdownField toUnbind = _element.Q<DropdownField>(null, "Tag_Field");
                if (toUnbind == null)
                {
                    return;
                }

                ENTITY_TYPES type = DetermineType(_element);

                //Set Basic Value
                toUnbind.SetValueWithoutNotify("Untagged");

                //Unregister the Callback to avoid any double registrations
                toUnbind.UnregisterCallback<ChangeEvent<string>>(_evt => OnTagFieldValueChanged(_evt, _index, type));
            };

            destroyItem = (_element) =>
            {
                GroupBox toRemove = _element as GroupBox;
                if (toRemove == null)
                {
                    return;
                }
            };

            void InitLists()
            {
                for (int i = 0; i < 3; i++)
                {
                    tagLists[i].makeItem = makeItem;
                    tagLists[i].bindItem = bindItem;
                    tagLists[i].unbindItem = unbindItem;
                    tagLists[i].destroyItem = destroyItem;
                    tagLists[i].selectionType = SelectionType.None;
                    tagLists[i].itemsSource = EManager.Relationships[i].list;
                    tagLists[i].style.height = 4 * itemHeight + 140;
                    tagLists[i].showBoundCollectionSize = false;
                    tagLists[i].fixedItemHeight = 40;
                    tagLists[i].Rebuild();
                }
            }

            InitLists();
            
        }
    }
}