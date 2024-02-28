using System.Collections.Generic;
using Editor.Tools_Scripts.Data_Management;
using Helper;
using UnityEditor;
using UnityEngine;
using UnityEngine.UIElements;
using Button = UnityEngine.UIElements.Button;

namespace Editor.Tools_Scripts.Entity_Configurer.Stats_Tool
{
    public class Tool_Stats : EditorWindow
    {
        [SerializeField] private VisualTreeAsset UXML_UI;
        [SerializeField] private EntityManager EManager;

        private Sprite[] sprites = new Sprite[4];
        private readonly Slider[] statSliders = new Slider[4];
        private readonly Image[] statImages = new Image[4];

        //Menu Tab Attribute
        [MenuItem("Window/I.A.I.T./Entity Configurer/Stats Tool")]
        public static void InitWindow()
        {
            EditorWindow window = GetWindow<Tool_Stats>();
            window.titleContent = new GUIContent("Stats Tool");
            window.minSize = new Vector2(465, 270);
            window.maxSize = new Vector2(465, 270);
        }

        public void CreateGUI()
        {
            ///-----EDITOR WINDOW SETUP-----///

            if (!Application.isEditor)
            {
                return;
            }

            ///-----UXML DOCUMENT SETUP-----///

            UXML_UI.CloneTree();

            TemplateContainer container = UXML_UI.Instantiate();
            rootVisualElement.Add(container);


            ///-----VISUAL ELEMENTS QUERIES-----///

            DropdownField Entity_Tag = rootVisualElement.Q<DropdownField>("EntityTagSelector", "Entity_Tag_Selector");

            Slider Health_Slider = rootVisualElement.Q<Slider>("HealthSlider", "Health_Slider");
            Slider Attack_Slider = rootVisualElement.Q<Slider>("AttackSlider", "Attack_Slider");
            Slider ASPD_Slider = rootVisualElement.Q<Slider>("ASPDSlider", "ASPD_Slider");
            Slider Speed_Slider = rootVisualElement.Q<Slider>("SpeedSlider", "Speed_Slider");

            Image Health_Image = rootVisualElement.Q<Image>("HealthImage", "Health_Image");
            Image Attack_Image = rootVisualElement.Q<Image>("AttackImage", "Attack_Image");
            Image ASPD_Image = rootVisualElement.Q<Image>("ASPDImage", "ASPD_Image");
            Image Speed_Image = rootVisualElement.Q<Image>("SpeedImage", "Speed_Image");

            Image Entity_Image = rootVisualElement.Q<Image>("EntityImage", "Entity_Image");

            Button Save_Button = rootVisualElement.Q<Button>("SaveButton", "Save_Button");

            ///-----EASY ACCESS LISTS-----///

            statSliders[0] = Health_Slider;
            statSliders[1] = Attack_Slider;
            statSliders[2] = ASPD_Slider;
            statSliders[3] = Speed_Slider;

            statImages[0] = Health_Image;
            statImages[1] = Attack_Image;
            statImages[2] = ASPD_Image;
            statImages[3] = Speed_Image;

            sprites[0] = AssetDatabase.LoadAssetAtPath<Sprite>("Assets/Editor/Tools Assets/Images/Health.png");
            sprites[1] = AssetDatabase.LoadAssetAtPath<Sprite>("Assets/Editor/Tools Assets/Images/Attack.png");
            sprites[2] = AssetDatabase.LoadAssetAtPath<Sprite>("Assets/Editor/Tools Assets/Images/ASPD.png");
            sprites[3] = AssetDatabase.LoadAssetAtPath<Sprite>("Assets/Editor/Tools Assets/Images/Speed.png");
            ///-----BUTTON FUNCTIONS-----///


            #region Init Functions

            void InitSliders(Slider[] _sliders, float[] _lows, float[] _highs)
            {
                for (int i = 0; i < _sliders.Length; i++)
                {
                    int localIndex = i;
                    _sliders[i].lowValue = _lows[i];
                    _sliders[i].highValue = _highs[i];
                    _sliders[i].showInputField = true;
                    _sliders[i].RegisterCallback<ChangeEvent<float>>(_evt => OnStatChange(_evt, localIndex));
                }
            }

            void InitImages(Image[] _images, Sprite[] _sprites)
            {
                for (int i = 0; i < _images.Length; i++)
                {
                    
                    _images[i].sprite = _sprites[i];
                }
            }

            void InitDropDownField()
            {
                // List<string> hey = new List<string>() { "Player", "2", "3" };
                // Entity_Tag.choices = hey;
                // Entity_Tag.value = hey[0];
                Entity_Tag.value = "Goblin";
            }

            #endregion

            #region Update Functions

            void UpdateSliders(Slider[] _sliders, float[] _stats)
            {
                for (int i = 0; i < _sliders.Length; i++)
                {
                    _sliders[i].SetValueWithoutNotify(_stats[i]);
                }
            }

            #endregion

            #region Event Functions

            void OnStatChange(ChangeEvent<float> _evt, int _index)
            {
                EManager.Stats[_index] = _evt.newValue;
            }

            void ChangeTag(EventBase _evt)
            {
                ResetData();
                CheckExistingData();
            }

            void SaveData(EventBase _evt)
            {
                EManager.SaveStats("Assets/Entities Data/", Entity_Tag.value);
            }

            #endregion

            #region Data Management

            void SetData()
            {
                UpdateSliders(statSliders, EManager.Stats);
            }

            void ResetData()
            {
                EManager.Relationships.Clear();
                EManager.Stats.Clear();
                UpdateSliders(statSliders, EManager.Stats);
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

            #endregion


            void Initialization()
            {
                float[] highs = { 1000, 100, 10, 10 };
                float[] lows = { 0, 0, 0, 0 };

                InitSliders(statSliders, lows, highs);
                InitImages(statImages, sprites);
                InitDropDownField();

                CheckExistingData();
            }

            Initialization();

            ///-----ASSIGN EVENTS TO FUNCTIONS-----///

            Entity_Tag.RegisterCallback<ChangeEvent<string>>(ChangeTag);
            Save_Button.RegisterCallback<ClickEvent>(SaveData);
        }
    }
}