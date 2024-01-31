using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System.Linq;
using System.Collections;

namespace WaveMakerScript
{

    public class DisplayWave : MonoBehaviour
    {
        Resources Resources;
        WaveMaker WaveMaker;

        void Awake()
        {
            Resources = GetComponent<Resources>();
            WaveMaker = GetComponent<WaveMaker>();
        }

        /// <summary>
        /// Destroys the Root prefab and its c
        /// Clears the Ignore list of the WD's gameobjects
        /// Puts to null the list of data
        /// </summary>
        public void Empty_WaveDisplayer()
        {
            DestroyImmediate(Resources.WDRoot);
            Resources.FileContent = null;
        }

        /// <summary>
        /// This is the main function that instantiate both the
        /// prefabs in the UI and the object in the FileContent List
        /// </summary>
        /// 

        public IEnumerator Fill_WaveDisplayer(Mode mode)
        {
            Empty_WaveDisplayer();

            #region Initializing Variables
            int waveNb, splitNb, enemyNb;
            GameObject wave, split, enemy;
            if (Resources.WDDatabase == null) { Resources.WDDatabase = new WaveDatabase(); }
            WaveDatabase database = Resources.WDDatabase;
            #endregion

            #region Root
            Resources.WDRoot = WaveMaker.Instantiate_UIObject(GroupBox.Root, Resources.Canvas.transform, -1, mode);
            #endregion

            #region Filling Data
            WaveMaker.Fill_FileContent();

            TMP_InputField fileName = Resources.WDRoot.Contains("File Name Input").GetComponent<TMP_InputField>();
            if (fileName.text == "")
            { fileName.text = Resources.SelectedFile; }

            waveNb = database.Waves.Count;
            WaveMaker.Fill_Amounts(waveNb);
            #endregion

            for (int waveID = 0; waveID < waveNb; waveID++)
            {

                #region Creates WaveGroupBox
                WaveGB waveGB = new WaveGB();
                Transform waveContent = Resources.FileContent.Content;

                wave = WaveMaker.Instantiate_UIObject(GroupBox.Wave, waveContent, -1, mode);
                if (mode == Mode.WaveMaker)
                {
                    WaveMaker.Instantiate_UIObject(GroupBox.WaveDZ, waveContent, -1, mode);
                }
                #endregion

                #region Fill_Data
                WaveMaker.Fill_GroupBox(wave, waveGB);
                Resources.FileContent.Waves.Add(waveGB);

                splitNb = database.Waves[waveID].Splits.Count;
                //AddParents
                waveGB.Layout.Parents.Add(Resources.WDRoot);
                //FillValues
                WaveMaker.Set_Color(wave,false);
                float[] waveValues = { waveID + 1, database.Waves[waveID].Timer, splitNb };
                WaveMaker.Fill_Values(waveGB, waveValues);
                #endregion

                for (int splitID = 0; splitID < splitNb; splitID++)
                {

                    #region Creates SplitGroupBox
                    SplitGB splitGB = new SplitGB();
                    Transform splitContent = Resources.FileContent.Waves[waveID].Content;

                    split = WaveMaker.Instantiate_UIObject(GroupBox.Split, splitContent, -1, mode);
                    if (mode == Mode.WaveMaker)
                    {
                        WaveMaker.Instantiate_UIObject(GroupBox.SplitDZ, splitContent, -1, mode);
                    }
                    #endregion

                    #region Fill_Data
                    WaveMaker.Fill_GroupBox(split, splitGB);
                    Resources.FileContent.Waves[waveID].Splits.Add(splitGB);

                    enemyNb = database.Waves[waveID].Splits[splitID].Enemies.Count;
                    //AddParents
                    splitGB.Layout.Parents.Add(waveGB.GroupBox);
                    splitGB.Layout.Parents.AddRange(waveGB.Layout.Parents);
                    //FillValues
                    WaveMaker.Set_Color(split, false);
                    float[] splitValues = { splitID + 1, database.Waves[waveID].Splits[splitID].Timer, enemyNb };
                    WaveMaker.Fill_Values(splitGB, splitValues);
                    #endregion

                    yield return null;

                    for (int enemyID = 0; enemyID < enemyNb; enemyID++)
                    {

                        #region Creates EnemyGroupBox
                        EnemyGB enemyGB = new EnemyGB();
                        Transform enemyContent = Resources.FileContent.Waves[waveID].Splits[splitID].Content;

                        enemy = WaveMaker.Instantiate_UIObject(GroupBox.Enemy, enemyContent, -1, mode);
                        if (mode == Mode.WaveMaker)
                        {
                            WaveMaker.Instantiate_UIObject(GroupBox.EnemyDZ, enemyContent, -1, mode);
                        }
                        #endregion

                        #region Fill_Data
                        WaveMaker.Fill_GroupBox(enemy, enemyGB);
                        Resources.FileContent.Waves[waveID].Splits[splitID].Enemies.Add(enemyGB);

                        //AddParents
                        enemyGB.Layout.Parents.Add(splitGB.GroupBox);
                        enemyGB.Layout.Parents.AddRange(splitGB.Layout.Parents);
                        //FillValues
                        WaveMaker.Set_Color(enemy, false);
                        float[] enemyValue = { enemyID + 1, database.Waves[waveID].Splits[splitID].Enemies[enemyID].Timer };
                        WaveMaker.Fill_Values(enemyGB, enemyValue);
                        enemyGB.Type.value = (int)database.Waves[waveID].Splits[splitID].Enemies[enemyID].Name;
                        WaveMaker.Change_UnitPicture(enemy);
                        #endregion

                    }
                    splitGB.Layout.UpdateLayout();
                }
                waveGB.Layout.UpdateLayout();
            }
            Resources.FileContent.Layout.UpdateLayout();
            Resources.FileContent.LoadingPanel.SetActive(false);
        }
    }
}
