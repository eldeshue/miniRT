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
	resources->cam.vtarget = ftmf4_set_vector(prs_atof(&line), prs_atof(&line), prs_atof(&line), 0.0f);
	resources->cam.vup = ftmf4_set_vector(0.0f, 0.0f, 1.0f, 0.0f);
	resources->fov = prs_atof(&line);
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
}