using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class RegulateTimers : MonoBehaviour
{
    [SerializeField][Range(0, 10)] int DigitNumber;
    TMP_InputField input;
    private void Start()
    {
        input = gameObject.GetComponent<TMP_InputField>();
    }

    public void Limit_Timers()
    {
        TMP_InputField input = gameObject.GetComponent<TMP_InputField>();
        if (input.text.Length > DigitNumber)
        {
            input.text = "";
            for (int i = 0; i < DigitNumber; i++)
            {
                input.text += "9";
            }
        }
    }
}
