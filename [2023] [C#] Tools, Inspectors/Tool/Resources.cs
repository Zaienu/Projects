using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

namespace WaveMakerScript
{
    #region Enums
    public enum GroupBox
    {
        Root,
        Wave,
        Split,
        Enemy,
        WaveDZ,
        SplitDZ,
        EnemyDZ
    }

    public enum Data
    {
        Number,
        Timer,
        Amount,
    }

    public enum Mode
    {
        WaveDisplay,
        WaveMaker,
    }
    #endregion

    [System.Serializable]
    public class FileContent
    {
        public GroupBoxLayout Layout;
        public GameObject LoadingPanel; 
        public List<WaveGB> Waves = new List<WaveGB>();
        public Transform Content;
        public List<TMP_InputField> Amount = new List<TMP_InputField>();
    }

    public class WaveGB
    {
        public GroupBoxLayout Layout;
        public GameObject GroupBox;
        public Transform Content;
        public List<SplitGB> Splits = new List<SplitGB>();
        public List<TMP_InputField> Data = new List<TMP_InputField>();
    }

    public class SplitGB
    {
        public GroupBoxLayout Layout;
        public GameObject GroupBox;
        public Transform Content;
        public List<EnemyGB> Enemies = new List<EnemyGB>();
        public List<TMP_InputField> Data = new List<TMP_InputField>();
    }

    public class EnemyGB
    {
        public GroupBoxLayout Layout;
        public GameObject GroupBox;
        public List<TMP_InputField> Data = new List<TMP_InputField>();
        public List<TMP_InputField> Stats = new List<TMP_InputField>();
        public TMP_Dropdown Type;
        public Image Image;
    }

    public class Resources : MonoBehaviour
    {

        /// <summary>
        /// FB = File Browser
        /// WD = Wave Displayer
        /// GO = Game Object
        /// </summary>

        [Header("                   UI Root")]
        public Canvas Canvas;
        public EventSystem EventSystem;
        public List<GameObject> DisableMenusGO = new List<GameObject>();

        [Header("                   Files Menu")]
        public List<Button> FilesMenu = new List<Button>();

        [Header("                   Files Browser")]
        public Button FBPrefab;
        public GameObject FBRoot;
        public GameObject FBContent;
        public List<Button> FBButtons = new List<Button>();
        public List<GameObject> FilesGO = new List<GameObject>();
        public Mode WTMode = Mode.WaveDisplay;

        [Header("                   Wave Displayer")]
        public GameObject[] WDPrefabs;
        public GameObject WDRoot;
        public FileContent FileContent;
        public WaveDatabase WDDatabase;
        public string SelectedFile;

        [Header("                   Wave Modifier")]
        public GameObject[] WMPrefabs;
        public string WMFileName;
        public GameObject WarningWindow;
        public GameObject SaveWindow;
        public GameObject[] WarnLimitWindows;
    }
}
