using System;
using Entities_Core_Scripts;
using Helper;
using UnityEngine;

namespace Behaviours
{

    public class Flee_Behaviour : MonoBehaviour
    {
        //Master
        Behaviour_Core Bhv_Core;
        
        #region Client's Parameters
        
        [SerializeField] public float ReqHealth = 10f;
        [SerializeField] public float ReqRadius = 10f;
        
        #endregion
        
        #region Private
        
        //Steering
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
                throw new Exception("Flee_Behaviour ERROR : The Component \"Master_Behaviour\" hasn't been found");
            }
            #endregion

            #region Subscription Management

            //Subscribe the function to the "Master_Behaviour" 's Update Delegate when the component is enabled.
            if (!enabled) { return; }
            Bhv_Core.Behaviour_Update -= Flee;
            Bhv_Core.Behaviour_Update += Flee;

            #endregion
            
        }

        private void Start()
        {
            //Init Master Data
            velocity = Bhv_Core.Velocity;
            currentHealth = Bhv_Core.Get_CurrentHealth();
            moveSpeed = Bhv_Core.Get_MoveSpeed();
        }

        void Flee()
        {
            //If flee from allies, enemies and neutral what to do ? -> LATER
            
            //Local Typedefs
            closestEnemy = Bhv_Core.Get_Closest(ENTITY_TYPES.Enemies);
            enemyPos = closestEnemy.Pos();
            
            //Entrance Condition
            if (currentHealth <= ReqHealth && closestEnemy.distance <= ReqRadius)
            {
                //Updating the State
                Bhv_Core.Change_State(ENTITY_STATE.Flee);
                //Flee Steering Behaviour
                Bhv_Core.Targets[(int)STATE.Current] = enemyPos;
                //Desired Velocity
                desiredVelocity = (transform.position - enemyPos).normalized;
                //Limit Speed
                steering = desiredVelocity * moveSpeed - velocity;
                //Apply Steering
                Bhv_Core.Velocity += steering * Time.deltaTime;
            }

            ////SEEK + ARRIVAL

            //Vector3 desiredVelocity = enemyPos - transform.position;
            //float distance = desiredVelocity.magnitude;
            //if (distance < smoothDist)
            //{
            //    desiredVelocity = Vector3.Normalize(desiredVelocity) * moveSpeed * (distance / smoothDist);
            //}
            //else
            //{
            //    desiredVelocity = Vector3.Normalize(desiredVelocity) * moveSpeed;
            //}
            //Vector3 steering = desiredVelocity * moveSpeed - velocity;
            //velocity += steering * Time.deltaTime;
            
        }

        #region Flee Debug

        private void OnDrawGizmos()
        {
            if (Bhv_Core.CurrentState != ENTITY_STATE.Flee) { return;}
            
            Vector3 position = transform.position;
            
            //Flee Circle & Flee Target
            Gizmos.color = Color.red;
            Gizmos.DrawWireSphere(position, ReqRadius);
            Gizmos.DrawLine(position, closestEnemy.Pos());
            //Desired Velocity
            Gizmos.color = Color.blue;
            Gizmos.DrawLine(position, position + desiredVelocity);
            //Steering
            Gizmos.color = Color.yellow;
            Gizmos.DrawLine(position, position + steering);
        }

        #endregion
        
    }

}
