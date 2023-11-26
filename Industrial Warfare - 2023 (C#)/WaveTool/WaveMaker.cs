using System.Collections.Generic;
using System.Linq;
using TMPro;
using UnityEngine;


namespace WaveMakerScript
{

    public class WaveMaker : MonoBehaviour
    {
        Resources Resources;
        GroupBoxManager GroupBoxManager;
        FileManager FileManager;
        private void Awake()
        {
            Resources = GetComponent<Resources>();
            FileManager = GetComponent<FileManager>();
        }

        public void SaveFile()
        {

            List<string> files = FileManager.Get_Files();
            if (files.Any(x => x == Resources.WMFileName) || Resources.WMFileName.Length < 5 || Resources.WMFileName.Length > 15)
            {
                if ((Resources.SelectedFile != Resources.WMFileName) || ((Resources.SelectedFile == Resources.WMFileName) && Resources.SelectedFile == "")
                || Resources.WMFileName == "Official" || Resources.WMFileName == "Tutorial")
                {
                    SoundsManager.Play(SoundsName.WaveMakerError_UI);
                    Resources.WarningWindow.SetActive(true); Resources.WarningWindow.transform.SetAsLastSibling();
                    return;
                }
            }

            WaveDatabaseScriptable database = ScriptableObject.CreateInstance<WaveDatabaseScriptable>();
            int waveSize = Resources.FileContent.Waves.Count();
            for (int waveID = 0; waveID < waveSize; waveID++)
            {

                Wave wave = new Wave();
                wave.Timer = Resources.FileContent.Waves[waveID].Timer();

                int splitSize = Resources.FileContent.Waves[waveID].Splits.Count();
                for (int splitID = 0; splitID < splitSize; splitID++)
                {

                    WaveStep waveStep = new WaveStep();
                    waveStep.Timer = Resources.FileContent.Waves[waveID].Splits[splitID].Timer();
                    wave.Splits.Add(waveStep);

                    int enemySize = Resources.FileContent.Waves[waveID].Splits[splitID].Enemies.Count();
                    for (int enemyID = 0; enemyID < enemySize; enemyID++)
                    {

                        List<EnemyGB> enemies = Resources.FileContent.Waves[waveID].Splits[splitID].Enemies;
                        Enemy enemy = new Enemy();

                        enemy.Timer = enemies[enemyID].Timer();
                        enemy.Name = (Enemies)enemies[enemyID].Type.value;
                        waveStep.Enemies.Add(enemy);
                    }
                }
                database.Waves.Add(wave);
            }
            WaveManager.SaveWavesInTxtFile(Resources.WMFileName + ".txt", database);
            Resources.SaveWindow.SetActive(true);
            Resources.SaveWindow.transform.SetAsLastSibling();
            SoundsManager.Play(SoundsName.WaveMakerConfirm_UI);
        }

        /// <summary>
        /// It's purpose is to instantiate a simple gameObject
        /// from the parent's transform, a type, an index and a version
        /// </summary>
        public GameObject Instantiate_UIObject(GroupBox type, Transform parent, int index, Mode mode)
        {
            GameObject GameObject = null;
            GameObject[] prefabs = mode == Mode.WaveDisplay ? Resources.WDPrefabs : Resources.WMPrefabs;
            GameObject = Instantiate(prefabs[(int)type]);
            GameObject.transform.SetParent(parent, false);
            GameObject.transform.SetSiblingIndex(index);
            GameObject.name = GameObject.name.Replace("(Clone)", "");
            return GameObject;
        }

        #region Set_Color

        private bool Compare_Colors(Color prevColor, Color currColor)
        {
            float sum = currColor.r + currColor.g + currColor.b;
            float sum2 = prevColor.r + prevColor.g + prevColor.b;
            if (Mathf.Abs(sum - sum2) < 0.3f)
            {
                return false;
            }
            return true;
        }

        private bool Compare_Colors(Color prevColor, Color currColor, Color nextColor)
        {

            List<Color> colors = new List<Color> { prevColor, nextColor };

            foreach (Color color in colors)
            {
                float sum = currColor.r + currColor.g + currColor.b;
                float sum2 = color.r + color.g + color.b;
                if (Mathf.Abs(sum - sum2) < 0.3f)
                {
                    return false;
                }
            }
            return true;
        }

        private Color Randomize_Color(GroupBox type)
        {
            bool canReturn = false;
            Color color;
            do
            {
                color = Random.ColorHSV(0.2f, 1f, 1f, 1f, 0.5f, 1f);
                switch (type)
                {
                    case GroupBox.Wave:
                        if (color.b > color.g * 1.2 && color.b > color.r * 1.2) { canReturn = true; }
                        break;
                    case GroupBox.Split:
                        if (color.g > color.r * 1.2 && color.g > color.b * 1.2) { canReturn = true; }
                        break;
                    case GroupBox.Enemy:
                        if (color.r > color.g * 1.2 && color.r > color.b * 1.2) { canReturn = true; }
                        break;
                }
            } while (!canReturn);
            return color;
        }

        private void Get_Color(GameObject obj, bool _isInit)
        {
            GBResources res = obj.GBRes();
            GroupBoxLayout gbl = obj.GBLayout();
            int offset = Resources.WTMode == Mode.WaveDisplay ? 1 : 2;
            int childOffset = Resources.WTMode == Mode.WaveDisplay ? 0 : -1;
            if (res.ListID > 0)
            {
                Color prevColor, color, nextColor;
                Transform content = gbl.Parents[0].GBRes().Content;
                int childs = content.childCount;
                prevColor = gbl.Parents[0].GBRes().Content.GetChild(res.HierarchyID - offset).gameObject.GBRes().color;
                if ((gbl.Parents[0].GBRes().Content.childCount + childOffset >= res.HierarchyID + offset) && _isInit)
                {
                    nextColor = gbl.Parents[0].GBRes().Content.GetChild(res.HierarchyID + offset).gameObject.GBRes().color;
                    do
                    {
                        color = Randomize_Color(res.Type);
                    } while (!Compare_Colors(prevColor, color, nextColor));
                    res.Color = color;
                    return;
                }
                do
                {
                    color = Randomize_Color(res.Type);
                } while (!Compare_Colors(prevColor, color));
                res.Color = color;
                return;
            }
            res.Color = Randomize_Color(res.Type);
        }

        #endregion

        #region Fill_GroupBox

        public void Set_Color(GameObject GroupBox, bool _isInit)
        {
            GBResources Res = GroupBox.GetComponent<GBResources>();
            Res.Start();
            Get_Color(GroupBox, _isInit);
        }


        /// <summary>
        /// Fills a Wave GroupBox
        /// with data from the groupbox prefab
        /// Allows better data management and optimization
        /// </summary>
        public void Fill_GroupBox(GameObject GroupBox, WaveGB Wave)
        {
            GBResources Res = GroupBox.GetComponent<GBResources>();
            Wave.Layout = GroupBox.GetComponent<GroupBoxLayout>();
            Wave.GroupBox = GroupBox;
            Wave.Content = Res.Content;
            Wave.Data = Res.Data;
        }

        /// <summary>
        /// Fills a Wave GroupBox
        /// with data from the groupbox prefab
        /// Allows better data management and optimization
        /// </summary>
        public void Fill_GroupBox(GameObject GroupBox, SplitGB Split)
        {
            GBResources Res = GroupBox.GetComponent<GBResources>();
            Split.Layout = GroupBox.GetComponent<GroupBoxLayout>();
            Split.GroupBox = GroupBox;
            Split.Content = Res.Content;
            Split.Data = Res.Data;
        }

        /// <summary>
        /// Fills a Wave GroupBox
        /// with data from the groupbox prefab
        /// Allows better data management and optimization
        /// </summary>
        public void Fill_GroupBox(GameObject GroupBox, EnemyGB Enemy)
        {
            GBResources Res = GroupBox.GetComponent<GBResources>();
            Enemy.Layout = GroupBox.GetComponent<GroupBoxLayout>();
            Enemy.GroupBox = GroupBox;
            Enemy.Data = Res.Data;
            Enemy.Stats = Res.Stats;
            Enemy.Type = Res.EnemyType;
            Enemy.Image = Res.Image;
        }

        #endregion

        #region Fill_Values
        /// <summary>
        /// Fills in a given Input Field a value
        /// used for modifying Timers, Numbers or Amounts
        /// </summary>
        public void Fill_Value(TMP_InputField Field, float value)
        {
            Field.text = Format_Value(value);
        }

        public string Format_Value(float value)
        {
            string str = null;
            str = value > 9 || value.ToString().Contains(',') ? value.ToString() : "0" + value.ToString();
            return str;
        }

        public void Fill_Values(WaveGB waveGB, float[] values)
        {
            Fill_Value(waveGB.Data[(int)Data.Number], values[0]);
            Fill_Value(waveGB.Data[(int)Data.Timer], values[1]);
            Fill_Value(waveGB.Data[(int)Data.Amount], values[2]);
        }
        public void Fill_Values(SplitGB splitGB, float[] values)
        {
            Fill_Value(splitGB.Data[(int)Data.Number], values[0]);
            Fill_Value(splitGB.Data[(int)Data.Timer], values[1]);
            Fill_Value(splitGB.Data[(int)Data.Amount], values[2]);
        }
        public void Fill_Values(EnemyGB enemyGB, float[] values)
        {
            Fill_Value(enemyGB.Data[(int)Data.Number], values[0]);
            Fill_Value(enemyGB.Data[(int)Data.Timer], values[1]);
        }
        public void Change_UnitPicture(GameObject gameObject)
        {
            gameObject.GBRes().Image.sprite = gameObject.GBRes().sprites[gameObject.GBRes().EnemyType.value];
        }

        public void Fill_Amounts(int value)
        {
            List<GameObject> results = new List<GameObject>();
            Resources.WDRoot.Contains("Wave_Amount", results);
            Resources.FileContent.Amount.AddRange(results.Select(x => x.GetComponent<TMP_InputField>()));
            Resources.FileContent.Amount.ForEach(x => Fill_Value(x, value));
        }
        #endregion

        #region File_Content
        public void Fill_FileContent()
        {
            Resources.FileContent = new FileContent();
            Resources.FileContent.Content = Resources.WDRoot.Contains("Waves_Content").transform;
            Resources.FileContent.LoadingPanel = Resources.WDRoot.Contains("Loading_Screen");
            Resources.FileContent.Layout = Resources.WDRoot.GetComponent<GroupBoxLayout>();
        }
        #endregion

        #region IgnoreList
        /// <summary>
        /// Allows the ignorelist to include the gameobjects
        /// from the wave displayer
        /// </summary>
        public void Fill_IgnoreList(GameObject gameObject, int index)
        {
            //List<GameObject> list = new List<GameObject>();
            //gameObject.GetAllChilds(list);
            //Resources.IgnoreList[index].AddRange(list);
        }

        public void Empty_IgnoreList(int index)
        {
            //Resources.IgnoreList[index].Clear();
        }

        #endregion

    }
}
