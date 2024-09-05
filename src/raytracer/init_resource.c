/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_resource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:39:55 by dogwak            #+#    #+#             */
/*   Updated: 2024/09/05 21:54:47 by dogwak           ###   ########.fr       */
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
	(void)argv;
	// test code
	// camera init
	self->fov = 90;
	self->cam.vpos = ftmf4_set_vector(0.0f, 200.0f, 280.0f, 1.0f);
	self->cam.vtarget = ftmf4_set_vector(0.0f, -0.8f, -1.0f, 0.0f);
	ftmf4_vnormalize(&self->cam.vtarget);
	self->cam.vup = ftmf4_set_vector(0.0f, 0.0f, 1.0f, 0.0f);

	// global ambient color setting
	self->amb_color = ftmf4_set_vector(155.0f, 155.0f, 155.0f, 0.0f);
	self->amb_intens = 0.3;

	// object init
	t_obj_desc	tmp;

	// sphere
	tmp.m.obj_color = ftmf4_set_vector(155.0f, 115.0f, 55.0f, 0.0f);	// green
	tmp.p1 = ftmf4_set_vector(-60.0f, 40.0f, 70.0f, 1.0f);        // 중심 좌표 (100, 100, 50)
	tmp.val = 30.0f;                                                // 반지름 30
	tmp.type = sphere;
	self->render_objects->push_back(self->render_objects, &tmp);

	// cylinder
	tmp.m.obj_color = ftmf4_set_vector(255.0f, 156.0f, 155.0f, 0.0f);
	tmp.p1 = ftmf4_set_vector(0.0f, 0.0f, 0.0f, 1.0f); // bottom center
	tmp.p2 = ftmf4_set_vector(0.0f, 0.0f, 40.0f, 1.0f); // top center
	tmp.val = 30.0f;
	tmp.type = cylinder;
	//self->render_objects->push_back(self->render_objects, &tmp);

	// plane
	tmp.m.obj_color = ftmf4_set_vector(155.0f, 155.0f, 155.0f, 0.0f);	// blue
	tmp.p1 = ftmf4_set_vector(0.0f, 0.0f, 0.0f, 1.0f);
	tmp.p2 = ftmf4_set_vector(0.0f, 0.0f, 1.0f, 0.0f);	// normal vector of plane
	tmp.val = 0.0f;
	tmp.type = plane;
	self->render_objects->push_back(self->render_objects, &tmp);

	// cone
	tmp.m.obj_color = ftmf4_set_vector(155.0f, 255.0f, 155.0f, 0.0f);	// red
	tmp.p1 = ftmf4_set_vector(0.0f, 0.0f, 0.0f, 1.0f);   // vertex
	tmp.p2 = ftmf4_set_vector(0.0f, 0.0f, 120.0f, 1.0f);  // center
	tmp.val = 50.0f;
	tmp.type = cone;
	self->render_objects->push_back(self->render_objects, &tmp);

	// light init
	t_light	l;

	l.ppos = ftmf4_set_vector(-100.0f, 0.0f, 170.0f, 1.0f);
	l.color = ftmf4_set_vector(255.0f, 40.0f, 40.0f, 0.0f);
	l.intensity = 0.7f;
	self->lights->push_back(self->lights, &l);

	l.ppos = ftmf4_set_vector(0.0f, 0.0f, 150.0f, 1.0f);
	l.color = ftmf4_set_vector(40.0f, 255.0f, 40.0f, 0.0f);
	l.intensity = 1.0f;
	self->lights->push_back(self->lights, &l);

	l.ppos = ftmf4_set_vector(100.0f, 0.0f, 170.0f, 1.0f);
	l.color = ftmf4_set_vector(40.0f, 40.0f, 255.0f, 0.0f);
	l.intensity = 0.7f;
	self->lights->push_back(self->lights, &l);

	set_view_plane(self);	// call set_view_plane after camera initialization.
	return (1);
}
