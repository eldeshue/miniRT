/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:17 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/09 15:26:45 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# include "./ft_graphics/ft_graphics.h"
# include "./ft_vector/ft_vector.h"

/*
	ftmlx	: mlx object
	cma		: virtual camera object
	fov		: vertical field of view, degree
	vdx		: vector of +x dir of camera coordinates, size is gap of pixels
	vdx		: vector of -y dir of camera coordinates, size is gap of pixels
	// global ambient light value
	// vector of lights
	// vector of render target objects, hittables
*/
typedef struct s_render_resource
{
	t_FTMLX		ftmlx;
	t_FTCAMERA	cam;
	t_FTMFLOAT4	*view_plane;
	float		fov;
	t_FTMFLOAT4	vdx;
	t_FTMFLOAT4	vdy;
	float		amb_intens;
	t_FTMFLOAT4	amb_color;
	t_ft_vector	*lights;
	t_ft_vector	*render_objects;
}				t_render_resource;

// resource initialize
t_render_resource	*new_render_resource(void);
int					init_render_resource(t_render_resource *self, char **argv);
void				delete_render_resource(t_render_resource *self);
void				set_view_plane(t_render_resource *const prsrc);

// render
// TODO : rendering window
// TODO : rendering image

// mlx hook
void				set_rt_hook(t_FTMLX *pmlx);

// etc
float				clamp(float f);
t_FTMFLOAT4			vmult(t_FTMFLOAT4 *v, float m);

#endif
