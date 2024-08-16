/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:39:12 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/14 11:30:09 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLIDERS_H
# define COLLIDERS_H

# include "rt_object.h"

t_hit		collider_plane(const t_ray *r, void *obj);
t_hit		collider_sphere(const t_ray *r, void *obj);
t_hit		collider_cylinder(const t_ray *r, void *obj);
t_hit		collider_cone(const t_ray *r, void *obj);
t_FTMFLOAT4	ray_at(const t_ray *ray, float t);
#endif