/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listpoints.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:05:12 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/21 09:56:19 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/datastructures.h"

t_node	*list_first(t_list *list)
{
	if (list->first == NULL)
		return (NULL);
	return (list->first);
}

t_node	*list_last(t_list *list)
{
	if (list->last == NULL)
		return (NULL);
	return (list->last);
}

t_node	*list_current(t_list *list)
{
	if (list->current == NULL)
		return (NULL);
	return (list->current);
}

t_node	*list_next(t_list *list)
{
	if (list->current->next == NULL)
		return (NULL);
	return (list->current->next);
}

t_node	*list_prev(t_list *list)
{
	if (list->current->prev == NULL)
		return (NULL);
	return (list->current->prev);
}
