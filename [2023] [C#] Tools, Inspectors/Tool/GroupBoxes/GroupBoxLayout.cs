using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using TMPro;

namespace WaveMakerScript
{
    public class GroupBoxLayout : MonoBehaviour
    {
        public List<RectTransform> Layouts = new List<RectTransform>();
        public RectTransform DDButton;
        Resources Resources;
        public GBResources GBResources;
        public List<GameObject> Parents;
        bool isActive = true;
        bool hasLoaded = false;

        private void Awake()
        {
            GBResources = GetComponent<GBResources>();
            Resources = FindObjectOfType<Resources>();
        }

        public void UpdateIDs()
        {
            GBResources.HierarchyID = transform.GetSiblingIndex();
            GBResources.ListID = Mathf.RoundToInt((GBResources.HierarchyID - 1) / 2);
            int id = GBResources.ListID + 1;
            GBResources.Data[(int)Data.Number].text = id > 9 ? id.ToString() : "0" + id.ToString();
        }


        public void Rebuild_SelfLayouts()
        {
            for (int i = 0; i < Layouts.Count; i++)
            {
                LayoutRebuilder.ForceRebuildLayoutImmediate(Layouts[i]);
            }
        }

        public void Rebuild_ParentsLayout()
        {
            for (int i = 0; i < Parents.Count; i++)
            {
                Parents[i].GetComponent<GroupBoxLayout>().UpdateLayout();
            }
        }

        //Updates the Layout : GroupBox and Content
        public void UpdateLayout()
        {
            //Needed because of the IEnumerator for the Waves Initialization
            if (!hasLoaded)
            {
                hasLoaded = true;
                bool hasChild;
                hasChild = Layouts[0].childCount > 0;
                Layouts[0].gameObject.SetActive(hasChild);
            }

            //Resizes the GroupBoxes depending on their content.
            Rebuild_SelfLayouts();
        }

        //Changes the appearance of the dropdown button
        private void Change_DDButton(bool _isActive)
        {
            DDButton.localEulerAngles = _isActive ? new Vector3(0, 0, 0) : new Vector3(0, 0, 90);
        }

        //Allows the Collapse and Expand of the GroupBoxes.
        public void Collapse()
        {
            //Resources.FileContent.LoadingPanel.SetActive(true);
            isActive = !isActive;

            if (Layouts[0].childCount > 0)
            {
                //if it has children then activate the content
                //Check if it is possible to do it manually in a coroutine
                Layouts[0].gameObject.SetActive(isActive);
            }


            //Updates the rest of the layouts
            Change_DDButton(isActive);
            Rebuild_SelfLayouts();

            for (int i = 0; i < Parents.Count; i++)
            {
                Parents[i].GetComponent<GroupBoxLayout>().UpdateLayout();
            }
            //Resources.FileContent.LoadingPanel.SetActive(false);
        }
    }
}