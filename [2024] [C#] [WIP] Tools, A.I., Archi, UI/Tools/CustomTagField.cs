using System.Collections.Generic;
using UnityEditor.UIElements;
using UnityEditorInternal;
using UnityEngine.UIElements;
using System.Reflection;
using Editor.Tool_Scripts;
using UnityEditor;

namespace UnityEditor.UIElements
{
    
    public class CustomTagField : PopupField<string>
    {
        private static List<string> tagList;
        MethodInfo getValueToDisplay;
        
        public new static readonly string ussClassName = "unity-tag-field";
        public new static readonly string labelUssClassName = CustomTagField.ussClassName + "__label";
        public new static readonly string inputUssClassName = CustomTagField.ussClassName + "__input";
        
        private static List<string> InitializeTags() => new List<string>(tagList);
        
        public CustomTagField() : this((string) null) { }

        public CustomTagField(string label, string defaultValue = null) : base(label)
        {
            this.AddToClassList(CustomTagField.ussClassName);
            this.labelElement.AddToClassList(CustomTagField.labelUssClassName);
            
            FieldInfo vInput = typeof(PopupField<string>).GetField("m_VisualInput", BindingFlags.NonPublic | BindingFlags.Instance);
            
            if (vInput != null)
            {
                // Get the value of the 'm_VisualInput' field
                VisualElement visualInputElement = vInput.GetValue(this) as VisualElement;

                // If the field is successfully retrieved and cast, perform operations
                if (visualInputElement != null)
                {
                    visualInputElement.AddToClassList(CustomTagField.inputUssClassName);
                }
            } 
            this.choices = CustomTagField.InitializeTags();
            if (defaultValue == null)
                return;
            this.SetValueWithoutNotify(defaultValue);
            
            getValueToDisplay = typeof(PopupField<string>).GetMethod("GetValueToDisplay", BindingFlags.NonPublic | BindingFlags.Instance);
            // getValueToDisplay.Invoke() => this.rawValue;
        }
        
        // internal override string GetValueToDisplay() => this.rawValue;

        public List<string> TagList
        {
            get => tagList;
            set => tagList = value;
        }
        
        public new class UxmlFactory : UxmlFactory<CustomTagField, UxmlTraits>
        {        
        }

        /// <summary>
        ///        <para>
        /// Defines UxmlTraits for the TagField.
        /// </para>
        ///      </summary>
        public new class UxmlTraits : BaseField<string>.UxmlTraits
        {
            private UxmlStringAttributeDescription m_Value;

            public override void Init(VisualElement ve, IUxmlAttributes bag, CreationContext cc)
            {
                base.Init(ve, bag, cc);
                ((BaseField<string>) ve).SetValueWithoutNotify(this.m_Value.GetValueFromBag(bag, cc));
            }
            
            public UxmlTraits()
            {
                UxmlStringAttributeDescription attributeDescription = new UxmlStringAttributeDescription
                {
                    name = "value"
                };
                this.m_Value = attributeDescription;
            }
        }
        
    }
}
