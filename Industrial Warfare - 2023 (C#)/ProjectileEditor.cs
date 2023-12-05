using UnityEngine;
using UnityEditor;
using UnityEditor.UIElements;
using UnityEngine.UIElements;

[CustomEditor(typeof(Projectile))]
public class ProjectileEditor : Editor
{
    [SerializeField] VisualTreeAsset UXML_UI;

    public override VisualElement CreateInspectorGUI()
    {
        if (Application.isPlaying)
        { return null; }
        VisualElement ProjInspector = new VisualElement();


        UXML_UI.CloneTree(ProjInspector);

        VisualElement InspectorFoldout = ProjInspector.Q("Default_Inspector");

        InspectorElement.FillDefaultInspector(InspectorFoldout, serializedObject, this);

        return ProjInspector;
    }
}
