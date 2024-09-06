# /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:21:43 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/20 15:48:40 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "./libft/libft.h"
#include "./parser/parser.h"
#include "./ft_string/ft_string.h"
#include "./raytracer/raytracer.h"

int	main(int argc, char *argv[])
{
	t_render_resource *const	prsrc = new_render_resource();
	if (argc < 2 || 3 < argc
		|| (argc == 3 && ft_strncmp(argv[2], "--save", 6) != 0))
	{
		write(2, "wrong arguments.\n", 17);
		return (0);
	}
	t_ft_string *file = new_ftstr_cstr(argv[1]);
	prs_read_file(file, prsrc);
	return 0;
}
