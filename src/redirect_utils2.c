/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:14:27 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 12:19:44 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>

// Opens the file 'filename' with the 'flags' and returns its file descriptor.
// On failure, prints an error message and returns -1 (setting errno).

// Creates a here document, reading the standard input until 'd' is found and
// saving the content into the specified temp 'file'.
// If 'x' is TRUE, the variable names are expanded.
// Exits with 0 on success, 1 on SIGINT received, or -1 in case of failure.
static int	read_hd_child(const char *d, int x, const char *file, char **env)
{
	int		fd_file;
	char	*line;
	char	*tmp;

	set_signals(HEREDOC);
	fd_file = open_file(file, O_CREAT | O_WRONLY | O_TRUNC);
	if (fd_file == -1)
		return (print_err_heredoc(EXIT_FAILURE));
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			ft_putstr_fd("\033[A\033[2K> ", STDOUT_FILENO);
		if (line == NULL || !ft_strncmp(line, d, ft_strlen(d) + 1))
			break ;
		if (x)
		{
			tmp = expand_vars(line, env);
			free(line);
			line = tmp;
		}
		ft_putendl_fd(line, fd_file);
		free(line);
	}
	exit(close(fd_file));
}

// Allocates and returns a copy of 'str' with its $VARIABLES expanded.
char	*expand_vars(const char *str, char **env)
{
	int		i;
	char	*ret_str;
	char	*tmp_str;
	char	*var;

	ret_str = ft_strdup("");
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && str[++i] && (ft_isalpha(str[i]) || str[i] == '_'))
		{
			tmp_str = ft_substr(str, 0, i - 1);
			ft_strjoin_free(&ret_str, tmp_str);
			free(tmp_str);
			var = env_get_var(str + i, env);
			if (var)
				ft_strjoin_free(&ret_str, var);
			str += i + env_name_len(str + i);
			i = 0;
		}
		else
			i++;
	}
	ft_strjoin_free(&ret_str, str);
	return (ret_str);
}

// Creates a here document, reading the standard input until 'delim' is found
// and saving the content into the specified temp 'file'.
// If 'exp' is TRUE, the variable names are expanded.
// Returns 0 on success, 1 on SIGINT received, or -1 in case of failure.
int	read_heredoc(const char *delim, int exp, const char *file, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		read_hd_child(delim, exp, file, env);
	wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status) && (WTERMSIG(status) == SIGINT))
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}
