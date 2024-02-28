using System;
using System.Linq;
using Editor.Tools_Scripts.Setup.Object_Setup;
using Helper;
using UnityEditor;
using UnityEngine;
using UnityEngine.UIElements;
using Button = UnityEngine.UIElements.Button;
using static Helper.UnityExtension;

namespace Editor.Tools_Scripts.Setup.Global_Setup
{
    public class Tool_GlobalSetup : EditorWindow, IDeterminable
    {
        [SerializeField] private VisualTreeAsset UXML_UI;
        [SerializeField] private VisualTreeAsset CheckBox;
        [SerializeField] private ObjectManager OManager;

        private ListView[] listViews;
        private SetupData[] dataLists;
        private Callbacks<bool>[] callbacks = {new(), new(), new(), new()};
        private CALLBACK_TYPE typeCB;
        private bool setupGSCallback = false;

        //Menu Tab Attribute
        [MenuItem("Window/I.A.I.T./Setup/Global Setup Tool")]
        public static void InitWindow()
        {
            EditorWindow window = GetWindow<Tool_GlobalSetup>();
            window.titleContent = new GUIContent("Global Setup Tool");
            window.minSize = new Vector2(435, 450);
            window.maxSize = new Vector2(435, 450);
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
            
            //UI Elements Queries
            ListView ETagCheckList = rootVisualElement.Q<ListView>("ETagCheckList", "Check_List");
            ListView ELayerCheckList = rootVisualElement.Q<ListView>("ELayerCheckList", "Check_List");

            ListView OTagCheckList = rootVisualElement.Q<ListView>("OTagCheckList", "Check_List");
            ListView OLayerCheckList = rootVisualElement.Q<ListView>("OLayerCheckList", "Check_List");

            Button Refresh_Button = rootVisualElement.Q<Button>("RefreshButton", "Button");

            void InitListViews()
            {
                listViews = new ListView[4];
                listViews[0] = ETagCheckList;
                listViews[1] = ELayerCheckList;
                listViews[2] = OTagCheckList;
                listViews[3] = OLayerCheckList;
            }

            void InitDictionaries()
            {
                OManager.Tags[(int)OBJECT_TYPE.ENTITY].LoadData("Assets/Editor/JSON/Entities/Available_Tags.txt");
                OManager.Layers[(int)OBJECT_TYPE.ENTITY].LoadData("Assets/Editor/JSON/Entities/Available_Layers.txt");
                
                OManager.Tags[(int)OBJECT_TYPE.OBSTACLE].LoadData("Assets/Editor/JSON/Obstacles/Available_Tags.txt");
                OManager.Layers[(int)OBJECT_TYPE.OBSTACLE].LoadData("Assets/Editor/JSON/Obstacles/Available_Layers.txt");
            }

            void ResizeData()
            {
                OManager.Tags[(int)OBJECT_TYPE.ENTITY].ResizeSetupData(true);
                OManager.Layers[(int)OBJECT_TYPE.ENTITY].ResizeSetupData(false);

                OManager.Tags[(int)OBJECT_TYPE.OBSTACLE].ResizeSetupData(true);
                OManager.Layers[(int)OBJECT_TYPE.OBSTACLE].ResizeSetupData(false);
            }

            void InitDataLists()
            {
                dataLists = new SetupData[4];
                dataLists[0] = OManager.Tags[(int)OBJECT_TYPE.ENTITY];
                dataLists[1] = OManager.Layers[(int)OBJECT_TYPE.ENTITY];
                dataLists[2] = OManager.Tags[(int)OBJECT_TYPE.OBSTACLE];
                dataLists[3] = OManager.Layers[(int)OBJECT_TYPE.OBSTACLE];

                for (int i = 0; i < dataLists.Length; i++)
                {
                    SaveDataList(i);
                }
            }

            void InitCallbacks()
            {
                for (int i = 0; i < dataLists.Length; i++)
                {
                    callbacks[i].SetupCallbacks(CALLBACK_TYPE.CURRENT, dataLists[i].dictionary.Count);
                }
            }

            void Initialization()
            {
                typeCB = CALLBACK_TYPE.CURRENT;
                InitListViews();
                InitDictionaries();
                ResizeData();
                InitDataLists();
                InitCallbacks();
            }

            Initialization();

            //List Delegates
            Func<VisualElement> makeItem = null;
            Action<VisualElement, int> bindItem = null;
            Action<VisualElement, int> unbindItem = null;
            Action<VisualElement> destroyItem = null;
            //Button Callbacks
            Refresh_Button.RegisterCallback<ClickEvent>(Refresh);
            
            GroupBox CloneCheckBox()
            {
                //Clone UXML Element and find the GroupBox within
                VisualElement root = CheckBox.CloneTree();
                return root.Q<GroupBox>("Root", "Root_Check_Box");
            }
            
            

            makeItem = CloneCheckBox;

            bindItem = (_element, _index) =>
            {
                //Check Whether the element is a Toogle and is valid
                Toggle toBind = _element.Q<Toggle>("ToggleBox", "Toggle_Box");
                if (toBind == null)
                {
                    return;
                }

                //Get Indexes Data
                int index = _index;
                DATA_TYPE type = (DATA_TYPE)DetermineType(toBind);
                string[] data = type == DATA_TYPE.ELAYER || type == DATA_TYPE.OLAYER ? Layers : Tags;
                toBind.text = data?[_index];

                if (setupGSCallback)
                {
                    setupGSCallback = false;
                    callbacks[(int)type].SetupCallbacks(typeCB, dataLists[(int)type].dictionary.Count);
                }

                //Set Value according to list index
                toBind.SetValueWithoutNotify(dataLists[(int)type].dictionary[data?[_index] ?? string.Empty]);

                //Bind the Function that will modify the value when it is changed in UI
                callbacks[(int)type].events[(int)typeCB][index] ??= _evt => OnCheckBoxValueChanged(_evt, index);
                toBind.RegisterValueChangedCallback(callbacks[(int)type].events[(int)typeCB][index]);
            };

            unbindItem = (_element, _index) =>
            {
                //Check Whether the element is a Toggle and is valid
                Toggle toUnbind = _element.Q<Toggle>("ToggleBox", "Toggle_Box");
                if (toUnbind == null)
                {
                    return;
                }

                //Get Indexes Data
                int type = DetermineType(_element);
                int index = _index;

                //Set Basic Value
                toUnbind.SetValueWithoutNotify(false);

                //Unregister the same Callback and put it at null
                toUnbind.UnregisterValueChangedCallback(callbacks[type].events[(int)CALLBACK_TYPE.CURRENT][index]);
                callbacks[(int)type].events[(int)CALLBACK_TYPE.CURRENT][index] = null;
            };

            destroyItem = (_element) => { Debug.Log("destroy called"); };

            void SaveDataList(int _index)
            {
                string[] paths =
                {
                    "Entities/Available_Tags.txt",
                    "Entities/Available_Layers.txt",
                    "Obstacles/Available_Tags.txt",
                    "Obstacles/Available_Layers.txt",
                };
                dataLists[_index].SaveData("Assets/Editor/JSON/" + paths[_index]);
            }

            void OnCheckBoxValueChanged(ChangeEvent<bool> _evt, int _index)
            {
                VisualElement item = _evt.target as VisualElement;
                DATA_TYPE type = (DATA_TYPE)DetermineType(item);
                string[] data = type == DATA_TYPE.ELAYER || type == DATA_TYPE.OLAYER ? Layers : Tags;
                dataLists[(int)type].dictionary[data?[_index] ?? String.Empty] = _evt.newValue;

                SaveDataList((int)type);
            }

            void InitLists()
            {
                for (int i = 0; i < listViews.Length; i++)
                {
                    listViews[i].makeItem = makeItem;
                    listViews[i].bindItem = bindItem;
                    listViews[i].unbindItem = unbindItem;
                    listViews[i].destroyItem = destroyItem;
                    listViews[i].destroyItem = default;
                    listViews[i].selectionType = SelectionType.None;
                    listViews[i].itemsSource = dataLists[i].dictionary.Values.ToList();
                    listViews[i].style.height = 5 * 25 + 6;
                    listViews[i].showBoundCollectionSize = false;
                    listViews[i].fixedItemHeight = 25;
                    listViews[i].Rebuild();
                }
            }

            InitLists();

            void Refresh(ClickEvent _evt)
            {
                ResizeData();
                InitDataLists();
                for (int i = 0; i < listViews.Length; i++)
                {
                    setupGSCallback = true;
                    typeCB = CALLBACK_TYPE.NEXT;
                    listViews[i].itemsSource = dataLists[i].dictionary.Values.ToList();
                    callbacks[i].SwapCallbacks();
                }

                typeCB = CALLBACK_TYPE.CURRENT;
            }
        }

        public int DetermineType(VisualElement _element)
        {
            string[] selector =
            {
                "ETagCheckList",
                "ELayerCheckList",
                "OTagCheckList",
                "OLayerCheckList",
            };

            ListView list = FindContainingListView(_element);

            for (int i = 0; i < selector.Length; i++)
            {
                if (list.name == selector[i])
                {
                    return i;
                }
            }

            throw new Exception("Tool_GlobalSetup ERROR : Type not Found");
        }
    }
}