/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:17:59 by dogwak            #+#    #+#             */
/*   Updated: 2024/08/09 18:23:05 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include <stdlib.h>

int	alloc_light(void *paddr, void *plight)
{
	t_light *const	param = plight;

	*(t_light **)paddr = malloc(sizeof(t_light));
	if (*(t_light **)paddr == NULL)
		return (0);
	**(t_light **)paddr = *param;
	return (1);
}

void	free_light(void *paddr)
{
	free(*(t_light **)paddr);
}
