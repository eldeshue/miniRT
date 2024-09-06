/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpolate_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:06:40 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/20 16:26:50 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_geo.h"

t_FTCOLOR	ftg_interpolate_color(int c1, int c2, int r1, int r2)
{
	t_FTCOLOR	result;

	result.b = (r1 * (int)(*(t_FTCOLOR *)(&c2)).b
			+ r2 * (int)(*(t_FTCOLOR *)(&c1)).b) / (r1 + r2 + 1);
	result.g = (r1 * (int)(*(t_FTCOLOR *)(&c2)).g
			+ r2 * (int)(*(t_FTCOLOR *)(&c1)).g) / (r1 + r2 + 1);
	result.r = (r1 * (int)(*(t_FTCOLOR *)(&c2)).r
			+ r2 * (int)(*(t_FTCOLOR *)(&c1)).r) / (r1 + r2 + 1);
	result.t = (r1 * (int)(*(t_FTCOLOR *)(&c2)).t
			+ r2 * (int)(*(t_FTCOLOR *)(&c1)).t) / (r1 + r2 + 1);
	return (result);
}
