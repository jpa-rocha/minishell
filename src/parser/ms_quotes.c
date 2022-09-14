/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:51:08 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/14 20:03:04 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_replace_err(t_shell *shell, char *dollar, char *str);
static char	*ms_replace_var(t_shell *shell, char *dollar, char *str);
static int	check_dollar_in_quotes(char *str, size_t idx, int c);

char	*remove_quotes(char *str, int index, int quote)
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
			index += 1;
			while (str[index] != '\0' && str[index] != quote)
			{
				temp[k] = str[index];
				k += 1;
				index += 1;
			}
			ret = ft_strjoin(temp, &str[index + 1]);
			free(str);
			free(temp);
			return (ret);
		}
	}
	return (NULL);
}

int	flag_quotes(char *str, int quote)
{
	size_t	i;
	size_t	len;
	int		quotes_flag;

	quotes_flag = 0;
	if (ft_strncmp(str, "", 0) == 1)
		len = ft_strlen(str);
	else
		len = 0;
	i = 0;
	while (i < len && str[i] != '\0')
	{
		if ((str[i] == quote) && quotes_flag == 0)
		{
			quotes_flag = 1;
			break ;
		}
		i++;
	}
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
		s_flag = flag_quotes(str, SQ);
		d_flag = flag_quotes(str, DQ);
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
					str = remove_quotes(str, i, SQ);
					i = index;
				}
				i++;
			}
			if (flag_quotes(str, SQ) == 0)
			{
				index = i;
				index++;
				while (str[index] != SQ)
						index++;
				str = remove_quotes(str, i, SQ);
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
					str = remove_quotes(str, i, DQ);
					i = index;
				}
				i++;
			}
			if (flag_quotes(str, DQ) == 0)
			{
				index = i;
				index++;
				while (str[index] != DQ)
					index++;
				str = remove_quotes(str, i, DQ);
				i = index;
				i -= 2;
			}
		}
		i++;
	}
	return (str);
}
