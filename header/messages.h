/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:33:14 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/22 15:52:39 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define ERR_ARG "minishell: The program does not require arguments.\n"

# define ALLOCATION_PROBLEM_EXIT 12
# define ERR_NULL "Cannot allocate memory\n"

# define ERR_INV ": command not found\n"
# define ERR_INV_ID "minishell: %s: `%s\': not a valid identifier\n"
# define ERR_CD "minishell: cd: %s: no such file or directory\n"
#endif
