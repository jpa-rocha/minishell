/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:51:08 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/12 22:19:50 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_sq(char *str, int index, int quote)
{
	char	*temp;
	char	*ret;
	int		k;

	k = 0;
	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, str, index + 1);
	k = index;
	while (str[index] != '\0')
	{
		if (str[index] == quote)
		{
			if (str[index + 1] == quote)
			{
				ret = ft_strjoin(temp, &str[index + 2]);
				free(str);
				free(temp);
				return (ret);
			}
			index++;
			while (str[index] != '\0' && str[index] != quote)
			{
				temp[k] = str[index];
				k++;					
				index++;
			}
			ret = ft_strjoin(temp, &str[index + 1]);
			free(str);
			free(temp);
			return (ret);
		}
	}
	return (NULL);
}

int	check_sq(char *str)
{
	size_t	i;
	size_t	len;
	int		quotes_flag;

	quotes_flag = 0;
	len = ft_strlen(str);
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == SQ) && quotes_flag == 0)
		{
			quotes_flag = 1;
			break ;
		}
		i++;
	}
	i++;
	while (i < len)
	{
		if ((str[i] == SQ) && quotes_flag == 1)
		{
			quotes_flag = 0;
			break ;
		}
		i++;
	}
	return (quotes_flag);
}

int	check_dq(char *str)
{
	size_t	i;
	size_t	len;
	int		quotes_flag;

	quotes_flag = 0;
	len = ft_strlen(str);
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == DQ) && quotes_flag == 0)
		{
			quotes_flag = 1;
			break ;
		}
		i++;
	}
	i++;
	while (i < len)
	{
		if (str[i] == DQ && quotes_flag == 1)
		{
			quotes_flag = 0;
			break ;
		}
		i++;
	}
	return (quotes_flag);
}

char	*check_quotes_pre_lexer(char *str)
{
	size_t		i;
	int			index;
	int			s_flag;
	int			d_flag;

	index = 0;
	i = 0;
	while (str[i] != '\0')
	{
		s_flag = check_sq(str);
		d_flag = check_dq(str);
		if (str[i] == SQ && s_flag == 0)
		{
			while (str[i] != '\0' && str[i] != SQ)
			{
				if (str[i] == DQ && d_flag == 0)
				{
					index = i;
					index++;
					while (str[index] != SQ)
						index++;
					str = remove_sq(str, i, SQ);
					i = index;
				}
				i++;
			}
			if (check_sq(str) == 0)
			{
				index = i;
				index++;
				while (str[index] != SQ)
						index++;
				str = remove_sq(str, i, SQ);
				i = index;
				i -= 2;
			}
		}
 		else if (str[i] == DQ && d_flag == 0) 
		{
			while (str[i] != '\0' && str[i] != DQ)
			{
				if (str[i] == SQ && s_flag == 0)
				{
					index = i;
					index++;
					while (str[index] != DQ)
						index++;
					str = remove_sq(str, i, DQ);
					i = index;
				}
				i++;
			}
			if (check_dq(str) == 0)
			{
					index = i;
					index++;
					while (str[index] != DQ)
						index++;
					str = remove_sq(str, i, DQ);
					i = index;
					i -= 2;
			}
		}
		i++;
	}
	return (str);
}
