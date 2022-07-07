/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listdef.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:32:19 by jrocha            #+#    #+#             */
/*   Updated: 2022/05/05 11:29:15 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include "../header/datastructures.h"

static void	**node_init(int capacity, int data_size);

t_list	*list_creator(int capacity, int data_size)
{
	t_list	*newlist;

	newlist = ft_calloc(1, sizeof(t_list));
	if (newlist == NULL)
		return (NULL);
	newlist->capacity = capacity;
	newlist->data_size = data_size;
	newlist->nodes = node_init(capacity, data_size);
	newlist->first = newlist->nodes[0];
	newlist->last = newlist->first;
	newlist->current = newlist->last;
	return (newlist);
}

static void	**node_init(int capacity, int data_size)
{
	char	*buf;
	void	**nodes;
	t_node	*node;
	int		i;

	i = 0;
	nodes = ft_calloc(capacity, sizeof(void *));
	if (nodes == NULL)
		return (NULL);
	buf = ft_calloc(capacity, sizeof(t_node) + data_size);
	if (buf == NULL)
	{
		free(nodes);
		return (NULL);
	}
	while (i < capacity)
	{
		nodes[i] = buf + (i * (sizeof(t_node) + data_size));
		node = nodes[i];
		if (data_size != 0)
			node->data = buf
				+ (i * (sizeof(t_node) + data_size)) + sizeof(t_node);
		i++;
	}
	return (nodes);
}

void	list_add_back(void *data, t_list *list)
{
	t_node	*temp;

	if (list->total == list->capacity)
		list = list_resize(list);
	temp = list->nodes[list->total];
	ft_memcpy(temp->data, data, list->data_size);
	if (list->total == 0)
	{
		list->first = list->nodes[list->total];
		list->current = list->first;
	}
	list->last = list->nodes[list->total];
	if (list->total > 0)
	{
		list->last->prev = list->current;
		list->current->next = list->last;
	}
	list->current = list->last;
	list->total++;
}

void	list_destroyer(t_list *list)
{
	free(list->nodes[0]);
	free(list->nodes);
	free(list);
}
