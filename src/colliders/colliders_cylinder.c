/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   colliders_cylinder.c							   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/08/20 15:30:32 by dogwak			#+#	#+#			 */
/*   Updated: 2024/08/22 15:42:05 by hyeonwch		 ###   ########.fr	   */
/*																			*/
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

void	cylinder_coll_set_vars(t_cylinder_coll_vars *vars, t_FTMFLOAT4 oc, t_FTMFLOAT4 ndir, t_FTMFLOAT4 h_unit, t_cylinder cylinder)
{
	float a_dot = ftmf4_vdot(ndir, h_unit);
	float c_dot = ftmf4_vdot(oc, h_unit);
	float radius = cylinder.radius;
	vars->a = ftmf4_vdot(ndir, ndir) - pow(a_dot, 2);
	vars->b = 2.0 * (ftmf4_vdot(oc, ndir) - a_dot * c_dot);
	vars->c = ftmf4_vdot(oc, oc) - pow(c_dot, 2) - radius * radius;
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

		float hit_z = oc.data[2] + vars->t * ndir.data[2];  // z 축의 hit position 계산
		float pcenter1_z = cylinder.pcenter1.data[2]; // 원기둥의 밑면 z 값
		float pcenter2_z = cylinder.pcenter2.data[2]; // 원기둥의 윗면 z 값

		// hit_z가 원기둥의 높이 범위 내에 있는지 확인
		if (hit_z < pcenter2_z || hit_z > pcenter1_z) {
			vars->t = -1.0; // 교차점이 원기둥의 범위를 벗어남
		}
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
	t_FTMFLOAT4	*h_unit;
	t_FTMFLOAT4	tmp;
	t_FTMFLOAT4	h;

	tmp = ftmf4_vsub(cylinder->pcenter2, cylinder->pcenter1);
	h_unit = ftmf4_vnormalize(&tmp);
	h = vmult(h_unit, vars.t);
	hit->dist = vars.t;
	hit->ppos = ray_at(r, vars.t);
	if (hit->ppos.data[2] > cylinder->pcenter1.data[2] || hit->ppos.data[2] < cylinder->pcenter2.data[2])
	{
		hit->dist = -1.0f;
		return ;
	}
	pqtrn = ftmf4_vsub(ftmf4_vsub(hit->ppos, cylinder->pcenter1), h);
	hit->vnormal = *ftmf4_vnormalize(&pqtrn);
	hit->pobj = obj;
}

t_FTMFLOAT4 vscale(t_FTMFLOAT4 v, float s) {
	t_FTMFLOAT4	result;

	result.data[0] = v.data[0] * s;
	result.data[1] = v.data[1] * s;
	result.data[2] = v.data[2] * s;
	result.data[3] = v.data[3] * s; // 이 값은 보통 1.0f로 유지되지만, 필요한 경우 스케일링 가능

	return result;
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
	cylinder_coll_set_vars(&vars, oc, r->ndir, h_unit, *cylinder);

	if (vars.discriminant >= 0)
	{
		cylinder_coll_compute_t(&vars);
		if (vars.t > EPSILON) // 곡면과의 교차가 존재하는 경우
			cylinder_coll_set_hit(&hit, (t_ray *)r, cylinder, vars, obj);
	}

	// 윗면과의 교차
	t_FTMFLOAT4 top_center = cylinder->pcenter2;
	float t_top = ftmf4_vdot(ftmf4_vsub(top_center, r->pstart), h_unit) / ftmf4_vdot(r->ndir, h_unit);
	if (t_top > EPSILON) {
		t_FTMFLOAT4 hit_pos = ray_at((t_ray *)r, t_top);
		t_FTMFLOAT4 topsub = ftmf4_vsub(hit_pos, top_center);
		if (ftmf4_vsize(&topsub) <= cylinder->radius) {
			hit.dist = t_top;
			hit.ppos = hit_pos;
			hit.vnormal = h_unit;
			hit.pobj = obj;
		}
	}

	// 밑면과의 교차
	t_FTMFLOAT4 bottom_center = cylinder->pcenter1;
	float t_bottom = ftmf4_vdot(ftmf4_vsub(bottom_center, r->pstart), h_unit) / ftmf4_vdot(r->ndir, h_unit);
	if (t_bottom > EPSILON) {
		t_FTMFLOAT4 hit_pos = ray_at((t_ray *)r, t_bottom);
		t_FTMFLOAT4 bottomsub = ftmf4_vsub(hit_pos, bottom_center);
		if (ftmf4_vsize(&bottomsub) <= cylinder->radius) {
			hit.dist = t_bottom;
			hit.ppos = hit_pos;
			hit.vnormal = vscale(h_unit, -1); // 밑면의 법선은 윗면의 반대 방향
			hit.pobj = obj;
		}
	}

	return (hit);
}
