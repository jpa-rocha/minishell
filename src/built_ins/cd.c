/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:26:27 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/15 09:54:02 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_cd_path_exists(t_shell *shell, t_envvar *path,
				t_envvar *oldpath);
static int	ms_cd_edge(t_shell *shell, t_envvar *path,
				t_envvar *oldpath, char *newpath);
static int	ms_cd_minus(t_shell *shell, t_envvar *path,
				t_envvar *oldpath);

int	ms_cd(t_shell *shell, char **args)
{
	t_envvar	*oldpath;
	t_envvar	*path;
	char		*home;
	char		*homejoin;

	if (ms_args_len(args) <= 2)
	{
		oldpath = ms_init_vars(shell, "OLDPWD");
		path = ms_init_vars(shell, "PWD");
		if (args[1] == NULL || (ft_strlen(args[1]) == 1))
			shell->status = ms_cd_edge(shell, path, oldpath, args[1]);
		else if (ms_args_len(args) == 2)
		{
			if (ft_strncmp(args[1], "~/", 2) == 0)
			{
				home = ms_env_ret_value(shell, "HOME=");
				if (home == NULL)
				{
					home = ft_strjoin(shell->home, &args[1][1]);
					shell->status = chdir(home);
					free(home);
				}
				else
				{
					homejoin = ft_strjoin(home, &args[1][1]);
					if (chdir(homejoin) == -1)
					{
						shell->status = EXIT_FAILURE;
						ft_printf(STDERR_FILENO, ERR_CD, homejoin);
						free(homejoin);
						free(home);
						return (shell->status);
					}
				}
			}
			else
				shell->status = chdir(args[1]);
			if (shell->status == EXIT_SUCCESS)
				shell->status = ms_cd_path_exists(shell, path, oldpath);
		}
		if (shell->status == -1)
		{
			shell->status = EXIT_FAILURE;
			ft_printf(STDERR_FILENO, ERR_CD, args[1]);
		}
		return (shell->status);
	}
	shell->status = EXIT_FAILURE;
	ft_printf(STDERR_FILENO, "minishell: cd: too many arguments\n");
	return (shell->status);
}

static int	ms_cd_path_exists(t_shell *shell, t_envvar *path,
				t_envvar *oldpath)
{
	char		*temp;
	char		*update;

	temp = NULL;
	update = NULL;
	update = getcwd(update, 1024);
	if (update == NULL)
	{
		shell->status = ERR_CWD;
		ft_printf(STD_ERR, ERR_CWD_MSG);
		return (shell->status);
	}
	if (path != NULL)
	{
		temp = ft_strdup(path->value);
		shell->status = ms_cd_switch_path(path, update);
	}
	if (path != NULL && oldpath != NULL)
		shell->status = ms_cd_switch_path(oldpath, temp);
	if (update != NULL)
		free(update);
	if (temp != NULL)
		free(temp);
	return (shell->status);
}

static int	ms_cd_edge(t_shell *shell, t_envvar *path,
				t_envvar *oldpath, char *newpath)
{
	t_envvar	*home;
	t_envvar	*old;

	home = ms_init_vars(shell, "HOME");
	if (newpath != NULL && newpath[0] == '-')
		shell->status = ms_cd_minus(shell, path, oldpath);
	else if (home == NULL)
	{
		ft_printf(STDERR_FILENO, "minishell: cd: HOME not set\n");
		shell->status = EXIT_FAILURE;
	}
	else if (newpath == NULL || newpath[0] == '~')
	{
		if (path == NULL)
		{
			ms_unset_var(shell, "OLDPWD");
		}
		old = ms_init_vars(shell, "OLDPWD");
		if (old != NULL)
			shell->status = ms_cd_switch_path(old, path->value);
		if (path != NULL)
			shell->status = ms_cd_switch_path(path, home->value);
		chdir(home->value);
	}
	return (shell->status);
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
	if (path != NULL)
	{
		temp = ft_strdup(path->value);
		shell->status = ms_cd_switch_path(path, oldpath->value);
		shell->status = ms_cd_switch_path(oldpath, temp);
		free(temp);
	}
	else
		ms_unset_var(shell, "OLDPWD");
	ms_pwd();
	return (shell->status);
}
