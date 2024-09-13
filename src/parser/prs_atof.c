/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_atof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:20:52 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/09/13 15:43:28 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	skip_whitespace_and_handle_sign(t_ft_string **str, size_t *i)
{
	int	sign;

	sign = 1;
	if (*(*str)->at(*str, *i) == ' ' || *(*str)->at(*str, *i) == '\t'
		|| *(*str)->at(*str, *i) == '\n' || *(*str)->at(*str, *i) == '\r'
		|| *(*str)->at(*str, *i) == '\f' || *(*str)->at(*str, *i) == '\v')
		prs_error_exit("Invalid string");
	while (*(*str)->at(*str, *i) == ' ' || *(*str)->at(*str, *i) == '\t'
		|| *(*str)->at(*str, *i) == '\n' || *(*str)->at(*str, *i) == '\r'
		|| *(*str)->at(*str, *i) == '\f' || *(*str)->at(*str, *i) == '\v')
		(*i)++;
	if (*((*str)->at((*str), *i)) == '-')
	{
		sign = -1;
		(*i)++;
	}
	return (sign);
}

static float	parse_integer_part(t_ft_string **str, size_t *i)
{
	float	ret;

	ret = 0.0f;
	if (*i > (*str)->size || *((*str)->at((*str), *i)) < '0'
		|| *((*str)->at((*str), *i)) > '9')
		prs_error_exit("Invalid string");
	while (*i < (*str)->size && *((*str)->at((*str), *i)) >= '0'
		&& *((*str)->at((*str), *i)) <= '9')
	{
		if ((*str)->size <= *i)
			break ;
		ret = ret * 10 + *((*str)->at((*str), *i)) - '0';
		(*i)++;
	}
	return (ret);
}

static float	parse_decimal_part(t_ft_string **str, size_t *i)
{
	float	ret;
	float	dec;	

	ret = 0.0f;
	dec = 1.0f;
	if (*i > (*str)->size || *((*str)->at((*str), *i)) < '0'
		|| *((*str)->at((*str), *i)) > '9')
		prs_error_exit("Invalid string");
	while (*((*str)->at((*str), *i)) >= '0' && *((*str)->at((*str), *i)) <= '9')
	{
		dec /= 10;
		ret += (*((*str)->at((*str), *i)) - '0') * dec;
		(*i)++;
		if ((*str)->size <= *i)
			break ;
	}
	return (ret);
}

static void	update_string(t_ft_string **str, size_t i)
{
	t_ft_string	*tmp;

	tmp = NULL;
	if ((*str)->size > i && *((*str)->at((*str), i)) == ',')
		i++;
	tmp = (*str)->substr((*str), i, (*str)->size - i);
	delete_ftstr(*str);
	*str = tmp;
}

float	prs_atof(t_ft_string **str)
{
	float	ret;
	size_t	i;
	int		sign;

	if ((*str)->size == 0)
		prs_error_exit("Empty string");
	ret = 0.0f;
	i = 0;
	sign = skip_whitespace_and_handle_sign(str, &i);
	ret = parse_integer_part(str, &i);
	if (i < (*str)->size && *((*str)->at((*str), i)) == '.')
	{
		i++;
		ret += parse_decimal_part(str, &i);
	}
	ret *= sign;
	update_string(str, i);
	return (ret);
}
