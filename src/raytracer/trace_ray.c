/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:07:22 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/14 15:56:30 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "../ray/ray.h"
#include "../hit/hit.h"


t_FTMFLOAT4	trace_ray(const t_ray *ray, const t_hit hit)
{
	const t_FTMFLOAT4	base_color = {0.0f, 0.0f, 0.0f, 0.0f};
	const t_material	*m = &((t_plane *)(hit.pobj->obj_ptr))->m;
	t_FTMFLOAT4			result;

	if (hit.pobj == NULL)
		return (base_color);
	result = vmult(&(m->amb_color), m->ka);
	// TODO : Diffuse
	// TODO : Specular
	// TODO : shadow
	clamp(&result);
	return (result);
}
