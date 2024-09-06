#include "parser.h"
#include "../light/light.h"

/**
 * @brief parse ambient line: <identifier> <ratio> <color>
 * @param line	"A	0.5	255,255,255"
 * @param rt	pointer to the raytracer
 * @return	void
 */
void	prs_ambient(t_ft_string *line, t_render_resource *resources)
{
	resources->amb_intens = prs_atof(&line);
	resources->amb_color = ftmf4_set_vector(prs_atof(&line), prs_atof(&line), prs_atof(&line), 0.0f);
	// (void)resources;
	// printf("-amb start-\n");
	// printf("A test : %s\n", line->pbuffer);
	// printf("---intense---\n");
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("---color---\n");
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("-amb finish-\n");
}

/**
 * @brief parse camera line: <identifier> <view_point> <normal_vector> <FOV>
 * @param line	"C	-50.0,0,20	0,0,1	70"
 * @param rt	pointer to the raytracer
 * @return	void
 */
void	prs_camera(t_ft_string *line, t_render_resource *resources)
{
	resources->cam.vpos = ftmf4_set_vector(prs_atof(&line), prs_atof(&line), prs_atof(&line), 1.0f);
	printf("vpos : %f, %f, %f\n", resources->cam.vpos.data[0], resources->cam.vpos.data[1], resources->cam.vpos.data[2]);
	resources->cam.vtarget = ftmf4_set_vector(prs_atof(&line), prs_atof(&line), prs_atof(&line), 0.0f);
	printf("vtarget : %f, %f, %f\n", resources->cam.vtarget.data[0], resources->cam.vtarget.data[1], resources->cam.vtarget.data[2]);
	resources->cam.vup = ftmf4_set_vector(0.0f, 0.0f, 1.0f, 0.0f);
	printf("vup : %f, %f, %f\n", resources->cam.vup.data[0], resources->cam.vup.data[1], resources->cam.vup.data[2]);
	// ftmf4_vnormalize(&resources->cam.vtarget);
	resources->fov = prs_atof(&line);
	printf("fov : %f\n", resources->fov);
	// (void)resources;
	// printf("-camera start-\n");
	// printf("C test : %s\n", line->pbuffer);
	// printf("---vtarget---\n");
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("---vup---\n");
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("---vpos---\n");
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("-camera finish-\n");
}

/**
 * @brief parse light line: <identifier> <center> <ratio> <color>
 * @param line	"L	0,0,20	0.5	255,255,255"
 * @param rt	pointer to the raytracer
 * @return	void
 */
void	prs_light(t_ft_string *line, t_render_resource *resources)
{
	t_light	*tmp;

	tmp = (t_light *)malloc(sizeof(t_light));
	tmp->ppos = ftmf4_set_vector(prs_atof(&line), prs_atof(&line), prs_atof(&line), 1.0f);
	tmp->intensity = prs_atof(&line);
	tmp->color = ftmf4_set_vector(prs_atof(&line), prs_atof(&line), prs_atof(&line), 0.0f);
	resources->lights->push_back(resources->lights, tmp);
	// (void)resources;
	// printf("-light start-\n");
	// printf("L test : %s\n", line->pbuffer);
	// printf("---ppos---\n");
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("---intensity---\n");
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("---color---\n");
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("-light finish-\n");
}