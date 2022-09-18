/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:51:08 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/18 19:52:26 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_r_quotes(char *str, char *temp)
{
	free(str);
	free(temp);
}

char	*remove_quotes(char *str, int index, int quote)
{
	char	*temp;
	char	*ret;
	int		k;

	k = 0;
	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	ft_strlcpy(temp, str, index + 1);
	k = index;
	while (str[index] != '\0')
	{
		if (str[index] == quote)
		{
			if (str[index + 1] == quote)
			{
				ret = ft_strjoin(temp, &str[index + 2]);
				free_r_quotes(str, temp);
				return (ret);
			}
			index += 1;
			while (str[index] != '\0' && str[index] != quote)
			{
				temp[k] = str[index];
				k += 1;
				index += 1;
			}
			ret = ft_strjoin(temp, &str[index + 1]);
			free_r_quotes(str, temp);
			return (ret);
		}
	}
	return (NULL);
}

static int	quotes_len(char *str)
{
	size_t	len;

	if (ft_strncmp(str, "", 0) == 1)
		len = ft_strlen(str);
	else
		len = 0;
	return (len);
}

static void	flag_quotes_helper(char *str, size_t i, size_t len, int quote)
{
	int	quotes_flag;

	quotes_flag = 0;
	while (i < len && str[i] != '\0')
	{
		if ((str[i] == quote) && quotes_flag == 0)
		{
			quotes_flag = 1;
			break ;
		}
		i++;
	}
}

int	flag_quotes(char *str, int quote)
{
	size_t	i;
	size_t	len;
	int		quotes_flag;

	quotes_flag = 0;
	len = quotes_len(str);
	i = 0;
	flag_quotes_helper(str, i, len, quote);
	i++;
	while (i < len && str[i] != '\0')
	{
		if ((str[i] == quote) && quotes_flag == 1)
		{
			quotes_flag = 0;
			break ;
		}
		i++;
	}
	return (quotes_flag);
}
