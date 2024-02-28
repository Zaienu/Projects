using System;
using System.Collections.Generic;
using Helper;
using Obstacles_Core_Scripts;
using UnityEditor;
using UnityEngine;
using UnityEngine.UIElements;
using Button = UnityEngine.UIElements.Button;
using System.Linq;
using static Helper.UnityExtension;


namespace Editor.Tools_Scripts.Setup.Object_Setup
{
    public class Tool_ObjectSetup : EditorWindow, IDeterminable
    {
        public static readonly int ENTITY = (int)OBJECT_TYPE.ENTITY;
        public static readonly int OBSTACLE = (int)OBJECT_TYPE.OBSTACLE;

        public static readonly int CB_CURRENT = (int)CALLBACK_TYPE.CURRENT;

        [SerializeField] private VisualTreeAsset UXML_UI;
        [SerializeField] private ObjectManager OManager;

        private ListView[] listViews;
        private DropdownField[] layerFields;
        private Button[] configButtons;
        private Callbacks<string>[] callbacks;

        private List<string>[] AvailableData;
        private int[] DataAmount;
        private string basePath = "Assets/Editor/JSON/";

        private string[][] paths =
        {
            new[]
            {
                "Entities/Available_Tags.txt",
                "Entities/Available_Layers.txt",
                "Obstacles/Available_Tags.txt",
                "Obstacles/Available_Layers.txt",
            },
            new[]
            {
                "Entities/Selected_Tags.txt",
                "Entities/Selected_Layer.txt",
                "Obstacles/Selected_Tags.txt",
                "Obstacles/Selected_Layer.txt",
            }
        };

        private List<string>[] SelectedTags;
        private string[] SelectedLayer;

        private bool canRemoveCB = false;

