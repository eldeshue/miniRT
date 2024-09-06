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
	void	(*func)(t_ft_string *line, t_render_resource *resources);
}	t_prs_funcs;
/**
 * {"A", prs_ambient}, {"C", prs_camera}, {"L", pas_light},
		{"pl", prs_plane}, {"sp", prs_sphere}, {"cy", prs_cylinder},
		{"co", prs_cone},
*/
void	prs_error_exit(char *msg);
void	prs_check_ext(t_ft_string *file);
void	prs_read_file(t_ft_string *file, t_render_resource *resources);
float	prs_atof(t_ft_string **str);
void	prs_ambient(t_ft_string *line, t_render_resource *resources);
void	prs_camera(t_ft_string *line, t_render_resource *resources);
void	prs_light(t_ft_string *line, t_render_resource *resources);
void	prs_plane(t_ft_string *line, t_render_resource *resources);
void	prs_sphere(t_ft_string *line, t_render_resource *resources);
void	prs_cylinder(t_ft_string *line, t_render_resource *resources);
void	prs_cone(t_ft_string *line, t_render_resource *resources);


#endif