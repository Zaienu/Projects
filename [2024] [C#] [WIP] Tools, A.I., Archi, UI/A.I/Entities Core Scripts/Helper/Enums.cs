using UnityEngine;

namespace Entities_Core_Scripts
{
    public enum STATE
    {
        Previous,
        Current,
        Next,
    }

    public enum ENTITY_TYPES
    {
        Allies,
        Neutral,
        Enemies,
    }

    public enum ENTITY_STATS
    {
        Current_Health,
        Max_Health,
        Attack_Damage,
        Attack_Speed,
        Move_Speed,
    }

    public enum ENTITY_STATE
    {
        Death,
        Hit,
        Flee,
        Evade,
        Group,
        Pursue,
        Seek,
        Avoidance,
        Wander,
        Idle,
    }

    public enum SENSES
    {
        Hearing,
        Sight,
    }
}