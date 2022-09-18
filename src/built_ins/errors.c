/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:33:38 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/16 14:41:25 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ms_error_messages(t_shell *shell, int error_num)
{
	if (error_num == -2)
		printf("quotes are not closed\n");
	if (error_num == -3)
		printf(ERR_MU, "|");
	if (error_num == -4)
		printf(ERR_MU, "||");
	if (error_num == -5)
		printf(ERR_MU, "newline");
	if (error_num == -6)
		printf(ERR_MU, "<");
	if (error_num == -7)
		printf(ERR_MU, "<<");
	if (error_num == -8)
		printf(ERR_MU, ">");
	if (error_num == -9)
		printf(ERR_MU, ">>");
	if (error_num == -10)
		printf("pipe needs argument\n");
	shell->status = 2;
	return (EXIT_SUCCESS);
}
