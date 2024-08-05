/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:01:57 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/05 13:57:30 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OBJECT_H
# define RT_OBJECT_H

# include "./ft_graphics/ft_math/ft_math.h"
# include "hit.h"
# include "ray.h"
# include "material.h"

// enum
typedef enum e_obj_type
{
	error,
	sphere,
	cylinder,
	cone
}			t_obj_type;

// descriptor of object
// will be passed as a parameter
typedef struct s_obj_desc
{
	t_material	m;
	t_FTMFLOAT4	point1;
	t_FTMFLOAT4	point2;
	float		val;
}				t_obj_desc;

// parent class
typedef struct s_rt_obj
{
	t_obj_type	type;
	void		*obj_ptr;
	t_hit(*hit(t_ray, void *));
}				t_rt_obj;

t_rt_obj		*new_obj(t_obj_type t, t_obj_desc d);
void			delete_obj(t_rt_obj *self);

// sphere
typedef struct s_sphere
{
	t_material	m;
	t_FTMFLOAT4	pcenter;
	float		radius;
}				t_sphere;

t_sphere		*new_sphere(t_obj_desc d);
void			delete_sphere(t_sphere *self);

// cylinder
typedef struct s_cylinder
{
	t_material	m;
	t_FTMFLOAT4	pcenter1;
	t_FTMFLOAT4	pcenter2;
	float		radius;
}				t_cylinder;

t_cylinder		*new_cylinder(t_obj_desc d);
void			delete_cylinder(t_cylinder *self);

// cone
typedef struct s_cone
{
	t_material	m;
	t_FTMFLOAT4	pcenter;
	t_FTMFLOAT4	pvertex;
	float		radius;
}				t_cone;

t_cone			*new_cone(t_obj_desc d);
void			delete_cone(t_cone *self);

#endif
