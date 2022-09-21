/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_other_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:48:10 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/21 10:07:01 by jrocha           ###   ########.fr       */
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
char	*ms_dollar_check(t_shell *shell, char *str)
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
					i = 0;
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
	t_dol_rep	*rep;
	char		*ret;

	rep = ft_calloc(1, sizeof(t_dol_rep));
	rep->beg_len = 0;
	rep->search = ms_replace_var_search(dollar + 1);
	rep->replace = ms_env_ret_value(shell, rep->search);
	if (rep->replace != NULL && ft_strlen(str) > 1)
	{
		while (str[rep->beg_len] != '$')
			rep->beg_len += 1;
		rep->beginning = ft_calloc(rep->beg_len + 1, sizeof(char));
		rep->var_len = ft_strlen(rep->replace);
		ft_strlcpy(rep->beginning, str, rep->beg_len + 1);
		rep->end = ft_strdup(&str[rep->beg_len + rep->var_len - 1]);
		rep->temp = ft_strjoin(rep->beginning, rep->replace);
		ret = ft_strjoin(rep->temp, rep->end);
		free(str);
		ms_dollar_rep_clean(rep);
		return (ret);
	}
	ret = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	ms_dollar_rep_clean(rep);
	free(str);
	return (ret);
}
