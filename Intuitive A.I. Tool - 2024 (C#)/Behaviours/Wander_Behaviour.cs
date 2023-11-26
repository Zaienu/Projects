using System;
using UnityEngine;
using Quaternion = UnityEngine.Quaternion;
using Random = UnityEngine.Random;
using Vector3 = UnityEngine.Vector3;

namespace Behaviours
{
    public class Wander_Behaviour : MonoBehaviour
    {
        //Master
        private Master_Behaviour master_Behaviour;

        #region Client's Parameters

        [SerializeField] public float WanderRadius = 2f;
        [SerializeField] public float Angle = 0f;
        [SerializeField] public float AngleStep = 20f;

        #endregion

        #region Private

        //Steering
        private Vector3 wanderPoint;
        private Vector3 displacement;
        private Vector3 desiredVelocity;
        private Vector3 steering;

        //Master's Data
        private Vector3 velocity;
        private float moveSpeed;

        #endregion

        void Awake()
        {
            #region Exceptions Management

            if (!TryGetComponent(out master_Behaviour))
            {
                throw new Exception("Wander_Behaviour ERROR : The Component \"Master_Behaviour\" hasn't been found");
            }

            #endregion

            #region Subscription Management

            //Subscribe the function to the "Master_Behaviour" 's Update Delegate when the component is enabled.
            if (!enabled) { return; }
            master_Behaviour.Behaviour_Update -= Wander;
            master_Behaviour.Behaviour_Update += Wander;

            #endregion
        }

        private void Start()
        {
            //Init Master Data
            velocity = master_Behaviour.Velocity;
            moveSpeed = master_Behaviour.Get_MoveSpeed();
        }

        void Wander()
        {
            
            master_Behaviour.Change_State(ENTITY_STATE.Wander);
            
            //Local Typedefs
            Vector3 position = transform.position;
            Vector3 forward = transform.forward;

            //Entrance Condition
            if (master_Behaviour.States[(int)STATE.Current] == ENTITY_STATE.Wander)
            {
                //Center of the Wander Circle in front of the Entity
                wanderPoint = transform.position + forward * 4;
                //Changing the orientation of the Displacement Force
                Angle += Random.value * AngleStep - AngleStep * 0.5f;
                displacement = wanderPoint + Quaternion.Euler(0, Angle, 0) * forward * WanderRadius;
                //Desired Velocity
                desiredVelocity = (displacement - position).normalized;
                //Limit Speed
                steering = desiredVelocity * moveSpeed - velocity;
                //Apply Steering
                master_Behaviour.Velocity += steering * Time.deltaTime;
            }
        }

        #region Wander Debug

        private void OnDrawGizmos()
        {
            if (master_Behaviour.CurrentState != ENTITY_STATE.Wander) { return;}
            
            Vector3 position = transform.position;
            
            //Wander Circle
            Gizmos.color = Color.red;
            Gizmos.DrawWireSphere(wanderPoint, WanderRadius);
            Gizmos.DrawLine(position, wanderPoint);
            //Displacement
            Gizmos.color = Color.blue;
            Gizmos.DrawLine(wanderPoint, displacement);
            //Entity to Displacement
            Gizmos.color = Color.green;
            Gizmos.DrawLine(position, displacement);
            //Wander Circle, Displacement point
            Gizmos.color = Color.yellow;
            Gizmos.DrawSphere(displacement, 0.3f);
        }

        #endregion
    }
}