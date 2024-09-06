#include "parser.h"

/**
 * @brief parse plane line: <identifier> <center> <normal> <color>
 * @param line	"pl	0,0,20	0,1,0	255,255,255"
 * @param rt	pointer to the raytracer
 * @return void
 */
void	prs_plane(t_ft_string *line, t_render_resource *resources)
{
	// (void)resources;
	// printf("pl test : %s\n", line->pbuffer);
	t_obj_desc	*tmp;
	tmp = (t_obj_desc *)malloc(sizeof(t_obj_desc));
	tmp->type = plane;
	tmp->p1 = ftmf4_set_vector(prs_atof(&line), prs_atof(&line), prs_atof(&line), 1.0f);
	tmp->p2 = ftmf4_set_vector(prs_atof(&line), prs_atof(&line), prs_atof(&line), 0.0f);
	tmp->val = 0.0f;
	tmp->m.obj_color = ftmf4_set_vector(prs_atof(&line), prs_atof(&line), prs_atof(&line), 0.0f);
	resources->render_objects->push_back(resources->render_objects, tmp);
}

/**
 * @brief parse sphere line: <identifier> <center> <diameter> <color>
 * @param line	"sp	0,0,20	10	255,255,255"
 * @param rt	pointer to the raytracer
 * @return void
 */
void	prs_sphere(t_ft_string *line, t_render_resource *resources)
{
	t_obj_desc	*tmp;

	tmp = (t_obj_desc *)malloc(sizeof(t_obj_desc));
	tmp->type = sphere;
	tmp->p1 = ftmf4_set_vector(prs_atof(&line), prs_atof(&line), prs_atof(&line), 1.0f);
	printf("p1 : %f, %f, %f\n", tmp->p1.data[0], tmp->p1.data[1], tmp->p1.data[2]);
	tmp->val = prs_atof(&line);
	tmp->m.obj_color = ftmf4_set_vector(prs_atof(&line), prs_atof(&line), prs_atof(&line), 0.0f);
	printf("p1 : %f, %f, %f\n", tmp->m.obj_color.data[0], tmp->m.obj_color.data[1], tmp->m.obj_color.data[2]);
	resources->render_objects->push_back(resources->render_objects, tmp);
	// (void)resources;
	// printf("-sphere start-\n");
	// printf("sp test : %s\n", line->pbuffer);
	// printf("---center---\n");
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("---ratio---\n");
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("---color---\n");
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("atof_result : %f\n", prs_atof(&line));
	// printf("-sphere finish-\n");
}

/**
 * @brief parse cylinder line:
 *        <identifier> <center> <normal> <diameter> <height> <color>
 * @param line	"cy	0,0,20	0,1,0	10.2	10.4	255,255,255"
 * @param rt	pointer to the raytracer
 * @return void
 */
void	prs_cylinder(t_ft_string *line, t_render_resource *resources)
{
	(void)resources;
	printf("cy test : %s\n", line->pbuffer);
}

/**
 * @brief parse cone line:
 * 	      <identifier> <center> <normal> <diameter> <height> <color>
 * @warning line and world must not be NULL
 * @param line	"co	0,0,20	0,1,0	10.2	10.4	255,255,255"
 * @param rt	pointer to the raytracer
 * @return void
 */
void	prs_cone(t_ft_string *line, t_render_resource *resources)
{
	(void)resources;
	printf("co test : %s\n", line->pbuffer);
}