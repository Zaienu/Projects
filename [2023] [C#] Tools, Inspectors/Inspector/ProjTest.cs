using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace Proj
{
    public class ProjTest : MonoBehaviour
    {
        [SerializeField] GameObject Proj;
        [SerializeField] GameObject Origin;
        [SerializeField] GameObject TargetGO;
        [SerializeField] bool Higher = false;
        // Start is called before the first frame update
        void Start()
        {

        }

        // Update is called once per frame
        void Update()
        {
            if(Input.GetKeyDown(KeyCode.Space))
            {
                Higher = !Higher;
            }
            if (Input.GetMouseButtonDown(0))
            {
                Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
                RaycastHit hit;
                if (Physics.Raycast(ray, out hit, 100))
                {
                    Instantiate(TargetGO, hit.point, Quaternion.identity);
                    if (Higher)
                    {
                        hit.point = new Vector3(hit.point.x, hit.point.y + 5.0f, hit.point.z);
                    }
                    Instantiate(Proj, Origin.transform.position, Quaternion.identity).GetComponent<Projectile>().Initialize(0, Origin.transform.position, hit.point, null, 8, null);
                }
            }
        }
    }

}