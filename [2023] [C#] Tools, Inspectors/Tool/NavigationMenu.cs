using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using System.Linq;

namespace WaveMakerScript
{

    #region Scalable
    public class Scalable
    {
        public GameObject obj;
        public Vector2 baseSize;
        public int delta;
        public Scalable(GameObject _obj, Vector2 _size, int _delta)
        {
            obj = _obj;
            baseSize = _size;
            delta = _delta;
        }
    }
    #endregion

    public class NavigationMenu : MonoBehaviour
    {
        Resources Resources;
        FileManager FileManager;
        GameObject selection;

        private void Awake()
        {
            Resources = GetComponent<Resources>();
            FileManager = GetComponent<FileManager>();
        }

        /// <summary>
        /// Displays or not the FilesMenu
        /// </summary>
        public void Display_FilesMenu(bool _display)
        {
            if (Resources.FilesMenu.Last().IsActive() == _display)
            { return; }

            foreach (Button button in Resources.FilesMenu)
            {
                if (button.name == "Files_Button")
                { continue; }

                button.gameObject.SetActive(_display);

                if (_display)
                { continue; }
            }
        }

        /// <summary>
        /// Displays or not the FilesMenu
        /// </summary>
        public void Display_FilesMenu()
        {
            foreach (Button button in Resources.FilesMenu)
            {
                if (button.name == "Files_Button")
                { continue; }
                button.gameObject.SetActive(!button.IsActive());

                if (button.gameObject.activeSelf)
                { continue; }
            }
        }

        /// <summary>
        /// Fills the DisableMenusGO's first dimension
        /// </summary>
        private void Fill_DisableMenusGO()
        {
            if (!Resources.FilesGO.Any(x => x == Resources.FBRoot))
            { Resources.FilesGO.Add(Resources.FBRoot); }
            Resources.FBRoot.GetAllChilds(Resources.FilesGO);

            List<GameObject> toRemove = new List<GameObject>();
            Resources.FBButtons.ForEach(x => toRemove.Add(x.gameObject));
            Resources.FBButtons.ForEach(x => x.gameObject.GetAllChilds(toRemove));
            Resources.FilesGO.RemoveAll(x => toRemove.Contains(x));
            if (!Resources.DisableMenusGO.Any(x => x == Resources.Canvas.gameObject))
            { Resources.DisableMenusGO.Add(Resources.Canvas.gameObject); }
        }

        /// <summary>
        /// Invoke the functions related to the opening of the FileMenus
        /// </summary>
        public void Files_Menus()
        {
            FileManager.Clear_FileBrowser();
            FileManager.Empty_SelectedFile();
        }

        /// <summary>
        /// Invoke the functions related to the opening of the FileBrowser
        /// </summary>
        public void Display_FileBrowser()
        {
            Resources.WTMode = Mode.WaveDisplay;
            Fill_DisableMenusGO();
            FileManager.Open_FileBrowser();
            Display_FilesMenu(false);
        }

        /// <summary>
        /// Invoke the functions related to the creation of a new FileContent
        /// </summary>
        public void Create_FileContent()
        {
            FileManager.Clear_FileBrowser();
            Fill_DisableMenusGO();
            Display_FilesMenu(false);
            Resources.WTMode = Mode.WaveMaker;
            FileManager.Display_FileContent();
        }

        /// <summary>
        /// Checks whether the FilesMenu should be closed 
        /// </summary>
        private void Check_Selection(GameObject _selection)
        {
            if (_selection == null)
            { return; }

            if (Resources.DisableMenusGO.Any(x => x == _selection))
            { FileManager.Clear_FileBrowser(); FileManager.Empty_SelectedFile(); }
        }

        private void Update()
        {
            selection = Resources.EventSystem.currentSelectedGameObject;
            Check_Selection(selection);
            if (Input.GetMouseButtonDown(0))
            {
                SoundsManager.Play(SoundsName.ButtonOnClick_UI);
            }

            if (Input.inputString != string.Empty)
            {
               SoundsManager.Play(SoundsName.Typewritting_UI);
            }
        }
    }
}
