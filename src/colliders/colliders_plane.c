/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:24 by dogwak            #+#    #+#             */
/*   Updated: 2024/09/05 14:53:38 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colliders.h"
#include "collider_obj_vars.h"
#include <math.h>

void	plane_coll_set_vars(t_plane_coll_vars *vars,
				t_FTMFLOAT4 from_gaze_to_plane,
						t_FTMFLOAT4 dir_of_gaze, t_FTMFLOAT4 normal_of_plane)
{
	vars->denom = ftmf4_vdot(dir_of_gaze, normal_of_plane);
	if ((vars->denom) < -EPSILON)
		vars->t = ftmf4_vdot(from_gaze_to_plane, normal_of_plane) / vars->denom;
	else
		vars->t = -1.0f;
}

void	plane_coll_set_hit(t_hit *hit, t_ray *r,
			t_plane *plane, t_plane_coll_vars vars)
{
	hit->dist = vars.t;
	hit->ppos = ray_at(r, vars.t);
	hit->vnormal = plane->vnormal;
//	set_face_normal(hit, r, plane->vnormal);	// why???
	hit->pobj = plane;
}

t_hit	collider_plane(const t_ray *r, void *obj)
{
	t_plane				*plane;
	t_hit				hit;
	t_FTMFLOAT4			p0_minus_o;
	t_plane_coll_vars	vars;

	plane = (t_plane *)obj;
	p0_minus_o = ftmf4_vsub(plane->pcenter, r->pstart);
	plane_coll_set_vars(&vars, p0_minus_o, r->ndir, plane->vnormal);
	if (vars.t > 0 && ftmf4_vdot(p0_minus_o, plane->vnormal) < 0)
		plane_coll_set_hit(&hit, (t_ray *)r, plane, vars);
	else
		hit.dist = -1.0f;
	return (hit);
}
