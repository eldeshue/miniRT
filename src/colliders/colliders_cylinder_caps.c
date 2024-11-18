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

float	cy_compute_cap_t(t_ray *r, t_FTMFLOAT4	center, t_FTMFLOAT4	h_unit)
{
	t_FTMFLOAT4	p0_minus_o;
	float		denom;
	float		t;

	p0_minus_o = ftmf4_vsub(center, r->pstart);
	denom = ftmf4_vdot(r->ndir, h_unit);
	if (fabs(denom) < EPSILON)
		return (FLOAT_MAX);
	t = ftmf4_vdot(p0_minus_o, h_unit) / denom;
	return (t);
}

void	cy_set_coll_cap_hit(t_hit *hit, t_ray *r, float t,
									t_cylinder_coll_vars vars)
{
	t_FTMFLOAT4	hit_pos;
	t_FTMFLOAT4	cp;

	if (t == FLOAT_MAX)
	{
		hit->dist = t;
		hit->pobj = vars.pobj;
		return ;
	}
	hit_pos = ray_at(r, t);
	cp = ftmf4_vsub(vars.cap_center, hit_pos);
	if (ftmf4_vdot(cp, cp) <= pow(vars.radius, 2))
	{
		hit->dist = t;
		hit->ppos = hit_pos;
		hit->pobj = vars.pobj;
		hit->vnormal = vars.cap_normal;
		set_face_normal(hit, r, vars.cap_normal);
	}
	else
		process_wrong_hit(hit);
}

void	cy_set_cap_var_top(t_cylinder_coll_vars *vars, t_ray *r,
				t_hit *hit_cap, float t)
{
	const t_cylinder	*cylinder = (t_cylinder *)vars->pobj;

	vars->cap_center = cylinder->pcenter2;
	vars->cap_normal = vars->h_unit;
	cy_set_coll_cap_hit(hit_cap, r, t, *vars);
}

void	cy_set_cap_var_bottom(t_cylinder_coll_vars *vars, t_ray *r,
				t_hit *hit_cap, float t)
{
	const t_cylinder	*cylinder = (t_cylinder *)vars->pobj;

	vars->cap_center = cylinder->pcenter1;
	vars->cap_normal = vmult(&(vars->h_unit), -1);
	cy_set_coll_cap_hit(hit_cap, r, t, *vars);
}

void	cy_check_coll_cap(t_cylinder_coll_vars *vars, t_ray *r, t_hit *hit_cap)
{
	const t_cylinder	*cylinder = (t_cylinder *)vars->pobj;
	float				t_top;
	float				t_bot;

	t_top = cy_compute_cap_t(r, cylinder->pcenter2, vars->h_unit);
	t_bot = cy_compute_cap_t(r, cylinder->pcenter1, vmult(&(vars->h_unit), -1));
	if (t_top != FLOAT_MAX && t_bot != FLOAT_MAX)
	{
		if (t_top < t_bot)
			cy_set_cap_var_top(vars, r, hit_cap, t_top);
		else
			cy_set_cap_var_bottom(vars, r, hit_cap, t_bot);
	}
	else if (t_top != FLOAT_MAX)
		cy_set_cap_var_top(vars, r, hit_cap, t_top);
	else if (t_bot != FLOAT_MAX)
		cy_set_cap_var_bottom(vars, r, hit_cap, t_bot);
}
