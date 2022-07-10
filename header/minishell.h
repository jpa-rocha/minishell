/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:45:27 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/10 14:26:55 by mgulenay         ###   ########.fr       */
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
	int			num_args;
  	t_symbols	*symb;
} t_cmd;

t_cmd	*ms_cmd_init(char **env);
int		ms_cmd_cleanup(t_cmd *cmd);
int		ms_error_management(int errnum);
void	ms_logo(void);
int		ms_parser(t_cmd *cmd);
int		ms_args_len(char **args);
int		ms_exec(char **args);
void	ms_signals(void);

/* built-in functions */
int		ms_pwd(void);
int		check_if_int(char *s );
int		ms_exit(void);
int		ms_echo(char **argv);

#endif
