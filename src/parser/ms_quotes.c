/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:51:08 by mgulenay          #+#    #+#             */
/*   Updated: 2022/08/30 19:56:56 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* need to remove quotes for printing if it is already closed: 
 -- first check, if already in double or single quote, then remove it, 
-- if we have a case like : 
	echo "hello 'world' ", 
we need to remove just the double quote
*/

char	*remove_sq(char *str)
{
	char	*temp;
	int		i;
	int		k;
	
	i = 0;
	k = 0;
	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == SQ)
		{
			i++;
			while (str[i] != '\0' && str[i] != SQ)
			{
				temp[k] = str[i];					
				k++;
				i++;
			}
		}
		else if (str[i] != SQ)
		{
			temp[k] = str[i];
			k++;
		}
		i++;
	}
	str = ft_strdup(temp);
	//printf("without quotes: %s\n", str);
	return(str);
}

char	*remove_dq(char *str)
{
	char	*temp;
	int		i;
	int		k;
	
	i = 0;
	k = 0;
	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (str[i])
	{
		if (str[i] == DQ)
		{
			i++;
			while (str[i] != '\0' && str[i] != DQ)
			{
				temp[k] = str[i];		
				k++;
				i++;
			}
		}
		else if (str[i] != DQ)
		{
			temp[k] = str[i];
			k++;
		}
		i++;
	}
	str = ft_strdup(temp);
	free(temp);
	//printf("%s\n", str);
	return (str);
}


char	*check_quotes_pre_lexer(char *str)
{
	int		i;

	i = 0;
	if (check_quotes(str) == EXIT_SUCCESS)
	{
		while (str[i] != '\0')
		{
			if (str[i] == SQ)
				str = remove_sq(str);
			if (str[i] == DQ)
				str = remove_dq(str);
			i++;
		}
	}
	return (str);
}
