/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:43:16 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/09/13 14:13:52 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../light/light.h"

int	prs_is_right_num_of_args(t_ft_string **line, int num)
{
	size_t	i;
	int		cnt;
	int		flag;

	i = 0;
	cnt = 0;
	flag = 0;
	while (i < (*line)->size)
	{
		if (*(*line)->at(*line, i) == ' ' || *(*line)->at(*line, i) == '\t'
			|| *(*line)->at(*line, i) == '\n'
			|| *(*line)->at(*line, i) == '\r'
			|| *(*line)->at(*line, i) == '\f'
			|| *(*line)->at(*line, i) == '\v')
			flag = 0;
		else if (flag == 0)
		{
			flag = 1;
			cnt++;
		}
		i++;
	}
	if (cnt != num)
		prs_error_exit("Wrong number of arguments");
	return (cnt);
}

/**
 * @brief parse ambient line: <identifier> <ratio> <color>
 * @param line	"A	0.5	255,255,255"
 * @param rt	pointer to the raytracer
 * @return	void
 */
void	prs_ambient(t_ft_string **line, t_render_resource *resources)
{
	prs_is_right_num_of_args(line, 2);
	resources->amb_intens = prs_atof(line);
	resources->amb_color = ftmf4_set_vector(prs_atof(line),
			prs_atof(line), prs_atof(line), 0.0f);
}

/**
 * @brief parse camera line: <identifier> <view_point> <normal_vector> <FOV>
 * @param line	"C	-50.0,0,20	0,0,1	70"
 * @param rt	pointer to the raytracer
 * @return	void
 */
void	prs_camera(t_ft_string **line, t_render_resource *resources)
{
	prs_is_right_num_of_args(line, 3);
	resources->cam.vpos = ftmf4_set_vector(prs_atof(line),
			prs_atof(line), prs_atof(line), 1.0f);
	resources->cam.vtarget = ftmf4_set_vector(prs_atof(line),
			prs_atof(line), prs_atof(line), 0.0f);
	resources->cam.vup = ftmf4_set_vector(0.0f, 0.0f, 1.0f, 0.0f);
	resources->fov = prs_atof(line);
}

/**
 * @brief parse light line: <identifier> <center> <ratio> <color>
 * @param line	"L	0,0,20	0.5	255,255,255"
 * @param rt	pointer to the raytracer
 * @return	void
 */
void	prs_light(t_ft_string **line, t_render_resource *resources)
{
	t_light	tmp;

	prs_is_right_num_of_args(line, 3);
	tmp.ppos = ftmf4_set_vector(prs_atof(line),
			prs_atof(line), prs_atof(line), 1.0f);
	tmp.intensity = prs_atof(line);
	tmp.color = ftmf4_set_vector(prs_atof(line),
			prs_atof(line), prs_atof(line), 0.0f);
	resources->lights->push_back(resources->lights, &tmp);
}
