/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:01:57 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/17 16:52:11 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OBJECT_H
# define RT_OBJECT_H

# include "../ft_graphics/ft_math/ft_math.h"
# include "../hit/hit.h"
# include "../ray/ray.h"
# include "../rt_object/material.h"

// enum
typedef enum e_obj_type
{
	error,
	plane,
	sphere,
	cylinder,
	cone
}			t_obj_type;

// descriptor of object
// will be passed as a parameter
typedef struct s_obj_desc
{
	t_obj_type	type;
	t_material	m;
	t_FTMFLOAT4	p1;
	t_FTMFLOAT4	p2;
	float		val;
}				t_obj_desc;

// parent class
typedef struct s_hit
{
	float			dist;
	t_FTMFLOAT4		ppos;
	t_FTMFLOAT4		vnormal;
	void	*pobj;
}					t_hit;

typedef t_hit(*t_hptr)(const t_ray *r, void *obj_ptr);

typedef struct s_rt_obj
{
	t_obj_type	type;
	void		*obj_ptr;
	t_hptr		hit;
}				t_rt_obj;

int				alloc_rt_obj(void *paddr, void *pobj_desc);
void			free_rt_obj(void *paddr);

// plane
typedef struct s_plane
{
	t_material	m;
	t_FTMFLOAT4	pcenter;
	t_FTMFLOAT4	vnormal;
}				t_plane;

t_plane			*new_plane(t_obj_desc *d);

// sphere
typedef struct s_sphere
{
	t_material	m;
	t_FTMFLOAT4	pcenter;
	float		radius;
}				t_sphere;

t_sphere		*new_sphere(t_obj_desc *d);

// cylinder
typedef struct s_cylinder
{
	t_material	m;
	t_FTMFLOAT4	pcenter1;
	t_FTMFLOAT4	pcenter2;
	float		radius;
}				t_cylinder;

t_cylinder		*new_cylinder(t_obj_desc *d);

// cone
typedef struct s_cone
{
	t_material	m;
	t_FTMFLOAT4	pcenter;
	t_FTMFLOAT4	pvertex;
	float		radius;
}				t_cone;

t_cone			*new_cone(t_obj_desc *d);

#endif
