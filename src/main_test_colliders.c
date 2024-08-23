/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main_test_colliders.c							  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/08/17 18:26:03 by hyeonwch		  #+#	#+#			 */
/*   Updated: 2024/08/22 13:23:00 by hyeonwch		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "./libft/libft.h"
#include "./raytracer/raytracer.h"
#include <stdio.h>
#include <math.h>
#include "./colliders/colliders.h"

void run_cylinder_tests()
{
	t_hit hit;

	// Test Case 1: 원기둥의 내부에서 시작하여 외부로 나가는 경우
	t_cylinder cylinder1 = { {0}, {{0, 0, 0, 1}}, {{0, 0, 2, 1}}, 1.0 };
	t_ray ray1 = { {{0, 0, 1, 1}}, {{0, 0, 1, 0}} };
	hit = collider_cylinder(&ray1, &cylinder1);
	printf("Cylinder Collider Test Case 1:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected to hit at a positive distance.\n\n");

	// Test Case 2: 원기둥의 외부에서 시작하여 스쳐 지나가는 경우
	t_cylinder cylinder2 = { {0}, {{0, 0, 0, 1}}, {{0, 0, 2, 1}}, 1.0 };
	t_ray ray2 = { {{2, 0, 1, 1}}, {{1, 0, 0, 0}} };
	hit = collider_cylinder(&ray2, &cylinder2);
	printf("Cylinder Collider Test Case 2:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected hit distance: -1.0 (no intersection)\n\n");

	// Test Case 3: 원기둥의 중심을 관통하는 경우
	t_cylinder cylinder3 = { {0}, {{0, 0, 0, 1}}, {{0, 0, 2, 1}}, 1.0 };
	t_ray ray3 = { {{0, 0, 3, 1}}, {{0, 0, -1, 0}} };
	hit = collider_cylinder(&ray3, &cylinder3);
	printf("Cylinder Collider Test Case 3:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected to hit at a positive distance.\n\n");

	// Test Case 4: 원기둥의 표면에서 시작하여 외부로 나가는 경우
	t_cylinder cylinder4 = { {0}, {{0, 0, 0, 1}}, {{0, 0, 2, 1}}, 1.0 };
	t_ray ray4 = { {{1, 0, 1, 1}}, {{1, 0, 0, 0}} };
	hit = collider_cylinder(&ray4, &cylinder4);
	printf("Cylinder Collider Test Case 4:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected hit distance: -1.0 (no intersection)\n\n");

	// Test Case 5: 원기둥의 외부에서 시작하여 내부로 진입하는 경우
	t_cylinder cylinder5 = { {0}, {{0, 0, 0, 1}}, {{0, 0, 2, 1}}, 1.0 };
	t_ray ray5 = { {{2, 0, 1, 1}}, {{-1, 0, 0, 0}} };
	hit = collider_cylinder(&ray5, &cylinder5);
	printf("Cylinder Collider Test Case 5:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected to hit at a positive distance.\n\n");
}

void run_sphere_tests()
{
	t_hit hit;

	// Test Case 1: 구의 내부에서 광선이 출발하여 외부로 나가는 경우
	t_sphere sphere1 = { {0}, {{0, 0, 0, 1}}, 1.0 };
	t_ray ray1 = { {{0, 0, 0.5, 1}}, {{0, 0, 1, 0}} };
	hit = collider_sphere(&ray1, &sphere1);
	printf("Sphere Collider Test Case 1:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected to hit at a positive distance.\n\n");

	// Test Case 2: 구의 외부에서 시작하여 구를 스쳐 지나가는 경우 (조정된 시작점)
	t_sphere sphere2 = { {0}, {{0, 0, 0, 1}}, 0.95 };
	t_FTMFLOAT4 *v = ftmf4_vnormalize(&(t_FTMFLOAT4){{0.1, -1, 1, 0}});
	t_ray ray2 = { {{0, 2, -2, 1}}, *v };
	hit = collider_sphere(&ray2, &sphere2);
	printf("Sphere Collider Test Case 2:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected hit distance: -1.0 (no intersection)\n\n");

	// Test Case 3: 구의 표면에서 시작하여 구를 통과하는 경우
	t_sphere sphere3 = { {0}, {{0, 0, 0, 1}}, 1.0 };
	t_ray ray3 = { {{0, 0, 1, 1}}, {{0, 0, -1, 0}} };
	hit = collider_sphere(&ray3, &sphere3);
	printf("Sphere Collider Test Case 3:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected to hit at a positive distance.\n\n");

	// Test Case 4: 구의 표면에서 시작하여 외부로 나가는 경우
	t_sphere sphere4 = { {0}, {{0, 0, 0, 1}}, 1.0 };
	t_ray ray4 = { {{0, 0, 1, 1}}, {{0, 0, 1, 0}} };
	hit = collider_sphere(&ray4, &sphere4);
	printf("Sphere Collider Test Case 4:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected hit distance: -1.0 (no intersection)\n\n");

	// Test Case 5: 구의 외부에서 시작하여 중심을 향하는 경우
	t_sphere sphere5 = { {0}, {{0, 0, 0, 1}}, 1.0 };
	t_ray ray5 = { {{2, 0, 0, 1}}, {{-1, 0, 0, 0}} };
	hit = collider_sphere(&ray5, &sphere5);
	printf("Sphere Collider Test Case 5:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected to hit at a positive distance.\n\n");
}

void run_plane_tests()
{
	t_hit hit;

	// Test Case 1: 광선이 평면을 수직으로 통과하는 경우
	t_plane plane1 = { {0}, {{0, 0, 0, 1}}, {{0, 1, 0, 0}} };
	t_ray ray1 = { {{0, -2, 0, 1}}, {{0, 1, 0, 0}} };
	hit = collider_plane(&ray1, &plane1);
	printf("Plane Collider Test Case 1:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected to hit at a positive distance.\n\n");

	// Test Case 2: 광선이 평면과 평행하게 진행하는 경우
	t_plane plane2 = { {0}, {{0, 0, 0, 1}}, {{0, 1, 0, 0}} };
	t_ray ray2 = { {{0, 2, 0, 1}}, {{1, 0, 0, 0}} };
	hit = collider_plane(&ray2, &plane2);
	printf("Plane Collider Test Case 2:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected hit distance: -1.0 (no intersection)\n\n");

	// Test Case 3: 광선이 평면과 역방향으로 진행하는 경우
	t_plane plane3 = { {0}, {{0, 0, 0, 1}}, {{0, 1, 0, 0}} };
	t_ray ray3 = { {{0, -2, 0, 1}}, {{0, -1, 0, 0}} };
	hit = collider_plane(&ray3, &plane3);
	printf("Plane Collider Test Case 3:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected hit distance: -1.0 (no intersection)\n\n");

	// Test Case 4: 평면의 표면에서 광선이 시작하는 경우
	t_plane plane4 = { {0}, {{0, 0, 0, 1}}, {{0, 1, 0, 0}} };
	t_ray ray4 = { {{0, 0, 0, 1}}, {{0, 1, 0, 0}} };
	hit = collider_plane(&ray4, &plane4);
	printf("Plane Collider Test Case 4:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected to hit at a positive distance.\n\n");

	// Test Case 5: 평면의 뒤에서 광선이 시작하는 경우
	t_plane plane5 = { {0}, {{0, 0, 0, 1}}, {{0, 1, 0, 0}} };
	t_ray ray5 = { {{0, -1, 0, 1}}, {{0, 1, 0, 0}} };
	hit = collider_plane(&ray5, &plane5);
	printf("Plane Collider Test Case 5:\n");
	printf("Hit distance: %f\n", hit.dist);
	printf("Expected to hit at a positive distance.\n\n");
}

int main()
{
	 // Run sphere collision tests
	run_sphere_tests();

	// Run plane collision tests
	run_plane_tests();

	// Run cylinder collision tests
	run_cylinder_tests();
	return 0;
}
