#include "colliders.h"
#include "ft_math.h"
#include "raytracer.h"

void    sphere_coll_set_vars(t_shpere_coll_vars *vars, t_FTMFLOAT4 oc, t_FTMFLOAT4 ndir, float radius)
{
    vars->a = ftmf4_qsize(ndir);
    vars->b = 2.0 * ftmf4_qsize(vmult(&ndir, ftmf4_qdot(oc, ndir)));
    vars->c = ftmf4_qsize(oc) - radius * radius;
    vars->discriminant = vars->b * vars->b - 4 * vars->a * vars->c;
}

float find_intersection_time(float t1, float t2)
{
    if (t1 > 0 && t2 > 0)  // 둘 다 양수인 경우
    {
        if (t1 < t2)
            return (t1);  // 가까운 지점 반환
        else
            return (t2);  // 가까운 지점 반환
    }
    else if ((t1 < 0 && t2 > 0) || (t1 > 0 && t2 < 0))  // 하나는 음수, 하나는 양수인 경우
    {
        if (t1 < 0)
            return (t2);  // 양수인 지점 반환
        else
            return (t1);  // 양수인 지점 반환
    }
    else  // 둘 다 음수인 경우
    {
        if (fabs(t1) < fabs(t2))
            return (t1);  // 가까운 지점 반환
        else
            return (t2);  // 가까운 지점 반환
    }
}

void    sphere_coll_compute_t(t_shpere_coll_vars *vars)
{
    vars->sqrt_disc = sqrt(vars->discriminant);
    vars->t1 = (-vars->b - vars->sqrt_disc) / (2.0 * vars->a);
    vars->t2 = (-vars->b + vars->sqrt_disc) / (2.0 * vars->a);
    vars->t = find_intersection_time(vars->t1, vars->t2);
}

void    sphere_coll_set_hit(t_hit *hit, t_ray *r, t_sphere *sphere, t_shpere_coll_vars vars, void *obj)
{
    t_FTMFLOAT4 pqtrn;

    hit->dist = vars.t;
    hit->ppos = ray_at(r, vars.t);
    pqtrn = ftmf4_qsub(hit->ppos, sphere->pcenter);
    hit->vnormal = ftmf4_qnormalize(&pqtrn);
    hit->pobj = obj;
}

t_hit collider_sphere(const t_ray *r, void *obj)
{
    t_sphere *sphere;
    t_hit hit;
    t_FTMFLOAT4 oc;
    t_shpere_coll_vars vars;

    sphere = (t_sphere *)obj;
    oc = ftmf4_qsub(r->pstart, sphere->pcenter);
    sphere_coll_set_vars(&vars, oc, r->ndir, sphere->radius);
    if (vars.discriminant < 0)
        hit.dist = -1.0;
    else
    {
        sphere_coll_compute_t(&vars);
        if (vars.t == -1.0)
            hit.dist = -1.0;
        else
            sphere_coll_set_hit(&hit, r, sphere, vars, obj);
    }
    return (hit);
}
