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

t_hit	collider_cylinder(const t_ray *r, void *obj)
{
	t_hit					hit_surface;
	t_hit					hit_cap;
	t_cylinder_coll_vars	vars;

	cy_check_coll_surface(&vars, (t_ray *)r, &hit_surface, obj);
	cy_check_coll_cap(&vars, (t_ray *)r, &hit_cap);
	if (hit_surface.dist < hit_cap.dist)
		return (hit_surface);
	return (hit_cap);
}
