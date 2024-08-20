/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_obj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:26:35 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/17 16:51:33 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_object.h"
#include "../colliders/colliders.h"
#include <stdlib.h>

static int	per_type_init(t_rt_obj *pobj, t_obj_desc *pobj_desc)
{
	if (pobj_desc->type == error)
		return (0);
	else if (pobj_desc->type == sphere)
	{
		pobj->obj_ptr = new_sphere(pobj_desc);
		pobj->hit = collider_sphere;
	}
	else if (pobj_desc->type == plane)
	{
		pobj->obj_ptr = new_plane(pobj_desc);
		pobj->hit = collider_plane;
	}
	// else if (pobj_desc->type == cylinder)
	// {
	// 	pobj->obj_ptr = new_cylinder(pobj_desc);
	// 	pobj->hit = collider_cylinder;
	// }
	// else if (pobj_desc->type == cone)
	// {
	// 	pobj->obj_ptr = new_cone(pobj_desc);
	// 	pobj->hit = collider_cone;
	// }
	return (1);
}

int	alloc_rt_obj(void *paddr, void *pobj_desc)
{
	t_rt_obj **const	address = paddr;
	t_obj_desc *const	param = pobj_desc;

	(void)param;
	*address = malloc(sizeof(t_rt_obj));
	if (*address == NULL)
		return (0);
	if (!per_type_init(*address, pobj_desc))
		return (0);
	return (1);
}

void	free_rt_obj(void *paddr)
{
	free((*(t_rt_obj **)paddr)->obj_ptr);
	free(*(t_rt_obj **)paddr);
}
