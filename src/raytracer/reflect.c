/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:40:42 by dogwak            #+#    #+#             */
/*   Updated: 2024/09/06 11:35:55 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raytracer.h"
#include "../light/light.h"
#include <math.h>

// check shadow
static int	is_shadowed(t_render_resource *prsrc,
							t_ray *pray_to_light,
							const float dist_to_light)
{
	t_hit	shadow_hit;

	pray_to_light->pstart = ftmf4_vadd(pray_to_light->pstart,
			vmult(&pray_to_light->ndir, 0.005f));
	shadow_hit = get_hit_per_ray(prsrc, pray_to_light);
	return (shadow_hit.pobj != NULL && shadow_hit.dist < dist_to_light);
}

static t_FTMFLOAT4	reflect_vector(t_FTMFLOAT4 lunit, t_FTMFLOAT4 nunit)
{
	t_FTMFLOAT4	common;
	t_FTMFLOAT4	not_common;

	common = vmult(&nunit, ftmf4_vdot(nunit, lunit));
	not_common = ftmf4_vsub(lunit, common);
	return (ftmf4_vsub(common, not_common));
}

static float	phong_reflect(t_ray *prtol, t_ray *pgaze,
								t_hit *phit)
{
	const float	diffuse_factor = ftmf4_vdot(prtol->ndir, phit->vnormal);
	const float	specular_factor = ftmf4_vdot(
			reflect_vector(prtol->ndir, phit->vnormal),
			vmult(&pgaze->ndir, -1));

	return (DIFFUSION_INTENSITY * diffuse_factor
		+ SPECULAR_INTENSITY
		* pow(specular_factor * (specular_factor > 0), SPECULAR_POWER));
}

static t_FTMFLOAT4	light_sum(t_render_resource *prsrc,
								t_ray *ray, t_hit *phit)
{
	t_FTMFLOAT4	result;
	t_ray		ray_to_light;
	t_light		*pl;
	size_t		idx;
	float		dist;

	result = vmult(&prsrc->amb_color, prsrc->amb_intens);
	idx = -1;
	while (++idx < prsrc->lights->size)
	{
		pl = *((t_light **)prsrc->lights->at(prsrc->lights, idx));
		ray_to_light.pstart = phit->ppos;
		ray_to_light.ndir = ftmf4_vsub(pl->ppos, phit->ppos);
		dist = ftmf4_vsize(&ray_to_light.ndir);
		ftmf4_vnormalize(&ray_to_light.ndir);
		if (!is_shadowed(prsrc, &ray_to_light, dist))
			result = ftmf4_vadd(result, vmult(&pl->color, pl->intensity
						* phong_reflect(&ray_to_light, ray, phit)));
	}
	clamp(&result);
	return (result);
}

// reflect
t_FTMFLOAT4	reflect_ray(t_render_resource *prsrc, t_ray *ray, t_hit hit)
{
	t_material const	*pm = &(((t_plane *)(hit.pobj))->m);
	t_FTMFLOAT4			result;

	result = light_sum(prsrc, ray, &hit);
	result.data[0] = result.data[0] * pm->obj_color.data[0] / 255.0f;
	result.data[1] = result.data[1] * pm->obj_color.data[1] / 255.0f;
	result.data[2] = result.data[2] * pm->obj_color.data[2] / 255.0f;
	return (result);
}
