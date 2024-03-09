/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:12:55 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 12:04:55 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

void				minish_loop(char **env);

// ERRORS

# define MSG_SYNTERR "syntax error near token"
# define EXIT_SYNTERR 258
# define MSG_WRONGAC "minish does not accept arguments"
# define EXIT_WRONGAC 2
# define MSG_CMD_NOT_FOUND "command not found"
# define EXIT_CMD_NOT_FOUND 127
# define MSG_PERM_DENIED "Permission denied"
# define EXIT_PERM_DENIED 126
# define MSG_IS_DIR "is a directory"
# define EXIT_IS_DIR 126
# define MSG_NOFILE "No such file or directory"
# define EXIT_NOFILE 127
# define MSG_AMBIG_REDIR "ambiguous redirect"
# define EXIT_AMBIG_REDIR 1
# define MSG_PIPE_ERR "pipe error"
# define EXIT_PIPE_ERR 1
# define MSG_HEREDOC_ERR "cannot create temp file for here document"

// BUILTIN

# define MSG_NUMARG "numeric argument required"
# define EXIT_NUMARG 255
# define MSG_IDENTERR "not a valid identifier"

int					print_err_syntax(const char *token, int ret);
int					print_err_argc(void);
void				print_err_filename(const char *filename);
void				print_err_pipe(void);
int					print_err_heredoc(int ret);

// BUILTIN ERRORS

int					print_err_identifier(const char *identifier,
						const char *builtin);
int					print_err_too_many_arg(void);
int					print_err_numeric_arg(const char *arg);
int					print_err_builtin(const char *builtin, const char *arg);

// EXEC ERRORS

void				print_err_exec(const char *cmdname);
void				print_err_nofile(const char *cmdname);
void				print_err_cmd_not_found(const char *cmdname);
void				print_err_perm_denied(const char *cmdname);
void				print_err_isdir(const char *path);
void				print_err_redir(void);

// ARRSTR

char				**arrstr_add(char **arr, const char *str);
char				**arrstr_dup(char **arr);
void				arrstr_free(char **arr);
size_t				arrstr_size(char **arr);
char				**arrstr_rm(char **arr, int i);
char				**arrstr_set(char **arr, const char *str, int index);

// BOOLEAN

# define TRUE 1
# define FALSE 0

// BASIC UTILS
// Characters

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isspace(int c);

// Strings

