/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:43:01 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/25 10:00:25 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <dirent.h>

typedef struct s_gc
{
	int			flag;
	void		*ptr;
	struct s_gc	*next;
}	t_gc;

typedef struct s_global
{
	int		rl;
	int		exit_status;
	t_gc	*gc;
}	t_global;

t_global	g_gl;

typedef enum s_type
{
	WSPACE,
	PIPE,
	VAR,
	WORD,
	SQUOTE,
	DQUOTE,
	OUTRED,
	INRED,
	APPEND,
	HERDOC,
}	t_type;

typedef struct s_lexer
{
	int				type;
	char			*str;
	struct s_lexer	*next;
	struct s_lexer	*previous;	
}	t_lexer;

typedef struct s_var
{
	char			*key;
	char			*val;
	struct s_var	*next;
}	t_var;

typedef struct s_simple_cmds
{
	char					**str;
	int						in_fd;
	int						out_fd;
	int						err;
	struct s_simple_cmds	*next;
}	t_simple_cmd;

typedef struct s_export
{
	char			*var;
	char			*val;
	struct s_export	*next;
}	t_export;

typedef struct s_all
{
	t_var				*env;
	t_var				*exp;
	t_simple_cmd		*cmd;
}	t_all;

typedef struct s_pwd
{
	t_var			*node;
	t_var			*pwd_en;
	t_var			*oldpwd_en;
	t_var			*pwd_ex;
	t_var			*oldpwd_ex;
}	t_pwd;

//list utils
void				create_node(t_lexer	**lst, char *s, int operator, int flag);
void				ft_lstadd_back(t_lexer **lst, t_lexer *new);
t_lexer				*ft_lstlast(t_lexer *lst);
t_simple_cmd		*create_scmd(t_lexer *cmd);
void				add_scmd(t_simple_cmd **lst, t_simple_cmd *new);
//lexer
t_lexer				*tokenize(char *line);
void				tokenize_word(t_lexer **node, char **s);
void				tokenize_var(t_lexer **node, char **s);
void				tokenize_dquote(t_lexer **node, char **s);
void				tokenize_squote(t_lexer **node, char **s);
void				tokenize_red(t_lexer **node, char **s);
char				*set_line(t_lexer **node, char **line);
void				get_token(t_lexer **node, char **line);

//syntax analyzer
bool				analyze_syntax(t_lexer *cmd);
bool				analyze_quote(t_lexer **node, int flag);
bool				pipe_analyze(t_lexer *cmd);
bool				pipe_checker(t_lexer *cmd, int i);
bool				red_analyze(t_lexer *cmd);

// parse
void				parse(t_all *all, t_lexer *cmdline);
void				parse_red(t_lexer **cmdline, t_simple_cmd **cmd);
void				out_red(t_lexer **node, char **line);
void				in_red(t_lexer **node, char **line);
void				close_quotes(t_lexer **node, char **s, char *tmp, int i);
char				*set_quote(t_lexer **node, char **s);
void				quote_word(t_lexer **node, char *s, int *i, int j);
t_lexer				*merge_word(t_lexer *cmd);
t_lexer				*filter(t_all *all, t_lexer *cmdline);
t_simple_cmd		*collect_scmds(t_lexer **cmdline, t_var *var, int i);

//redirection	
void				parse_hd(t_simple_cmd **scmd, t_lexer **cmdline, \
					t_var *var);
void				read_hd(t_var *var, char *s, int fd[2]);
void				parse_red(t_lexer **cmdline, t_simple_cmd **cmd);

//expander	
t_lexer				*expand_var(t_lexer *cmd, t_var *var);
void				hd_var(t_lexer **node, t_lexer **cmdline);
char				*find_var(t_var *var, char *str);
char				*expand(t_var *var, char *line);

//extra utils	
void				lst_var(t_var **var, char **s);
char				**ft_split(char *str);
char				*ft_strjoin(char *s1, char *s2);
char				**ft_free(char **p, int j);
char				**ft_freee(char **p);
char				*ft_strcpy(char *str, int size);
char				*ft_strcpy(char *str, int size);
int					ft_strlen(char *s);
bool				valid_var(char c);
bool				is_symbol(char c);
bool				is_digit(char c);
bool				is_alnum(char c);
bool				is_alpha(int c);
bool				valid_var(char c);
int					count_wd(t_lexer *cmd);
bool				is_ws(char c);
int					count_len(char *str);
t_simple_cmd		*empty_cmd(t_simple_cmd *tmp);

// parsing utils
t_lexer				*parse_wc(t_lexer *cmd);
void				collect_filenames(t_lexer **node);
t_lexer				*rm_space(t_lexer *cmd);
t_lexer				*merge_word(t_lexer *cmd);
void				join_words(t_lexer **node, t_lexer *cmd, char *str);
t_lexer				*rm_quote(t_lexer *cmdline);

