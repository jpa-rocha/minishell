/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:54:37 by jrocha            #+#    #+#             */
/*   Updated: 2022/05/05 11:25:44 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/datastructures.h"

int	list_total(t_list *list)
{
	if (list == NULL)
		return (0);
	return (list->total);
}

int	list_capacity(t_list *list)
{
	if (list == NULL)
		return (0);
	return (list->capacity);
}

t_list	*list_resize(t_list *list)
{
	t_list	*new;

	new = list_creator((int) list->capacity + (list->capacity / 4),
			list->data_size);
	ft_memcpy(new, list, sizeof(list));
	free(list);
	return (new);
}
