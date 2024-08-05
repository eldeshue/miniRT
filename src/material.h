/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:42:38 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/05 14:06:33 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "./ft_graphics/ft_math/ft_math.h"

typedef struct s_material
{
	t_FTMFLOAT4	amb_color;
	float		ka;
	float		kd;
	float		ks;
	float		specular_pow;
}				t_material;

#endif
