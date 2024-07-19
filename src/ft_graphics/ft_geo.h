/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_geo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:26:14 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/26 14:09:43 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GEO_H
# define FT_GEO_H

# include "./ft_math/ft_math.h"

typedef struct s_FTCOLOR
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	t;
}					t_FTCOLOR;

t_FTCOLOR	ftg_interpolate_color(int c1, int c2, int r1, int r2);

typedef struct s_FTGVERTEX
{
	t_FTCOLOR	color;
	t_FTMFLOAT4	pos;
}				t_FTGVERTEX;

#endif
