using System.Collections.Generic;
using UnityEngine;
using Interfaces;

enum PROJPS
{
    TRAIL,
    IMPACT,
}

enum AXIS
{
    X,
    Y,
    Z,
}

public enum PROJTYPE
{
    HUMAN_BULLET,
    ALIEN_BULLET,
    HUMAN_EXPLOSION,
    ALIEN_EXPLOSION,
    HUMAN_HEAL,
    ALIEN_HEAL,
    FLAME_THROWER,
    MINI_GUN,
}

public class Projectile : MonoBehaviour
{

    //NEEDS TO BE REORDERED
    //Default Inspector
    [Header("Projectile Data")]
    [SerializeField] PROJTYPE Type;
    List<GameObject> ParticleSystems;
    [SerializeField] GameObject Trail;
    [SerializeField] GameObject Impact;


    [Header("Trajectory Data")]
    [SerializeField] bool InvertKey;
    [SerializeField] int List;
    [SerializeField] int KeyID;
    [SerializeField] AnimationCurve CurveX;
    [SerializeField] AnimationCurve CurveY;
    [SerializeField] AnimationCurve CurveZ;

    [SerializeField] ProjectileFX ProjFX;
    [SerializeField] float duration;

    public IDamageable owner;

    bool hasHit;

    float damage;
    float TBI;
    float inversibleValue;

    float[] origin;
    float[] target;

    LayerMask TargetMask;
    LayerMask Layer;

    Vector3 vecOrigin;
    Vector3 vecTarget;
    Vector3 prev;

    GameObject projectilePool;

    AnimationCurve[] Curves;

    public void Awake()
    {
        ParticleSystems = new List<GameObject>(){Trail, Impact};
    }

    public void Initialize(float _damage, Vector3 _vecOrigin, Vector3 _vecTarget, IDamageable _owner, int _layer
        , GameObject _projectilePool)
    {
        ParticleSystems[(int)PROJPS.TRAIL].SetActive(true);
        damage = _damage;
        vecOrigin = _vecOrigin;
        vecTarget = _vecTarget;
        owner = _owner;
        layer = _layer;
        projectilePool = _projectilePool;
        InitializeTrajectory();
    }

    private void InitializeTrajectory()
    {
        //Preparing Data
        Curves = new AnimationCurve[] { CurveX, CurveY, CurveZ };
        TBI = 0.0f;
        inversibleValue = Curves[(int)AXIS.Y].keys[KeyID].value;
        origin = new float[] { vecOrigin.x, vecOrigin.y, vecOrigin.z };
        target = new float[] { vecTarget.x, vecTarget.y, vecTarget.z };
    }

