/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clliders_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:09 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/20 17:25:38 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colliders.h"
#include "../raytracer/raytracer.h"

t_FTMFLOAT4	ray_at(t_ray *ray, float t)
{
	return (ftmf4_vadd(ray->pstart, vmult(&ray->ndir, t)));
}
