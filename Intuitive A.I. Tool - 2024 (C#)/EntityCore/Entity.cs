using JetBrains.Annotations;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;
using UnityEngine.AI;
using static UnityEngine.EventSystems.EventTrigger;

namespace Behaviours
{

    public enum STATE
    {
        Previous,
        Current,
        Next,
    }

    public enum ENTITY_TYPES
    {
        Allies,
        Neutral,
        Enemies,
    }

    public enum ENTITY_STATS
    {
        Current_Health,
        Max_Health,
        Attack_Damage,
        Attack_Speed,
        Move_Speed,
    }

    public enum ENTITY_STATE
    {
        Death,
        Hit,
        Flee,
        Evade,
        Group,
        Pursue,
        Seek,
        Wander,
        Idle,
    }

    public class CLOSEST//eventual rename
    {
        public GameObject entity = new GameObject();
        public float distance = new float();
    }

    public class Entity : MonoBehaviour
    {

        //Entity Stats
        public float[] stats = new float[5]; //currHealth, maxHealth, attackDamage, attackSpeed, run speed... 
        //The closest entity to self from each type (Ally, Enemy, Neutral)
        public CLOSEST[] closestEntities = new CLOSEST[3];
        //0 -> Allies | 1 -> Neutral | 2 -> Enemies.
        List<string>[] relationships = new List<string>[3];
        //0-> Previous | 1 -> Current
        public ENTITY_STATE[] states = new ENTITY_STATE[2]; //Modify to include NextState(optional)
        //0-> Previous | 1 -> Current | 2 -> Next.
        public Vector3[] targets = new Vector3[3];
        //Agent
        public NavMeshAgent agent;

        private void Init_Array(ref CLOSEST[] _array)
        {
            for(int i = 0; i < _array.Length; i++)
            {
                _array[i] = new CLOSEST();
            }
        }

        private void Init_Array(ref float[] _array)
        {
            for (int i = 0; i < _array.Length; i++)
            {
                _array[i] = new float();
            }
        }

        public void Awake()
        {
            #region Exceptions Management

            if (!TryGetComponent(out agent))
            {
                throw new Exception("Entity ERROR : The Component \"NavMeshAgent\" hasn't been found");
            }

            #endregion
            Init_Array(ref closestEntities);
            Init_Array(ref stats);
        }

        private void Start()
        {

        }

    }

}