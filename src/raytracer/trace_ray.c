/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:07:22 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/21 17:23:53 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "../ray/ray.h"

t_FTMFLOAT4	trace_ray(const t_ray *ray, t_hit hit)
{
	const t_FTMFLOAT4	base_color = {0.0f, 0.0f, 0.0f, 0.0f};
	t_material 			*pm;
	t_FTMFLOAT4			result;

	if (hit.pobj == NULL)
		return (base_color);
	pm = &(((t_plane *)(hit.pobj))->m);
	result = vmult(&(pm->obj_color), pm->ka);
	ray++;	// tmp
	// TODO : Diffuse
	// TODO : Specular
	// TODO : shadow
	clamp(&result);
	return (result);
}
