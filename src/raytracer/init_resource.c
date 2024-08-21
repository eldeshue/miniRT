/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_resource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:39:55 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/21 17:39:12 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raytracer.h"
#include "../light/light.h"

#include <stdio.h>

// TODO : Parsing
int	init_render_resource(t_render_resource *self, char **argv)
{

	//
	argv++;

/*
	// test code
	// camera init
	self->fov = 90;
	self->cam.vpos = ftmf4_set_vector(-100.0f, 0.0f, 100.0f, 1.0f);
	self->cam.vtarget = ftmf4_set_vector(1.0f, 0.0f, -0.3f, 0.0f);
	ftmf4_vnormalize(&self->cam.vtarget);
	self->cam.vup = ftmf4_set_vector(0.0f, 0.0f, 1.0f, 0.0f);

	// object init
	t_obj_desc	tmp;

	// sphere
	tmp.m.obj_color = ftmf4_set_vector(255.0f, 0.0f, 0.0f, 0.0f);	// red
	tmp.p1 = ftmf4_set_vector(200.0f, 0.0f, 100.0f, 1.0f);
	tmp.val = 40.0f;
	tmp.type = sphere;
	self->render_objects->push_back(self->render_objects, &tmp);

	// plane
	tmp.m.obj_color = ftmf4_set_vector(55.0f, 55.0f, 200.0f, 0.0f);	// blue
	tmp.p1 = ftmf4_set_vector(0.0f, 0.0f, 0.0f, 1.0f);
	tmp.p2 = ftmf4_set_vector(0.0f, 0.0f, 1.0f, 0.0f);	// normal vector of plane
	tmp.val = 0.0f;
	tmp.type = plane;
	self->render_objects->push_back(self->render_objects, &tmp);

	// light init
	t_light	l;

	l.ppos = ftmf4_set_vector(0.0f, 0.0f, 500.0f, 1.0f);
	l.color = ftmf4_set_vector(255.0f, 255.0f, 255.0f, 0.0f);
	l.intensity = 0.6f;
	self->lights->push_back(self->lights, &l);
*/

	set_view_plane(self);	// call set_view_plane after camera initialization.
	return (1);
}
