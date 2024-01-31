using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

namespace Entities_Core_Scripts
{

    [Serializable]
    public class Relations
    {
        public List<string> list = new List<string>();
    }
    
    public class Entity_Core : MonoBehaviour
    {

        //Entity_Core Stats
        public float[] stats = new float[5]; //currHealth, maxHealth, attackDamage, attackSpeed, run speed... 
        //The closest entity to self from each type (Ally, Enemy, Neutral)
        public CLOSEST[] closestEntities = new CLOSEST[3] {new(), new(), new()};
        //0 -> Allies | 1 -> Neutral | 2 -> Enemies.
        List<string>[] relationships = new List<string>[3];
        //0-> Previous | 1 -> Current
        public ENTITY_STATE[] states = new ENTITY_STATE[2]; //Modify to include NextState(optional)
        //0-> Previous | 1 -> Current | 2 -> Next.
        public Vector3[] targets = new Vector3[3];
        //Agent
        public NavMeshAgent agent;

        public void Awake()
        {
            #region Exceptions Management
            if (!TryGetComponent(out agent))
            {
                throw new Exception("Entity_Core ERROR : The Component \"NavMeshAgent\" hasn't been found");
            }
            #endregion
        }

        private void Start()
        {

        }

    }

}