using Behaviours;
using UnityEngine;

public static class UnityExtensions
{
    public static Vector3 Get_Pos(this GameObject _gameObject)
    {
        return _gameObject.transform.position;
    }

    public static Vector3 Get_Pos(this Transform _transform)
    {
        return _transform.position;
    }

    #region Entity Stats Getters
    public static float Get_CurrentHealth(this Master_Behaviour _master_Behaviour)
    {
        return _master_Behaviour.Stats[(int)ENTITY_STATS.Current_Health];
    }

    public static float Get_MaxHealth(this Master_Behaviour _master_Behaviour)
    {
        return _master_Behaviour.Stats[(int)ENTITY_STATS.Max_Health];
    }

    public static float Get_AttackDamage(this Master_Behaviour _master_Behaviour)
    {
        return _master_Behaviour.Stats[(int)ENTITY_STATS.Attack_Damage];
    }

    public static float Get_AttackSpeed(this Master_Behaviour _master_Behaviour)
    {
        return _master_Behaviour.Stats[(int)ENTITY_STATS.Attack_Speed];
    }

    public static float Get_MoveSpeed(this Master_Behaviour _master_Behaviour)
    {
        return _master_Behaviour.Stats[(int)ENTITY_STATS.Move_Speed];
    }
    #endregion

    public static CLOSEST Get_Closest(this Master_Behaviour _master_Behaviour, ENTITY_TYPES _type)
    {
        return _master_Behaviour.Closest[(int)_type];
    }

    public static Vector3 Pos(this CLOSEST _closest)
    {
        return _closest.entity.transform.position;
    }
    
}
