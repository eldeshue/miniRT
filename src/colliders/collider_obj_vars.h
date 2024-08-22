/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collider_obj_vars.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:18 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/21 16:08:32 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLIDER_OBJ_VARS_H
# define COLLIDER_OBJ_VARS_H

# include "colliders.h"

/**
 * t_sphere_coll_vars 구조체
 *
 * 이 구조체는 광선과 구의 충돌 계산에서 사용되는 2차 방정식의 계수와 결과값들을 저장합니다.
 * 광선(ray)과 구(sphere)의 교차 여부를 계산하고 교차 시 교차 지점을 찾기 위해 필요한 변수들이 포함됩니다.
 *
 * @param a            2차 방정식의 계수 a (방정식에서 t^2의 계수)
 * @param b            2차 방정식의 계수 b (방정식에서 t의 계수)
 * @param c            2차 방정식의 상수항 c (방정식의 상수 부분)
 * @param discriminant 판별식 (b^2 - 4ac)으로, 방정식의 해의 존재 여부를 결정함
 * @param sqrt_disc    판별식의 제곱근 (sqrt(discriminant))으로, 방정식의 두 해를 계산하는 데 사용됨
 * @param t1           2차 방정식의 첫 번째 해 (t1 = (-b - sqrt_disc) / 2a)
 * @param t2           2차 방정식의 두 번째 해 (t2 = (-b + sqrt_disc) / 2a)
 * @param t            최종적으로 선택된 해, 교차 지점을 나타내는 값
 */
typedef struct s_sphere_coll_vars
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	sqrt_disc;
	float	t1;
	float	t2;
	float	t;
}	t_shpere_coll_vars;

/**
 * t_plane_coll_vars 구조체
 *
 * 이 구조체는 광선과 평면의 충돌 계산에서 사용되는 변수들을 저장합니다.
 * 광선(ray)과 평면(plane)의 교차 여부를 계산하고 교차 시 교차 지점을 찾기 위해 필요한 변수들이 포함됩니다.
 *
 * @param denom 평면의 방정식에서 광선의 방향벡터와 평면의 법선벡터의 내적값
 * @param t     광선과 평면이 교차하는 지점을 나타내는 값
 */
typedef struct s_plane_coll_vars
{
	float	denom;
	float	t;
}	t_plane_coll_vars;


/**
 * t_cylinder_coll_vars 구조체
 *
 * 이 구조체는 광선과 원통의 충돌 계산에서 사용되는 변수들을 저장합니다.
 * 광선(ray)과 원통(cylinder)의 교차 여부를 계산하고 교차 시 교차 지점을 찾기 위해 필요한 변수들이 포함됩니다.
 *
 * @param a            2차 방정식의 계수 a (방정식에서 t^2의 계수)
 * @param b            2차 방정식의 계수 b (방정식에서 t의 계수)
 * @param c            2차 방정식의 상수항 c (방정식의 상수 부분)
 * @param discriminant 판별식 (b^2 - 4ac)으로, 방정식의 해의 존재 여부를 결정함
 * @param sqrt_disc    판별식의 제곱근 (sqrt(discriminant))으로, 방정식의 두 해를 계산하는 데 사용됨
 * @param t1           2차 방정식의 첫 번째 해 (t1 = (-b - sqrt_disc) / 2a)
 * @param t2           2차 방정식의 두 번째 해 (t2 = (-b + sqrt_disc) / 2a)
 * @param t            최종적으로 선택된 해, 교차 지점을 나타내는 값
 */
typedef struct s_cylinder_coll_vars
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	sqrt_disc;
	float	t1;
	float	t2;
	float	t;
}	t_cylinder_coll_vars;

#endif
