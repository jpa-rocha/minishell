/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_other_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:48:10 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/14 19:50:41 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* finds  dollar sign in the string
 + if env comes after we need to get env variable
 + if ? comes after we need to get exit status of the previous command call
 + if '$ENV' prints $ENV but if "$ENV" , print env variable
 + same also for $?
 */

static int	check_dollar_in_quotes(char *str, size_t idx, int c)
{
	int		quotes_flag;
	int		index;
	size_t	i;

	i = 0;
	quotes_flag = 0;
	index = 0;
	while (i < idx)
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
	i = index - 1;
	while (i < ft_strlen(str))
	{
		if (str[i] == c && quotes_flag == 0)
		{
			quotes_flag = 1;
			break ;
		}
		i--;
	}
	return (quotes_flag);
}

/* check the single quotes, needs to return the string, not the actual value*/
void	*ms_dollar_check(t_shell *shell, char *str)
{
	char	*dollar;
	char	*ret;
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{	
			if (check_dollar_in_quotes(str, i, '$') == 0)
			{
				dollar = ft_strchr(str, '$');
				if (dollar != NULL)
				{
					if (ft_strncmp(dollar + 1, "?", 1) != 0)
					{
						str = ms_replace_var(shell, dollar, str);
					}
					else
					{
						str = ms_replace_err(shell, dollar, str);
					}
				}
			}
		}
		i++;
	}
	ret = ft_strdup(str);
	free(str);
	return (ret);
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
