/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:11:47 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/20 16:04:33 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	ms_prompt_create(char *prompt, t_envvar *user,
				t_envvar *path, t_envvar *home);
static char	*ms_colour(char *colour);
static char	*ms_prompt_null_handle(t_shell *shell);

void	ms_logo(void)
{
	write(1, "  __        __   _            _     ", 37);
	write(1, "                        _      _      \n", 39);
	write(1, " |  \\      /  | |_|          |_|     ", 37);
	write(1, "                      | |    | |    \n", 38);
	write(1, " |   \\    /   |  _   __   _   _   __", 37);
	write(1, "____   _    _   _____  | |    | |    \n", 38);
	write(1, " |    \\  /    | | | |  \\ | | | | | ", 37);
	write(1, " ____| | |  | | |  ___| | |    | |    \n", 39);
	write(1, " |  |\\ \\/ /|  | | | |   \\| | | | |", 37);
	write(1, " |____  | |__| | | |__   | |    | |    \n", 40);
	write(1, " |  | \\  / |  | | | | |\\   | | | |_", 37);
	write(1, "____ | |  __  | |  __|  | |    | |    \n", 39);
	write(1, " |  |  \\/  |  | | | | | \\  | | |  _", 37);
	write(1, "___| | | |  | | | |___  | |__  | |__  \n", 39);
	write(1, " |__|      |__| |_| |_|  \\_| |_| |__", 37);
	write(1, "____| |_|  |_| |_____| |____| |____| \n", 38);
	write(1, "-------------------------------------", 37);
	write(1, "------------------------------------\n", 37);
	write(1, "  By mgulenay & jrocha \n", 25);
	write(1, "-------------------------------------", 37);
	write(1, "------------------------------------\n", 37);
}

char	*ms_prompt(t_shell *shell)
{
	t_envvar	*user;
	t_envvar	*path;
	t_envvar	*home;
	char		*prompt;

	user = NULL;
	path = NULL;
	home = NULL;
	if (ms_env_find_entry(shell->workenv, "USER") != NULL)
		user = (t_envvar *) ms_env_find_entry(shell->workenv, "USER")->data;
	if (ms_env_find_entry(shell->workenv, "PWD") != NULL)
		path = (t_envvar *) ms_env_find_entry(shell->workenv, "PWD")->data;
	if (ms_env_find_entry(shell->workenv, "HOME") != NULL)
		home = (t_envvar *) ms_env_find_entry(shell->workenv, "HOME")->data;
	if (user == NULL || path == NULL || home == NULL)
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
	if (ft_strncmp(path->value, home->value, ft_strlen(home->value)) == 0)
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