/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:45:27 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/10 22:11:22 by jrocha           ###   ########.fr       */
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

typedef struct s_envvar {
	char	*name;
	char	*value;
}	t_envvar;

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
	t_list 		*workenv;
  	t_symbols	*symb;
} t_cmd;

// General Functions

t_cmd		*ms_cmd_init(char **env, char **argv);
int			ms_cmd_cleanup(t_cmd *cmd);
void		ms_list_data_cleaner(t_list *list);
int			ms_error_management(int errnum);
void		ms_logo(void);
int			ms_args_len(char **args);
int			ms_list_env_len(t_list *env);
char		**ms_create_env(char **env, char **argv);
void 		ms_free_args(char **args);

// Signal Functions

  void	ms_signals(void);

// Parsing Functions

int	ms_parser(t_cmd *cmd);

// Executing Functions


int	ms_exec(char **args);

// Built-in Functions

void	ms_env(t_list *env);
char	**ms_env_init_env(t_list *env);
t_list	*ms_env_create_work_env(char **env, char **argv);

#endif
