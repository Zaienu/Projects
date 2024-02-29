using System;
using Entities_Core_Scripts;
using Helper;
using UnityEngine;
using Quaternion = UnityEngine.Quaternion;
using Random = UnityEngine.Random;
using Vector3 = UnityEngine.Vector3;

namespace Behaviours
{
    public class Pursue_Behaviour : MonoBehaviour
    {
        //Master
        private Behaviour_Core Bhv_Core;

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

            if (!TryGetComponent(out Bhv_Core))
            {
                throw new Exception("Pursue_Behaviour ERROR : The Component \"Master_Behaviour\" hasn't been found");
            }

            #endregion

            #region Subscription Management

            //Subscribe the function to the "Master_Behaviour" 's Update Delegate when the component is enabled.
            if (!enabled) { return; }
            Bhv_Core.Behaviour_Update -= Pursue;
            Bhv_Core.Behaviour_Update += Pursue;

            #endregion
        }

        private void Start()
        {
            //Init Master Data
            velocity = Bhv_Core.Velocity;
            currentHealth = Bhv_Core.Get_CurrentHealth();
            moveSpeed = Bhv_Core.Get_MoveSpeed();
        }

        void Pursue()
        {
            //Local Typedefs
            Vector3 position = transform.position;
            
            closestEnemy = Bhv_Core.Get_Closest(ENTITY_TYPES.Enemies);
            enemyPos = closestEnemy.Pos();
            
            //possible refactor
            
            //Entrance Condition
            if (currentHealth <= ReqHealth && closestEnemy.distance <= DetectionRange)
            {
                // Debug.Log((enemyPos - transform.position).magnitude);
                Bhv_Core.Change_State(ENTITY_STATE.Pursue);
                
                Bhv_Core.Targets[(int)STATE.Current] = enemyPos;
                
                enemyVelocity = closestEnemy.entity.GetComponent<Behaviour_Core>().Velocity;

                enemyPredictedPos = enemyPos + enemyVelocity * (Time.deltaTime * 50);
                
                desiredVelocity = (enemyPredictedPos - position).normalized;

                steering = desiredVelocity * moveSpeed - velocity;
                
                Bhv_Core.Velocity += steering * Time.deltaTime;
            }
        }

        #region Pursue Debug

        private void OnDrawGizmos()
        {
            if (Bhv_Core.CurrentState != ENTITY_STATE.Pursue) { return;}
            
            Vector3 position = transform.position;

            //Pursue Target
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