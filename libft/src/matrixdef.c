/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixdef.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:22:18 by jrocha            #+#    #+#             */
/*   Updated: 2022/05/05 11:26:34 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/datastructures.h"

t_matrix	*matrix_init(int x, int y, int data_size)
{
	t_matrix	*matrix;

	matrix = ft_calloc(1, sizeof(t_matrix));
	if (matrix == NULL)
		return (NULL);
	matrix->count_x = x;
	matrix->count_y = y;
	matrix->capacity = x * y;
	matrix->data_size = data_size;
	matrix->data = (char *)ft_calloc(matrix->capacity, data_size);
	if (matrix->data == NULL)
		return (NULL);
	return (matrix);
}

void	matrix_cleanup(t_matrix *matrix)
{
	if (matrix == NULL)
		return ;
	if (matrix->data != NULL)
		free(matrix->data);
	free(matrix);
}

void	*matrix_get(t_matrix *matrix, int index_x, int index_y)
{
	char	*data;

	if (index_x < 0 || index_y < 0)
		return (NULL);
	if (index_x >= matrix->count_x || index_y >= matrix->count_y)
		return (NULL);
	data = matrix->data + (index_y * matrix->count_x * matrix->data_size)
		+ (index_x * matrix->data_size);
	return (data);
}

void	matrix_set(t_matrix *matrix, int index_x, int index_y, void *data)
{
	char	*block;

	if (index_x < 0 || index_y < 0)
		return ;
	if (index_x >= matrix->count_x)
		return ;
	if (index_y >= matrix->count_y)
	{
		if (matrix_resize(matrix, index_y + 1) == NULL)
			return ;
	}
	block = (char *)matrix_get(matrix, index_x, index_y);
	ft_memcpy(block, data, matrix->data_size);
}

void	*matrix_resize(t_matrix *matrix, int new_y)
{
	char	*new;

	new = ft_calloc(matrix->count_x * new_y, matrix->data_size);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, matrix->data, matrix->capacity * matrix->data_size);
	matrix->capacity = matrix->count_x * new_y;
	free(matrix->data);
	matrix->count_y = new_y;
	matrix->data = new;
	return (new);
}
