#include "colliders.h"
#include "raytracer.h"

t_FTMFLOAT4 ray_at(const t_ray *ray, float t)
{
	return (ftmf4_qadd(ray->pstart, vmult(&ray->ndir, t)));
}

