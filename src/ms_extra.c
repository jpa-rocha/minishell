/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:11:47 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/21 17:20:31 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	ms_prompt_create(char *prompt, t_envvar *user,
				t_envvar *path, t_envvar *home);
static char	*ms_colour(char *colour);
static char	*ms_prompt_null_handle(t_shell *shell);

void	ms_logo(void)
{
	printf("\e[1;31m  __        __   _            _     ");
	printf("                        _      _      \n");
	printf("\e[1;31m |  \\      /  | |_|          |_|     ");
	printf("                      | |    | |    \n");
	printf("\e[1;33m |   \\    /   |  _   __   _   _   __");
	printf("____   _    _   _____  | |    | |    \n");
	printf("\e[1;32m |    \\  /    | | | |  \\ | | | | | ");
	printf(" ____| | |  | | |  ___| | |    | |    \n");
	printf("\e[1;36m |  |\\ \\/ /|  | | | |   \\| | | | |");
	printf(" |____  | |__| | | |__   | |    | |    \n");
	printf("\e[1;34m |  | \\  / |  | | | | |\\   | | | |_");
	printf("____ | |  __  | |  __|  | |    | |    \n");
	printf("\e[1;35m |  |  \\/  |  | | | | | \\  | | |  _");
	printf("___| | | |  | | | |___  | |__  | |__  \n");
	printf("\e[1;35m |__|      |__| |_| |_|  \\_| |_| |__");
	printf("____| |_|  |_| |_____| |____| |____| \n");
	printf("\033[0m");
	printf("-------------------------------------");
	printf("------------------------------------\n");
	printf("  By mgulenay & jrocha \n");
	printf("-------------------------------------");
	printf("------------------------------------\n");
}

char	*ms_prompt(t_shell *shell)
{
	t_envvar	*user;
	t_envvar	*path;
	t_envvar	*home;
	char		*prompt;

	user = ms_init_vars(shell, "USER");
	path = ms_init_vars(shell, "PWD");
	home = ms_init_vars(shell, "HOME");
	if (user == NULL || path == NULL)
		return (ms_prompt_null_handle(shell));
	prompt = ft_calloc(26 + ft_strlen(user->value) + ft_strlen(path->value)
			+ 7, sizeof(char));
	if (prompt == NULL)
		return (ms_prompt_null_handle(shell));
	if (ms_prompt_create(prompt, user, path, home) != EXIT_SUCCESS)
		shell->exitcode = ALLOCATION_PROBLEM_EXIT;
	return (prompt);
}

static char	*ms_prompt_null_handle(t_shell *shell)
{
	char	*prompt;

	prompt = ft_calloc(ft_strlen("minishell$ ") + 1, sizeof(char));
	if (prompt == NULL)
	{
		shell->exitcode = ALLOCATION_PROBLEM_EXIT;
		return (prompt);
	}
	ft_strlcpy(prompt, "minishell$ ", ft_strlen("minishell$ ") + 1);
	return (prompt);
}

static int	ms_prompt_create(char *prompt, t_envvar *user,
	t_envvar *path, t_envvar *home)
{
	char		*relative;

	ft_strlcpy(prompt, ms_colour("green"), 8);
	ft_strlcpy(&prompt[ft_strlen(prompt)],
		user->value, ft_strlen(user->value) + 1);
	ft_strlcpy(&prompt[ft_strlen(prompt)], ms_colour("reset"), 5);
	prompt[ft_strlen(prompt)] = ':';
	ft_strlcpy(&prompt[ft_strlen(prompt)], ms_colour("blue"), 8);
	if (home != NULL &&
		ft_strncmp(path->value, home->value, ft_strlen(home->value)) == 0)
	{
		relative = ft_strjoin("~/", &path->value[ft_strlen(home->value) + 1]);
		if (relative == NULL)
			return (ALLOCATION_PROBLEM_EXIT);
		ft_strlcpy(&prompt[ft_strlen(prompt)],
			relative, ft_strlen(relative) + 1);
		free(relative);
	}
	else
		ft_strlcpy(&prompt[ft_strlen(prompt)],
			path->value, ft_strlen(path->value) + 1);
	ft_strlcpy(&prompt[ft_strlen(prompt)], ms_colour("reset"), 5);
	ft_strlcpy(&prompt[ft_strlen(prompt)], "$ ", ft_strlen("$ ") + 1);
	return (EXIT_SUCCESS);
}

static char	*ms_colour(char *colour)
{
	char		*ret;

	if (ft_strncmp(colour, "blue", ft_strlen(colour)) == 0)
		ret = "\033[1;34m";
	if (ft_strncmp(colour, "green", ft_strlen(colour)) == 0)
		ret = "\033[1;32m";
	if (ft_strncmp(colour, "reset", ft_strlen(colour)) == 0)
		ret = "\033[0m";
	return (ret);
}