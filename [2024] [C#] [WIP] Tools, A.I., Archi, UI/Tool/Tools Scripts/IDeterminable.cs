using System;
using UnityEngine.UIElements;

namespace Editor.Tools_Scripts
{
    public interface IDeterminable
    {
        public int DetermineType(VisualElement _element);
    }
}
