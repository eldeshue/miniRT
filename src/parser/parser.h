/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:42:37 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/09/13 15:30:04 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../raytracer/raytracer.h"
# include "../ft_string/ft_string.h"
# include "../ft_graphics/ft_graphics.h"

typedef struct t_prs_funcs
{
	char	*identifier;
	void	(*func)(t_ft_string **line, t_render_resource *resources);
}	t_prs_funcs;

void	prs_error_exit(char *msg);
void	prs_check_ext(t_ft_string *file);
void	prs_read_file(t_ft_string *file, t_render_resource *resources);
float	prs_atof(t_ft_string **str);
void	prs_ambient(t_ft_string **line, t_render_resource *resources);
void	prs_camera(t_ft_string **line, t_render_resource *resources);
void	prs_light(t_ft_string **line, t_render_resource *resources);
void	prs_plane(t_ft_string **line, t_render_resource *resources);
void	prs_sphere(t_ft_string **line, t_render_resource *resources);
void	prs_cylinder(t_ft_string **line, t_render_resource *resources);
void	prs_cone(t_ft_string **line, t_render_resource *resources);
int		prs_is_right_num_of_args(t_ft_string **line, int num);

#endif