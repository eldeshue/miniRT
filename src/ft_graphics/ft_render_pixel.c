/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:52:03 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/20 17:57:24 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graphics.h"
#include <unistd.h>

void	ft_clear_rbuffer(t_FTMLX *pmlx)
{
	int	idx;

	idx = -1;
	while (++idx < pmlx->view_height * pmlx->view_width)
	{
		*(int *)(pmlx->rdr_tgt_img.pbuffer + idx * (pmlx->rdr_tgt_img.bpp / 8))
			= (unsigned int)(0);
	}
}

void	ft_render_pixel(t_FTIMAGE *pimg, int x, int y, t_FTCOLOR color)
{
	char	*dst;

	dst = pimg->pbuffer + (y * pimg->buffer_width + x * (pimg->bpp / 8));
	*(t_FTCOLOR *)dst = color;
}
