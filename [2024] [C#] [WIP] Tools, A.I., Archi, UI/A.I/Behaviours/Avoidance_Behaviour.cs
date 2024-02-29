using System;
using Entities_Core_Scripts;
using Helper;
using UnityEngine;
using Quaternion = UnityEngine.Quaternion;
using Random = UnityEngine.Random;
using Vector3 = UnityEngine.Vector3;

namespace Behaviours
{
    public class Avoidance_Behaviour : MonoBehaviour
    {
        //Master
        private Behaviour_Core Bhv_Core;

        #region Client's Parameters

        [SerializeField] public float MaxSight = 10f;
        [SerializeField] public LayerMask AvoidanceTargets;
        [SerializeField] public float ReqHealth = 10f;

        #endregion

        #region Private

        //Steering
        private Vector3 ahead;
        private Vector3 halfAhead;
        private Vector3 desiredVelocity;
        private Vector3 steering;

        //Master's Data
        private CLOSEST closestEnemy;
        private Vector3 enemyPos;
        private Vector3 velocity;
        private float currentHealth;
        private float moveSpeed;
        
        //Typedefs
        private Vector3 position;

        #endregion

        void Awake()
        {
            #region Exceptions Management

            if (!TryGetComponent(out Bhv_Core))
            {
                throw new Exception("Evade_Behaviour ERROR : The Component \"Master_Behaviour\" hasn't been found");
            }

            #endregion

            #region Subscription Management

            //Subscribe the function to the "Master_Behaviour" 's Update Delegate when the component is enabled.
            if (!enabled) { return; }
            Bhv_Core.Behaviour_Update -= Avoidance;
            Bhv_Core.Behaviour_Update += Avoidance;

            #endregion
        }

        private void Start()
        {
            //Init Master Data
            velocity = Bhv_Core.Velocity;
            currentHealth = Bhv_Core.Get_CurrentHealth();
            moveSpeed = Bhv_Core.Get_MoveSpeed();
        }

        private bool RayCasting()
        {

            RaycastHit aheadRay;
            RaycastHit halfAheadRay;
                
            Physics.Raycast(position, velocity, out aheadRay, ahead.magnitude, AvoidanceTargets);
            Physics.Raycast(position, velocity, out halfAheadRay, halfAhead.magnitude, AvoidanceTargets);
            
            return true;
            
        }

        void Avoidance()
        {
            //Local Typedefs
            position = transform.position;
            
            closestEnemy = Bhv_Core.Get_Closest(ENTITY_TYPES.Enemies);
            enemyPos = closestEnemy.Pos();
            
            //possible refactor
            
            //On_Enter_Behaviour();
            
            //Entrance Condition
            
                // Debug.Log((enemyPos - transform.position).magnitude);
                
                Bhv_Core.Change_State(ENTITY_STATE.Avoidance);

                ahead = position + velocity.normalized * MaxSight;

                halfAhead = ahead * 0.5f;

                //May be needed to slow this
                if (RayCasting())
                {
                    
                }

                // master_Behaviour.Targets[(int)STATE.Current] = enemyPos;
                //
                // enemyVelocity = closestEnemy.entity.GetComponent<Master_Behaviour>().Velocity;
                //
                // enemyPredictedPos = enemyPos + enemyVelocity * (Time.deltaTime * 50);
                //
                // desiredVelocity = (position - enemyPredictedPos).normalized;
                //
                // steering = desiredVelocity * moveSpeed - velocity;
                //
                // master_Behaviour.Velocity += steering * Time.deltaTime;
                
                //On_Exit_Behaviour();
            }
            
            

        #region Avoidance Debug

        private void OnDrawGizmos()
        {
            if (Bhv_Core.CurrentState != ENTITY_STATE.Evade) { return;}
            
            Vector3 position = transform.position;

            // //Evade Target
            // Gizmos.DrawWireSphere(position, DetectionRange);
            // Gizmos.color = Color.red;
            // Gizmos.DrawSphere(enemyPredictedPos, 0.5f);
            // Gizmos.DrawLine(position, enemyPredictedPos);
            // //Enemy Movement
            // Gizmos.color = Color.blue;
            // Gizmos.DrawSphere(enemyPos, 0.5f);
            // Gizmos.DrawLine(enemyPos, enemyPredictedPos);
            // //Entity to Displacement
            // Gizmos.color = Color.green;
            // Gizmos.DrawLine(position, position + desiredVelocity);
        }

        #endregion
        
    }
    
}