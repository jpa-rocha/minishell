/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:26:27 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/19 16:50:03 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_cd_switch_path(t_envvar *oldpath, char *newpath);
static int	ms_cd_home(t_shell *shell, t_envvar *oldpath,
				t_envvar *path, t_envvar *home);

int	ms_cd(t_shell *shell, char *newpath)
{
	t_envvar	*oldpath;
	t_envvar	*path;
	t_envvar	*home;
	char		*temp;

	oldpath = (t_envvar *) ms_env_find_entry(shell->workenv, "OLDPWD")->data;
	path = (t_envvar *) ms_env_find_entry(shell->workenv, "PWD")->data;
	home = (t_envvar *) ms_env_find_entry(shell->workenv, "HOME")->data;
	if (newpath == NULL || )
		shell->exitcode = ms_cd_home(shell, oldpath, path, home);
	else if (ft_strlen(newpath) == 1 && newpath[0] == '-')
	{
		temp = ft_strdup(path->value);
		shell->exitcode = ms_cd_switch_path(path, oldpath->value);
		shell->exitcode = ms_cd_switch_path(oldpath, temp);
		free(temp);
		chdir(path->value);
		ms_pwd();
		return (shell->exitcode);
	}
	shell->exitcode = EXIT_SUCCESS;
	return (shell->exitcode);
}

static int	ms_cd_home(t_shell *shell, t_envvar *oldpath,
	t_envvar *path, t_envvar *home)
{
	shell->exitcode = ms_cd_switch_path(oldpath, path->value);
	shell->exitcode = ms_cd_switch_path(path, home->value);
	chdir(home->value);
	return (shell->exitcode);
}

static int	ms_cd_switch_path(t_envvar *oldpath, char *newpath)
{
	free(oldpath->value);
	oldpath->value = ft_calloc(ft_strlen(newpath) + 2, sizeof(char));
	if (oldpath->value == NULL)
		return (ALLOCATION_PROBLEM_EXIT);
	ft_strlcpy(oldpath->value, newpath, ft_strlen(newpath) + 1);
	return (EXIT_SUCCESS);
}