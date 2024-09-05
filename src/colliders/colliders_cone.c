/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:29:56 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/09/05 16:50:56 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colliders.h"
#include "collider_obj_vars.h"
#include <math.h>
#include <stdio.h>

void	cone_coll_set_vars(t_cone_coll_vars *vars, t_cone *cone, t_ray *r)
{
	float		a_dot;
	float		c_dot;

	vars->oc = ftmf4_vsub(r->pstart, cone->pvertex);
	vars->cone_axis = ftmf4_vsub(cone->pvertex, cone->pcenter);
	vars->cone_height = ftmf4_vsize(&vars->cone_axis);
	vars->m = pow(cone->radius / ftmf4_vsize(&vars->cone_axis), 2);
	a_dot = ftmf4_vdot(r->ndir, vars->h_unit);
	c_dot = ftmf4_vdot(vars->oc, vars->h_unit);
	vars->a = ftmf4_vdot(r->ndir, r->ndir) - (vars->m + 1) * pow(a_dot, 2);
	vars->b = 2.0 * (ftmf4_vdot(vars->oc, r->ndir)
			- (vars->m + 1) * a_dot * c_dot);
	vars->c = ftmf4_vdot(vars->oc, vars->oc) - (vars->m + 1) * pow(c_dot, 2);
	vars->discriminant = pow(vars->b, 2) - 4 * vars->a * vars->c;
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

void	co_check_coll_cap(t_hit *hit, t_cone_coll_vars *var, t_ray *r)
{
	t_FTMFLOAT4	bottom_center;
	t_FTMFLOAT4	hit_pos;
	t_FTMFLOAT4	bottomsub;
	float		projection_on_axis;
	float		t_bottom;

	projection_on_axis = ftmf4_vdot(var->oc, var->h_unit);
	if (projection_on_axis < 0)
	{
		bottom_center = ((t_cone *)var->pobj)->pcenter;
		t_bottom = ftmf4_vdot(ftmf4_vsub(bottom_center, r->pstart), var->h_unit)
			/ ftmf4_vdot(r->ndir, var->h_unit);
		hit_pos = ray_at((t_ray *)r, t_bottom);
		bottomsub = ftmf4_vsub(hit_pos, bottom_center);
		if (ftmf4_vsize(&bottomsub) <= ((t_cone *)var->pobj)->radius)
		{
			hit->dist = t_bottom;
			hit->ppos = hit_pos;
			hit->vnormal = vmult(&var->h_unit, -1);
			hit->pobj = var->pobj;
			return ;
		}
	}
	process_wrong_hit(hit);
}

void	co_check_coll_surface(t_hit *hit, t_cone_coll_vars *vars, t_ray *r)
{
	t_FTMFLOAT4			hv;
	float				vdot_hv_cv;
	float				size_hv;
	float				tmp_cos;
	t_FTMFLOAT4			center_to_hit;

	hit->pobj = vars->pobj;
	hit->dist = vars->t;
	hit->ppos = ray_at(r, vars->t);
	hv = ftmf4_vsub(hit->ppos, ((t_cone *)vars->pobj)->pvertex);
	vdot_hv_cv = ftmf4_vdot(hv, vars->cone_axis);
	size_hv = ftmf4_vsize(&hv);
	tmp_cos = size_hv / vdot_hv_cv / vars->cone_height / size_hv;
	hit->vnormal = ftmf4_vadd(vmult(&(vars->h_unit), tmp_cos), hv);
	ftmf4_vnormalize(&hit->vnormal);
	if (hit->dist != FLOAT_MAX)
	{
		center_to_hit = ftmf4_vsub(hit->ppos, ((t_cone *)vars->pobj)->pcenter);
		if (ftmf4_vdot(center_to_hit, vars->cone_axis) < 0
			|| vars->cone_height < ftmf4_vsize(&center_to_hit))
			process_wrong_hit(hit);
	}
	else
		process_wrong_hit(hit);
}

void	init_coll_vars(t_cone_coll_vars *vars)
{
	vars->a = 0;
	vars->b = 0;
	vars->c = 0;
	vars->discriminant = 0;
	vars->sqrt_disc = 0;
	vars->t1 = 0;
	vars->t2 = 0;
	vars->t = 0;
	vars->m = 0;
	vars->oc = ftmf4_set_vector(0, 0, 0, 0);
	vars->cv = ftmf4_set_vector(0, 0, 0, 0);
	vars->cone_axis = ftmf4_set_vector(0, 0, 0, 0);
	vars->h_unit = ftmf4_set_vector(0, 0, 0, 0);
	vars->height_on_axis = 0;
	vars->cone_height = 0;
	vars->pobj = NULL;
}

t_hit	collider_cone(const t_ray *r, void *obj)
{
	t_hit				hit_surface;
	t_hit				hit_cap;
	t_cone_coll_vars	vars;

	init_hit(&hit_surface);
	init_hit(&hit_cap);
	init_coll_vars(&vars);
	vars.h_unit = ftmf4_vsub(((t_cone *)obj)->pvertex,
			((t_cone *)obj)->pcenter);
	ftmf4_vnormalize(&vars.h_unit);
	vars.pobj = obj;
	//
	cone_coll_set_vars(&vars, (t_cone *)obj, (t_ray *)r);
	if (vars.t != FLOAT_MAX)
		co_check_coll_surface(&hit_surface, &vars, (t_ray *)r);
	co_check_coll_cap(&hit_cap, &vars, (t_ray *)r);
	if (hit_surface.dist < hit_cap.dist)
		return (hit_surface);
	return (hit_cap);
}
