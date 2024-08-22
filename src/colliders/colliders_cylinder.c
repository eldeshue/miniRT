/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:32 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/22 13:29:26 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colliders.h"
#include "collider_obj_vars.h"
#include <math.h>
#include <stdio.h>

/** cylinder struct
typedef struct s_cylinder
{
	t_material	m;
	t_FTMFLOAT4	pcenter1; // 밑면으로 생각하고 짜기
	t_FTMFLOAT4	pcenter2;
	float		radius;
}				t_cylinder;
*/

float	cy_find_intersection_time(float t1, float t2)
{
	if (t1 > EPSILON && t2 > EPSILON)  // 둘 다 양수인 경우
	{
		if (t1 < t2)
			return (t1);  // 가까운 지점 반환
		else
			return (t2);  // 가까운 지점 반환
	}
	else if ((t1 < EPSILON && t2 > EPSILON) || (t1 > EPSILON && t2 < EPSILON)) // 하나는 음수, 하나는 양수인 경우
	{
		if (t1 < EPSILON)
			return (t2);  // 양수인 지점 반환
		else
			return (t1);  // 양수인 지점 반환
	}
	else  // 둘 다 음수인 경우
	{
		if (fabs(t1) < fabs(t2))
			return (t1);  // 가까운 지점 반환
		else
			return (t2);  // 가까운 지점 반환
	}
}

void	cylinder_coll_set_vars(t_cylinder_coll_vars *vars, t_FTMFLOAT4 oc, t_FTMFLOAT4 ndir, t_FTMFLOAT4 h_unit, float radius)
{
	float a_dot = ftmf4_vdot(ndir, h_unit);

	vars->a = ftmf4_vdot(ndir, ndir) - pow(a_dot, 2);
	vars->b = 2.0 * (ftmf4_vdot(oc, ndir) - a_dot * ftmf4_vdot(oc, h_unit));
	vars->c = ftmf4_vdot(oc, oc) - pow(ftmf4_vdot(oc, h_unit), 2) - radius * radius;
	vars->discriminant = vars->b * vars->b - 4 * vars->a * vars->c;

	// 디버깅 정보 출력
	// printf("a: %f, b: %f, c: %f, discriminant: %f\n", vars->a, vars->b, vars->c, vars->discriminant);

	// a == 0인 경우 특별 처리
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


void	cylinder_coll_compute_t(t_cylinder_coll_vars *vars)
{
	vars->sqrt_disc = sqrt(vars->discriminant);
	vars->t1 = (-vars->b - vars->sqrt_disc) / (2.0 * vars->a);
	vars->t2 = (-vars->b + vars->sqrt_disc) / (2.0 * vars->a);
	vars->t = cy_find_intersection_time(vars->t1, vars->t2);
}

void	cylinder_coll_set_hit(t_hit *hit, t_ray *r, t_cylinder *cylinder, t_cylinder_coll_vars vars, void *obj)
{
	t_FTMFLOAT4	pqtrn;
	t_FTMFLOAT4	h_unit;
	t_FTMFLOAT4	tmp;
	t_FTMFLOAT4	h;

	tmp = ftmf4_vsub(cylinder->pcenter2, cylinder->pcenter1);
	h_unit = *ftmf4_vnormalize(&tmp);
	h = vmult(&h_unit, vars.t);
	hit->dist = vars.t;
	hit->ppos = ray_at(r, vars.t);
	// printf("Intersection Point: (%f, %f, %f)\n",
        //    hit->ppos.data[0], hit->ppos.data[1], hit->ppos.data[2]);
	pqtrn = ftmf4_vsub(ftmf4_vsub(hit->ppos, cylinder->pcenter1), h);
	hit->vnormal = *ftmf4_vnormalize(&pqtrn);
	hit->pobj = obj;
}

t_hit	collider_cylinder(const t_ray *r, void *obj)
{
	t_cylinder			*cylinder;
	t_hit				hit;
	t_FTMFLOAT4			oc; // 광선의 시작점과 원의 중심(밑면) 사이의 벡터
	t_FTMFLOAT4			h_unit; // cylinder의 높이 방향 벡터
	t_FTMFLOAT4			tmp;
	t_cylinder_coll_vars	vars;

	cylinder = (t_cylinder *)obj;
	oc = ftmf4_vsub(r->pstart, cylinder->pcenter1);
	tmp = ftmf4_vsub(cylinder->pcenter2, cylinder->pcenter1);
	h_unit = *ftmf4_vnormalize(&tmp);
	cylinder_coll_set_vars(&vars, oc, r->ndir, h_unit, cylinder->radius);
	if (vars.discriminant < 0)
		hit.dist = -1.0;
	else
	{
		cylinder_coll_compute_t(&vars);
		if (vars.t == -1.0)
			hit.dist = -1.0;
		else
			cylinder_coll_set_hit(&hit, (t_ray *)r, cylinder, vars, obj);
	}
	return (hit);
}
