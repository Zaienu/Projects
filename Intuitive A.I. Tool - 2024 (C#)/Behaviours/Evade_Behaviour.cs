using System;
using UnityEngine;
using Quaternion = UnityEngine.Quaternion;
using Random = UnityEngine.Random;
using Vector3 = UnityEngine.Vector3;

namespace Behaviours
{
    public class Evade_Behaviour : MonoBehaviour
    {
        //Master
        private Master_Behaviour master_Behaviour;

        #region Client's Parameters

        [SerializeField] public float DetectionRange = 10f;
        [SerializeField] public float ReqHealth = 10f;

        #endregion

        #region Private

        //Steering
        private Vector3 enemyVelocity;
        private Vector3 enemyPredictedPos;
        private Vector3 desiredVelocity;
        private Vector3 steering;

        //Master's Data
        private CLOSEST closestEnemy;
        private Vector3 enemyPos;
        private Vector3 velocity;
        private float currentHealth;
        private float moveSpeed;


        #endregion

        void Awake()
        {
            #region Exceptions Management

            if (!TryGetComponent(out master_Behaviour))
            {
                throw new Exception("Evade_Behaviour ERROR : The Component \"Master_Behaviour\" hasn't been found");
            }

            #endregion

            #region Subscription Management

            //Subscribe the function to the "Master_Behaviour" 's Update Delegate when the component is enabled.
            if (!enabled) { return; }
            master_Behaviour.Behaviour_Update -= Evade;
            master_Behaviour.Behaviour_Update += Evade;

            #endregion
        }

        private void Start()
        {
            //Init Master Data
            velocity = master_Behaviour.Velocity;
            currentHealth = master_Behaviour.Get_CurrentHealth();
            moveSpeed = master_Behaviour.Get_MoveSpeed();
        }

        void Evade()
        {
            //Local Typedefs
            Vector3 position = transform.position;
            
            closestEnemy = master_Behaviour.Get_Closest(ENTITY_TYPES.Enemies);
            enemyPos = closestEnemy.Pos();
            
            //possible refactor
            
            //Entrance Condition
            if (currentHealth <= ReqHealth && closestEnemy.distance <= DetectionRange)
            {
                // Debug.Log((enemyPos - transform.position).magnitude);
                
                master_Behaviour.Change_State(ENTITY_STATE.Evade);
                
                master_Behaviour.Targets[(int)STATE.Current] = enemyPos;
                
                enemyVelocity = closestEnemy.entity.GetComponent<Master_Behaviour>().Velocity;

                enemyPredictedPos = enemyPos + enemyVelocity * (Time.deltaTime * 50);
                
                desiredVelocity = (position - enemyPredictedPos).normalized;

                steering = desiredVelocity * moveSpeed - velocity;
                
                Debug.Log(steering);
                
                master_Behaviour.Velocity += steering * Time.deltaTime;
            }
        }

        #region Evade Debug

        private void OnDrawGizmos()
        {
            if (master_Behaviour.CurrentState != ENTITY_STATE.Evade) { return;}
            
            Vector3 position = transform.position;

            //Evade Target
            Gizmos.DrawWireSphere(position, DetectionRange);
            Gizmos.color = Color.red;
            Gizmos.DrawSphere(enemyPredictedPos, 0.5f);
            Gizmos.DrawLine(position, enemyPredictedPos);
            //Enemy Movement
            Gizmos.color = Color.blue;
            Gizmos.DrawSphere(enemyPos, 0.5f);
            Gizmos.DrawLine(enemyPos, enemyPredictedPos);
            //Entity to Displacement
            Gizmos.color = Color.green;
            Gizmos.DrawLine(position, position + desiredVelocity);
        }

        #endregion
    }
}