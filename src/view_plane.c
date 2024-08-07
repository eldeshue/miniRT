/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:15:47 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/07 21:40:40 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raytracer.h"
#include "math.h"

static t_FTMFLOAT4	vmult(t_FTMFLOAT4 *v, float m)
{
	return (ftmf4_set_vector(v->data[0] * m, v->data[1] * m,
			v->data[2] * m, v->data[3]));
}

/*
	asp : aspect ratio, width / height
	dx : delta x, gap between pixel of x direction
	dy : delta y, gap between pixel of y direction
	focal length : distance between camera and view plane
		fov is vertical fov
		tand(fov / 2) == tanf(fov / 2 * pi / 180) == asp / focal_len
*/
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
		= ftmf4_vadd(prsrc->cam.vpos, vmult(prsrc->cam.vtarget, focal_len));
	*left_up_point
		= ftmf4_vadd(ftmf4_vsub(left_up_point, vmult(del_x, asp)), del_y);
	del_x->data[0] *= dx;
	del_x->data[1] *= dx;
	del_x->data[2] *= dx;
	del_y->data[0] *= -dy;
	del_y->data[1] *= -dy;
	del_y->data[2] *= -dy;
}

/*
	calculate and set position of a pixel on the screen plane

	- all points are described in the world coordinates
*/
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
	t_FTMFLOAT4			vdelx;
	t_FTMFLOAT4			vdely;

	set_property(prsrc, &plu, &vdelx, &vdely);
	set_points(prsrc, &plu, &vdelx, &vdely);
}
