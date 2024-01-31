using System;
using System.Collections.Generic;
using Entities_Core_Scripts;
using Unity.VisualScripting.YamlDotNet.Core.Tokens;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine;
using UnityEngine.UIElements;
using Button = UnityEngine.UIElements.Button;
using Utility;

namespace Editor.Tool_Scripts.Entity_Stats_Configurer
{
    public class Editor_EntityBehaviourConfirgurer : EditorWindow
    {
        
        [SerializeField] private VisualTreeAsset UXML_UI;
        [SerializeField] private VisualTreeAsset TagBox;
        [SerializeField] private EntityManager EManager;

        private readonly ListView[] tagLists = new ListView[3];
        private readonly Slider[] statSliders = new Slider[4];

        //Menu Tab Attribute
        [MenuItem("Window/I.A.I.T./Entity Behaviour Configurer")]
        public static void InitWindow()
        {
            EditorWindow window = GetWindow<Editor_EntityBehaviourConfirgurer>();
            window.titleContent = new GUIContent("Entity_Configurer");
            window.minSize = new Vector2(495, 405);
            window.maxSize = new Vector2(495, 405);
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
        }
    }
}