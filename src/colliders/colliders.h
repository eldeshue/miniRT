/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:39:12 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/31 16:36:55 by hyeonwch         ###   ########.fr       */
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

// cyllinder collider
t_hit		collider_cylinder(const t_ray *r, void *obj);
float		cy_compute_cap_t(t_ray *r, t_FTMFLOAT4	center, t_FTMFLOAT4	h_unit,
				float radius);
void		cy_set_coll_cap_hit(t_hit *hit, t_ray *r, float t,
				t_cylinder_coll_vars vars);
void		cy_check_coll_cap(t_cylinder_coll_vars *vars, t_ray *r,
				t_hit *hit_cap);
float		cy_find_intersection_time(float t1, float t2);
void		cy_solve_quadratic(t_cylinder_coll_vars *vars, t_ray *r,
				float a_dot, float c_dot);
void		cy_coll_set_vars(t_cylinder_coll_vars *vars, t_ray *r, void *obj);
void		cy_coll_set_surface_hit(t_hit *hit, t_ray *r,
				t_cylinder_coll_vars vars);
void		cy_check_coll_surface(t_cylinder_coll_vars *vars, t_ray *r,
				t_hit *hit_surface, void *obj);

t_hit		collider_plane(const t_ray *r, void *obj);
t_hit		collider_sphere(const t_ray *r, void *obj);
t_hit		collider_cone(const t_ray *r, void *obj);
float		find_intersection_time(float t1, float t2);
t_FTMFLOAT4	ray_at(t_ray *ray, float t);
void		init_hit(t_hit *hit);
void		process_wrong_hit(t_hit *hit);
void		set_face_normal(t_hit *hit, t_ray *r, t_FTMFLOAT4 outward_normal);

#endif
