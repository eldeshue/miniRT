/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:39:12 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/28 15:43:44 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLIDERS_H
# define COLLIDERS_H

# include "../rt_object/rt_object.h"
# include "../ft_graphics/ft_math/ft_math.h"
# include "../raytracer/raytracer.h"
# define EPSILON 1e-6
# define FLOAT_MAX 3.402823466e+38F
# define FLOAT_MIN 1.175494351e-38F

typedef struct s_cy_cap_vars
{
	t_FTMFLOAT4	cap;
	float		t;
} t_cy_cap_vars;

t_hit		collider_plane(const t_ray *r, void *obj);
t_hit		collider_sphere(const t_ray *r, void *obj);
t_hit		collider_cylinder(const t_ray *r, void *obj);
t_hit		collider_cone(const t_ray *r, void *obj);
float		cy_find_intersection_time(float t1, float t2);
t_FTMFLOAT4	ray_at(t_ray *ray, float t);
void		init_hit(t_hit *hit);
t_FTMFLOAT4 vscale(t_FTMFLOAT4 v, float s);
void		set_face_normal(t_hit *hit, t_ray *r, t_FTMFLOAT4 outward_normal);

#endif
