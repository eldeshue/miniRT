/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:25:59 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/14 15:50:10 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static void	clamp_channel(float *pf)
{
	if (*pf > 255.0f)
		*pf = 255.0f;
	if (*pf < 0.0f)
		*pf = 0.0f;
}

void	clamp(t_FTMFLOAT4 *c)
{
	clamp_channel(&c->data[0]);
	clamp_channel(&c->data[1]);
	clamp_channel(&c->data[2]);
	clamp_channel(&c->data[3]);
}

t_FTMFLOAT4	vmult(t_FTMFLOAT4 *v, float m)
{
	return (ftmf4_set_vector(v->data[0] * m, v->data[1] * m,
			v->data[2] * m, v->data[3]));
}
