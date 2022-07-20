/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:33:14 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/20 16:36:48 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define ERR_ARG "minishell: The program does not require arguments.\n"

# define ALLOCATION_PROBLEM_EXIT 12
# define ERR_NULL "Cannot allocate memory\n"

# define MISSUSED_BUILTIN 2
# define ERR_MU "minishell: syntax error near unexpected token `%s'\n"

# define IS_DIR_SLASH 126
# define IS_DIR_BSLASH 127
# define ERR_ISDIR "minishell: %s: Is a directory\n"
# define ERR_NF "minishell: %s: command not found\n"

# define ERR_INV ": command not found\n"

#endif
