/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:29:56 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/08/22 20:48:13 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colliders.h"
#include "collider_obj_vars.h"
#include <math.h>
#include <stdio.h>

/** cone struct
typedef struct s_cone
{
	t_material	m;
	t_FTMFLOAT4	pcenter;
	t_FTMFLOAT4	pvertex;
	float		radius;
}				t_cone;
*/

void	cone_coll_set_vars(t_cone_coll_vars *vars, t_FTMFLOAT4 oc, t_FTMFLOAT4 ndir, t_FTMFLOAT4 h_unit, float m, t_cone cone)
{
	(void)cone;
	float a_dot = ftmf4_vdot(ndir, h_unit);
	float c_dot = ftmf4_vdot(oc, h_unit);
	vars->a = ftmf4_vdot(ndir, ndir) - (m + 1) * pow(a_dot, 2);
	vars->b = 2.0 * (ftmf4_vdot(oc, ndir) - (m + 1) * a_dot * c_dot);
	vars->c = ftmf4_vdot(oc, oc) - (m + 1) * pow(c_dot, 2);
	vars->discriminant = pow(vars->b, 2) - 4 * vars->a * vars->c;

	if (vars->a == 0) {
		vars->t = -1.0;  // 교차 없음으로 처리
	} else if (vars->discriminant < 0) {
		vars->t = -1.0; // 교차점 없음으로 설정
	} else {
		vars->sqrt_disc = sqrt(vars->discriminant);
		vars->t1 = (-vars->b - vars->sqrt_disc) / (2.0 * vars->a);
		vars->t2 = (-vars->b + vars->sqrt_disc) / (2.0 * vars->a);
		vars->t = cy_find_intersection_time(vars->t1, vars->t2);

	}
}

void	cone_coll_compute_t(t_cone_coll_vars *vars)
{
	vars->sqrt_disc = sqrt(vars->discriminant);
	vars->t1 = (-vars->b - vars->sqrt_disc) / (2.0 * vars->a);
	vars->t2 = (-vars->b + vars->sqrt_disc) / (2.0 * vars->a);
	vars->t = cy_find_intersection_time(vars->t1, vars->t2);
}


t_hit	collider_cone(const t_ray *r, void *obj)
{
	t_cone				*cone;
	t_hit				hit;
	t_FTMFLOAT4			oc; // 광선의 시작점과 원뿔 꼭짓점 사이의 벡터
	t_FTMFLOAT4			h_unit; // 원뿔의 높이 방향 벡터
	t_FTMFLOAT4			tmp;
	t_FTMFLOAT4			tmp2;
	t_cone_coll_vars	vars;

	cone = (t_cone *)obj;
	oc = ftmf4_vsub(r->pstart, cone->pvertex);
	tmp = ftmf4_vsub(cone->pvertex, cone->pcenter);
	tmp2 = ftmf4_vsub(cone->pvertex, cone->pcenter);
	h_unit = *ftmf4_vnormalize(&tmp);
	cone_coll_set_vars(&vars, oc, r->ndir, h_unit, pow(cone->radius / ftmf4_vsize(&tmp2) , 2), *cone);
	if (vars.discriminant < 0)
		hit.dist = -1.0;
	else
	{
		cone_coll_compute_t(&vars);
		if (vars.t == -1.0)
			hit.dist = -1.0;
		else
		{
			// hit 설정 (충돌 지점 계산)
			hit.dist = vars.t;
			hit.ppos = ray_at((t_ray *)r, vars.t);
			float projection = ftmf4_vdot(ftmf4_vsub(hit.ppos, cone->pvertex), h_unit);
			t_FTMFLOAT4 ww = ftmf4_vadd(cone->pvertex, vmult(&h_unit, projection));
			t_FTMFLOAT4 hit_normal = ftmf4_vsub(hit.ppos, ww);
			hit.vnormal = *ftmf4_vnormalize(&hit_normal);
			hit.pobj = obj;
		}

		t_FTMFLOAT4 bottom_center = cone->pcenter;
		float t_bottom = ftmf4_vdot(ftmf4_vsub(bottom_center, r->pstart), h_unit) / ftmf4_vdot(r->ndir, h_unit);
		if (t_bottom > EPSILON) {
			t_FTMFLOAT4 hit_pos = ray_at((t_ray *)r, t_bottom);
			t_FTMFLOAT4 bottomsub = ftmf4_vsub(hit_pos, bottom_center);
			if (ftmf4_vsize(&bottomsub) <= cone->radius) {
				hit.dist = t_bottom;
				hit.ppos = hit_pos;
				hit.vnormal = h_unit;
				hit.pobj = obj;
			}
		}

		// hit 검사
		if (hit.dist != -1.0)
		{
			t_FTMFLOAT4 center_to_vertex = ftmf4_vsub(cone->pvertex, cone->pcenter);
			t_FTMFLOAT4 center_to_hit = ftmf4_vsub(hit.ppos, cone->pcenter);

			if (ftmf4_vdot(center_to_hit, center_to_vertex) < 0||
				ftmf4_vsize(&center_to_vertex) < ftmf4_vsize(&center_to_hit))
			{
				hit.dist = -1.0f;
				hit.pobj = NULL;
			}
		}
	}
	return (hit);
}
