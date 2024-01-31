using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

namespace WaveMakerScript
{
    public class GBResources : MonoBehaviour
    {
        public GroupBox Type;
        public Transform Content;
        public List<TMP_InputField> Data = new List<TMP_InputField>();

        public int ListID;
        public int HierarchyID;

        public List<TMP_InputField> Stats = new List<TMP_InputField>();
        public TMP_Dropdown EnemyType;
        public Image Image;
        public Sprite[] sprites;

        public Image colorSpot;
        public Color color;

        public void Start()
        {
            if(FindObjectOfType<Resources>().WTMode == Mode.WaveDisplay)
            {
                HierarchyID = transform.GetSiblingIndex();
                ListID = HierarchyID - 1;
            }
            else
            {
                HierarchyID = transform.GetSiblingIndex();
                ListID = Mathf.RoundToInt((HierarchyID - 1) / 2);
            }
        }

        public Color Color
        {
            set 
            {
                color = value;
                colorSpot.color = color;
            }
        }
    }
}
