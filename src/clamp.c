/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:25:59 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/07 19:29:41 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

float	clamp(float f)
{
	float	result;

	result = f;
	if (f > 255.0f)
		result = 255.0f;
	if (f < 0.0f)
		result = 0.0f;
	return (result);
}
