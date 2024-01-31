using System;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

namespace WaveMakerScript
{

    public class GroupBoxManager : MonoBehaviour
    {
        Resources Resources;
        WaveMaker WaveMaker;

        private void Awake()
        {
            Resources = GetComponent<Resources>();
            WaveMaker = GetComponent<WaveMaker>();
        }

        private void Disable_Objects(List<GameObject> _list)
        {
            _list.ForEach(x => x.SetActive(false));
        }

        #region Remove_GroupBox
        private void Remove_Wave(GameObject self)
        {
            GroupBoxLayout layout = self.GBLayout();
            int waveID = layout.GBResources.ListID;
            Resources.FileContent.Waves.RemoveAt(waveID);
        }

        private void Remove_Split(GameObject self)
        {
            GroupBoxLayout layout = self.GBLayout();
            GroupBoxLayout wave = layout.Parents[0].GBLayout();
            int waveID = wave.GBResources.ListID;
            int splitID = layout.GBResources.ListID;
            Resources.FileContent.Waves[waveID].Splits.RemoveAt(splitID);
        }

        private void Remove_Enemy(GameObject self)
        {
            GroupBoxLayout layout = self.GBLayout();
            GroupBoxLayout wave = layout.Parents[0].GBLayout().Parents[0].GBLayout();
            GroupBoxLayout split = layout.Parents[0].GBLayout();
            int waveID = wave.GBResources.ListID;
            int splitID = split.GBResources.ListID;
            int enemyID = layout.GBResources.ListID;
            Resources.FileContent.Waves[waveID].Splits[splitID].Enemies.RemoveAt(enemyID);
        }

        #endregion

        private List<TMP_InputField> FillAmountList(GameObject self)
        {
            List<TMP_InputField> list = new List<TMP_InputField>();
            GBResources res = self.GBLayout().Parents[0].GBRes();
            if (res.Type == GroupBox.Root)
            {
                list.AddRange(res.Data);
            }
            else
            {
                list.Add(res.Data[(int)Data.Amount]);
            }
            return list;
        }

        public void Remove(GameObject self)
        {
            GroupBoxLayout layout = self.GBLayout();
            GBResources gbRes = self.GBRes();
            int HID = self.transform.GetSiblingIndex();

            Transform content = layout.Parents[0].GBRes().Content;
            List<TMP_InputField> amounts = FillAmountList(self);

            GameObject dropZone = content.GetChild(HID + 1).gameObject;

            float value = Mathf.RoundToInt((content.childCount - 3) / 2);
            amounts.ForEach(x => WaveMaker.Fill_Value(x, value));

            Disable_Objects(new List<GameObject>() { self, dropZone });
            layout.Rebuild_ParentsLayout();

            string exception = null;

            switch (gbRes.Type)
            {
                case GroupBox.Wave:
                    Remove_Wave(self);
                    exception = "Wave_DropArea";
                    break;
                case GroupBox.Split:
                    Remove_Split(self);
                    exception = "Split_DropArea";
                    break;
                case GroupBox.Enemy:
                    Remove_Enemy(self);
                    exception = "Enemy_DropArea";
                    break;
            }

            DestroyImmediate(self);
            DestroyImmediate(dropZone);
            content.gameObject.GetChilds(exception).ForEach(x => x.GBLayout().UpdateIDs());

        }

        #region Create_GroupBox

        private void Create_Wave(GameObject groupBox, int id)
        {
            int ID = Mathf.RoundToInt((id - 1) / 2);
            WaveGB waveGB = new WaveGB();

            WaveMaker.Fill_GroupBox(groupBox, waveGB);
            Resources.FileContent.Waves.Insert(ID, waveGB);

            waveGB.Layout.Parents.Add(Resources.WDRoot);

            WaveMaker.Set_Color(groupBox, true);

            float[] values = { ID, 0, 0 };
            WaveMaker.Fill_Values(waveGB, values);

        }

        private void Create_Split(GameObject groupBox, GameObject parent, int id)
        {
            int waveID = parent.GBRes().ListID;
            int ID = Mathf.RoundToInt((id - 1) / 2);
            SplitGB splitGB = new SplitGB();

            WaveMaker.Fill_GroupBox(groupBox, splitGB);
            Resources.FileContent.Waves[waveID].Splits.Insert(ID, splitGB);

            splitGB.Layout.Parents.Add(Resources.FileContent.Waves[waveID].GroupBox);
            splitGB.Layout.Parents.AddRange(Resources.FileContent.Waves[waveID].Layout.Parents);

            WaveMaker.Set_Color(groupBox, true);

            float[] values = { ID, 0, 0 };
            WaveMaker.Fill_Values(splitGB, values);

        }

        private void Create_Enemy(GameObject groupBox, GameObject parent, int id)
        {
            Debug.Log("hey3");
            int waveID = parent.GBLayout().Parents[0].GBRes().ListID;
            int splitID = parent.GBRes().ListID;
            int ID = Mathf.RoundToInt((id - 1) / 2);
            EnemyGB enemyGB = new EnemyGB();

            WaveMaker.Fill_GroupBox(groupBox, enemyGB);
            Resources.FileContent.Waves[waveID].Splits[splitID].Enemies.Insert(ID, enemyGB);

            enemyGB.Layout.Parents.Add(Resources.FileContent.Waves[waveID].Splits[splitID].GroupBox);
            enemyGB.Layout.Parents.AddRange(Resources.FileContent.Waves[waveID].Splits[splitID].Layout.Parents);

            WaveMaker.Set_Color(groupBox, true);

            float[] values = { ID, 0 };
            WaveMaker.Fill_Values(enemyGB, values);
            WaveMaker.Change_UnitPicture(groupBox);
        }

        #endregion

        public void Add(Transform parent, int id)
        {
            GroupBoxLayout parentlayout = parent.CRes().Parent.GBLayout();
            GBResources parentRes = parent.CRes().Parent.GBRes();

            GameObject groupBox = WaveMaker.Instantiate_UIObject(parentRes.Type + 1, parent, id, Mode.WaveMaker);
            GameObject dropZone = WaveMaker.Instantiate_UIObject(parentRes.Type + 4, parent, id + 1, Mode.WaveMaker);

            string exception = null;
            Debug.Log("hey");
            switch (parentRes.Type + 1)
            {
                case GroupBox.Wave:
                    exception = "Wave_DropArea";
                    Create_Wave(groupBox, id);
                    break;
                case GroupBox.Split:
                    exception = "Split_DropArea";
                    Create_Split(groupBox, parent.CRes().Parent, id);
                    break;
                case GroupBox.Enemy:
                    exception = "Enemy_DropArea";
                    Debug.Log("hey2");
                    Create_Enemy(groupBox, parent.CRes().Parent, id);
                    break;
            }

            List<TMP_InputField> amounts = FillAmountList(groupBox);
            float value = Mathf.RoundToInt((parentRes.Content.childCount - 1) / 2);
            amounts.ForEach(x => WaveMaker.Fill_Value(x, value));

            groupBox.GBLayout().Rebuild_ParentsLayout();
            parentRes.Content.gameObject.GetChilds(exception).ForEach(x => x.GBLayout().UpdateIDs());
        }
    }
}
