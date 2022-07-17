/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:31:47 by mgulenay          #+#    #+#             */
/*   Updated: 2022/07/14 16:24:44 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* pwd -- print working directory -- prints the path
	the max. path size/length in mac 1024 & 4096 in linux
	buffer stores the current working directory
*/
int	ms_pwd(void)
{
	char	buffer[PATH_SIZE_MAC];
	char	*cwd;
	
	cwd = getcwd(buffer, PATH_SIZE_MAC);
 	if (cwd == NULL)
	{
		perror("Error in current working directory\n");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
