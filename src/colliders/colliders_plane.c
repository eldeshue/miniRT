/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:24 by dogwak            #+#    #+#             */
/*   Updated: 2024/09/03 16:14:52 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colliders.h"
#include "collider_obj_vars.h"
#include <math.h>
static void	plane_coll_set_vars(t_plane_coll_vars *vars, t_FTMFLOAT4 p0_minus_o,
								t_FTMFLOAT4 ndir, t_FTMFLOAT4 vnormal)
{
	vars->denom = ftmf4_vdot(ndir, vnormal);
	if (fabs(vars->denom) < EPSILON)
		vars->t = FLOAT_MAX;
	else
		vars->t = -1.0f;
}

static void	plane_coll_set_hit(t_hit *hit, t_ray *r, t_plane *plane,
								t_plane_coll_vars vars)
{
	hit->dist = vars.t;
	hit->ppos = ray_at(r, vars.t);
	hit->vnormal = plane->vnormal;
	set_face_normal(hit, r, plane->vnormal);
}

t_hit	collider_plane(const t_ray *r, void *obj)
{
	t_plane				*plane;
	t_hit				hit;
	t_FTMFLOAT4			p0_minus_o;
	t_plane_coll_vars	vars;

	hit.pobj = obj;
	plane = (t_plane *)obj;
	p0_minus_o = ftmf4_vsub(plane->pcenter, r->pstart);
	plane_coll_set_vars(&vars, p0_minus_o, r->ndir, plane->vnormal);
	if (vars.t == FLOAT_MAX)
		process_wrong_hit(&hit);
	else
		plane_coll_set_hit(&hit, (t_ray *)r, plane, vars);
	return (hit);
}
