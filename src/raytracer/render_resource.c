/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_resource.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:14:41 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/14 14:33:55 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "../light/light.h"
#include "../rt_object/rt_object.h"

t_render_resource	*new_render_resource(void)
{
	t_render_resource *const	self = malloc(sizeof(t_render_resource));

	if (self == NULL
		|| !ft_set_mlx(&self->ftmlx, SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT"))
		return (NULL);
	self->view_plane
		= malloc(SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(t_FTMFLOAT4));
	self->lights = new_ftvec(alloc_light, free_light, sizeof(t_light *));
	self->render_objects
		= new_ft_vec(alloc_rt_obj, free_rt_obj, sizeof(t_rt_obj *));
	if (self->view_plane == NULL || self->lights == NULL
		|| self->render_objects == NULL)
		return (NULL);
	set_view_plane(self);
	return (self);
}

void	delete_render_resource(t_render_resource *self)
{
	ft_del_mlx(&self->ftmlx);
	free(self->view_plane);
	delete_ftvec(self->lights);
	delete_ftvec(self->render_objects);
}
