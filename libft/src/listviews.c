/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listviews.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:17:33 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/21 09:56:04 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/datastructures.h"

void	*list_check_current(t_list *list)
{
	if (list->current == NULL)
		return (NULL);
	return (list->current->data);
}

void	*list_check_top(t_list *list)
{
	if (list->last == NULL)
		return (NULL);
	list->current = list->last;
	return (list->last->data);
}

void	*list_check_bottom(t_list *list)
{
	if (list->first == NULL)
		return (NULL);
	list->current = list->first;
	return (list->first->data);
}

void	*list_check_next(t_list *list)
{
	if (list->current == list->last)
		return (NULL);
	list->current = list->current->next;
	return (list->current->data);
}

void	*list_check_prev(t_list *list)
{
	if (list->current == list->first)
		return (NULL);
	list->current = list->current->prev;
	return (list->current->data);
}
