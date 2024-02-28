using System;
using System.Collections.Generic;
using Entities_Core_Scripts;
using Helper;
using Obstacles_Core_Scripts;
using UnityEngine;
using UnityEngine.AI;
using Object = UnityEngine.Object;

namespace Editor.Tools_Scripts.Setup.Object_Setup
{
    [CreateAssetMenu(fileName = "ObjectManager", menuName = "I.A.I.T./ObjectManager", order = 1)]
    public class ObjectManager : ScriptableObject
    {
        [SerializeField] public GameObject OM_Prefab;
        [SerializeField] public GameObject EM_Prefab;

        [SerializeField] public string Entities_Layer = new string("");
        [SerializeField] public string Obstacles_Layer = new string("");

        [SerializeField] public List<string> Entities_Tags = new List<string>();
        [SerializeField] public List<string> Obstacles_Tags = new List<string>();

        private SetupData[] tags = {new(), new()};
        private SetupData[] layers = {new(), new()};
        
        private List<System.Type> Obstacles_Scripts = new List<Type>()
        {
            typeof(Obstacle_Core)
        };

        private List<System.Type> Entities_Scripts = new List<Type>()
        {
            typeof(Entity_Core),
            typeof(Behaviour_Core),
            typeof(NavMeshAgent),
            typeof(Targetting_Core),
            typeof(Rigidbody)
        };

        //NEEDS TO BE MOVED TO THE ENTITY CONFIGURER
        private List<System.Type> Senses_Scripts = new List<Type>()
        {
            typeof(Hearing),
            typeof(Sight)
        };

        private GameObject sensesFolder;

        private string[] senseLabels = new string[2]
        {
            "Hearing",
            "Sight"
        };

        private float[] senseRanges = new float[2]
        {
            3,
            4
        };

        private float sightFOV;
        
        void Create_SenseCollider(SENSES _sense)
        {
            //Creating a sense
            GameObject sense = new GameObject();
            
            //Setting up the sense
            sense.Set_Parent(sensesFolder);
            sense.name = senseLabels[(int)_sense];
            sense.AddComponent(Senses_Scripts[(int)_sense]);
            
            //Determining the Layers it shouldn't evaluate
            LayerMask excludedLayers = ~ (1 << LayerMask.NameToLayer(Entities_Layer));

            //Creating the collider
            SphereCollider collider = sense.AddComponent<SphereCollider>();
            
            //Setting up the collider
            collider.radius = senseRanges[(int)_sense] / 2;
            collider.isTrigger = true;
            collider.excludeLayers = excludedLayers;
            collider.includeLayers = ~excludedLayers;
        }

        private void AssignScriptsTo_Entities(List<GameObject> _entities)
        {
            foreach (GameObject entity in _entities)
            {
                foreach (System.Type script in Entities_Scripts)
                {
                    entity.TryAddComponent(script);
                }

                //Displace the following to the Entity Configurer
                sensesFolder = new GameObject();
                sensesFolder.name = "Senses";
                sensesFolder.Set_Parent(entity);

                Create_SenseCollider(SENSES.Hearing);
                Create_SenseCollider(SENSES.Sight);
                
                if (entity.TryGetComponent<Targetting_Core>(out var T_Core))
                {
                    T_Core.Entities_Layer = Entities_Layer;
                }
            }
        }

        private void AssignScriptsTo_Obstacles(List<GameObject> _obstacles)
        {
            foreach (GameObject obstacle in _obstacles)
            {
                foreach (System.Type script in Obstacles_Scripts)
                {
                    obstacle.TryAddComponent(script);
                }

                if (!ObstacleManager.Obstacle_List.Contains(obstacle))
                {
                    ObstacleManager.Obstacle_List.Add(obstacle);
                }
            }
        }
        
        private void AssignToLayer<T>(string _layer) where T : MonoBehaviour
        {
            T[] entities = Object.FindObjectsOfType<T>();

            foreach (T entity in entities)
            {
                entity.gameObject.layer = LayerMask.NameToLayer(_layer);
            }
        }

        #region Object Configuration

        public void Configure_Obstacles()
        {
            //Search every gameObject having any of the tags entered by the client
            List<GameObject> obstacles = new List<GameObject>();
            foreach (string tag in Obstacles_Tags)
            {
                obstacles.AddRange(GameObject.FindGameObjectsWithTag(tag));
            }

            AssignScriptsTo_Obstacles(obstacles);
            AssignToLayer<Obstacle_Core>(Obstacles_Layer);
        }

        public void Configure_Entities()
        {
            //Search every gameObject having any of the tags entered by the client
            List<GameObject> entities = new List<GameObject>();
            foreach (string tag in Entities_Tags)
            {
                entities.AddRange(GameObject.FindGameObjectsWithTag(tag));
            }
            
            AssignScriptsTo_Entities(entities);
            AssignToLayer<Entity_Core>(Entities_Layer);
        }

        #endregion
        
        public SetupData[] Tags
        {
            get => tags;
            set => tags = value;
        }
        
        public SetupData[] Layers
        {
            get => layers;
            set => layers = value;
        }
    }
}