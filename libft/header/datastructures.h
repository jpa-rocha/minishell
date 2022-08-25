/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datastructures.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:33:59 by jrocha            #+#    #+#             */
/*   Updated: 2022/08/22 15:16:16 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASTRUCTURES_H
# define DATASTRUCTURES_H

# include "libft.h"
# include <stdlib.h>

typedef struct s_node
{
	void			*data;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	int		capacity;
	int		total;
	int		data_size;
	void	**nodes;
	t_node	*first;
	t_node	*current;
	t_node	*last;
}	t_list;

typedef struct s_matrix
{
	int		count_x;
	int		count_y;
	int		capacity;
	int		data_size;
	char	*data;
}	t_matrix;

t_list		*list_creator(int capacity, int data_size);
void		list_destroyer(t_list *list);
void		**list_grow(t_list *list);
void		list_add_back(void *data, t_list *list);
void		**list_resize(t_list *list, int new_capacity);
void		*list_check_top(t_list *list);
void		*list_check_bottom(t_list *list);
void		*list_check_next(t_list *list);
void		*list_check_prev(t_list *list);
void		*list_check_current(t_list *list);
int			list_swap(t_list *list);
int			list_push(t_list *src, t_list *dst);
int			list_rotate(t_list *list);
int			list_reverse_rotate(t_list *list);
int			list_total(t_list *list);
int			list_capacity(t_list *list);
t_node		*list_first(t_list *list);
t_node		*list_last(t_list *list);
t_node		*list_current(t_list *list);
t_node		*list_next(t_list *list);
t_node		*list_prev(t_list *list);
t_matrix	*matrix_init(int x, int y, int data_size);
void		matrix_cleanup(t_matrix *matrix);
void		*matrix_get(t_matrix *matrix, int index_x, int index_y);
void		matrix_set(t_matrix *matrix, int index_x, int index_y, void *data);
void		*matrix_resize(t_matrix *matrix, int new_y);

#endif
