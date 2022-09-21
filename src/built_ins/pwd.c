/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:31:47 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/21 21:40:55 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* pwd -- print working directory -- prints the path
	the max. path size/length in mac 1024 & 4096 in linux
	buffer stores the current working directory
*/
int	ms_pwd(t_shell *shell)
{
	//could fix it like bash
	char		buffer[PATH_SIZE];
	char		*cwd;
	t_envvar	*pwd;	

	cwd = getcwd(buffer, PATH_SIZE);
	if (cwd == NULL)
	{
		pwd = ms_init_vars(shell, "PWD");
		printf("%s\n", pwd->value);
		return (0);
	}
	printf("%s\n", cwd);
	return (0);
}
