/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:03:37 by dogwak            #+#    #+#             */
/*   Updated: 2024/09/10 20:07:18 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colliders.h"
#include "collider_obj_vars.h"
#include <math.h>
#include <stdio.h>

// 내적 결과가 0보다 작고, 밑면 보다 위에 있어야 함
static int	is_position_sane(t_cone const *const cone,
								t_cone_coll_vars const *const vars,
								t_FTMFLOAT4 const *const pos)
{
	const float	dvh = ftmf4_vdot(vars->h_unit, ftmf4_vsub(*pos, cone->pvertex));

	return ((dvh < 0.0f) && (-dvh < vars->cone_height));
}

// 원뿔의 방정식을 풀어서 얻은 t1, t2는 크게 몇 가지 문제가 생길 수 있음.
// 둘 다 유효하지 않은 경우 or 둘 중 하나만 유효한 경우 or 둘 다 유효하지만 둘 중 가까운 것
// 유효성은 원뿔의 어느 면에 만나는지 여부로 측정할 예정
t_FTMFLOAT4	get_cone_hit(t_cone *cone, t_cone_coll_vars *vars, t_ray *r)
{
	t_FTMFLOAT4 const	pos1 = ray_at(r, vars->t1);
	t_FTMFLOAT4 const	pos2 = ray_at(r, vars->t2);
	int const			is_p1_sane = is_position_sane(cone, vars, &pos1);
	int const			is_p2_sane = is_position_sane(cone, vars, &pos2);

	if ((is_p1_sane && is_p2_sane && vars->t1 < vars->t2) || is_p1_sane)
	{
		vars->t = vars->t1;
		return (pos1);
	}
	else if ((is_p1_sane && is_p2_sane && vars->t2 < vars->t1) || is_p2_sane)
		vars->t = vars->t2;
	else
		vars->t = 0.0f;
	return (pos2);
}
