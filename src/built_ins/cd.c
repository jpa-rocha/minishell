/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:26:27 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/01 12:02:24 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_cd_path_exists(t_shell *shell, t_envvar *path,
				t_envvar *oldpath);
static int	ms_cd_paths_null(t_shell *shell, t_envvar *path,
				t_envvar *oldpath);
static int	ms_cd_edge(t_shell *shell, t_envvar *path,
				t_envvar *oldpath, char *newpath);
static int	ms_cd_minus(t_shell *shell, t_envvar *path,
				t_envvar *oldpath);

int	ms_cd(t_shell *shell, char **args)
{
	t_envvar	*oldpath;
	t_envvar	*path;
	int			argslen;

	argslen = ms_args_len(args);
	if (argslen <= 2)
	{
		oldpath = ms_init_vars(shell, "OLDPWD");
		path = ms_init_vars(shell, "PWD");
		if (args[1] == NULL || (ft_strlen(args[1]) == 1))
			shell->exitcode = ms_cd_edge(shell, path, oldpath, args[1]);
		else if (chdir(args[1]) == 0)
			shell->exitcode = ms_cd_path_exists(shell, path, oldpath);
		else
		{
			shell->exitcode = EXIT_FAILURE;
			printf(ERR_CD, args[1]);
		}
		return (shell->exitcode);
	}
	shell->exitcode = EXIT_FAILURE;
	printf("minishell: cd: too many arguments\n");
	return (shell->exitcode);
}

static int	ms_cd_path_exists(t_shell *shell, t_envvar *path,
				t_envvar *oldpath)
{
	char		*temp;
	char		*update;

	shell->exitcode = ms_cd_paths_null(shell, path, oldpath);
	if (shell->exitcode == ALLOCATION_PROBLEM_EXIT)
		return (shell->exitcode);
	temp = ft_strdup(path->value);
	update = NULL;
	update = getcwd(update, 1024);
	shell->exitcode = ms_cd_switch_path(path, update);
	shell->exitcode = ms_cd_switch_path(oldpath, temp);
	if (update != NULL)
		free(update);
	free(temp);
	return (shell->exitcode);
}

static int	ms_cd_edge(t_shell *shell, t_envvar *path,
				t_envvar *oldpath, char *newpath)
{
	t_envvar	*home;

	home = ms_init_vars(shell, "HOME");
	shell->exitcode = ms_cd_paths_null(shell, path, oldpath);
	if (path == NULL)
		path = ms_init_vars(shell, "PWD");
	if (shell->exitcode == ALLOCATION_PROBLEM_EXIT)
		return (shell->exitcode);
	if (newpath != NULL && path != NULL && newpath[0] == '-')
		shell->exitcode = ms_cd_minus(shell, path, oldpath);
	else if (home == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		shell->exitcode = EXIT_FAILURE;
	}
	else if (newpath == NULL || newpath[0] == '~')
	{
		if (oldpath == NULL)
			oldpath = ms_init_vars(shell, "OLDPWD");
		shell->exitcode = ms_cd_switch_path(oldpath, path->value);
		shell->exitcode = ms_cd_switch_path(path, home->value);
		chdir(home->value);
	}
	return (shell->exitcode);
}

static int	ms_cd_minus(t_shell *shell, t_envvar *path, t_envvar *oldpath)
{
	char		*temp;

	if (oldpath == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (EXIT_FAILURE);
	}
	chdir(oldpath->value);
	temp = ft_strdup(path->value);
	shell->exitcode = ms_cd_switch_path(path, oldpath->value);
	shell->exitcode = ms_cd_switch_path(oldpath, temp);
	ms_pwd();
	free(temp);
	return (shell->exitcode);
}

static int	ms_cd_paths_null(t_shell *shell, t_envvar *path, t_envvar *oldpath)
{
	if (path == NULL)
	{
		shell->exitcode = ms_cd_new_path(shell, path);
	}
	if (oldpath == NULL)
	{
		shell->exitcode = ms_cd_new_oldpath(shell, oldpath);
	}
	return (shell->exitcode);
}
