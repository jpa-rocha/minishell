/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:11:47 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/14 20:11:13 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	ms_prompt_create(char *prompt, char *user,
				char *path, t_envvar *home);
static char	*ms_colour(char *colour);
static char	*ms_prompt_null_handle(t_shell *shell);

void	ms_logo(void)
{
	printf("\n\e[1;31m |\\\\\\      ///| |||          |||     ");
	printf("                      |||    |||    \n");
	printf("\e[1;33m ||\\\\\\    ///||                     ");
	printf("                       |||    |||    \n");
	printf("\e[1;32m |||\\\\\\  ///||| ||| ||\\\\ ||| ||| ||");
	printf("|||||| |||  ||| ||||||| |||    |||    \n");
	printf("\e[1;36m ||||\\\\\\///|||| ||| ||\\\\\\||| ||| |");
	printf("||      |||  ||| |||     |||    |||    \n");
	printf("\e[1;34m |||| \\\\// |||| ||| |||\\\\\\|| ||| ||");
	printf("|||||| |||||||| ||||||  |||    |||    \n");
	printf("\e[1;35m ||||  \\/  |||| ||| ||| \\\\|| |||   ");
	printf("   ||| |||  ||| |||     |||    |||    \n");
	printf("\e[1;35m ||||      |||| ||| |||  \\|| ||| |||");
	printf("||||| |||  ||| ||||||| |||||| |||||| \n");
	printf("\033[0m");
	printf("-------------------------------------");
	printf("------------------------------------\n\033[0m");
	printf("  By \e[1;32mmgulenay\033[0m & \e[1;32mjrocha\033[0m \n");
	printf("-------------------------------------");
	printf("------------------------------------\n\033[0m");
}

char	*ms_prompt(t_shell *shell)
{
	t_envvar	*home;
	t_envvar	*pwd;
	char		*prompt;
	char		buffer[PATH_SIZE];
	char		*path;

	ft_memset(buffer, 0, PATH_SIZE);
	path = getcwd(buffer, PATH_SIZE);
	home = ms_init_vars(shell, "HOME");
	pwd = ms_init_vars(shell, "PWD");
	if (pwd != NULL)
		path = pwd->value;
	prompt = ft_calloc(26 + ft_strlen(shell->user) + ft_strlen(path)
			+ 7, sizeof(char));
	if (prompt == NULL)
		return (ms_prompt_null_handle(shell));
	if (ms_prompt_create(prompt, shell->user, path, home) != EXIT_SUCCESS)
		shell->status = ALLOCATION_PROBLEM_EXIT;
	return (prompt);
}

static char	*ms_prompt_null_handle(t_shell *shell)
{
	char	*prompt;

	prompt = ft_strdup("minishell$ ");
	if (prompt == NULL)
	{
		shell->status = ALLOCATION_PROBLEM_EXIT;
		return (prompt);
	}
	return (prompt);
}

static int	ms_prompt_create(char *prompt, char *user,
	char *path, t_envvar *home)
{
	char		*rel;

	ft_strlcpy(prompt, ms_colour("green"), 8);
	ft_strlcpy(&prompt[ft_strlen(prompt)],
		user, ft_strlen(user) + 1);
	ft_strlcpy(&prompt[ft_strlen(prompt)], ms_colour("reset"), 5);
	prompt[ft_strlen(prompt)] = ':';
	ft_strlcpy(&prompt[ft_strlen(prompt)], ms_colour("blue"), 8);
	if (home != NULL
		&& ft_strncmp(path, home->value, ft_strlen(home->value)) == 0)
	{
		rel = ft_strjoin("~/", &path[ft_strlen(home->value)] + 1);
		ft_strlcpy(&prompt[ft_strlen(prompt)], rel, ft_strlen(rel) + 1);
		free(rel);
	}
	else
		ft_strlcpy(&prompt[ft_strlen(prompt)],
			path, ft_strlen(path) + 1);
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
