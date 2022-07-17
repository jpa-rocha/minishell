/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:45:27 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/17 21:15:10 by mgulenay         ###   ########.fr       */
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

# define BI_PATH "./src/built_ins/"
# define SQ '\''
# define DQ '\"'
# define PIPE '|'
# define GR '>'
# define GRGR '>>'
# define SM '<'
# define SMSM '<<'
# define DOLLAR '$'

# define PATH_SIZE_MAC 1024
# define PATH_SIZE_LINUX 4096

typedef struct s_envvar {
	char	*name;
	char	*value;
	int		env_order;
}	t_envvar;

typedef struct s_symbols {
	int	sq;
	int	dq;
	int	pipe;
	int	gr;
	int	grgr;
	int	sm;
	int	smsm;
	int	dollar;

}	t_symbols;

typedef struct s_cmd {
	int			builtin_num;
	char		*line;
	int			n_cmd;
	char		**args;
	char		**env;
	char		**path;
	t_symbols	*symb;
}	t_cmd;

typedef struct s_shell {
	char		*name;
	t_cmd		*cmd;
	t_list		*workenv;
	char		**env;
	char		**argv;
	char		**path;
	int			exitcode;
}	t_shell;

// General Functions

int			ms_shell(char **env, char **argv);
t_shell		*ms_shell_init(char **env, char **argv);
t_cmd		*ms_cmd_init(t_shell *shell);
int			ms_cmd_cleanup(t_cmd *cmd);
int			ms_shell_cleanup(t_shell *shell);
void		ms_list_data_cleaner(t_list *list);
int			ms_error_management(t_shell *shell);
void		ms_logo(void);
int			ms_args_len(char **args);
int			ms_list_env_len(t_list *env);
char		**ms_create_env(char **env, char **argv);
void		ms_free_args(char **args);
char		**ms_shell_path_creator(t_shell *shell);

// Signal Functions

void		ms_signals(void);

// Parsing Functions

int			ms_parser(t_shell *shell);
int			n_commands(t_cmd *cmd);
void		ms_lexer(t_cmd *cmd);

// Executing Functions

int			ms_exec(t_shell *shell);
int			ms_check_pipe(t_cmd *cmd);

// Built-in Functions

// Entry point into the env function
int			ms_env(t_shell *shell);
char		**ms_env_init_env(t_list *workenv);
t_list		*ms_env_create_work_env(t_shell *shell, char **env);
t_node		*ms_env_find_entry(t_list *env, char *name);
int			ms_export(t_shell *shell, t_list *env, char *newvar);
int			ms_pwd(void);
int			ms_exit(t_shell *shell);
int			ms_echo(t_cmd *cmd);

#endif
