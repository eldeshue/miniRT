/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collider_obj_vars.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:18 by dogwak            #+#    #+#             */
/*   Updated: 2024/09/12 18:27:02 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLIDER_OBJ_VARS_H
# define COLLIDER_OBJ_VARS_H

# include "colliders.h"

typedef struct s_sphere_coll_vars
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	sqrt_disc;
	float	t1;
	float	t2;
	float	t;
}	t_shpere_coll_vars;

typedef struct s_plane_coll_vars
{
	float	denom;
	float	t;
}	t_plane_coll_vars;

typedef struct s_cylinder_coll_vars
{
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		sqrt_disc;
	float		t1;
	float		t2;
	float		t;
	float		radius;
	void		*pobj;
	t_FTMFLOAT4	oc;
	t_FTMFLOAT4	h_unit;
	t_FTMFLOAT4	cylinder_axis;
	t_FTMFLOAT4	cap_center;
	t_FTMFLOAT4	cap_normal;
	float		height_on_axis;
	float		cylinder_height;
	float		denom;
}	t_cylinder_coll_vars;

typedef struct s_cone_coll_vars
{
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		sqrt_disc;
	float		t1;
	float		t2;
	float		t;
	float		m;
	t_FTMFLOAT4	oc;
	t_FTMFLOAT4	cv;
	t_FTMFLOAT4	cone_axis;
	t_FTMFLOAT4	h_unit;
	float		height_on_axis;
	float		cone_height;
	void		*pobj;
}	t_cone_coll_vars;

#endif
