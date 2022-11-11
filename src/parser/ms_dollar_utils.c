/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:15:43 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/22 10:18:20 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ms_rep_setup(t_dol_rep *rep, char *str)
{
	while (str[rep->beg_len] != '$')
		rep->beg_len += 1;
	rep->beginning = ft_calloc(rep->beg_len + 1, sizeof(char));
	rep->var_len = ft_strlen(rep->replace);
	ft_strlcpy(rep->beginning, str, rep->beg_len + 1);
	if (ft_strlen(str) > (size_t)(rep->beg_len + rep->var_len - 1))
		rep->end = ft_strdup(&str[rep->beg_len + rep->var_len - 1]);
	else
		rep->end = ft_strdup("");
	rep->temp = ft_strjoin(rep->beginning, rep->replace);
}