// execution	
int					exec(t_all *all);
int					one_cmd(t_all *all, t_simple_cmd *tmp);
int					is_builtin(t_simple_cmd *tmp);
void				wa_itt(t_simple_cmd *tmp, t_simple_cmd *t);

// <<<<<<<<<<<<<<<pipe>>>>>>>>>>>>>>>>>>>>>>>>>>>>//

void				many_cmds(t_all *all, t_simple_cmd *tmp);

// <<<<<<<<<<<<<<<<builtins cmds>>>>>>>>>>>>>>>>>>>//

			//---{cd}---//
int					cd(t_all *all);
int					cd_home(t_all *all);
int					home_success(t_all *all, t_pwd *pwd);
void				cd_error(char *path, char *str);
int					cd_swap(t_all *all);
void				swap_success(t_pwd *pwd);
int					curr_cd(t_all *all);
int					curr_success(t_all *all, t_pwd *pd, char *pwd);
int					cd_prvs(t_all *all);
int					prvs_to_home(t_pwd *pwd, char *val);
void				prvs_succes(t_all *all, t_pwd *pwd, char *val, char *path);
int					cd_else(t_all *all);
int					else_success(t_all *all, t_pwd *pwd, char *path);

			//--{export}--//
int					export(t_all *all, t_simple_cmd	*p);
void				exist_egal(t_all *all, t_simple_cmd *p, int i, int k);
int					just_egal_not_plus(t_all *all, t_simple_cmd *p, \
					int i, int k);
int					egal_plus(t_all *all, t_simple_cmd *p, int i, int k);
void				egal_plus_empty(t_all *all, t_simple_cmd *p, int i, int k);
t_var				*ft_last(t_var *lst);
t_var				*lstnew_exen(char *key, char *val);
void				add_exen_back(t_var **exen, t_var *new);
void				add_both(t_all *all, char *key, char *val);
t_var				*check_char(t_var *env, char *str);
t_var				*sort_env(t_var *lst);
void				only_exp(t_all *all, int flag);
void				egal_not_exist(t_all *all, t_simple_cmd *p, int i);
int					is_valid(char *c);
void				print_invalid(t_simple_cmd *p, int i);
int					not_valid(t_simple_cmd *p, int i, int k);

			//---{echo}---//
void				echo(t_simple_cmd *a);
void				only_echo(t_simple_cmd *p, int flag);
void				exist_arg(t_simple_cmd *p, int flag);
int					arg(char *str);
void				ft_putstr(char *str);

			//---{env}---//
void				env(t_all *all);
void				empty_env(t_all *all);
void				set_env(t_all *all, char **env);

			//---{exit}---//
unsigned long long	ft_atoi(char *str);
int					ex_it(t_all *all);

			//---{pwd}---//
void				get_pwd(t_all *all);
void				pwd(t_all *all);

			//---{unset}---//
int					unset(t_simple_cmd *p, t_var **env, t_var **exp);
t_var				*unset_exp(char *str, t_var **exp);
t_var				*unset_env(char *str, t_var **env);
t_var				*check_exist_key(t_var	*lst, char	*str);
void				ft_lstdelone(t_var *lst);
int					invalid_unset(char *c);

			//---{utils}---//
int					ft_strcmp(char *st1, char *st2);
void				ft_putstr_fd(char *s, int fd);
char				*ft_strjoin_n(char *s1, char *s2);
char				**my_env(t_all *all);
int					ft_strrchr(char *str, char c);
int					ft_strchr(char *str, int ch);
char				*ft_substr(char *s, int start, int len);
char				*ft_strdup(char *str);
int					alpha(int c);

// <<<<<<<<<<<<<<<<<<<<<not_builtin>>>>>>>>>>>>>>>>>>>>>>//

void				one_cmd_nopipe(t_all *all, t_simple_cmd *p);
void				one_cmd_nob(t_all *all, t_simple_cmd *p);
int					my_atoi(char *str);
char				*ft_itoa(int n);
int					ft_count(int n);
void				check_path(t_var *key, char **k, t_simple_cmd *p);
void				cmd_not_found(char **path, char **k, t_simple_cmd *p);
char				**ft_split_path(char *str);
char				*ft(char *s, char *s2, int len);
int					count_path(char *str);
void				shelvl(t_all *all, t_simple_cmd *p);
void				print_message(t_simple_cmd *tmp);
void				print_message_err(t_simple_cmd *tmp);			
void				*ft_malloc(int size, int flag);
// char				**ft_free(char **p);

void				free_gb(void);
void				free_enex(t_var *lst);
void				sig_handler(void);
void				handle_int(int sig);
void				sigreset(void);
void				hd_sig(int sig);
int					event(void);

#endif