/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:32 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/22 14:06:45 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colliders.h"
#include "collider_obj_vars.h"
#include <math.h>
#include <stdio.h>

float	find_intersection_time(float t1, float t2)
{
	if (t1 > 0 && t2 > 0)  // 둘 다 양수인 경우
	{
		return (t1 < t2) ? t1 : t2;  // 더 가까운 지점을 반환
	}
	else if (t1 > 0 || t2 > 0)  // 하나만 양수인 경우
	{
		return (t1 > 0) ? t1 : t2;  // 양수인 지점을 반환
	}
	else  // 둘 다 음수인 경우
	{
		return -1.0;  // 교차점이 없음을 의미
	}
}

void	sphere_coll_set_vars(t_shpere_coll_vars *vars, t_FTMFLOAT4 oc, t_FTMFLOAT4 ndir, float radius)
{
	vars->a = ftmf4_vdot(ndir, ndir);  // ndir의 크기를 이용하여 a 계산
	vars->b = 2.0 * ftmf4_vdot(oc, ndir);
	vars->c = ftmf4_vdot(oc, oc) - radius * radius;
	vars->discriminant = vars->b * vars->b - 4 * vars->a * vars->c;

	// 디버깅 정보 출력
	// printf("a: %f, b: %f, c: %f, discriminant: %f\n", vars->a, vars->b, vars->c, vars->discriminant);

	// a == 0 인 경우 특별 처리
	if (vars->a == 0) {
		vars->t = -1.0;  // 교차 없음으로 처리
	} else if (vars->discriminant < 0) {
		vars->t = -1.0; // 교차점 없음으로 설정
	} else {
		vars->sqrt_disc = sqrt(vars->discriminant);
		vars->t1 = (-vars->b - vars->sqrt_disc) / (2.0 * vars->a);
		vars->t2 = (-vars->b + vars->sqrt_disc) / (2.0 * vars->a);
		vars->t = find_intersection_time(vars->t1, vars->t2);
	}
}

void	sphere_coll_compute_t(t_shpere_coll_vars *vars)
{
	vars->sqrt_disc = sqrt(vars->discriminant);
	vars->t1 = (-vars->b - vars->sqrt_disc) / (2.0 * vars->a);
	vars->t2 = (-vars->b + vars->sqrt_disc) / (2.0 * vars->a);
	//printf("t1: %f, t2: %f\n", vars->t1, vars->t2);
	// t1과 t2가 구와의 교차점
	// 근이 2개일 경우, 양수이고 더 작은 값을 반환하여 가장 가까운 교차점을 선택
	vars->t = find_intersection_time(vars->t1, vars->t2);
}


void	sphere_coll_set_hit(t_hit *hit, t_ray *r, t_sphere *sphere, t_shpere_coll_vars vars, void *obj)
{
	t_FTMFLOAT4	pqtrn;

	hit->dist = vars.t;
	hit->ppos = ray_at(r, vars.t);
	pqtrn = ftmf4_vsub(hit->ppos, sphere->pcenter);
	hit->vnormal = *ftmf4_vnormalize(&pqtrn);
	hit->pobj = obj;
}

t_hit	collider_sphere(const t_ray *r, void *obj)
{
	t_sphere			*sphere;
	t_hit				hit; // 충돌 정보를 저장할 구조체
	t_FTMFLOAT4			oc; // 광선의 시작점과 구의 중심 사이의 벡터
	t_shpere_coll_vars	vars; // 구 충돌 계산에 사용되는 변수들

	hit.dist = -1.0;
	hit.ppos = ftmf4_set_vector(0.0f, 0.0f, 0.0f, 0.0f);
	hit.vnormal = ftmf4_set_vector(0.0f, 0.0f, 0.0f, 0.0f);
	hit.pobj = NULL;
	sphere = (t_sphere *)obj;
	oc = ftmf4_vsub(r->pstart, sphere->pcenter);
	sphere_coll_set_vars(&vars, oc, r->ndir, sphere->radius);
	if (vars.discriminant < 0)
		hit.dist = -1.0;
	else
	{
		sphere_coll_compute_t(&vars);
		if (vars.t == -1.0)
			hit.dist = -1.0;
		else
			sphere_coll_set_hit(&hit, (t_ray *)r, sphere, vars, obj);
	}
	return (hit);
}
