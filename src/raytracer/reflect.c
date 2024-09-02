/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:40:42 by dogwak            #+#    #+#             */
/*   Updated: 2024/09/02 19:11:31 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raytracer.h"
#include "../light/light.h"
#include <math.h>

// check shadow
static int	is_shadowed(t_render_resource *prsrc,
							t_ray *pray_to_light)
{
	pray_to_light->pstart = ftmf4_vadd(pray_to_light->pstart,
			vmult(&pray_to_light->ndir, 0.005f));
	return (get_hit_per_ray(prsrc, pray_to_light).pobj != NULL);
}

static t_FTMFLOAT4	reflect_vector(float angle, t_FTMFLOAT4 v,
									t_FTMFLOAT4 s)
{
	const t_FTMFLOAT4	common = vmult(&s, angle);
	const t_FTMFLOAT4	not_common = ftmf4_vadd(v, common);

	return (ftmf4_vadd(common, not_common));
}

static t_FTMFLOAT4	light_sum(t_render_resource *prsrc,
								t_ray *ray, const t_hit *phit)
{
	t_FTMFLOAT4	result;
	t_ray		ray_to_light;
	t_light		*pl;
	size_t		idx;
	float		cos[2];

	result = vmult(&prsrc->amb_color, prsrc->amb_intens);
	idx = -1;
	while (++idx < prsrc->lights->size)
	{
		pl = *((t_light **)prsrc->lights->at(prsrc->lights, idx));
		ray_to_light.pstart = phit->ppos;
		ray_to_light.ndir = ftmf4_vsub(pl->ppos, phit->ppos);
		ftmf4_vnormalize(&ray_to_light.ndir);
		if (!is_shadowed(prsrc, &ray_to_light))
		{
			cos[0] = (ftmf4_vdot(ray_to_light.ndir, phit->vnormal));
			cos[1] = (ftmf4_vdot(reflect_vector(cos[0], ray->ndir,
							phit->vnormal), ray_to_light.ndir));
			result = ftmf4_vadd(result, vmult(&pl->color, pl->intensity
						* (cos[0] + pow(cos[1], SPECULAR_POWER))));
		}
	}
	clamp(&result);
	return (result);
}

// reflect
t_FTMFLOAT4	reflect_ray(t_render_resource *prsrc,
							t_ray *ray, t_hit hit)
{
	t_material const	*pm = &(((t_plane *)(hit.pobj))->m);
	t_FTMFLOAT4			result;

	result = light_sum(prsrc, ray, &hit);
	result.data[0] = result.data[0] * pm->obj_color.data[0] / 255.0f;
	result.data[1] = result.data[1] * pm->obj_color.data[1] / 255.0f;
	result.data[2] = result.data[2] * pm->obj_color.data[2] / 255.0f;
	return (result);
}
