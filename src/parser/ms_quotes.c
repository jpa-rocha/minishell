/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:51:08 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/08 23:00:50 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_sq(char *str)
{
	char	*temp;
	size_t	i;
	int		k;

	i = 0;
	k = 0;
	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == SQ)
		{
			i++;
			while (str[i] != '\0' && str[i] != SQ)
			{
				temp[k] = str[i];					
				k++;
				i++;
			}
		}
 		else if (str[i] != SQ)
		{
			temp[k] = str[i];
			k++;
		}
		i++;
	}
	temp[k] = '\0';
	str = ft_strdup(temp);
	free (temp);
	return(str);
}

char	*remove_dq(char *str)
{
	char	*temp;
	size_t	i;
	int		k;
	
	i = 0;
	k = 0;
	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == DQ)
		{
			i++;
			while (str[i] != '\0' && str[i] != DQ)
			{
				temp[k] = str[i];		
				k++;
				i++;
			}
		}
 		else if (str[i] != DQ)
		{
			temp[k] = str[i];
			k++;
		}
		i++;
	}
	temp[k] = '\0';
	str = ft_strdup(temp);
	free(temp);
	return (str);
}

int	check_sq(char *str)
{
	size_t	i;
	int		quotes_flag;
	int		index;

	quotes_flag = 0;
	index = 0;
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
	while (i < ft_strlen(str))
	{
		if ((str[i] == SQ) && quotes_flag == 1)
		{
			index += i;
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
	int		quotes_flag;
	int		index;

	quotes_flag = 0;
	index = 0;
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
	while (i < ft_strlen(str))
	{
		if (str[i] == DQ && quotes_flag == 1)
		{
			index += i;
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
	int			s_flag;
	int			d_flag;

	i = 0;
	s_flag = check_sq(str);
	d_flag = check_dq(str);
	while (i < ft_strlen(str))
	{
		if (str[i] == SQ && s_flag == 0)
		{
			s_flag = 1;
			while (str[i] != '\0')
			{
				if (str[i] == DQ && d_flag == 0)
					str = remove_sq(str);
				i++;
			}
			if (s_flag == 1)
				str = remove_sq(str);
		}
 		if (str[i] == DQ && d_flag == 0)
		{
			d_flag = 1;
			while (str[i] != '\0')
			{
				if (str[i] == SQ && s_flag == 0)
					str = remove_dq(str);
				i++; 
			}
			if (d_flag == 1)
				str = remove_dq(str);
		}
		i++;
	}
	return (str);
}
