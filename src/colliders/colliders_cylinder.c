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

void	cy_init_coll_var(t_cylinder_coll_vars *vars, void *obj)
{
	vars->a = 0;
	vars->b = 0;
	vars->c = 0;
	vars->discriminant = 0;
	vars->sqrt_disc = 0;
	vars->t1 = 0;
	vars->t2 = 0;
	vars->t = 0;
	vars->radius = 0;
	vars->pobj = obj;
	vars->oc = ftmf4_set_vector(0, 0, 0, 0);
	vars->h_unit = ftmf4_set_vector(0, 0, 0, 0);
	vars->cylinder_axis = ftmf4_set_vector(0, 0, 0, 0);
	vars->cap_center = ftmf4_set_vector(0, 0, 0, 0);
	vars->cap_normal = ftmf4_set_vector(0, 0, 0, 0);
	vars->height_on_axis = 0;
	vars->cylinder_height = 0;
	vars->denom = 0;
}

t_hit	collider_cylinder(const t_ray *r, void *obj)
{
	t_hit					hit_surface;
	t_hit					hit_cap;
	t_cylinder_coll_vars	vars;

	init_hit(&hit_surface);
	init_hit(&hit_cap);
	cy_init_coll_var(&vars, obj);
	cy_check_coll_surface(&vars, (t_ray *)r, &hit_surface);
	cy_check_coll_cap(&vars, (t_ray *)r, &hit_cap);
	if (hit_surface.dist < hit_cap.dist)
		return (hit_surface);
	return (hit_cap);
}
