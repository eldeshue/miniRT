/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:40:42 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/22 12:24:47 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raytracer.h"

// check shadow
static int	is_shadowed(t_render_resource const *prsrc, const t_hit *hit)
{
	// creat ray toward light source

	// check collision, hit per ray

	// return bool value
}

static t_FTMFLOAT4	light_sum(t_render_resource const *prsrc,
								const t_ray *ray, const t_hit *hit)
{
	size_t		idx;

	idx = -1;
	while (++idx < prsrc->lights->size)
	{
		// check shadow
		if (!is_shadowed(prsrc, hit))
		{
			// diffusion
			// specular
		}
	}
}

// reflect
t_FTMFLOAT4	reflect_ray(t_render_resource const *prsrc,
							const t_ray *ray, t_hit hit)
{
	t_material const	*pm = &(((t_plane *)(hit.pobj))->m);
	t_FTMFLOAT4			result;

	result = vmult(&prsrc->amb_color, prsrc->amb_intens);
	result = ftmf4_vadd(result, light_sum(prsrc, ray, &hit));
	// absorb and reflect
}
