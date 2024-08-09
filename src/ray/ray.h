/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:01:54 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/09 20:25:07 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "../ft_graphics/ft_math/ft_math.h"

typedef struct s_ray
{
	t_FTMFLOAT4	pstart;
	t_FTMFLOAT4	ndir;
}				t_ray;

#endif
