/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_atof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:20:52 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/09/05 20:33:48 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

float prs_atof(t_ft_string **str)
{
	float	ret;
	size_t	i;
	int		sign;

	ret = 0.0f;
	i = 0;
	sign = 1;
	while (*((*str)->at((*str), i)) == ' ' || *((*str)->at((*str), i)) == '\t')
		i++;
	if (*((*str)->at((*str), i)) == '-')
	{
		sign = -1;
		i++;
	}
	while (i < (*str)->size && *((*str)->at((*str), i)) >= '0' && *((*str)->at((*str), i)) <= '9')
	{
		if ((*str)->size <= i)
			break ;
		ret = ret * 10 + *((*str)->at((*str), i)) - '0';
		i++;
	}
	if (i < (*str)->size && *((*str)->at((*str), i)) == '.')
	{
		i++;
		float dec = 1.0f;
		while (*((*str)->at((*str), i)) >= '0' && *((*str)->at((*str), i)) <= '9')
		{
			dec /= 10;
			ret += (*((*str)->at((*str), i)) - '0') * dec;
			i++;
			if ((*str)->size <= i)
				break ;
		}
	}
	ret *= sign;
	if ((*str)->size > i)
	{
		if (*((*str)->at((*str), i)) == 'f')
			i++;
		if (*((*str)->at((*str), i)) == ',')
			i++;
		t_ft_string	*tmp = (*str)->substr((*str), i, (*str)->size - i);
		free(*str);
		*str = tmp;
	}
	return (ret);
}