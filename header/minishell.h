/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:45:27 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/22 12:36:40 by jrocha           ###   ########.fr       */
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
# include <dirent.h>

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

typedef struct s_dol_rep {
	char	*replace;
	char	*beginning;
	char	*end;
	char	*search;
	char	*temp;
	int		var_len;
	int		beg_len;
}	t_dol_rep;

typedef struct s_breaks {
	int		i;
	int		j;
	int		k;
	int		count;
}	t_breaks;

typedef struct s_lexcheck {
	size_t		i;
	int			index;
	int			s_flag;
	int			d_flag;
}	t_lexcheck;

typedef struct s_qcheck {
	int		quotes_flag;
	int		firstq;
	int		secondq;
	int		iter;
	int		i;
}	t_qcheck;

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
	int			error_inc;
}	t_cmd;

typedef struct s_shell {
	int			shlvl;
	pid_t		pid;
	char		*name;
	char		*home;
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

void		ms_signals_parent(void);
void		ms_signals_child(void);
void		ms_signals_heredoc(void);
void		ms_signals_block(void);
void		ms_parent_signal_handler(int num);
void		ms_child_signal_handler(int num);
void		ms_here_signal_handler(int num);

// Parsing Functions

int			ms_parser(t_shell *shell);
int			get_nmb_cmd(t_cmd *cmd);
int			ms_lexer(t_shell *shell);
void		alloc_lexer(t_shell *shell);
char		***create_seq_from_lexer(t_shell *shell);
char		**get_each_word(char *str);
char		*remove_quotes(char *str, int index, int quote);
char		*check_quotes_pre_lexer(char *str);
char		*remove_white_spaces(char *str);
char		*ms_dollar_check(t_shell *shell, char *str);
int			check_dollar_in_quotes(char *str, size_t idx, int c);
t_dol_rep	*ms_dollar_rep_init(t_shell *shell, char *dollar);
void		ms_rep_setup(t_dol_rep *rep, char *str);
void		*ms_dollar_rep_clean(t_dol_rep *rep);
char		*ms_replace_var_empty(t_dol_rep *rep, char *str);
char		*ms_replace_var_search(char *dollar);
int			check_char_in_quotes(char *str, int idx, int c);
int			flag_quotes(char *str, int quote);

// Error checks for the variable line

int			check_char_errors(t_cmd *cmd);
int			check_quotes(t_cmd *cmd);
int			check_redirections(t_cmd *cmd);
int			check_slash(t_cmd *cmd);
int			ms_slash_flag_check(t_cmd *cmd);
int			check_empty_pipes(t_cmd *cmd);
int			check_pipes(t_cmd *cmd);
int			ms_error_messages(t_shell *shell, int error_num);

// Executing Functions

int			ms_exec(t_shell *shell);
int			ms_check_pipe(t_cmd *cmd);
int			ms_exec_set_in_out(t_shell *shell);
int			ms_exec_error(t_shell *shell);
int			ms_exec_here_doc_fork(t_shell *shell, int i);
int			ms_find_cmd_loop(t_shell *shell);
int			ms_next_cmd(t_shell *shell);
int			ms_top_pipe(t_shell *shell);
int			ms_bot_pipe(t_shell *shell);
int			ms_cmd_executing(t_shell *shell);
int			ms_call_built_in(t_shell *shell);
int			ms_cmd_separator(t_shell *shell);
int			ms_cmd_replace_in(t_shell *shell, char **cmd, int i);
int			ms_cmd_replace_out(t_shell *shell, char **cmd, int i);

// Built-handling
int			ms_is_built_in(t_shell *shell, char **curr_cmd);
int			ms_control_state(t_shell *shell, char **curr_cmd);

// Entry point into the env function
int			ms_env(t_shell *shell);
char		**ms_env_init_env(t_shell *shell);
t_list		*ms_env_create_work_env(t_shell *shell, char **env);
t_node		*ms_env_find_entry(t_list *env, char *name);

// Entry point into the export function
int			ms_export(t_shell *shell, char **args);
int			ms_export_order(t_list *env);
int			ms_var_check(t_shell *shell, char *called_from, char *newvar);
int			ms_export_size_adjust(t_envvar *line);

// Entry point into the unset function
int			ms_unset(t_shell *shell, char **args);
int			ms_unset_var(t_shell *shell, char *var);

// Entry point into cd
int			ms_cd(t_shell *shell, char **args);
int			ms_cd_new_path(t_shell *shell, t_envvar *path, char *var);
int			ms_cd_switch_path(t_envvar *oldpath, char *newpath);
int			ms_cd_path_exists(t_shell *shell, t_envvar *path,
				t_envvar *oldpath);
t_envvar	*ms_init_vars(t_shell *shell, char *envvar);

// Return the current working path
int			ms_pwd(t_shell *shell);

// Exits current program
int			ms_exit(t_shell *shell, char **args);

// Echo description
int			ms_echo(t_cmd *cmd);

#endif
