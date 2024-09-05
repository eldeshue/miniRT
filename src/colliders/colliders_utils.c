/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:09 by dogwak            #+#    #+#             */
/*   Updated: 2024/09/03 15:22:06 by dogwak           ###   ########.fr       */
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

t_FTMFLOAT4 vscale(t_FTMFLOAT4 v, float s) {
	t_FTMFLOAT4	result;

	result.data[0] = v.data[0] * s;
	result.data[1] = v.data[1] * s;
	result.data[2] = v.data[2] * s;
	result.data[3] = v.data[3] * s;
	return (result);
}

void	set_face_normal(t_hit *hit, t_ray *r, t_FTMFLOAT4 outward_normal)
{
	int	front_face;

	front_face = ftmf4_vdot(r->ndir, outward_normal) < 0;
	if (front_face)
		hit->vnormal = outward_normal;
	else
		hit->vnormal = vscale(outward_normal, -1);
}
