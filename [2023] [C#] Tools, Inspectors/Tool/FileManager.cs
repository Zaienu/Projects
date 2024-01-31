using UnityEngine;
using System.IO;
using UnityEngine.UI;
using System.Linq;
using TMPro;
using System.Collections.Generic;

namespace WaveMakerScript
{
    public class FileManager : MonoBehaviour
    {
        Resources Resources;
        DisplayWave DisplayWave;
        List<Scalable> scalables = new List<Scalable>();
        string path;

        private void Awake()
        {
            Resources = GetComponent<Resources>();
            DisplayWave = GetComponent<DisplayWave>();
        }

        /// <summary>
        /// Removes the FilesButtons from the FileBrowser
        /// Stops Displaying the FileBrowser
        /// Empties the related file;
        /// </summary>
        public void Clear_FileBrowser()
        {
            foreach (Transform child in Resources.FBContent.transform)
            {
                Destroy(child.gameObject);
            }
            Resources.FBContent.transform.DetachChildren();
            Resources.FBRoot.SetActive(false);
            Resources.FBButtons.Clear();
        }

        public List<string> Get_Files()
        {
            path = Application.streamingAssetsPath + "/Waves/";
            List<string> files = Directory.GetFiles(path).Where(x => !x.Contains(".meta")).ToList();
            for (int i = 0; i < files.Count; i++)
            {
                files[i] = files[i].Replace(path, "").Replace(".txt", "");
            }
            files.RemoveAll(x => x == "Official");
            files.RemoveAll(x => x == "Tutorial");
            return files;
        }

        /// <summary>
        /// Scales the FileBrowser depending on the number of Files
        /// </summary>
        private void Scale_FileBrowser()
        {
            if (!(Resources.FilesGO.Count > 0))
            { return; }
            List<string> names = new List<string>() { "WSBackground", "Search Bar", "Content", "Scrollable List" };
            List<GameObject> list = new List<GameObject>();
            List<Vector2> size = new List<Vector2>();
            list = Resources.FilesGO.Where(x => names.Contains(x.name)).ToList();
            list.ForEach(x => size.Add(x.GetComponent<RectTransform>().sizeDelta));

            int ID = 0;
            names.ForEach(x =>
            {
                if (!scalables.Any(y => y.obj.name == x))
                    scalables.Add(new Scalable(list[ID], size[ID], 60));
                ID++;
            });

            if (!Resources.FilesGO.Find(x => x.gameObject.name == "Content"))
            { return; }

            RectTransform content = Resources.FilesGO.Find(x => x.gameObject.name == "Content").GetComponent<RectTransform>();
            LayoutRebuilder.ForceRebuildLayoutImmediate(content);
            content.position = new Vector3(content.position.x, 450 - 13, content.position.z);
            scalables.ForEach(x =>
            {
                if (content.childCount > 11) x.obj.GetComponent<RectTransform>().sizeDelta
                    = new Vector2(x.baseSize.x, x.baseSize.y);
                else x.obj.GetComponent<RectTransform>().sizeDelta
                    = new Vector2(x.baseSize.x - x.delta, x.baseSize.y);
            });
        }

        /// <summary>
        /// Opens the FileBrowser, instantiate the FileButtons
        /// Renaming the Files
        /// </summary>
        public void Open_FileBrowser()
        {
            //Clearing Script & Visual Containers
            Clear_FileBrowser();
            Resources.FBRoot.SetActive(true);
            //Indexing files
            List<string> files = Get_Files();
            int ID = 0;

            //Filling the Script & Visual Containers
            foreach (string file in files)
            {
                Button button = Instantiate(Resources.FBPrefab, Resources.FBContent.transform);
                button.name = "File_" + ID;
                button.GetComponentInChildren<TextMeshProUGUI>().text = file.Replace(path, "").Replace(".txt", "");
                button.onClick.AddListener(() => { Fill_SelectedFile(button.GetComponentInChildren<TextMeshProUGUI>().text, button); });
                Resources.FBButtons.Add(button);
                ID++;
            }
            Scale_FileBrowser();
        }

        /// <summary>
        /// Fills the SelectedFile string
        /// Fills the Database
        /// Fills the WaveDisplayer
        /// </summary>
        public void Fill_SelectedFile(string _fileName, Button _button)
        {
            Resources.WTMode = Mode.WaveDisplay;
            Resources.SelectedFile = _fileName;
            Resources.FBButtons.ForEach(x => x.GetComponent<Image>().color = Color.white);
            _button.GetComponent<Image>().color = new Vector4(0.8f, 0.8f, 0.8f, 1.0f);
            Resources.WDDatabase = WaveManager.GetWavesFromTxtFile(_fileName + ".txt");

            Display_FileContent();
        }

        public void Display_FileContent()
        {
            StartCoroutine(DisplayWave.Fill_WaveDisplayer(Resources.WTMode));
        }

        /// <summary>
        /// Empties the SelectedFile string
        /// Clears the Database
        /// Empties the WaveDisplayer
        /// </summary>
        public void Empty_SelectedFile()
        {
            Resources.SelectedFile = "";
            Resources.WDDatabase = null;
            DisplayWave.Empty_WaveDisplayer();
        }

        public class SearchItems
        {
            public Button file;
            public bool isExcluded = false;
            public SearchItems(Button _file)
            {
                file = _file;
                isExcluded = false;
            }
        }

        public void ValueChanged_SearchBar()
        {
            List<SearchItems> searchItems = new List<SearchItems>();
            Resources.FBButtons.ForEach(x => searchItems.Add(new SearchItems(x)));
            TMP_InputField inputField = Resources.FilesGO.FirstOrDefault(x => x.name == "Search Bar").GetComponent<TMP_InputField>();

            if (inputField.text == string.Empty)
            {
                searchItems.ForEach(x => x.isExcluded = false);
            }
            else
            {
                int ID = 0;
                searchItems.ForEach(file =>
                {
                    bool isIncluded = Resources.FBButtons[ID].GetComponentInChildren<TMP_Text>()
                    .text.ToLower().Contains(inputField.text.ToLower());
                    if (!isIncluded)
                        file.isExcluded = true;
                    else file.isExcluded = false;
                    ID++;
                });
            }
            searchItems.ForEach(x => x.file.gameObject.SetActive(!x.isExcluded));
        }
    }
}
