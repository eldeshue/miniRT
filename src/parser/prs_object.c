/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:44:30 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/09/12 18:45:49 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief parse plane line: <identifier> <center> <normal> <color>
 * @param line	"pl	0,0,20	0,1,0	255,255,255"
 * @param rt	pointer to the raytracer
 * @return void
 */
void	prs_plane(t_ft_string *line, t_render_resource *resources)
{
	t_obj_desc	*tmp;

	tmp = (t_obj_desc *)malloc(sizeof(t_obj_desc));
	tmp->type = plane;
	tmp->p1 = ftmf4_set_vector(prs_atof(&line),
			prs_atof(&line), prs_atof(&line), 1.0f);
	tmp->p2 = ftmf4_set_vector(prs_atof(&line),
			prs_atof(&line), prs_atof(&line), 0.0f);
	tmp->val = 0.0f;
	tmp->m.obj_color = ftmf4_set_vector(prs_atof(&line),
			prs_atof(&line), prs_atof(&line), 0.0f);
	resources->render_objects->push_back(resources->render_objects, tmp);
}

/**
 * @brief parse sphere line: <identifier> <center> <diameter> <color>
 * @param line	"sp	0,0,20	10	255,255,255"
 * @param rt	pointer to the raytracer
 * @return void
 */
void	prs_sphere(t_ft_string *line, t_render_resource *resources)
{
	t_obj_desc	*tmp;

	tmp = (t_obj_desc *)malloc(sizeof(t_obj_desc));
	tmp->type = sphere;
	tmp->p1 = ftmf4_set_vector(prs_atof(&line),
			prs_atof(&line), prs_atof(&line), 1.0f);
	tmp->val = prs_atof(&line) / 2;
	tmp->m.obj_color = ftmf4_set_vector(prs_atof(&line),
			prs_atof(&line), prs_atof(&line), 0.0f);
	resources->render_objects->push_back(resources->render_objects, tmp);
}

/**
 * @brief parse cylinder line:
 *        <identifier> <center> <normal> <diameter> <height> <color>
 * @param line	"cy	0,0,20	0,1,0	10.2	10.4	255,255,255"
 * @param rt	pointer to the raytracer
 * @return void
 */
void	prs_cylinder(t_ft_string *line, t_render_resource *resources)
{
	t_obj_desc	*tmp;
	t_FTMFLOAT4	normal;
	t_FTMFLOAT4	cy_center;
	float		h;

	tmp = (t_obj_desc *)malloc(sizeof(t_obj_desc));
	cy_center = ftmf4_set_vector(prs_atof(&line),
			prs_atof(&line), prs_atof(&line), 1.0f);
	normal = ftmf4_set_vector(prs_atof(&line),
			prs_atof(&line), prs_atof(&line), 0.0f);
	tmp->val = prs_atof(&line) / 2;
	h = prs_atof(&line);
	tmp->m.obj_color = ftmf4_set_vector(prs_atof(&line),
			prs_atof(&line), prs_atof(&line), 0.0f);
	tmp->p1 = ftmf4_vsub(cy_center, vmult(&normal, h / 2));
	tmp->p2 = ftmf4_vadd(cy_center, vmult(&normal, h / 2));
	tmp->type = cylinder;
	resources->render_objects->push_back(resources->render_objects, tmp);
}

/**
 * @brief parse cone line:
 * 	      <identifier> <bot center> <top center> <diameter> <color>
 * @warning line and world must not be NULL
 * @param line	"co	0,0,20	0,0,40	10.2	255,255,255"
 * @param rt	pointer to the raytracer
 * @return void
 */
void	prs_cone(t_ft_string *line, t_render_resource *resources)
{
	t_obj_desc	*tmp;

	tmp = (t_obj_desc *)malloc(sizeof(t_obj_desc));
	tmp->p1 = ftmf4_set_vector(prs_atof(&line),
			prs_atof(&line), prs_atof(&line), 1.0f);
	tmp->p2 = ftmf4_set_vector(prs_atof(&line),
			prs_atof(&line), prs_atof(&line), 0.0f);
	tmp->val = prs_atof(&line) / 2;
	tmp->m.obj_color = ftmf4_set_vector(prs_atof(&line),
			prs_atof(&line), prs_atof(&line), 0.0f);
	tmp->type = cone;
	resources->render_objects->push_back(resources->render_objects, tmp);
}
