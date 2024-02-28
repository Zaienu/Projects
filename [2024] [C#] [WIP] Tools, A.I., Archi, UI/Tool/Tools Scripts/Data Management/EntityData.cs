using System.Collections.Generic;
using Entities_Core_Scripts;
using Helper;
using UnityEngine;

namespace Editor.Tools_Scripts.Data_Management
{
    [CreateAssetMenu(fileName = "EntityData", menuName = "I.A.I.T./EntityData", order = 1)]
    public class EntityData : ScriptableObject
    {
        [SerializeField] private float[] stats = new float[4];
        [SerializeField] private Relations[] relationships = new Relations[3] {new(), new(), new()};
        [SerializeField] private List<string> behaviours = new List<string>();
        public float[] Stats
        {
            get => stats;
            set => stats = value;
        }

        public Relations[] Relationships
        {
             get => relationships;
             set => relationships = value;
        }
        
        public List<string> Behaviours
        {
            get => behaviours;
            set => behaviours = value;
        }
    }
}