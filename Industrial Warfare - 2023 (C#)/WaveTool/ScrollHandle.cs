using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScrollHandle : MonoBehaviour
{
    public void Update()
    {
            RectTransform RectTR = gameObject.GetComponent<RectTransform>();
            RectTR.anchoredPosition = new Vector2(0.5f, 0.5f);
            RectTR.sizeDelta = new Vector2(60, 30);
        }
}
