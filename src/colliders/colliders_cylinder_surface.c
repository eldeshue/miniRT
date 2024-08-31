/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   colliders_cylinder.c							   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/08/20 15:30:32 by dogwak			#+#	#+#			 */
/*   Updated: 2024/08/22 15:42:05 by hyeonwch		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "colliders.h"
#include "collider_obj_vars.h"
#include <math.h>
#include <stdio.h>

void	cy_solve_quadratic(t_cylinder_coll_vars *vars, t_ray *r,
							float a_dot, float c_dot)
{
	vars->a = ftmf4_vdot(r->ndir, r->ndir) - pow(a_dot, 2);
	vars->b = 2.0 * (ftmf4_vdot(vars->oc, r->ndir) - a_dot * c_dot);
	vars->c = ftmf4_vdot(vars->oc, vars->oc) - pow(c_dot, 2)
		- vars->radius * vars->radius;
	vars->discriminant = vars->b * vars->b - 4 * vars->a * vars->c;
	if (vars->a < EPSILON)
		vars->t = FLOAT_MAX;
	else if (vars->discriminant < 0)
		vars->t = FLOAT_MAX;
	else
	{
		vars->sqrt_disc = sqrt(vars->discriminant);
		vars->t1 = (-vars->b - vars->sqrt_disc) / (2.0 * vars->a);
		vars->t2 = (-vars->b + vars->sqrt_disc) / (2.0 * vars->a);
		vars->t = find_intersection_time(vars->t1, vars->t2);
		if (vars->t < EPSILON)
			vars->t = FLOAT_MAX;
	}
}

void	cy_coll_set_vars(t_cylinder_coll_vars *vars, t_ray *r, void *obj)
{
	float		a_dot;
	float		c_dot;
	float		radius;
	t_cylinder	*cylinder;
	t_FTMFLOAT4	top_to_bottom;

	vars->oc = ftmf4_vsub(r->pstart, cylinder->pcenter1);
	top_to_bottom = ftmf4_vsub(cylinder->pcenter2, cylinder->pcenter1);
	vars->h_unit = *ftmf4_vnormalize(&top_to_bottom);
	vars->radius = cylinder->radius;
	vars->pobj = obj;
	a_dot = ftmf4_vdot(r->ndir, vars->h_unit);
	c_dot = ftmf4_vdot(vars->oc, vars->h_unit);
	radius = vars->radius;
	cyl_solve_quadratic(vars, r, a_dot, c_dot);
	cylinder = (t_cylinder *)vars->pobj;
	vars->height_on_axis = ftmf4_vdot(vars->oc, vars->h_unit);
	vars->cylinder_axis = ftmf4_vsub(cylinder->pcenter2, cylinder->pcenter1);
	vars->cylinder_height = ftmf4_vsize(&vars->cylinder_axis);
}

void	cy_coll_set_surface_hit(t_hit *hit, t_ray *r, t_cylinder_coll_vars vars)
{
	t_cylinder	*cylinder;
	t_FTMFLOAT4	pqtrn;
	t_FTMFLOAT4	p_to_hit;

	cylinder = (t_cylinder *)vars.pobj;
	hit->dist = vars.t;
	hit->ppos = ray_at(r, vars.t);
	p_to_hit = ftmf4_vsub(hit->ppos, cylinder->pcenter1);
	if (vars.height_on_axis < 0 || vars.height_on_axis > vars.cylinder_height)
	{
		process_wrong_hit(hit);
		return ;
	}
	pqtrn = ftmf4_vsub(p_to_hit, vmult(&(vars.h_unit), vars.height_on_axis));
	hit->vnormal = *ftmf4_vnormalize(&pqtrn);
	hit->pobj = vars.pobj;
}

void	cy_check_coll_surface(t_cylinder_coll_vars *vars, t_ray *r,
								t_hit *hit_surface, void *obj)
{
	cy_coll_set_vars(&vars, r, obj);
	init_hit(hit_surface);
	if (vars->discriminant >= 0)
	{
		if (vars->t == FLOAT_MAX)
			process_wrong_hit(hit_surface);
		else
			cy_coll_set_surface_hit(hit_surface, (t_ray *)r, *vars);
	}
}
