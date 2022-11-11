/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:33:14 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/22 11:42:35 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define ERR_ARG "minishell: The program does not require arguments.\n"
# define EXIT_MSG "minishell: exit: %s: numeric argument required\n"
# define ERR_NULL "Cannot allocate memory\n"
# define ERR_QUOTES "minishell: quotes must be closed\n"
# define ERR_MU "minishell: syntax error near unexpected token `%s'\n"
# define ERR_ISDIR "minishell: %s: Is a directory\n"
# define ERR_NF "minishell: %s: command not found\n"
# define ERR_INV ": command not found\n"
# define ERR_INV_ID "minishell: %s: `%s\': not a valid identifier\n"
# define ERR_CD "minishell: cd: %s: no such file or directory\n"
# define ERR_EXIT "minishell: exit: too many arguments\n"
# define ERR_CWD_MSG "cd: error retrieving current directory:\
 getcwd: cannot access parent directories: No such file or directory\n"
# define HEREDOC_MSG "minishell: warning: here-document\
 delimited by end-of-file (wanted `%s')\n"

# define MISSUSED_BUILTIN 2
# define ALLOCATION_PROBLEM_EXIT 12
# define IS_DIR_SLASH 126
# define COMMAND_NOT_FOUND 127
# define ERR_CWD 130
# define ERR_INV ": command not found\n"
# define ERR_INV_ID "minishell: %s: `%s\': not a valid identifier\n"
# define ERR_CD "minishell: cd: %s: no such file or directory\n"

#endif
