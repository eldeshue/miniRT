/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:01:44 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/09 18:17:01 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "./ft_graphics/ft_math/ft_math.h"

typedef struct s_light
{
	t_FTMFLOAT4	ppos;
	t_FTMFLOAT4	color;
}				t_light;

int				alloc_light(void *paddr, void *plight);
void			free_light(void *paddr);

#endif