int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *str, char c);
char				**ft_split(const char *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_strjoin_free(char **s1, const char *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
long long			ft_atoll(char *str);

// Other

void				restore_exit(int exit_status);
void				*p_malloc(size_t size);
char				*ft_itoa(int n);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(const char *s, int fd);
size_t				arr_size(const void **arr);

// MODES OF SETTING SIGNALS

# define INTER 1
# define NON_INTER -1
# define HEREDOC 0

void				set_signals(int mode);
void				signals_print_handler(int foo);
void				stop_signals(void);

// Number of the received signal.

int					g_signal;

// LISTS

typedef struct s_list
{
	void			*val;
	struct s_list	*nxt;
	struct s_list	*pre;
}					t_list;

size_t				lst_size(t_list *lst);
t_list				*lst_new(void *value, size_t size);
t_list				*lst_last(t_list *lst);
t_list				*lst_first(t_list *lst);
t_list				*lst_move(t_list *node, int n);
void				lst_add(t_list **lst, t_list *to_add);
void				lst_add_many(t_list **lst, t_list *pos, t_list *to_add);
void				lst_clear(t_list **lst, void (*del)(void *));
void				lst_delone(t_list *lst, void (*del)(void *));
void				lst_link(t_list *n1, t_list *n2);
void				lst_rm_one(t_list **lst, t_list *to_rm,
						void (*del)(void *));
void				lst_rm_many(t_list **lst, t_list *to_rm, size_t n,
						void (*del)(void *));
void				lst_split(t_list *node);

char				*get_input(void);

// TOKENS

enum				e_token_type
{
	WORD,
	REDIR,
	PIPE,
	INVALID,
	NULL_TOK
};

// A token can be of type WORD, REDIRection, PIPE or INVALID.
// It's value is defined as a string.
typedef struct s_token
{
	char			*val;
	unsigned int	type;
}					t_token;

void				tok_del(void *token);
int					tok_type(const char *str);
t_token				tok_create(const char *str);
t_token				*tok_get(t_list *node);
t_token				tok_create_null(void);
t_list				**parse(t_list *tokens, int *exit_status);
t_list				*tokenize(const char *input);

// INPUT UTILS

int					is_blankchr(int c);
int					is_metachr(int c);
int					is_operatorchr(int c);
int					is_redirectionchr(int c);
int					is_quotechr(int c);
int					is_word(const char *str);

// QUOTE UTILS

# define UNQUOTED 0
# define QUOTED 1
# define DQUOTED 2

int					quote_stat(int *curr_stat, char c);

// EXPAND AND SPLIT

t_list				*expand(t_list *toks, int exit_status, char **env);
void				split_words(t_list **xtokens);
void				remove_quotes(t_list *xtokens);
t_list				*normalize(t_list *xtokens);
t_list				**expand_and_split(t_list **commands, int exit_status,
						char **env);

// XCHARS

# define UNEXPANDED 0
# define EXPANDED 1

// An xchar associates a char with a couple of flags to indicate its quote
// status ('q') and if it resulted from an expansion ('x').
typedef struct s_xchar
{
	char			c;
	unsigned int	x;
	unsigned int	q;
}					t_xchar;

t_xchar				xc_new(char c, int x_flag, int q_flag);
t_xchar				xc_get(t_list *node);
char				*xclst_to_str(t_list *xclst);
t_list				*str_to_xclst(const char *str, int x_flag, int q_flag);

// XTOKENS

// A stoken can be of type word, redirection, pipe or invalid.
// It's value is defined as a list of xchars, with quote and expansion flags.
typedef struct s_xtoken
{
	t_list			*val;
	unsigned int	type;
}					t_xtoken;

t_xtoken			*xtok_get(t_list *node);
void				xtok_add_many(t_xtoken *xtok, t_list *pos, t_list *to_add);
void				xtok_addc(t_xtoken *xtok, char c, int x_flag, int q_flag);
void				xtok_addxc(t_xtoken *xtok, t_xchar xc);
void				xtok_rm_one(t_xtoken *xtok, t_list *to_rm);
void				xtok_rm_many(t_xtoken *xtok, t_list *to_rm, size_t n);
void				xtok_rm_xcs(t_xtoken *xtok, t_xchar *to_rm);
t_token				xtok_to_tok(t_xtoken *xtok);
t_xtoken			tok_to_xtok(t_token *tok);
void				xtoklst_clear(t_list **xtoks);
int					xtok_strncmp(t_xtoken *xtok, const char *str, size_t n);

int					open_file(const char *filename, int flags);

// REDIRECT AND EXECUTE

# define READ_END 0 // pipe's read end index
# define WRITE_END 1 // pipe's write end index

typedef struct s_pipe
{
	int				cmds_amount;
	int				prev_fds[2];
	int				next_fds[2];
	int				i;
}					t_pipe;

int					read_all_heredocs(t_list **cmds, int cmds_amount,
						char **env);
pid_t				fork_or_die(void);
void				pipe_or_die(int fd_pipe[2]);
void				link_read_end(int *fd_pipe);
void				link_write_end(int *fd_pipe);
int					wait_children(pid_t pid, size_t n);
int					process_command(t_pipe *p, t_list *cmd, int e_stat,
						char **env);

// REDIRECT

# define SAVE 1 // Save mode for save_restore_stdio()
# define RESTORE 0 // Restore mode for save_restore_stdio()

int					redirect(t_list **cmd, int n);
void				save_restore_stdio(int std_in, int std_out, int mode);
int					read_heredocs(t_list *cmd, int n, char **env);
void				clear_heredocs(int n);
void				redirect_and_execute(t_list **commands, int *exit_status,
						char ***env);

// EXECUTE

int					execute_builtin(t_list *cmd, int exit_status, char ***env,
						int child);
void				execute_command(t_list *cmd, int exit_status, char **env);
char				**get_args_from_cmd(t_list *cmd);
void				exec_cmd(char **cmd, char **env);
char				*get_executable(const char *file, char **env);
int					can_execute(const char *path);
int					is_directory(const char *path);
int					path_exists(const char *path);

// BUILTIN

int					is_builtin_name(const char *str);
int					is_builtin_cmd(t_list *cmd);
int					exec_builtin(char **args, int exit_status, char ***env,
						int is_child);

# define HEREDOC_FILENAME_PREFIX "/tmp/heredoc_temp_"

int					has_quotes(const char *word);
void				delim_quote_remove(char **str);
int					link_input_file(const char *filename);
int					link_output_file(const char *filename, int append);
char				*expand_vars(const char *str, char **env);
char				*heredoc_filename(int n);
int					read_heredoc(const char *delim, int exp, const char *file,
						char **env);
int					link_heredoc(int n);

# define OPEN_FILE_MODE 0644

// ENVIRONMENT

char				**env_get_vars(const char *varname, char **env);
char				*env_get_var(const char *varname, char **env);
int					env_name_len(const char *str);
void				env_set_var(const char *varname, const char *value,
						char ***env, int fl);
void				env_rm_var(const char *varname, char ***env);
int					env_valid_varname(char *word);
char				*env_get_varname(const char *str);
int					env_find_var_index(const char *varname, char **env);
char				*env_find_var_line(const char *varname, char **env);

// BUILTIN

# define LLINT_MIN_STR "9223372036854775808"
# define LLINT_MAX_STR "9223372036854775807"

int					cd_builtin(char **args, char **env);
int					echo_builtin(char **args);
int					env_builtin(char **env);
int					exit_builtin(char **args, int exit_status, int is_child);
int					export_builtin(char **args, char ***env, int exit_status);
int					pwd_builtin(void);
int					unset_builtin(char **args, char ***env);
void				*ft_memcpy(void *dst, const void *src, size_t n);

#endif