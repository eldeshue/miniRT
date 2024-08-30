/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:07:22 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/28 19:23:00 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "../ray/ray.h"

t_FTMFLOAT4	trace_ray(t_render_resource *prsrc,
							t_ray *ray, t_hit hit)
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
