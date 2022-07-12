/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:31:47 by mgulenay          #+#    #+#             */
/*   Updated: 2022/07/10 11:04:38 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ms_pwd(void)
{
	char	buffer[1024]; // stores the current working directory
	char	*path;
	
	path = getcwd(buffer, 1024);
 	if (path == NULL)
	{
		perror("Error in getcwd\n");
		return (1);
	}
	else
	{
		printf("%s\n", path);
		return (0);
	}
	return (0);
}
