using System;
using Helper;
using UnityEngine;

namespace Entities_Core_Scripts
{

    public class Targetting_Core : MonoBehaviour
    {
        [SerializeField] private bool canHear;
        [SerializeField] private float hearingRange;
        [SerializeField] private bool canSee;
        [SerializeField] private float seeingRange;
        [SerializeField] private bool canXRay;
        [SerializeField] private float xRayRange;

        [SerializeField] public string Entities_Layer;
        private GameObject senses;
        private SphereCollider[] senses_Colliders = new SphereCollider[3];

        void Create_SenseCollider(string _name, float _radius)
        {
            //Configuring Sense_System
            GameObject sense = new GameObject();
            sense.transform.parent = senses.transform;
            sense.name = _name;
            LayerMask excludedLayers = ~ (1 << LayerMask.NameToLayer(Entities_Layer));

            //Configuring Sense_Collider
            SphereCollider collider = sense.AddComponent<SphereCollider>();
            collider.radius = _radius / 2;
            collider.isTrigger = true;
            collider.excludeLayers = excludedLayers;
            collider.includeLayers = ~excludedLayers;
        }

        private void Start()
        {
            //Configure Senses GameObject that will contain the senses.
            senses = new GameObject();
            senses.transform.parent = transform;
            senses.name = "Senses";

            if (canHear)
            {
                Create_SenseCollider("Hearing_System", hearingRange);
                senses_Colliders[(int)SENSES.Hearing] = gameObject.Contains("Hearing_System").GetComponent<SphereCollider>();
            }

            if (canSee)
            {
                Create_SenseCollider("Sight_System", seeingRange);
                senses_Colliders[(int)SENSES.Sight] = gameObject.Contains("Seeing_System").GetComponent<SphereCollider>();
            }
        }
    }
}