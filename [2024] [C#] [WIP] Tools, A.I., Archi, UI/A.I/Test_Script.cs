using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using UnityEngine.AI;

[ExecuteInEditMode]
public class Test_Script : MonoBehaviour
{
    GameObject[] Entities;
    void Start()
    {

    }


    void Update()
    {
        //Debug.Log("hey");
        //Entities = GameObject.FindGameObjectsWithTag("Test");
        //if (Entities.Length > 0)
        //{
        //    foreach (GameObject go in Entities)
        //    {
        //        if (!go.TryGetComponent<Test_Script>(out Test_Script script))
        //        {
        //            Debug.Log("Component not found on : " + go.name + "Adding the component ..");
        //            go.AddComponent<Test_Script>();
        //        }
        //        if (go.GetComponent<Test_Script>())
        //        {
        //            Debug.Log("Component Added to : ");
        //        }
        //        Debug.Log(go.name);
        //    }
        //}
        //NavMesh.GetAreaFromName();
    }
}
