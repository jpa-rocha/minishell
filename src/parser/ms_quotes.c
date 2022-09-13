/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:51:08 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/13 11:15:54 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_replace_err(t_shell* shell, char *dollar, char *str);
static char	*ms_replace_var(t_shell *shell, char *dollar, char *str);

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
					str = remove_sq(str, i, SQ);
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
			if (flag_quotes(str, DQ) == 0)
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


void	*ms_dollar_check(t_shell *shell, char **str)
{
	char	*dollar;
	int		i;

	i = 0;
	while (str[i] != NULL)
	{
		if (check_dollar_in_quotes(str[i]) == 0)
		{
			dollar = ft_strchr(str[i], '$');
			if (dollar != NULL)
			{
				if (ft_strncmp(dollar + 1, "?", 1) != 0)
				{
					str[i] = ms_replace_var(shell, dollar, str[i]);
				}
				else
				{
					str[i] = ms_replace_err(shell, dollar, str[i]);
				}
			}
		}
		i += 1;
	}
	return (EXIT_SUCCESS);
}

static char	*ms_replace_err(t_shell* shell, char *dollar, char *str)
{
	char	*end;
	char	*beginning;
	char	*num;
	int		i;

	i = 0;
	while (str[i] != '$')
		i += 1;
	beginning = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(beginning, str, i + 1);
	dollar += 2;
	num = ft_itoa(shell->status);
	end = ft_strjoin(num, dollar);
	free(str);
	str = ft_strjoin(beginning, end);
	free(num);
	free(beginning);
	free(end);
	return (str);
}

static char	*ms_replace_var(t_shell *shell, char *dollar, char *str)
{
	char	*end;
	char	*beginning;
	int		i;

	i = 0;
	end = ms_env_ret_value(shell, dollar + 1);
	if (end != NULL)
	{
		while (str[i] != '$')
			i += 1;
		beginning = ft_calloc(i + 1, sizeof(char));
		ft_strlcpy(beginning, str, i + 1);
		free(str);
		str = ft_strjoin(beginning, end);
		free(beginning);
		free(end);
		return (str);
	}
	free(str);
	return (ft_strdup(""));
}
