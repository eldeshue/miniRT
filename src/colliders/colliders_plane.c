#include "colliders.h"
#include "ft_math.h"
#include "raytracer.h"
#include "collider_obj_vars.h"

/**
 * type: plane
typedef struct s_plane
{
	t_material	m; // material
	t_FTMFLOAT4	pcenter; // center point
	t_FTMFLOAT4	vnormal; // normal vector
}				t_plane;
typedef struct s_ray
{
	t_FTMFLOAT4	pstart;
	t_FTMFLOAT4	ndir;
}				t_ray;
*/


t_hit		collider_plane(const t_ray *r, void *obj)
{
	t_plane		*plane;
	t_FTMFLOAT4	oc;
	t_FTMFLOAT4	ndir;
	float		denom;
	float		t;
	t_hit	hit;

	plane = (t_plane *)obj;
	oc = ftmf4_vsub(plane->pcenter, r->pstart);
	ndir = *ftmf4_vnormalize(&plane->vnormal);
	denom = ftmf4_vdot(ndir, r->ndir);
	if (fabs(denom) > 0.0001)
	{
		t = ftmf4_qdot(oc, ndir) / denom;
		if (t > 0)
		{
			hit.dist = t;
			hit.ppos = ray_at(r, t);
			hit.vnormal = plane->vnormal;
			hit.pobj = obj;
		}
	}
	return (hit);
}