    private void Update()
    {
        //Inverting the curve at the specified key
        if (InvertKey)
        {
            Keyframe[] keys = Curves[(int)AXIS.Y].keys;
            keys[KeyID].value = origin[(int)AXIS.Y] > target[(int)AXIS.Y] ? -Mathf.Abs(inversibleValue) : Mathf.Abs(inversibleValue);
            Curves[(int)AXIS.Y].keys = keys;
        }

        //Computing Data
        if (TBI <= duration)
        {
            if (hasHit)
            { return; }
            TBI += Time.deltaTime;
            float percent = Mathf.Clamp01(TBI / duration);
            float[] coords = new float[6];
            //Calculating the coordinates of the current and previous positions
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < Curves.Length; j++)
                {
                    float curvePercent = Curves[j].Evaluate(Mathf.Clamp01(percent - i * TBI / 10));
                    coords[j + i * 3] = Mathf.LerpUnclamped(origin[j], target[j], curvePercent);
                }
            }
            //Directing the projectile
            transform.position = new Vector3(coords[(int)AXIS.X], coords[(int)AXIS.Y], coords[(int)AXIS.Z]);
            prev = new Vector3(coords[3], coords[4], coords[5]);
            Vector3 direction = (transform.position - prev).normalized;
            transform.forward = direction;
        }
        else
        {
            OnDestroyProj(false);
        }

    }

    private void CheckHit(Collider _other)
    {
        if (_other.GetComponent<IDamageable>() == owner)
        {
            return;
        }
        
        bool isHealing = Type == PROJTYPE.HUMAN_HEAL || Type == PROJTYPE.ALIEN_HEAL;

        bool enemyHeal = _other.gameObject.layer == 9 && gameObject.layer == 6;            //EnemyUnit vs EnemyProj
        bool allyHeal = _other.gameObject.layer == 8 && gameObject.layer == 7;                 //AllyUnit vs AllyProj

        bool enemyHit = _other.gameObject.layer == 9 && gameObject.layer == 7;               //EnemyUnit vs AllyProj
        bool allyHit = _other.gameObject.layer == 8 && gameObject.layer == 6;                    //AllyUnit vs EnemyProj

        bool serverHit = _other.gameObject.layer == 16 && gameObject.layer == 6;              //Server vs EnemyProj
        bool complexHit = _other.gameObject.layer == 14 || _other.gameObject.layer == 11;    //GroundHit or WallHit
        
        if (isHealing)
        {
            if (enemyHeal || allyHeal)
            {
                OnDestroyProj(true, _other);
            }
        }

        if (enemyHit || allyHit || serverHit || complexHit)
        {
            OnDestroyProj(true, _other);
        }

    }

    private void OnTriggerEnter(Collider _other)
    {
        if (Type == PROJTYPE.HUMAN_EXPLOSION || Type == PROJTYPE.ALIEN_EXPLOSION)
        {
            if (!_other.isTrigger && !hasHit)
            {
                CheckHit(_other);
                hasHit = true;
            }
        }
        else
        {
            if (!_other.isTrigger)
            {
                CheckHit(_other);
            }
        }
    }

    private void OnDestroyProj(bool _damage, Collider _other = null)
    {
        hasHit = true;
        ProjFX.PostEffects(_damage, _other);
        bool isST = Type is PROJTYPE.HUMAN_BULLET or PROJTYPE.ALIEN_BULLET;
        Invoke(nameof(ProjectileGoBackToPool), isST ? 0.1f : 3f);
    }

    private void ProjectileGoBackToPool()
    {
        hasHit = false;
        ParticleSystems.ForEach(x => x.SetActive(false));
        transform.position = Vector3.zero;
        transform.SetParent(projectilePool.transform);
        SoundsManager.Stop(SoundsName.Explosion_Battle, gameObject, FMOD.Studio.STOP_MODE.ALLOWFADEOUT);
        gameObject.SetActive(false);
    }

    //Getters
    public PROJTYPE type
    {
        get { return Type; }
    }

    public float damages
    {
        get { return damage; }
    }

    public List<GameObject> ParticlesSys
    {
        get { return ParticleSystems; }
    }

    public int layer
    {
        get { return Layer; }
        set
        {
            Layer = value;
            TargetMask = Layer == LayerMask.NameToLayer("Allies") ?
            LayerMask.NameToLayer("Allies_Proj") : LayerMask.NameToLayer("Enemies_Proj");
            gameObject.layer = TargetMask;
        }
    }

    public LayerMask layerMask
    {
        get
        {

            #region Booleans
            bool isAlienAttack = Type == PROJTYPE.ALIEN_EXPLOSION || Type == PROJTYPE.ALIEN_BULLET;
            bool isHumanAttack = Type == PROJTYPE.HUMAN_EXPLOSION || Type == PROJTYPE.HUMAN_BULLET;
            bool isAlienHeal = Type == PROJTYPE.ALIEN_HEAL;
            bool isHumanHeal = Type == PROJTYPE.HUMAN_HEAL;
            #endregion

            //Attacks
            if (isAlienAttack)
            { return 1 << LayerMask.NameToLayer("Allies") | 1 << LayerMask.NameToLayer("Objectif"); }
            if (isHumanAttack)
            { return 1 << LayerMask.NameToLayer("Enemies"); }
            //Heals
            if (isAlienHeal)
            { return 1 << LayerMask.NameToLayer("Enemies");}
            if (isHumanHeal)
            { return 1 << LayerMask.NameToLayer("Allies");}
            
            return 0;
        }
    }

    public Vector3 Position
    {
        get { return transform.position; }
    }

    public float[] Origin
    {
        get { return origin; }
    }

}