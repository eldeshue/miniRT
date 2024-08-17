#include "colliders.h"
#include "../raytracer/raytracer.h"

t_FTMFLOAT4 ray_at(t_ray *ray, float t)
{
	return (ftmf4_qadd(ray->pstart, vmult(&ray->ndir, t)));
}
