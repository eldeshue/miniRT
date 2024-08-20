/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:39:12 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/20 17:23:03 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLIDERS_H
# define COLLIDERS_H

# include "../rt_object/rt_object.h"
# include "../ft_graphics/ft_math/ft_math.h"
# include "../raytracer/raytracer.h"
# define EPSILON 1e-6


t_hit		collider_plane(const t_ray *r, void *obj);
t_hit		collider_sphere(const t_ray *r, void *obj);
// t_hit		collider_cylinder(const t_ray *r, void *obj);
// t_hit		collider_cone(const t_ray *r, void *obj);
t_FTMFLOAT4	ray_at(t_ray *ray, float t);

#endif
