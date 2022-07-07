/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:12:09 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/21 09:56:50 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include "../header/datastructures.h"

int	list_swap(t_list *list)
{
	if (list->last->prev == list->first)
	{
		list->current = list->last;
		list->last = list->first;
		list->first = list->current;
		list->first->prev = NULL;
		list->first->next = list->last;
		list->last->prev = list->first;
		list->last->next = NULL;
		list->current = list->last;
		return (0);
	}
	if (list->last->prev != NULL)
	{
		list->current = list->last;
		list->last = list->last->prev;
		list->current->prev = list->last->prev;
		list->current->prev->next = list->current;
		list->last->prev = list->current;
		list->last->next = NULL;
		list->current->next = list->last;
		list->current = list->last;
		return (0);
	}
	return (1);
}

static int	list_push_helper(t_list *src, t_list *dst)
{
	if (src->total == 0)
		return (1);
	if (src->total == 1)
	{
		src->last->prev = dst->last;
		dst->last->next = src->last;
		dst->last = src->last;
		src->last = NULL;
		src->first = NULL;
		src->current = NULL;
	}
	return (0);
}

int	list_push(t_list *src, t_list *dst)
{
	int	ret;

	ret = list_push_helper(src, dst);
	if (ret == 1)
		return (1);
	if (dst->total > 0)
		dst->last->next = src->last;
	if (src->total > 1)
	{
		src->current = src->last->prev;
		src->last->prev = dst->last;
		dst->last = src->last;
		src->last = src->current;
		src->last->next = NULL;
	}
	if (dst->total == 0)
	{
		dst->first = dst->last;
		dst->first->prev = NULL;
	}
	dst->current = dst->last;
	src->total--;
	dst->total++;
	return (0);
}

int	list_rotate(t_list *list)
{
	if (list->total < 2)
		return (1);
	if (list->total == 2)
	{
		list_swap(list);
		return (0);
	}
	list->current = list->last->prev;
	list->last->prev = NULL;
	list->last->next = list->first;
	list->first->prev = list->last;
	list->first = list->last;
	list->last = list->current;
	list->last->next = NULL;
	list->current = list->first;
	return (0);
}

int	list_reverse_rotate(t_list *list)
{
	if (list->total < 2)
		return (1);
	if (list->total == 2)
	{
		list_swap(list);
		return (0);
	}
	list->current = list->first->next;
	list->first->next = NULL;
	list->last->next = list->first;
	list->first->prev = list->last;
	list->last = list->first;
	list->first = list->current;
	list->first->prev = NULL;
	list->current = list->last;
	return (0);
}