        //Menu Tab Attribute
        [MenuItem("Window/I.A.I.T./Setup/Object Setup Tool")]
        public static void InitWindow()
        {
            EditorWindow window = GetWindow<Tool_ObjectSetup>();
            window.titleContent = new GUIContent("Object Setup Tool");
            window.minSize = new Vector2(435, 320);
            window.maxSize = new Vector2(435, 320);
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

            //Configuration Buttons
            Button CE_Button = rootVisualElement.Q<Button>("SetupEntities", "Config_Button");
            Button CO_Button = rootVisualElement.Q<Button>("SetupObstacles", "Config_Button");

            //Entities Tag List
            ListView ET_List = rootVisualElement.Q<ListView>("ETList", "Tag_List");
            Button ETL_AddButton = rootVisualElement.Q<Button>("AddEntityButton", "List_AddButton");
            Button ETL_SubButton = rootVisualElement.Q<Button>("RemoveEntityButton", "List_RemoveButton");

            //Obstacles Tag List
            ListView OT_List = rootVisualElement.Q<ListView>("OTList", "Tag_List");
            Button OTL_AddButton = rootVisualElement.Q<Button>("AddObstacleButton", "List_AddButton");
            Button OTL_SubButton = rootVisualElement.Q<Button>("RemoveObstacleButton", "List_RemoveButton");

            //Layer Fields
            DropdownField ELayer_Field = rootVisualElement.Q<DropdownField>("ELayer_Field", "Layer_Selector");
            DropdownField OLayer_Field = rootVisualElement.Q<DropdownField>("OLayer_Field", "Layer_Selector");

            void InitListViews()
            {
                listViews = new ListView[2];
                listViews[ENTITY] = ET_List;
                listViews[OBSTACLE] = OT_List;
            }

            void InitLayerFields()
            {
                layerFields = new DropdownField[2];
                layerFields[ENTITY] = ELayer_Field;
                layerFields[OBSTACLE] = OLayer_Field;
            }

            void InitConfigButtons()
            {
                configButtons = new Button[2];
                configButtons[ENTITY] = CE_Button;
                configButtons[OBSTACLE] = CO_Button;
                configButtons[ENTITY].RegisterCallback<ClickEvent>(Configure_Entities);
                configButtons[OBSTACLE].RegisterCallback<ClickEvent>(Configure_Obstacles);
            }

            void InitAvailableData()
            {
                AvailableData = new List<string>[4];

                for (int i = 0; i < AvailableData.Length; i++)
                {
                    SetupData data = JSON_Helper.LoadFromJSON<SetupData>(basePath + paths[0][i]);
                    AvailableData[i] = data.dictionary.Where(x => x.Value).Select(x => x.Key).ToList();
                    AvailableData[i].Add("Unknown");
                }

                DataAmount = new[] { AvailableData[0].Count - 1, AvailableData[2].Count - 1 };
            }

            void InitData()
            {
                //Inits
                SelectedTags = new List<string>[listViews.Length];
                SelectedLayer = new string[listViews.Length];

                for (int i = 0; i < SelectedLayer.Length; i++)
                {
                    //Tags
                    SelectedTags[i] = JSON_Helper.LoadFromJSON<List<string>>(basePath + paths[1][i]);

                    //Layers
                    int? layerID = JSON_Helper.LoadFromJSON<int?>(basePath + paths[1][i + 2]);
                    SelectedLayer[i] = layerID.HasValue ? LayerMask.LayerToName(layerID.Value) : "Unknown";
                }
            }

            void InitCallbacks()
            {
                callbacks = new Callbacks<string>[] { new(), new() };
                for (int i = 0; i < SelectedTags.Length; i++)
                {
                    callbacks[i].SetupCallbacks(CALLBACK_TYPE.CURRENT, SelectedTags[i].Count);
                }
            }

            void CheckConfigButtonsActivation()
            {
                for (int i = 0; i < configButtons.Length; i++)
                {
                    bool isActive = SelectedLayer[i] != "Unknown" &&
                                    SelectedTags[i].Count > 0 &&
                                    SelectedTags[i].All(x => x != "Unknown");
                    configButtons[i].SetEnabled(isActive);
                }
            }

            void Initialization()
            {
                InitListViews();
                InitLayerFields();
                InitConfigButtons();
                InitAvailableData();
                InitData();
                InitCallbacks();
                CheckConfigButtonsActivation();
            }

            Initialization();

            void Configure_Entities(EventBase _evt)
            {
                OManager.Configure_Entities();
            }

            void Configure_Obstacles(EventBase _evt)
            {
                ObstacleManager.Obstacle_List.Clear();
                OManager.Configure_Obstacles();
            }

            //List Delegates
            Func<VisualElement> makeItem = null;
            Action<VisualElement, int> bindItem = null;
            Action<VisualElement, int> unbindItem = null;

            //Assign Functions to buttons
            ETL_AddButton.RegisterCallback<ClickEvent>(_evt => AddTagItem(_evt, OBJECT_TYPE.ENTITY));
            ETL_SubButton.RegisterCallback<ClickEvent>(_evt => SubTagItem(_evt, OBJECT_TYPE.ENTITY));

            OTL_AddButton.RegisterCallback<ClickEvent>(_evt => AddTagItem(_evt, OBJECT_TYPE.OBSTACLE));
            OTL_SubButton.RegisterCallback<ClickEvent>(_evt => SubTagItem(_evt, OBJECT_TYPE.OBSTACLE));

            //Item Size
            StyleLength itemWidth = ET_List.parent.style.width;
            StyleLength itemHeight = ET_List.style.height.value.Divide(5);

            makeItem = () =>
            {
                DropdownField item = new DropdownField();

                //Style
                item.style.width = itemWidth;
                item.style.height = itemHeight;

                //Value
                item.value = "Unknown";

                return item;
            };

            bindItem = (_element, _index) =>
            {
                //Check Whether the element is a TagField and is valid
                DropdownField toBind = _element as DropdownField;
                if (toBind == null)
                {
                    return;
                }

                int type = DetermineType(_element);
                int index = _index;

                //Set Value according to list index
                toBind.choices = AvailableData[type * 2];
                toBind.SetValueWithoutNotify(SelectedTags[type][index]);

                //Bind the Function that will modify the value when it is changed in UI
                callbacks[type].events[CB_CURRENT][index] ??=
                    _evt => OnDropDownValueChanged(_evt, index, (OBJECT_TYPE)type);
                toBind.RegisterValueChangedCallback(callbacks[type].events[CB_CURRENT][index]);
            };

            unbindItem = (_element, _index) =>
            {
                //Check Whether the element is a TagField and is valid
                DropdownField toUnbind = _element as DropdownField;
                if (toUnbind == null)
                {
                    return;
                }

                int type = DetermineType(_element);
                int index = _index;

                //Set Basic Value
                toUnbind.SetValueWithoutNotify("Unknown");

                //Unregister the same Callback and put it at null
                toUnbind.UnregisterValueChangedCallback(callbacks[type].events[CB_CURRENT][index]);
                callbacks[type].events[CB_CURRENT][index] = null;

                if (canRemoveCB && index == SelectedTags[type].Count)
                {
                    //Resize while removing the last element that just has been unsubscribbed
                    Callbacks<string> tempArray = new Callbacks<string>();
                    tempArray.SetupCallbacks(CALLBACK_TYPE.CURRENT, SelectedTags[type].Count);
                    callbacks[type].events[CB_CURRENT] = tempArray.events[CB_CURRENT];
                    canRemoveCB = false;
                }
            };

            //Link each TextField to its TagList value
            void OnDropDownValueChanged(ChangeEvent<string> _evt, int _index, OBJECT_TYPE _type)
            {
                //Put back the former Tag in Available Data
                string value = SelectedTags[(int)_type][_index];
                if (AvailableData[(int)_type * 2].All(x => x != value))
                {
                    AvailableData[(int)_type * 2].Add(value);
                }

                //Remove the new tag from Available Data
                SelectedTags[(int)_type][_index] = _evt.newValue;
                AvailableData[(int)_type * 2].Remove(_evt.newValue);

                //Save data
                CheckConfigButtonsActivation();
                JSON_Helper.SaveToJSON(SelectedTags[(int)_type], basePath + paths[1][(int)_type * 2]);
            }


            //Add an Element to the List
            void AddTagItem(EventBase _evt, OBJECT_TYPE _type)
            {
                if (SelectedTags[(int)_type].Count == DataAmount[(int)_type])
                {
                    return;
                }

                SelectedTags[(int)_type].Add("Unknown");

                //Copy the callbacks to the bigger array
                Callbacks<string> tempArray = new Callbacks<string>();
                tempArray.SetupCallbacks(CALLBACK_TYPE.CURRENT, SelectedTags[(int)_type].Count);

                Array.Copy(callbacks[(int)_type].events[CB_CURRENT],
                    tempArray.events[CB_CURRENT],
                    callbacks[(int)_type].events[CB_CURRENT].Length);

                callbacks[(int)_type].events[CB_CURRENT] = tempArray.events[CB_CURRENT];

                //Update in real time the List
                listViews[(int)_type].itemsSource = SelectedTags[(int)_type];
                listViews[(int)_type].Rebuild();
            }

            //Sub an Element to the List
            void SubTagItem(EventBase _evt, OBJECT_TYPE _type)
            {
                int length = SelectedTags[(int)_type].Count;
                if (length <= 0)
                {
                    return;
                }

                canRemoveCB = true;
                AvailableData[(int)_type * 2].Add(SelectedTags[(int)_type][length - 1]);
                SelectedTags[(int)_type].RemoveAt(length - 1);

                //Update in real time the List
                listViews[(int)_type].itemsSource = SelectedTags[(int)_type];
                listViews[(int)_type].Rebuild();
            }

            void InitLists()
            {
                for (int i = 0; i < listViews.Length; i++)
                {
                    listViews[i].makeItem = makeItem;
                    listViews[i].bindItem = bindItem;
                    listViews[i].unbindItem = unbindItem;
                    listViews[i].destroyItem = default;
                    listViews[i].selectionType = SelectionType.None;
                    listViews[i].itemsSource = SelectedTags[i];
                    listViews[i].style.height = 4 * 25 + 6;
                    listViews[i].showBoundCollectionSize = false;
                    listViews[i].fixedItemHeight = 25;
                    listViews[i].Rebuild();
                }
            }

            InitLists();

            void InitLayers()
            {
                for (int i = 0; i < layerFields.Length; i++)
                {
                    SelectedLayer[i] ??= "Unknown";
                    int index = i;

                    layerFields[i].value = SelectedLayer[i];
                    layerFields[i].choices = AvailableData[i * 2 + 1];
                    layerFields[i].RegisterCallback<ChangeEvent<string>>(_evt => OnLayerValueChanged(_evt, index));
                }
            }

            InitLayers();

            void OnLayerValueChanged(ChangeEvent<string> _evt, int _type)
            {
                //Put back the former Layer in Available Data
                string value = SelectedLayer[_type];
                if (AvailableData[_type * 2 + 1].All(x => x != value))
                {
                    AvailableData[_type * 2 + 1].Add(value);
                }

                //Remove the new layer from Available Data
                SelectedLayer[_type] = _evt.newValue;
                AvailableData[_type * 2 + 1].Remove(_evt.newValue);

                //Save data
                CheckConfigButtonsActivation();
                JSON_Helper.SaveToJSON(SelectedLayer[_type], basePath + paths[1][_type * 2 + 1]);
            }
        }

        public int DetermineType(VisualElement _element)
        {
            string[] selector =
            {
                "ETList",
                "OTList",
            };

            ListView list = FindContainingListView(_element);

            for (int i = 0; i < selector.Length; i++)
            {
                if (list.name == selector[i])
                {
                    return i;
                }
            }

            throw new Exception("Tool_ObjectSetup ERROR : Type not Found");
        }
    }
}