/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:15:47 by dogwak            #+#    #+#             */
/*   Updated: 2024/09/11 19:17:26 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include <math.h>

static void	set_property(t_render_resource *const prsrc,
							t_FTMFLOAT4 *left_up_point,
							t_FTMFLOAT4 *del_x,
							t_FTMFLOAT4 *del_y)
{
	const float	asp
		= (float)(prsrc->ftmlx.view_width) / prsrc->ftmlx.view_height;
	const float	dx = 2.0f * asp / prsrc->ftmlx.view_width;
	const float	dy = 2.0f / prsrc->ftmlx.view_height;
	const float	focal_len = asp / tanf((prsrc->fov / 2) * M_PI / 180.0f);

	*del_x = ftmf4_vcross(prsrc->cam.vup, prsrc->cam.vtarget);
	*del_y = ftmf4_vcross(prsrc->cam.vtarget, *del_x);
	ftmf4_vnormalize(del_x);
	ftmf4_vnormalize(del_y);
	*left_up_point
		= ftmf4_vadd(prsrc->cam.vpos, vmult(&prsrc->cam.vtarget, focal_len));
	*left_up_point
		= ftmf4_vadd(ftmf4_vsub(*left_up_point, vmult(del_x, asp)), *del_y);
	del_x->data[0] *= dx;
	del_x->data[1] *= dx;
	del_x->data[2] *= dx;
	del_y->data[0] *= -dy;
	del_y->data[1] *= -dy;
	del_y->data[2] *= -dy;
	*left_up_point
		= ftmf4_vadd(*left_up_point,
			ftmf4_vadd(vmult(del_x, 0.5f), vmult(del_y, 0.5f)));
}

static void	set_points(t_render_resource *const prsrc,
							t_FTMFLOAT4 *left_up_point,
							t_FTMFLOAT4 *del_x,
							t_FTMFLOAT4 *del_y)
{
	int	r;
	int	c;

	r = -1;
	while (++r < prsrc->ftmlx.view_height)
	{
		c = -1;
		while (++c < prsrc->ftmlx.view_width)
		{
			prsrc->view_plane[r * prsrc->ftmlx.view_width + c]
				= ftmf4_vadd(*left_up_point,
					ftmf4_vadd(vmult(del_y, r), vmult(del_x, c)));
		}
	}
}

void	set_view_plane(t_render_resource *const prsrc)
{
	t_FTMFLOAT4			plu;
	t_FTMFLOAT4			vdx;
	t_FTMFLOAT4			vdy;

	ftmf4_vnormalize(&prsrc->cam.vtarget);
	if (fabs(ftmf4_vdot(prsrc->cam.vtarget, prsrc->cam.vup)) == 1.0f)
		prsrc->cam.vup.data[0] += 0.0001f;
	set_property(prsrc, &plu, &vdx, &vdy);
	set_points(prsrc, &plu, &vdx, &vdy);
}
