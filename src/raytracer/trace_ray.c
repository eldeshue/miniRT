/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:07:22 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/17 16:47:00 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "../ray/ray.h"
#include "../hit/hit.h"


t_FTMFLOAT4	trace_ray(const t_ray *ray, t_hit hit)
{
	(void)ray;
	const t_plane		*plane = (t_plane *)hit.pobj;
	const t_FTMFLOAT4	base_color = {0.0f, 0.0f, 0.0f, 0.0f};
	const t_material	*m = &(plane->m);
	t_FTMFLOAT4			result;

	if (hit.pobj == NULL)
		return (base_color);
	result = vmult((t_FTMFLOAT4 *)&(m->amb_color), m->ka);
	// TODO : Diffuse
	// TODO : Specular
	// TODO : shadow
	clamp(&result);
	return (result);
}
