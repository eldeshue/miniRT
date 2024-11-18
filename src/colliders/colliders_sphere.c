/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:32 by dogwak            #+#    #+#             */
/*   Updated: 2024/09/13 14:48:00 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colliders.h"
#include "collider_obj_vars.h"
#include <math.h>

static void	sphere_coll_set_vars(t_shpere_coll_vars *vars, t_FTMFLOAT4 oc,
				t_FTMFLOAT4 ndir, float radius)
{
	vars->a = ftmf4_vdot(ndir, ndir);
	vars->b = 2.0 * ftmf4_vdot(oc, ndir);
	vars->c = ftmf4_vdot(oc, oc) - radius * radius;
	vars->discriminant = vars->b * vars->b - 4 * vars->a * vars->c;
	if (vars->a == 0)
		vars->t = FLOAT_MAX;
	else if (vars->discriminant < 0)
		vars->t = FLOAT_MAX;
	else
	{
		vars->sqrt_disc = sqrt(vars->discriminant);
		vars->t1 = (-vars->b - vars->sqrt_disc) / (2.0 * vars->a);
		vars->t2 = (-vars->b + vars->sqrt_disc) / (2.0 * vars->a);
		vars->t = find_intersection_time(vars->t1, vars->t2);
	}
}

static void	sphere_coll_set_hit(t_hit *hit, t_ray *r, t_sphere *sphere,
								t_shpere_coll_vars vars)
{
	t_FTMFLOAT4	pqtrn;

	hit->dist = vars.t;
	hit->ppos = ray_at(r, vars.t);
	pqtrn = ftmf4_vsub(hit->ppos, sphere->pcenter);
	hit->vnormal = *ftmf4_vnormalize(&pqtrn);
}

t_hit	collider_sphere(const t_ray *r, void *obj)
{
	t_sphere			*sphere;
	t_hit				hit;
	t_FTMFLOAT4			oc;
	t_shpere_coll_vars	vars;

	init_hit(&hit);
	hit.pobj = obj;
	sphere = (t_sphere *)obj;
	oc = ftmf4_vsub(r->pstart, sphere->pcenter);
	sphere_coll_set_vars(&vars, oc, r->ndir, sphere->radius);
	if (vars.t != FLOAT_MAX)
		sphere_coll_set_hit(&hit, (t_ray *)r, sphere, vars);
	else
		process_wrong_hit(&hit);
	return (hit);
}
