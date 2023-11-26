using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScrollBarInit : MonoBehaviour
{
    void Start()
    {
        gameObject.GetComponent<Scrollbar>().value = 0.9999f;
    }
}
