/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:09 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/31 17:49:24 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colliders.h"
#include "../raytracer/raytracer.h"

t_FTMFLOAT4	ray_at(t_ray *ray, float t)
{
	return (ftmf4_vadd(ray->pstart, vmult(&ray->ndir, t)));
}

void	init_hit(t_hit *hit)
{
	hit->dist = -1;
	hit->pobj = NULL;
	hit->ppos = ftmf4_set_vector(0, 0, 0, 0);
	hit->vnormal = ftmf4_set_vector(0, 0, 0, 0);
}

void	process_wrong_hit(t_hit *hit)
{
	hit->dist = FLOAT_MAX;
	hit->pobj = NULL;
}

void	set_face_normal(t_hit *hit, t_ray *r, t_FTMFLOAT4 outward_normal)
{
	int front_face;

	front_face = ftmf4_vdot(r->ndir, outward_normal) < 0;
	if (front_face)
		hit->vnormal = outward_normal;
	else
		hit->vnormal = vmult(&outward_normal, -1);
}

float	find_intersection_time(float t1, float t2)
{
	if (t1 > EPSILON && t2 > EPSILON)
	{
		if (t1 < t2)
			return (t1);
		else
			return (t2);
	}
	else if ((t1 < EPSILON && t2 > EPSILON) || (t1 > EPSILON && t2 < EPSILON))
	{
		if (t1 < EPSILON)
			return (t2);
		else
			return (t1);
	}
	else
		return (FLOAT_MAX);
}
