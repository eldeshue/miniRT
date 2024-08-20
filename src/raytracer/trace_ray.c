/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:07:22 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/20 15:33:54 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "../ray/ray.h"

t_FTMFLOAT4	trace_ray(const t_ray *ray, const t_hit hit)
{
	const t_FTMFLOAT4	base_color = {0.0f, 0.0f, 0.0f, 0.0f};
	t_material *const	m = &((t_plane *)(((t_rt_obj *)hit.pobj)->obj_ptr))->m;
	t_FTMFLOAT4			result;

	if (hit.pobj == NULL)
		return (base_color);
	result = vmult(&(m->amb_color), m->ka);
	ray++;	// tmp
	// TODO : Diffuse
	// TODO : Specular
	// TODO : shadow
	clamp(&result);
	return (result);
}
