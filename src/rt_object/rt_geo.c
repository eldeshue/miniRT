/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_geo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:52:18 by dogwak            #+#    #+#             */
/*   Updated: 2024/09/03 15:13:06 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_object.h"
#include <stdlib.h>

t_plane	*new_plane(t_obj_desc *d)
{
	t_plane *const	self = malloc(sizeof(t_plane));

	if (self == NULL)
		return (NULL);
	self->m = d->m;
	self->pcenter = d->p1;
	self->vnormal = d->p2;
	ftmf4_vnormalize(&self->vnormal);
	return (self);
}

t_sphere	*new_sphere(t_obj_desc *d)
{
	t_sphere *const	self = malloc(sizeof(t_sphere));

	if (self == NULL)
		return (NULL);
	self->m = d->m;
	self->pcenter = d->p1;
	self->radius = d->val;
	return (self);
}

t_cylinder	*new_cylinder(t_obj_desc *d)
{
	t_cylinder *const	self = malloc(sizeof(t_cylinder));

	if (self == NULL)
		return (NULL);
	self->m = d->m;
	self->pcenter1 = d->p1;
	self->pcenter2 = d->p2;
	self->radius = d->val;
	return (self);
}

t_cone	*new_cone(t_obj_desc *d)
{
	t_cone *const	self = malloc(sizeof(t_cone));

	if (self == NULL)
		return (NULL);
	self->m = d->m;
	self->pcenter = d->p1;
	self->pvertex = d->p2;
	self->radius = d->val;
	return (self);
}
