using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace WaveMakerScript
{
    public static class GameObjectUtility
    {
        public static GameObject Contains(this GameObject gameObject, string name)
        {
            if (gameObject.name == name)
            { return gameObject; };

            foreach (Transform child in gameObject.transform)
            {
                GameObject result = Contains(child.gameObject, name);
                if (result)
                { return result; };
            }
            return null;
        }

        public static void Contains(this GameObject gameObject, string name, List<GameObject> list)
        {
            foreach (Transform child in gameObject.transform)
            {
                Contains(child.gameObject, name, list);

                if (!(child.name == name))
                { continue; };

                if (list.Any(x => x.gameObject == child.gameObject))
                { continue; };

                list.Add(child.gameObject);
            }
        }

        public static void GetAllChilds(this GameObject gameObject, List<GameObject> list)
        {
            foreach (Transform child in gameObject.transform)
            {
                GetAllChilds(child.gameObject, list);

                if (list.Any(x => x.gameObject == child.gameObject))
                { continue; }

                list.Add(child.gameObject);
            }
        }

        public static List<GameObject> GetChilds(this GameObject gameObject, string exception = null)
        {
            List<GameObject> list = new List<GameObject>();
            foreach (Transform child in gameObject.transform)
            {
                if (child.gameObject.name != exception || exception == null)
                {
                    list.Add(child.gameObject);
                }
            }
            return list;
        }

        public static GroupBoxLayout GBLayout(this GameObject gameObject)
        {
            return gameObject.GetComponent<GroupBoxLayout>();
        }

        public static GBResources GBRes(this GameObject gameObject)
        {
            return gameObject.GetComponent<GroupBoxLayout>().GBResources;
        }

        public static void RemoveNull(this List<List<GameObject>> list, int id)
        {
            list[id].ForEach(x => { if (x == null) list[id].Remove(x); });
        }

        public static void RemoveNull(this List<GameObject> list)
        {
            list.ForEach(x => { if (x == null) list.Remove(x); });
        }

    }

    public static class TransformUtility
    {
        public static GetParent CRes(this Transform transform)
        {
            return transform.GetComponent<GetParent>();
        }
    }

    public static class WaveGBUtility
    {
        public static float Timer(this WaveGB waveGB)
        {
            float result;
            float.TryParse(waveGB.Data[(int)Data.Timer].text, out result);
            return result;
        }
    }
    public static class SplitGBUtility
    {
        public static float Timer(this SplitGB splitGB)
        {
            float result;
            float.TryParse(splitGB.Data[(int)Data.Timer].text, out result);
            return result;
        }
    }

    public static class EnemyGBUtility
    {
        public static float Timer(this EnemyGB enemyGB)
        {
            float result;
            float.TryParse(enemyGB.Data[(int)Data.Timer].text, out result);
            return result;
        }
    }
}