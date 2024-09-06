#include "parser.h"

void	prs_func_select(int fd, t_ft_string *word, t_ft_string *line, t_render_resource *resources)
{
	size_t				i;
	t_ft_string			*tmp;
	const t_prs_funcs	parser[] = {
		{"A", prs_ambient}, {"C", prs_camera}, {"L", prs_light},
		{"pl", prs_plane}, {"sp", prs_sphere}, {"cy", prs_cylinder},
		{"co", prs_cone}, {NULL, NULL}};

	i = 0;
	while (parser[i].identifier != NULL)
	{
		tmp = new_ftstr_cstr(parser[i].identifier);
		if (word->compare(word, tmp) == 0 && word->size == tmp->size)
		{
			line->getline(line, fd);
			printf("word : %s\n", word->pbuffer);
			printf("tmp : %s\n", tmp->pbuffer);
			printf("line : %s\n", line->pbuffer);
			parser[i].func(line, resources);
			break ;
		}
		i++;
	}
	if (parser[i].identifier == NULL)
			prs_error_exit("Unknown identifier");
}

void	prs_rt_file(int fd, t_render_resource *resources)
{
	t_ft_string	*word;
	t_ft_string	*line;

	while (1)
	{
		line = new_ftstr();
		word = new_ftstr();
		word->getword(word, fd);
		if (word->size == 0)
			break ;
		prs_func_select(fd, word, line, resources);
	}
}

void	prs_check_ext(t_ft_string *file)
{
	size_t		len;
	t_ft_string	*extract_ext;
	t_ft_string	ext;

	len = file->size;
	ext = construct_ftstr_cstr(".rt");
	extract_ext = file->substr(file, len - 3, 3);
	if (ext.compare(&ext, extract_ext) != 0)
		prs_error_exit("file extension is not .rt");
	delete_ftstr(extract_ext);
}


/**
 * @brief read file and check extension
 * @issue : file을 열 때 경로를 입력하지 않으면 에러를 반환, 경로를 입력하지 않아도 파일을 열 수 있도록 구현할 지 고민 중
*/
void	prs_read_file(t_ft_string *file, t_render_resource *resources)
{  
	int		fd;

	printf("file name : %s\n", file->pbuffer);
	fd = open(file->pbuffer, O_RDONLY);
	printf("fd : %d\n", fd);
	if (fd < 0)
	{
		perror("Error opening file");
		prs_error_exit("file extension is not .rt");
	}
	prs_check_ext(file);
	prs_rt_file(fd, resources);
	close(fd);
	set_view_plane(resources);
}