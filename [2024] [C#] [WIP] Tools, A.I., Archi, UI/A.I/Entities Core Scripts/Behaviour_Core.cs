using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using UnityEngine;
using UnityEngine.AI;
using Utility;

namespace Entities_Core_Scripts
{
    
    public class Behaviour_Core : MonoBehaviour
    {
        [SerializeField] GameObject GO;

        private Entity_Core entity;
        
        public delegate void Behaviour();
        public Behaviour Behaviour_Update;
        
        private List<Delegate> fctList = new List<Delegate>();
        
        bool isSorted = false;
        
        float stoppingDist = 1.1f;
        float fleeDist = 15f;
        
        void Awake()
        {
            #region Exceptions Management
            if (!TryGetComponent(out entity))
            {
                throw new Exception("Master_Behaviour ERROR : The Component \"Entity\" hasn't been found");
            }
            #endregion
        }
        
        private void Start()
        {
            //TESTS
            //entity.closestEntities[(int)ENTITY_TYPES.Enemies].entity = GO;
            entity.stats[(int)ENTITY_STATS.Move_Speed] = 4;
        }

        #region Sort Helper Functions
        
        private void Unsubscribe_All(List<Delegate> _behaviours)
        {
            _behaviours.ForEach(x => Behaviour_Update -= (Behaviour)x);
        }

        private void Subscribe_All(List<Delegate> _behaviours)
        {
            _behaviours.ForEach(x => Behaviour_Update += (Behaviour)x);
        }
        
        private static void Swap_Elements<T>(ref List<T> _list, int _index1, int _index2)
        {
            (_list[_index1], _list[_index2]) = (_list[_index2], _list[_index1]);
        }

        private int Partition(ref List<ENTITY_STATE> _behaviours, int _start, int _end)
        {
            int pivot = (int)_behaviours[_start];
            int swapIndex = _start;
            for (int i = _start + 1; i < _end; i++)
            {
                if ((int)_behaviours[i] < pivot)
                {
                    swapIndex++;
                    //switching both the Lists
                    Swap_Elements(ref _behaviours, i, swapIndex);
                    Swap_Elements(ref fctList, i, swapIndex);
                }
            }
            //switching both the Lists
            Swap_Elements(ref _behaviours, _start, swapIndex);
            Swap_Elements(ref fctList, _start, swapIndex);
            return swapIndex;
        }
        
        private void QuickSort(ref List<ENTITY_STATE> _behaviours, int _start, int _end)
        {
            if (_start < _end)
            {
                int pivot = Partition(ref _behaviours, _start, _end);
                QuickSort(ref _behaviours, _start, pivot);
                QuickSort(ref _behaviours, pivot + 1, _end);
            }
        }
        
        #endregion
        
        public void Sort_Behaviours()
        {
            //List of the Functions subscribed to the Delegate.
            fctList = Behaviour_Update.GetInvocationList().ToList();
            List<ENTITY_STATE> stateList = new List<ENTITY_STATE>();
            
            //We can't sort the Functions directly so we'll make a Sortable List.
            //So we can switch the indexes of the Functions at the same time as when
            //We switch the Sortable List's values.
            for (int id = 0; id < fctList.Count; id++)
            {
                if (Enum.TryParse(fctList[id].GetMethodInfo().Name, out ENTITY_STATE element))
                {
                    stateList.Add(element);
                }
            }
            
            //Unsubscribes all the Functions to sort them.
            Unsubscribe_All(fctList);
            
            //QuickSorts the Sortable List and the Functions List.
            QuickSort(ref stateList, 0, stateList.Count);
            
            //Subscribes back all the Functions in the correct priority order.
            Subscribe_All(fctList);
        }

        private void Clamp_Velocity()
        {
            float moveSpeed = entity.stats[(int)ENTITY_STATS.Move_Speed];

            if (entity.agent.velocity.magnitude > moveSpeed)
            {
                entity.agent.velocity = Vector3.ClampMagnitude(entity.agent.velocity, moveSpeed);
            }

            Vector3 distance = gameObject.Get_Pos() - entity.targets[(int)STATE.Current];

            //switch(entity.states[(int)STATE.Current])
            //{
            //    case ENTITY_STATE.Flee:
            //        if (distance.magnitude > fleeDist)
            //        {
            //            agent.velocity = Vector3.zero;
            //        }
            //        break;
            //}

            if (distance.magnitude < stoppingDist)
            {
                entity.agent.velocity = Vector3.zero;
            }
        }

        public void Change_State(ENTITY_STATE _state)
        {
            //Modify to include NextState (optional)
            if (CurrentState != _state && _state != ENTITY_STATE.Death)
            {
                PreviousState = CurrentState;
                CurrentState = _state;
            }
        }

        #region State Getters
        
        public ENTITY_STATE PreviousState
        {
            get => entity.states[(int)STATE.Previous];
            set => entity.states[(int)STATE.Previous] = value;
        }
        
        public ENTITY_STATE CurrentState
        {
            get => entity.states[(int)STATE.Current];
            set => entity.states[(int)STATE.Current] = value;
        }

        // public ENTITY_STATE NextState
        // {
        //     get => entity.states[(int)STATE.Next];
        //     set => entity.states[(int)STATE.Next] = value;
        // }

        #endregion

        #region Entity Data Getters

        public NavMeshAgent Agent
        {
            get => entity.agent;
            set => entity.agent = value;
        }

        public ENTITY_STATE[] States
        {
            get => entity.states;
            set => entity.states = value;
        }
        
        public Vector3[] Targets
        {
            get => entity.targets;
            set => entity.targets = value;
        }

        public Vector3 Velocity
        {
            get => Agent.velocity;
            set => Agent.velocity = value;
        }

        public CLOSEST[] Closest
        {
            get => entity.closestEntities;
            set => entity.closestEntities = value;
        }

        public float[] Stats
        {
            get => entity.stats;
            set => entity.stats = value;
        }
        
        #endregion

        void Update()
        {
            //Sort the Subscribed Functions by priority.
            if (!isSorted && Behaviour_Update != null)
            {
                Sort_Behaviours();
                isSorted = true;
            }

            //TESTS
            if (GO)
            {
                Vector3 vec = transform.position - GO.transform.position;
                entity.closestEntities[(int)ENTITY_TYPES.Enemies].distance = vec.magnitude;
            }

            //If there is no Behaviour then do not Invoke it (NullException).
            if (Behaviour_Update != null)
            {
                //Invoke the Functions added to the delegate to compose a complete Behaviour.
                Behaviour_Update.Invoke();
            }
            Clamp_Velocity();
        }
    }

}
