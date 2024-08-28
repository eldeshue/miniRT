/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:24 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/28 19:26:26 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colliders.h"
#include "collider_obj_vars.h"
#include <math.h>

void	plane_coll_set_vars(t_plane_coll_vars *vars, t_FTMFLOAT4 p0_minus_o, t_FTMFLOAT4 ndir, t_FTMFLOAT4 vnormal)
{
	vars->denom = ftmf4_vdot(ndir, vnormal);
	if (fabs(vars->denom) < EPSILON) // 교차 가능성 있음
		vars->t = FLOAT_MAX; // 평행하여 교차하지 않음
	else
		vars->t = ftmf4_vdot(p0_minus_o, vnormal) / vars->denom;
}

void	plane_coll_set_hit(t_hit *hit, t_ray *r, t_plane *plane, t_plane_coll_vars vars, void *obj)
{
	hit->dist = vars.t;
	hit->ppos = ray_at(r, vars.t);
	hit->vnormal = plane->vnormal;
	set_face_normal(hit, r, plane->vnormal);
	hit->pobj = obj;
}

t_hit	collider_plane(const t_ray *r, void *obj)
{
	t_plane				*plane;
	t_hit				hit; // 충돌 정보를 저장할 구조체
	t_FTMFLOAT4			p0_minus_o; // 평면의 중심과 광선 시작점 사이의 벡터
	t_plane_coll_vars	vars; // 평면 충돌 계산에 사용되는 변수들

	plane = (t_plane *)obj;
	p0_minus_o = ftmf4_vsub(plane->pcenter, r->pstart);
	plane_coll_set_vars(&vars, p0_minus_o, r->ndir, plane->vnormal);
	if (vars.t < 0)
		hit.dist = -1.0; // 교차점이 유효하지 않은 경우
	else
		plane_coll_set_hit(&hit, (t_ray *)r, plane, vars, obj);
	return (hit);
}

