/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:39:12 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/06 18:31:28 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLIDERS_H
# define COLLIDERS_H

# include "rt_object.h"

t_hit	collider_plane(const t_ray *r, void *obj);
t_hit	collider_sphere(const t_ray *r, void *obj);
t_hit	collider_cylinder(const t_ray *r, void *obj);
t_hit	collider_cone(const t_ray *r, void *obj);

#endif
