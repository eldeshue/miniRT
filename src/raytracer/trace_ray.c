/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:07:22 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/22 15:59:36 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "../ray/ray.h"

t_FTMFLOAT4	trace_ray(t_render_resource const *prsrc,
							const t_ray *ray, t_hit hit)
{
	const t_FTMFLOAT4	base_color = {0.0f, 0.0f, 0.0f, 0.0f};

	if (hit.pobj != NULL)
	{
		// phong reflection
		return (reflect_ray(prsrc, ray, hit));
	}
	else
		return (base_color);
}
