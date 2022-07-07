/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:31:47 by mgulenay          #+#    #+#             */
/*   Updated: 2022/07/07 17:59:11 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ms_pwd(void)
{
	char	buffer[1024]; // stores the current working directory
	char	*path;
	
	path = getcwd(buffer, 1024);
 	if (path == NULL)
		printf("Error in getcwd\n");
	else
		printf("Current working directory: \n%s\n", path);
}