/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rt_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:22:00 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/09 20:26:08 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "../ft_graphics/ft_keycode.h"

static int	exit_hook(void)
{
	exit(0);
	return (1);
}

static int	key_hook(int keycode, t_FTMLX *pmlx)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(pmlx->hmlx, pmlx->hwin);
		exit(0);
	}
	return (1);
}

void	set_rt_hook(t_FTMLX *pmlx)
{
	mlx_key_hook(pmlx->hwin, key_hook, pmlx);
	mlx_hook(pmlx->hwin, 17, 0, exit_hook, 0);
}
