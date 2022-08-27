/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:05:45 by mgulenay          #+#    #+#             */
/*   Updated: 2022/08/26 15:53:06 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* prints substrings within the lexer */
void	print_lexer(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->lexer[i])
	{
		printf("[%d] %s\n", i, shell->lexer[i]);
		i++;
	}
}

int	ms_parser(t_shell *shell)
{
	if (shell->cmd->line != NULL)
		shell->exitcode = ms_lexer(shell);
	shell->cmd->curr_cmd = shell->lexer;
	if (shell->cmd->curr_cmd == NULL)
	{
		shell->exitcode = ALLOCATION_PROBLEM_EXIT;
		return (shell->exitcode);
	}
/* 	int a = get_nmb_cmd(shell->cmd);
	printf("%d\n", a); */
	
	print_nb_words(shell);
	/* char **words;
	int i=0;
	int j=0;
	while (j < shell->cmd->n_cmd)
	{
		words = get_each_word(shell->lexer[j]);
		while (i < count_words(shell->lexer[j]))
		{
        	printf("%s",words[i]);
			printf("\n");
			i++;
		}
		j++;
	} */
/* 	char ***a;
	a = create_seq_from_lexer(shell);
	int i, j, k;
	j = 0;
	k = 0;
	while (j < shell->cmd->n_cmd)
	{
		while (k < 2)
		{
			while (i < 2)
			{
				printf("%c", a[j][k][i]);
				i++;
			}
			i = 0;
			k++;
			printf("\n");
		}
		k = 0;
		j++;
	} */
	return (EXIT_SUCCESS);
}
