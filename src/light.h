/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:01:44 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/05 11:16:03 by dogwak           ###   ########.fr       */
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

#endif
