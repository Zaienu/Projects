using UnityEngine;
using TMPro;
using UnityEngine.SceneManagement;
using System.IO;
using UnityEngine.UI;

namespace WaveMakerScript
{
    public class LinkButtons : MonoBehaviour
    {
        GroupBoxManager GroupBoxManager;
        Resources Resources;
        FileManager FileManager;
        WaveMaker WaveMaker;
        private void Awake()
        {
            FileManager = FindObjectOfType<FileManager>();
            GroupBoxManager = FindObjectOfType<GroupBoxManager>();
            Resources = FindObjectOfType<Resources>();
            WaveMaker = FindObjectOfType<WaveMaker>();
        }

        public void Destroy_GroupBox()
        {
            SoundsManager.Play(SoundsName.WaveMakerError_UI);
            GroupBoxManager.Remove(gameObject);
        }

        public void Create_GroupBox()
        {
            SoundsManager.Play(SoundsName.WaveMakerConfirm_UI);
            int id = transform.GetSiblingIndex();
            if (transform.parent.childCount <= 101)
            {
                GroupBoxManager.Add(transform.parent, id + 1); return;
            }
            int index = (int)transform.parent.CRes().Parent.GBRes().Type - 1;
            Resources.WarnLimitWindows[index].SetActive(true); Resources.WarnLimitWindows[index].transform.SetAsLastSibling();
        }

        public void Switch_Mode(bool _loadFileContent)
        {
            SoundsManager.Play(SoundsName.WaveMakerError_UI);
            Resources.WTMode = (Mode)((int)(Resources.WTMode + 1) % 2);
            if (_loadFileContent)
            {
                Resources.WMFileName = Resources.SelectedFile;
                Resources.WDDatabase = WaveManager.GetWavesFromTxtFile(Resources.SelectedFile + ".txt");
                Resources.GetComponent<FileManager>().Display_FileContent();
            }
        }

        public void Select_FileContent()
        {
            WaveManager.LoadWavesFromTxtFile(Resources.SelectedFile + ".txt");
            GameManager.Instance.WaveName = Resources.SelectedFile;
            GameManager.Instance.SaveName = Resources.SelectedFile;
            SceneManager.LoadScene("FactionChoice");
        }

        public void Cancel_Modifications()
        {
            Destroy(Resources.WDRoot);
            Resources.WMFileName = null;
            Switch_Mode(!(Resources.SelectedFile == ""));
        }

        public void Save()
        {
            Resources.GetComponent<WaveMaker>().SaveFile();
            if (Resources.SelectedFile != "")
            {
                FileManager.Open_FileBrowser();
            }
        }

        public void Change_FileName()
        {
            TMP_InputField input = gameObject.GetComponent<TMP_InputField>();
            Resources.WMFileName = input.text;
        }

        public void Close_Warning()
        {
            SoundsManager.Play(SoundsName.WaveMakerConfirm_UI);
            Resources.WarningWindow.SetActive(false);
        }

        public void Close_Save()
        {
            SoundsManager.Play(SoundsName.WaveMakerConfirm_UI);
            Resources.SaveWindow.SetActive(false);
        }

        public void Close_WaveWarning()
        {
            SoundsManager.Play(SoundsName.WaveMakerConfirm_UI);
            Resources.WarnLimitWindows[(int)GroupBox.Wave - 1].SetActive(false);
        }

        public void Close_SplitWarning()
        {
            SoundsManager.Play(SoundsName.WaveMakerConfirm_UI);
            Resources.WarnLimitWindows[(int)GroupBox.Split - 1].SetActive(false);
        }

        public void Close_EnemyWarning()
        {
            SoundsManager.Play(SoundsName.WaveMakerConfirm_UI);
            Resources.WarnLimitWindows[(int)GroupBox.Enemy - 1].SetActive(false);
        }

        public void Return()
        {
            SceneManager.LoadScene("Main Menu");
        }

        public void Change_UnitPic()
        {
            WaveMaker.Change_UnitPicture(gameObject);
        }

        public void Delete_FileContent()
        {
            if (transform.parent.GetComponentInChildren<TextMeshProUGUI>().text == Resources.SelectedFile)
            { FileManager.Empty_SelectedFile(); }
            File.Delete(Application.streamingAssetsPath + "/Waves/" + transform.parent.GetComponentInChildren<TextMeshProUGUI>().text + ".txt");
            FileManager.Open_FileBrowser();
            GameObject scrollbar = Resources.FilesGO.Find(x => x.name == "ScrollBar");
            GameObject go = scrollbar.Contains("Handle");
            scrollbar.GetComponent<Scrollbar>().value = 0.999f;
            go.GetComponent<ScrollHandle>().Update();
        }

    }
}
