/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:01:50 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/14 11:24:12 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "../ft_graphics/ft_math/ft_math.h"
# include "../rt_object/rt_object.h"

typedef struct s_hit
{
	float		dist;
	t_FTMFLOAT4	ppos;
	t_FTMFLOAT4	vnormal;
	t_rt_obj	*pobj;
}				t_hit;

#endif
