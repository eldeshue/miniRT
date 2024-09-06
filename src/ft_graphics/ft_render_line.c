/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:45:53 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/26 14:10:23 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graphics.h"
#include <math.h>

static void	upper_bresenham(t_FTMLX *pmlx, int *start, int *end, int *pparam)
{
	int			x;
	int			y;
	int			f;
	const int	df1 = 2 * pparam[0];
	const int	df2 = df1 - 2 * pparam[1];

	x = start[0];
	y = start[1] - 1;
	f = 2 * pparam[0] - pparam[1];
	while (++y < end[1])
	{
		ft_render_pixel(&(pmlx->rdr_tgt_img), x, y,
			ftg_interpolate_color(start[2], end[2],
				y - start[1], end[1] - y));
		if (f < 0)
			f += df1;
		else
		{
			x += 1 - 2 * (start[0] > end[0]);
			f += df2;
		}
	}
}

static void	lower_bresenham(t_FTMLX *pmlx, int *start, int *end, int *pparam)
{
	int			x;
	int			y;
	int			f;
	const int	df1 = 2 * pparam[1];
	const int	df2 = df1 - 2 * pparam[0];

	x = start[0] - 1;
	y = start[1];
	f = 2 * pparam[1] - pparam[0];
	while (++x <= end[0])
	{
		ft_render_pixel(&(pmlx->rdr_tgt_img), x, y,
			ftg_interpolate_color(start[2], end[2],
				x - start[0], end[0] - x));
		if (f < 0)
			f += df1;
		else
		{
			y += 1 - 2 * (start[1] > end[1]);
			f += df2;
		}
	}
}

void	ft_render_line(t_FTMLX *pmlx, t_FTGVERTEX *p1, t_FTGVERTEX *p2)
{
	int		param_arr[8];

	param_arr[0] = roundf(p1->pos.data[0]);
	param_arr[1] = roundf(p1->pos.data[1]);
	param_arr[2] = *(int *)(&(p1->color));
	param_arr[3] = roundf(p2->pos.data[0]);
	param_arr[4] = roundf(p2->pos.data[1]);
	param_arr[5] = *(int *)(&(p2->color));
	param_arr[6] = roundf(fabsf(p2->pos.data[0] - p1->pos.data[0]));
	param_arr[7] = roundf(fabsf(p2->pos.data[1] - p1->pos.data[1]));
	if (param_arr[6] < param_arr[7])
	{
		if (param_arr[1] <= param_arr[4])
			upper_bresenham(pmlx, param_arr, param_arr + 3, param_arr + 6);
		upper_bresenham(pmlx, param_arr + 3, param_arr, param_arr + 6);
	}
	else
	{
		if (param_arr[0] <= param_arr[3])
			lower_bresenham(pmlx, param_arr, param_arr + 3, param_arr + 6);
		lower_bresenham(pmlx, param_arr + 3, param_arr, param_arr + 6);
	}
}
