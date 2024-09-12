/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:17 by dogwak            #+#    #+#             */
/*   Updated: 2024/09/11 19:16:04 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# define DIFFUSION_INTENSITY 0.5f
# define SPECULAR_INTENSITY 0.5f
# define SPECULAR_POWER 50

# include "../ft_graphics/ft_graphics.h"
# include "../ft_vector/ft_vector.h"

# include "../ray/ray.h"
# include "../rt_object/rt_object.h"

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
t_hit				get_hit_per_ray(t_render_resource *const prsrc,
						t_ray *const pgaze);
t_FTMFLOAT4			trace_ray(t_render_resource *prsrc,
						t_ray *ray, t_hit hit);

// render
void				render_rt_window(t_render_resource *const prsrc);

// mlx hook
void				set_rt_hook(t_FTMLX *pmlx);

// reflect : phong reflection model
t_FTMFLOAT4			reflect_ray(t_render_resource *prsrc,
						t_ray *ray, t_hit hit);
// etc
void				clamp(t_FTMFLOAT4 *c);
t_FTMFLOAT4			vmult(t_FTMFLOAT4 *v, float m);

#endif
