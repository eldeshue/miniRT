/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:43:59 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/20 17:33:41 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_graphics.h"

static int	ft_set_image(t_FTMLX *this)
{
	t_FTIMAGE	*this_image;

	this_image = &(this->rdr_tgt_img);
	this_image->himg = mlx_new_image(this->hmlx,
			this->view_width, this->view_height);
	if (this_image->himg == NULL)
		return (0);
	this_image->pbuffer = mlx_get_data_addr(
			this_image->himg,
			&(this_image->bpp),
			&(this_image->buffer_width),
			&(this_image->endian));
	if (this_image->pbuffer == NULL)
		return (0);
	return (1);
}

int	ft_set_mlx(t_FTMLX *this,
			int width, int height, const char *pwindow_name)
{
	this->hmlx = mlx_init();
	if (this->hmlx == NULL)
		return (0);
	this->hwin
		= mlx_new_window(this->hmlx, width, height, (char *)pwindow_name);
	if (this->hwin == NULL)
	{
		return (0);
	}
	this->view_width = width;
	this->view_height = height;
	if (!ft_set_image(this))
	{
		ft_del_mlx(this);
		return (0);
	}
	return (1);
}

void	ft_del_mlx(t_FTMLX *this)
{
	if (this->rdr_tgt_img.himg != NULL)
		mlx_destroy_image(this->hmlx, this->rdr_tgt_img.himg);
	if (this->hwin != NULL)
		mlx_destroy_window(this->hmlx, this->hwin);
}
