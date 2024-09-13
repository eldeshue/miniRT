/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_readfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:49:49 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/09/13 15:55:59 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	prs_func_select(int fd, t_ft_string *word,
		t_ft_string **line, t_render_resource *resources)
{
	size_t				i;
	t_ft_string			*tmp;
	const t_prs_funcs	parser[] = {
	{"A", prs_ambient}, {"C", prs_camera}, {"L", prs_light},
	{"pl", prs_plane}, {"sp", prs_sphere}, {"cy", prs_cylinder},
	{"co", prs_cone}, {NULL, NULL}};

	i = 0;
	tmp = NULL;
	while (parser[i].identifier != NULL)
	{
		tmp = new_ftstr_cstr(parser[i].identifier);
		if (word->compare(word, tmp) == 0 && word->size == tmp->size)
		{
			(*line)->getline(*line, fd);
			parser[i].func(line, resources);
			delete_ftstr(tmp);
			break ;
		}
		i++;
		delete_ftstr(tmp);
	}
	if (parser[i].identifier == NULL)
		prs_error_exit("Unknown identifier");
}

void	check_resources(t_render_resource *resources)
{
	if (resources->fov < 0 || resources->fov > 179)
		prs_error_exit("wrong fov value.");
	if (resources->flag_is_init_cam == 0)
		prs_error_exit("Camera is not initialized");
	if (resources->flag_is_init_amb == 0)
		prs_error_exit("Ambient light is not initialized");
}

void	prs_rt_file(int fd, t_render_resource *resources)
{
	t_ft_string	*word;
	t_ft_string	**line;

	line = malloc(sizeof(t_ft_string *));
	while (1)
	{
		*line = new_ftstr();
		word = new_ftstr();
		word->getword(word, fd);
		if (word->size == 0)
		{
			delete_ftstr(word);
			delete_ftstr(*line);
			break ;
		}
		prs_func_select(fd, word, line, resources);
		delete_ftstr(word);
		delete_ftstr(*line);
	}
	free(line);
}

void	prs_check_ext(t_ft_string *file)
{
	size_t		len;
	t_ft_string	*extract_ext;
	t_ft_string	*ext;

	len = file->size;
	ext = new_ftstr_cstr(".rt");
	extract_ext = file->substr(file, len - 3, 3);
	if (ext->compare(ext, extract_ext) != 0)
		prs_error_exit("file extension is not .rt");
	delete_ftstr(extract_ext);
	delete_ftstr(ext);
}

void	prs_read_file(t_ft_string *file, t_render_resource *resources)
{
	int		fd;

	resources->flag_is_init_cam = 0;
	resources->flag_is_init_amb = 0;
	printf("file name : %s\n", file->c_str(file));
	fd = open(file->c_str(file), O_RDONLY);
	if (fd < 0)
		prs_error_exit("Error opening file");
	prs_check_ext(file);
	prs_rt_file(fd, resources);
	close(fd);
	check_resources(resources);
	set_view_plane(resources);
}
