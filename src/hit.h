/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:01:50 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/05 13:55:32 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "./ft_graphics/ft_math/ft_math.h"
# include "rt_object.h"

typedef struct s_hit
{
	float		dist;
	t_FTMFLOAT4	ppos;
	t_FTMFLOAT4	vnormal;
	t_rt_obj	*pobj;
}				t_hit;

#endif
