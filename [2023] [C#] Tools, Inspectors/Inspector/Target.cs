using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Target : MonoBehaviour
{
    float timer = 0.0f;

    private void Update()
    {
        timer += Time.deltaTime;
        if (timer>=2.0f)
        {
            Destroy(gameObject);
        }
    }
}
