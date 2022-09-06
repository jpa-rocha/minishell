/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:51:08 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/06 16:17:37 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* need to remove quotes for printing if it is already closed: 
 -- first check, if already in double or single quote, then remove it, 
-- if we have a case like : 
	echo "hello 'world' ", 
we need to remove just the double quote
*/
static int	check_dollar_in_quotes(char *str);
static char	*ms_replace_err(char *dollar, char *str);
static char	*ms_replace_var(t_shell *shell, char *dollar, char *str);

char	*remove_sq(char *str)
{
	char	*temp;
	int		i;
	int		k;
	
	i = 0;
	k = 0;
	temp = ft_calloc(ft_strlen(str) - 2, sizeof(char));
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
	//temp[k] = '\0';
	str = ft_strdup(temp);
	//printf("without quotes: %s\n", str);
	return(str);
}

char	*remove_dq(char *str)
{
	char	*temp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	temp = ft_calloc(ft_strlen(str) - 2, sizeof(char));
	if (!temp)
		return (NULL);
	while (str[i])
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
	str = ft_strdup(temp);
	free(temp);
	//printf("%s\n", str);
	return (str);
}


char	*check_quotes_pre_lexer(char *str)
{
	int		i;

	i = 0;
	if (check_quotes(str) == EXIT_SUCCESS)
	{
		while (str[i] != '\0')
		{
			if (str[i] == SQ)
				str = remove_sq(str);
			if (str[i] == DQ)
				str = remove_dq(str);				
			i++;
		}
	}
	return (str);
}

static int	check_dollar_in_quotes(char *str)
{
	size_t	i;
	int		quotes_flag;
	int		index;

	quotes_flag = 0;
	index = 0;
	i = 0;
	while (str[i])
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
		if (str[i] == '$' && quotes_flag == 0)
		{
			quotes_flag = 1;
			break ;
		}
		i--;
	}
	return (quotes_flag);
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
					str[i] = ms_replace_err(dollar, str[i]);
				}
			}
		}
		i += 1;
	}
	return (EXIT_SUCCESS);
}

static char	*ms_replace_err(char *dollar, char *str)
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
	num = ft_itoa(g_exit);
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
