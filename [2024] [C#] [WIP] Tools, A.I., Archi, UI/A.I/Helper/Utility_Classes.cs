using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

namespace Helper
{

    [Serializable]
    public class CLOSEST
    {
        public GameObject entity;
        public float distance;
    }

    [Serializable]
    public class Relations
    {
        public List<string> list = new();
    }

    [Serializable]
    public class SetupData
    {
        public Dictionary<string, bool> dictionary = new();

        public void LoadData(string _filePath)
        {
            dictionary = JSON_Helper.LoadFromJSON<SetupData>(_filePath).dictionary;
        }

        public void SaveData(string _filePath)
        {
            JSON_Helper.SaveToJSON(this, _filePath);
        }
    }

    [Serializable]
    public class Callbacks<T>
    {
        //CALLBACK_TYPE -> Event ID  
        public EventCallback<ChangeEvent<T>>?[][] events;

        public Callbacks()
        {
            events = new EventCallback<ChangeEvent<T>>?[2][];
        }

        public Callbacks(Callbacks<T> _obj)
        {
            events = _obj.events;
        }

        ~Callbacks()
        {
        }

        public void SetupCallbacks(CALLBACK_TYPE _CT, int _size)
        {
            //Create the Callback Array depending on the specified size.
            events[(int)_CT] = new EventCallback<ChangeEvent<T>>?[_size];
            //Fill it with nulls so it can be easily replaced.
            for (int i = 0; i < _size; i++)
            {
                events[(int)_CT][i] = null;
            }
        }

        public void SwapCallbacks()
        {
            //(Array1, Array2) = (Array2, Array1)
            (events[(int)CALLBACK_TYPE.NEXT], events[(int)CALLBACK_TYPE.CURRENT]) =
                (events[(int)CALLBACK_TYPE.CURRENT], events[(int)CALLBACK_TYPE.NEXT]);

            events[(int)CALLBACK_TYPE.NEXT] = null;
            
        }
    }
}