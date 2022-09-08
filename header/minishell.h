/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:45:27 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/08 12:04:19 by jrocha           ###   ########.fr       */
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

# define BI_NUM 8
# define BI_PATH "./src/built_ins/"
# define SQ '\''
# define DQ '\"'
# define PIPE '|'
# define GR '>'
# define GRGR ">>"
# define SM '<'
# define SMSM "<<"
# define DOLLAR '$'
# define SLASH '/'
# define BSLASH '\\'

# define PATH_SIZE 1024

extern int	g_exit;

typedef struct s_envvar {
	char	*name;
	char	*value;
	int		env_order;
}	t_envvar;

typedef struct s_cmd {
	int			builtin_num;
	char		*line;
	int			n_cmd;
	int			n_words;
	int			input;
	int			output;
	int			heredoc;
	int			changes_state;
	int			cmd_idx;
	char		*limiter;
	char		*cmd_name;
	char		**curr_cmd;
	char		**path;
	char		***seq;
	int			pfd[2];
	int			temp_fd[2];
}	t_cmd;

typedef struct s_shell {
	int			shlvl;
	char		*name;
	char		*user;
	t_cmd		*cmd;
	t_list		*workenv;
	char		*builtins[BI_NUM];
	char		**env;
	char		**argv;
	char		**lexer;
	int			status;
}	t_shell;

// General Functions

int			ms_shell(char **env, char **argv, int shlvl);
t_shell		*ms_shell_init(char **env, char **argv, int shlvl);
t_cmd		*ms_cmd_init(t_shell *shell);
int			ms_cmd_cleanup(t_cmd *cmd);
int			ms_shell_cleanup(t_shell *shell);
void		ms_list_data_cleaner(t_list *list);
int			ms_error_management(t_shell *shell);
void		ms_logo(void);
char		*ms_prompt(t_shell *shell);
int			ms_args_len(char **args);
int			ms_list_env_len(t_list *env);
char		**ms_create_env(char **env, char **argv);
void		ms_free_args(char **args);
void		ms_free_seq(t_cmd *cmd);
char		**ms_cmd_path_creator(t_shell *shell);
int			ms_env_swap_data(t_envvar *line, t_envvar *nline);
char		**ms_copy_cmd(char **cmd);
char		*ms_env_ret_value(t_shell *shell, char *name);
// Signal Functions

void		ms_signals(void);

// Parsing Functions

int			ms_parser(t_shell *shell);
int			get_nmb_cmd(t_cmd *cmd);
int			ms_lexer(t_shell *shell);
void		alloc_lexer(t_shell *shell);
int			count_words(char *str);
int			check_pipe_in_quotes(char *str);
char		***create_seq_from_lexer(t_shell *shell);
int			get_nb_words_store(t_shell *shell);
char		**get_each_word(char *str);
void		*ms_dollar_check(t_shell *shell, char **str);

// Error checks for the variable line
int			check_quotes(char *str);
int			counter_io(t_cmd *cmd);
int			check_only_io(t_cmd *cmd);
int			check_slash(t_cmd *cmd);
//int			check_char_errors(t_cmd *cmd);
int			check_if_only_pipe(t_cmd *cmd);
int			count_pipes(t_cmd *cmd);

// for printing
void		print_nb_words(t_shell *shell);
void		print_lexer(t_shell *shell);

// Executing Functions

int			ms_exec(t_shell *shell);
int			ms_check_pipe(t_cmd *cmd);
int			ms_exec_set_in_out(t_shell *shell, char **cmd);
int			ms_exec_here_doc(t_shell *shell);
int			ms_top_pipe(t_shell *shell);
int			ms_bot_pipe(t_shell *shell);
int			ms_cmd_executing(t_shell *shell);
int			ms_call_built_in(t_shell *shell);
int			ms_cmd_separator(t_shell *shell);

// Built-in Functions

// Entry point into the env function
int			ms_env(t_shell *shell);
char		**ms_env_init_env(t_shell *shell);
t_list		*ms_env_create_work_env(t_shell *shell, char **env);
t_node		*ms_env_find_entry(t_list *env, char *name);

// Entry point into the export function
int			ms_export(t_shell *shell, char **args);
int			ms_export_order(t_list *env);
int			ms_var_check(t_shell *shell, char *called_from, char *newvar);

// Entry point into the unset function
int			ms_unset(t_shell *shell, char **args);
int			ms_unset_var(t_shell *shell, char *var);

// Entry point into cd
int			ms_cd(t_shell *shell, char **args);
int			ms_cd_new_path(t_shell *shell, t_envvar *path, char *var);
int			ms_cd_switch_path(t_envvar *oldpath, char *newpath);
t_envvar	*ms_init_vars(t_shell *shell, char *envvar);

// Return the current working path
int			ms_pwd(void);

// Exits current program
int			ms_exit(t_shell *shell);

// Echo description
int			ms_echo(t_cmd *cmd);

#endif
