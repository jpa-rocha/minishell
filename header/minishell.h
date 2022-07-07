/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:45:27 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/06 18:28:17 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "messages.h"
# include "../libft/header/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h> 
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>

# define SQ '\''
# define DQ '\"'
# define PIPE '|'
# define GR '>'
# define GRGR '>>'
# define SM '<'
# define SMSM '<<'
# define DOLLAR '$'


typedef struct s_symbols {
	int 	sq;
	int 	dq;
	int 	pipe;
	int 	gr;
	int 	grgr;
	int 	sm;
	int 	smsm;
	int 	dollar;

} t_symbols;
  
typedef struct s_cmd {
	int		errnum;
	char		*line;
	char		**args;
	char		**env;
  	t_symbols	*symb;
} t_cmd;

t_cmd	*ms_cmd_init(char **env);
int	ms_cmd_cleanup(t_cmd *cmd);
int	ms_error_management(int errnum);
void	ms_logo(void);
int	ms_parser(t_cmd *cmd);
int	ms_args_len(char **args);
int	ms_exec(char **args);
void	ms_signals(void);

#endif
