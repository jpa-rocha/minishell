/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:22:34 by mgulenay          #+#    #+#             */
/*   Updated: 2022/08/17 10:48:21 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(t_shell *shell)
{
	int i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	j = 0;
	while (shell->lexer[j])
	{
		while (shell->lexer[j][i])
		{
			if (shell->lexer[j][i] != ' ' || shell->lexer[j][i] != '\t')
				count++;
			i++;
		}
		j++;
	}
	return (count);
}

char	*get_each_token(t_shell *shell)
{
	int		i;
	int		j;
	char	*token;
	int		length;

	length = count_words(shell);
	i = 0;
	j = 0;
	while (shell->lexer[j])
	{
		token = malloc(sizeof(char) * length + 1);
		if (!token)
			return (NULL);
		while (shell->lexer[j][i])
		{
			if (shell->lexer[j][i] != ' ')
			{
				token[i] = shell->lexer[j][i];
			}
			i++;
		}
		token[i] = '\0';
		j++;
	}
	printf("works\n");
	printf("%d\n", length);
	return (token); 

}
