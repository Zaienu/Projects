namespace Helper
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
    
    #if UNITY_EDITOR
    
    public enum DATA_TYPE
    {
        ETAG,
        ELAYER,
        OTAG,
        OLAYER,
    }
    
    public enum OBJECT_TYPE
    {
        ENTITY,
        OBSTACLE,
    }

    public enum CALLBACK_TYPE
    {
        CURRENT,
        NEXT,
    }
    
    #endif
    
}