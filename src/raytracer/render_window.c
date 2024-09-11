/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:40:07 by dogwak            #+#    #+#             */
/*   Updated: 2024/09/11 19:16:55 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "../ray/ray.h"
#include "../ft_graphics/ft_math/ft_math.h"

#include <stdio.h>

t_hit	get_hit_per_ray(t_render_resource *const prsrc,
								t_ray *const pgaze)
{
	size_t		idx;
	t_hit		result;
	t_hit		cur_hit;
	t_rt_obj	*pobj;

	idx = -1;
	result.dist = 2e9;
	result.pobj = NULL;
	while (++idx < prsrc->render_objects->size)
	{
		pobj = *((t_rt_obj **)prsrc->render_objects
				->at(prsrc->render_objects, idx));
		cur_hit = pobj->hit(pgaze, pobj->obj_ptr);
		if (cur_hit.dist > 0 && cur_hit.dist < result.dist)
			result = cur_hit;
	}
	return (result);
}

static t_FTCOLOR	get_color_pixel(t_render_resource *const prsrc,
										int row, int col)
{
	t_ray		gaze;
	t_FTMFLOAT4	color;
	t_FTCOLOR	result_color;

	gaze.pstart = prsrc->cam.vpos;
	gaze.ndir = ftmf4_vsub(
			prsrc->view_plane[row * prsrc->ftmlx.view_width + col],
			prsrc->cam.vpos);
	ftmf4_vnormalize(&gaze.ndir);
	color = trace_ray(prsrc, &gaze, get_hit_per_ray(prsrc, &gaze));
	result_color.r = color.data[0];
	result_color.g = color.data[1];
	result_color.b = color.data[2];
	result_color.t = color.data[3];
	return (result_color);
}

void	render_rt_window(t_render_resource *const prsrc)
{
	int			r;
	int			c;

	r = -1;
	while (++r < prsrc->ftmlx.view_height)
	{
		c = -1;
		while (++c < prsrc->ftmlx.view_width)
		{
			ft_render_pixel(&prsrc->ftmlx.rdr_tgt_img, c, r,
				get_color_pixel(prsrc, r, c));
		}
	}
	mlx_put_image_to_window(prsrc->ftmlx.hmlx,
		prsrc->ftmlx.hwin, prsrc->ftmlx.rdr_tgt_img.himg, 0, 0);
	mlx_loop(prsrc->ftmlx.hmlx);
}
