using UnityEngine;
using Interfaces;
using System.Collections;

public class ProjectileFX : MonoBehaviour
{
    private Projectile proj;
    [SerializeField] private float ExplosionRadius;

    private void Start()
    {
        proj = GetComponent<Projectile>();
    }
    public void PostEffects(bool _damage, Collider _other)
    {
        proj.ParticlesSys[(int)PROJPS.IMPACT].SetActive(true);

        if (proj.type == PROJTYPE.ALIEN_HEAL || proj.type == PROJTYPE.HUMAN_HEAL)
        {
            proj.ParticlesSys[(int)PROJPS.IMPACT].transform.eulerAngles = new Vector3(90, 0, 0);
        }

        switch (proj.type)
        {
            case PROJTYPE.HUMAN_BULLET:
            case PROJTYPE.MINI_GUN:
            case PROJTYPE.ALIEN_BULLET: Bullet(_damage, _other); break;

            case PROJTYPE.HUMAN_EXPLOSION:
            case PROJTYPE.FLAME_THROWER:
            case PROJTYPE.ALIEN_EXPLOSION: Explosion(_damage, proj.Position); break;

            case PROJTYPE.HUMAN_HEAL:
            case PROJTYPE.ALIEN_HEAL: StartCoroutine(Heal(_damage, proj.Position)); break;
        }
    }

    private void Update()
    {
        if (proj.type == PROJTYPE.ALIEN_HEAL)
        {
            Vector3 pos = proj.ParticlesSys[(int)PROJPS.IMPACT].transform.position;
            proj.ParticlesSys[(int)PROJPS.IMPACT].transform.position = new Vector3(pos.x, 0.5f, pos.z);
        }
    }

    private void Bullet(bool _damage, Collider _other)
    {
        if (_damage)
        {
            _other.GetComponent<IDamageable>()?.Hurt(proj.damages, proj.owner);
        }
    }

    private void Explosion(bool _damage, Vector3 _pos)
    {
        SoundsManager.Play(SoundsName.Explosion_Battle, proj.gameObject);
        SoundsManager.SetDistanceEffect(SoundsName.Explosion_Battle, proj.gameObject);

        Collider[] colliders = Physics.OverlapSphere(_pos, ExplosionRadius, proj.layerMask);
        if (_damage)
        {
            foreach (Collider collider in colliders)
            {
                collider.GetComponent<IDamageable>().Hurt(proj.damages, proj.owner);
            }
        }
    }

    private IEnumerator Heal(bool _damage, Vector3 _pos)
    {
        float TBI = 0.0f;
        float duration = 4.0f;

        yield return new WaitForSeconds(0.2f); //Wait for heal

        while (TBI < duration)
        {
            Collider[] colliders = Physics.OverlapSphere(_pos, ExplosionRadius, proj.layerMask);
            if (_damage)
            {
                foreach (Collider collider in colliders)
                {
                    collider.GetComponent<IDamageable>().Hurt(-proj.damages);
                }
            }
            yield return new WaitForSeconds(0.5f);
            TBI += 0.5f;
        }
    }

}
