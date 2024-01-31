using System;
using System.Collections.Generic;
using Entities_Core_Scripts;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UIElements;

namespace Utility
{
    public static class UnityExtension
    {
        public static GameObject Contains(this GameObject gameObject, string name)
        {
            if (gameObject.name == name)
            {
                return gameObject;
            }

            ;

            foreach (Transform child in gameObject.transform)
            {
                GameObject result = Contains(child.gameObject, name);
                if (result)
                {
                    return result;
                }

                ;
            }

            return null;
        }

        public static Vector3 Get_Pos(this GameObject _gameObject)
        {
            return _gameObject.transform.position;
        }

        public static void Set_Parent(this GameObject _gameObject, GameObject _parent)
        {
            _gameObject.transform.parent = _parent.transform;
        }

        #region Entity Stats Getters

        public static float Get_CurrentHealth(this Behaviour_Core _master_Behaviour)
        {
            return _master_Behaviour.Stats[(int)ENTITY_STATS.Current_Health];
        }

        public static float Get_MaxHealth(this Behaviour_Core _master_Behaviour)
        {
            return _master_Behaviour.Stats[(int)ENTITY_STATS.Max_Health];
        }

        public static float Get_AttackDamage(this Behaviour_Core _master_Behaviour)
        {
            return _master_Behaviour.Stats[(int)ENTITY_STATS.Attack_Damage];
        }

        public static float Get_AttackSpeed(this Behaviour_Core _master_Behaviour)
        {
            return _master_Behaviour.Stats[(int)ENTITY_STATS.Attack_Speed];
        }

        public static float Get_MoveSpeed(this Behaviour_Core _master_Behaviour)
        {
            return _master_Behaviour.Stats[(int)ENTITY_STATS.Move_Speed];
        }

        #endregion

        public static CLOSEST Get_Closest(this Behaviour_Core _master_Behaviour, ENTITY_TYPES _type)
        {
            return _master_Behaviour.Closest[(int)_type];
        }

        public static Vector3 Pos(this CLOSEST _closest)
        {
            return _closest.entity.transform.position;
        }

        public static void TryAddComponent<T>(this GameObject _gameObject, T _comp) where T : System.Type
        {
            Component comp = _gameObject.GetComponent(_comp);

            if (!comp)
            {
                _gameObject.AddComponent(_comp);
            }
        }

        public static float Divide(this Length _length, Length _divider)
        {
            return _length.value / _divider.value;
        }

        public static void Clear<T>(this T[] _array)
        {
            Array.Clear(_array, 0, _array.Length);
            //PROBLEM WITH RELATIONSHIPS
        }

        public static void Clear(this Relations[] _array)
        {
            Array.Clear(_array, 0, _array.Length);
            for (int i = 0; i < _array.Length; i++)
            {
                _array[i] = new Relations();
            }
        }

        public static void Clear<T>(this List<T>[] _list)
        {
            for (int i = 0; i < _list.Length; i++)
            {
                //Security in case, each array element is null
                _list[i]?.Clear();
            }
        }

        public static void Init<T>(this List<T>[] _list)
        {
            for (int i = 0; i < _list.Length; i++)
            {
                _list[i] = new List<T>();
            }
        }

        public static void Init<T>(this T[] _array)
        {
            for (int i = 0; i < _array.Length; i++)
            {
                _array[i] = default;
            }
        }
        
        public static T[] Copy<T>(this T[] _array)
        {
            return _array.Clone() as T[];
        }
        
        public static List<T>[] Copy<T>(this List<T>[] _list)
        {
            List<T>[] clonedList = new List<T>[_list.Length];
            for (int i = 0; i < _list.Length; i++)
            {
                clonedList[i] = new List<T>(_list[i]);
            }
            return clonedList;
        }
    }
}

