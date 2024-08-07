/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:17 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/07 20:36:51 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "./ft_graphics/ft_graphics.h"
# include "ray.h"

typedef struct s_render_resource
{
	t_FTMLX		ftmlx;
	t_FTCAMERA	cam;
	t_FTMFLOAT4	*view_plane;
	float		fov;
	// TODO : global ambient light
	// TODO : vector of lights
	// TODO : vector of render target objects
}				t_render_resource;

// resource initialize
// int			set_render_resource(t_render_resource *self, char **argv);
// void			destruct_render_resource(t_render_resource *self);
void			set_view_plane(t_render_resource *const prsrc);

// render
// TODO : rendering routine

// etc
float			clamp(float f);

#endif
