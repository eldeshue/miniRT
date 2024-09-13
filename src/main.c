/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:21:43 by dogwak            #+#    #+#             */
/*   Updated: 2024/09/12 22:18:58 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "./libft/libft.h"
#include "./raytracer/raytracer.h"
#include "./ft_string/ft_string.h"
#include "./parser/parser.h"

void leak_check(void)
{
	system("leaks miniRT");
}

int	main(int argc, char *argv[])
{
	atexit(leak_check);
	t_render_resource *const	prsrc = new_render_resource();
	t_ft_string					*file;

	if (argc < 2)
	{
		write(2, "Error : wrong arguments.\n", 17);
		return (0);
	}
	if (prsrc == NULL)
	{
		write(2, "resource object allocation failed.\n", 33);
		return (0);
	}
	file = new_ftstr_cstr(argv[1]);
	prs_read_file(file, prsrc);
	delete_ftstr(file);
	set_rt_hook(&prsrc->ftmlx);
	render_rt_window(prsrc);
	delete_render_resource(prsrc);
}
