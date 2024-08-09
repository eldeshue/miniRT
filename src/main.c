/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:21:43 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/09 18:45:46 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include <stdlib.h>
#include <unistd.h>
#include "./libft/libft.h"

int	main(int argc, char *argv[])
{
	t_render_resource *const	prsrc = new_render_resource();

	if (argc < 2 || 3 < argc
		|| (argc == 3 && ft_strncmp(argv[2], "--save", 6) != 0))
	{
		write(2, "wrong arguments.\n", 17);
		return (0);
	}
	if (prsrc == NULL)
	{
		write(2, "resource object allocation fail.\n", 33);
		return (0);
	}
	if (!init_render_resource(prsrc, argv))
	{
		write(2, "parsing failed.\n", 16);
		return (0);
	}
	set_rt_hook(&prsrc->ftmlx);
	if (argc == 3)
		;// render image
	else
		;// render window
	delete_render_resource(prsrc);
}
