/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_other_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:48:10 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/20 14:10:28 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	*ms_dollar_check_helper(t_shell *shell, char *str, int i);
static char	*ms_replace_err(t_shell *shell, char *dollar, char *str);
static char	*ms_replace_var(t_shell *shell, char *dollar, char *str);

/* finds  dollar sign in the string
 + if env comes after we need to get env variable
 + if ? comes after we need to get exit status of the previous command call
 + if '$ENV' prints $ENV but if "$ENV" , print env variable
 + same also for $?
 */

/* check the single quotes, needs to return the string, not the actual value*/
void	*ms_dollar_check(t_shell *shell, char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ms_dollar_check_helper(shell, str, i);
	return (ret);
}

static char	*ms_dollar_check_helper(t_shell *shell, char *str, int i)
{
	char	*dollar;
	char	*ret;

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
						str = ms_replace_var(shell, dollar, str);
					else
						str = ms_replace_err(shell, dollar, str);
				}
			}
		}
		i++;
	}
	ret = ft_strdup(str);
	free(str);
	return (ret);
}

static char	*ms_replace_err(t_shell *shell, char *dollar, char *str)
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
