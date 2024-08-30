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
		return (FLOAT_MAX);  // 교차점이 없음을 의미
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
	if (vars->a < EPSILON)
		vars->t = FLOAT_MAX;  // 교차 없음으로 처리
	else if (vars->discriminant < 0)
		vars->t = FLOAT_MAX; // 교차점 없음으로 설정
	else
	{
		vars->sqrt_disc = sqrt(vars->discriminant);
		vars->t1 = (-vars->b - vars->sqrt_disc) / (2.0 * vars->a);
		vars->t2 = (-vars->b + vars->sqrt_disc) / (2.0 * vars->a);
		vars->t = cy_find_intersection_time(vars->t1, vars->t2);
		if (vars->t < EPSILON)
			vars->t = FLOAT_MAX;
	}
}

void check_cylinder_caps(t_hit *hit, t_ray *r, t_cylinder *cylinder, void *obj, int is_top)
{
	t_FTMFLOAT4 h;
	t_FTMFLOAT4	h_unit;
	t_FTMFLOAT4	center;
	t_FTMFLOAT4	p0_minus_o;
	t_FTMFLOAT4	cp;
	t_FTMFLOAT4 hit_pos;
	float		t;
	float		denom;

	h = ftmf4_vsub(cylinder->pcenter2, cylinder->pcenter1);
	h_unit = *ftmf4_vnormalize(&h);

	if (is_top)
		center = cylinder->pcenter2;
	else
	{
		center = cylinder->pcenter1;
		h_unit = vscale(h_unit, -1);
	}

	p0_minus_o = ftmf4_vsub(center, r->pstart);
	denom = ftmf4_vdot(r->ndir, h_unit);

	// denom이 0에 가까운 경우를 처리
	if (fabs(denom) < EPSILON)
	{
		hit->dist = FLOAT_MAX;
		hit->pobj = NULL;
		return ;
	}

	t = ftmf4_vdot(p0_minus_o, h_unit) / denom;
	hit_pos = ray_at(r, t);
	cp = ftmf4_vsub(center, hit_pos);

	// 교차점이 원기둥의 캡 범위 안에 있는지 확인
	if (ftmf4_vdot(cp, cp) <= pow(cylinder->radius, 2))
	{
		hit->dist = t;
		hit->ppos = hit_pos;
		hit->pobj = obj;
		hit->vnormal = h_unit;
		set_face_normal(hit, r, h_unit);
	}
	else
	{
		hit->dist = FLOAT_MAX;
		hit->pobj = NULL;
	}
}

void	cylinder_coll_set_hit(t_hit *hit, t_ray *r, t_cylinder *cylinder, t_cylinder_coll_vars vars, void *obj)
{
	t_FTMFLOAT4	pqtrn;
	t_FTMFLOAT4	h_unit;
	t_FTMFLOAT4	h;
	t_FTMFLOAT4	cylinder_axis;
	t_FTMFLOAT4	p_to_hit;
	float		height_on_axis;
	float		cylinder_height;

	// cylinder 축 계산
	h = ftmf4_vsub(cylinder->pcenter2, cylinder->pcenter1);
	h_unit = *ftmf4_vnormalize(&h);

	hit->dist = vars.t;
	hit->ppos = ray_at(r, vars.t);

	// 밑면에서 교차점까지의 벡터
	p_to_hit = ftmf4_vsub(hit->ppos, cylinder->pcenter1);

	// 원기둥 축 방향으로의 투영 길이
	height_on_axis = ftmf4_vdot(p_to_hit, h_unit);

	// 원기둥의 높이
	cylinder_axis = ftmf4_vsub(cylinder->pcenter2, cylinder->pcenter1);
	cylinder_height = ftmf4_vsize(&cylinder_axis);

	// 교차점이 원기둥의 높이 범위 내에 있는지 확인
	if (height_on_axis < 0 || height_on_axis > cylinder_height)
	{
		hit->dist = FLOAT_MAX;
		return ;
	}

	// 교차점에서 원기둥 축을 따라 height_on_axis 만큼 이동한 지점을 구하고, 이를 원기둥 표면에서의 교차점으로 변환
	pqtrn = ftmf4_vsub(p_to_hit, vmult(&h_unit, height_on_axis));
	hit->vnormal = *ftmf4_vnormalize(&pqtrn);
	hit->pobj = obj;
}


t_hit	collider_cylinder(const t_ray *r, void *obj)
{
	t_cylinder			*cylinder;
	t_hit				hit;
	t_hit				hit_surface;
	t_hit				hit_top;
	t_hit				hit_bottom;
	t_FTMFLOAT4			oc; // 광선의 시작점과 원의 중심(밑면) 사이의 벡터
	t_FTMFLOAT4			h_unit; // cylinder의 높이 방향 벡터
	t_FTMFLOAT4			tmp;
	t_cylinder_coll_vars	vars;

	cylinder = (t_cylinder *)obj;
	oc = ftmf4_vsub(r->pstart, cylinder->pcenter1);
	tmp = ftmf4_vsub(cylinder->pcenter2, cylinder->pcenter1);
	h_unit = *ftmf4_vnormalize(&tmp);
	cylinder_coll_set_vars(&vars, oc, r->ndir, h_unit, *cylinder);
	init_hit(&hit_surface);
	init_hit(&hit_top);
	init_hit(&hit_bottom);
	if (vars.discriminant >= 0)
	{
		if (vars.t == FLOAT_MAX)
			hit_surface.dist = FLOAT_MAX;
		else
			cylinder_coll_set_hit(&hit_surface, (t_ray *)r, cylinder, vars, obj);
	}
	check_cylinder_caps(&hit_top, (t_ray *)r, cylinder, obj, 0);
	check_cylinder_caps(&hit_bottom, (t_ray *)r, cylinder, obj, 1);
	if (hit_top.dist == FLOAT_MAX && hit_bottom.dist == FLOAT_MAX)
		hit = hit_surface;
	else if (hit_top.dist < hit_bottom.dist)
		hit = hit_top;
	else
		hit = hit_bottom;

	if (hit_surface.dist < hit.dist)
		hit = hit_surface;

	return (hit);
}
