/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:37:40 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/05 15:42:50 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// Collects error numbers, and outputs the correct error message, in case the
// error occurs after allocations were made, a cleanup function must be called.
int ms_error_management(int errnum)
{
  if (errnum == 1)
    printf("%s", ERR_ARG);
  if (errnum == 2)
    printf("%s", ERR_NULL);
  return (errnum);
}
