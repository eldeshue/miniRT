/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graphics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:15:35 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/26 14:09:33 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GRAPHICS_H
# define FT_GRAPHICS_H

# include "ft_geo.h"
# include "./mlx/mlx.h"
# include "./ft_math/ft_math.h"

// object handle
// mlx, window, etc...
typedef void*	t_handle;

/* ----------------- image object ----------------------- */
// randering target object for mlx
typedef struct s_FTIMAGE
{
	t_handle	himg;
	char		*pbuffer;
	int			bpp;
	int			buffer_width;
	int			endian;
}				t_FTIMAGE;

/* ----------------- mlx object ------------------------- */
// mlx object that holds everything needed to use mlx api
typedef struct s_FTMLX
{
	t_handle	hmlx;
	t_handle	hwin;
	int			view_width;
	int			view_height;
	t_FTIMAGE	rdr_tgt_img;
}				t_FTMLX;

int		ft_set_mlx(t_FTMLX *this,
			int width, int height, const char *pwindow_name);
void	ft_del_mlx(t_FTMLX *this);

/* --------------- camera object ----------------------- */
// pass it to the ftmf44_set_view
typedef struct s_FTCAMERA
{
	t_FTMFLOAT4	vpos;
	t_FTMFLOAT4	vtarget;
	t_FTMFLOAT4	vup;
}				t_FTCAMERA;

// rasterize
void	ft_clear_rbuffer(t_FTMLX *pmlx);
void	ft_render_pixel(t_FTIMAGE *pimg, int x, int y, t_FTCOLOR color);
void	ft_render_line(t_FTMLX *pmlx, t_FTGVERTEX *p1, t_FTGVERTEX *p2);

#endif
