/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:11:08 by ydunay            #+#    #+#             */
/*   Updated: 2024/03/09 12:15:41 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <readline/readline.h>

// Allocates and returns a string representing the here document temp filename
// for the 'n'-th command.
char	*heredoc_filename(int n)
{
	char	*tmp;
	char	*filename;

	filename = ft_strdup(HEREDOC_FILENAME_PREFIX);
	tmp = ft_itoa(n);
	ft_strjoin_free(&filename, tmp);
	free(tmp);
	return (filename);
}

// Performs quote removal on 'word'.
void	delim_quote_remove(char **word)
{
	char	last_quote;
	int		i;
	int		j;
	char	*str;

	str = (char *)p_malloc(sizeof(char) * (ft_strlen(word[0]) + 1));
	i = -1;
	j = -1;
	last_quote = 0;
	while (word[0][++i])
	{
		if (last_quote != 0 && last_quote == word[0][i])
			last_quote = 0;
		else if (last_quote == 0 && is_quotechr(word[0][i]))
			last_quote = word[0][i];
		else
			str[++j] = word[0][i];
	}
	str[++j] = '\0';
	free(*word);
	*word = str;
}

// Returns TRUE if the null-terminated string 'word' has any ' or " character.
// Otherwise, returns FALSE.
int	has_quotes(const char *word)
{
	if (!ft_strchr(word, '"') && !ft_strchr(word, '\''))
		return (FALSE);
	return (TRUE);
}

// Reads the here document for the 'n'-th command, assuming 'str' is the word
// right next to the << token.
// Returns 0 on success, or -1 in case of failure (setting errno).
static int	read_heredoc_n(const char *str, int n, char **env)
{
	char	*delim;
	int		expand;
	char	*file;
	int		ret;

	delim = ft_strdup(str);
	expand = !has_quotes(delim);
	delim_quote_remove(&delim);
	file = heredoc_filename(n);
	ret = read_heredoc(delim, expand, file, env);
	free(delim);
	free(file);
	return (ret);
}

// Reads the here documents for 'cmd' from left to right, into a temp file
// knowing it's the 'n'-th command.
// If there's more than one here document, the previous ones are overwritten.
// Returns 0 on success. Otherwise, returns a non-zero value.
int	read_heredocs(t_list *cmd, int n, char **env)
{
	t_list	*node;
	t_token	*tok;
	int		err;

	node = cmd;
	while (node)
	{
		tok = tok_get(node);
		if (tok->type == REDIR && !ft_strncmp(tok->val, "<<", 3))
		{
			err = read_heredoc_n(tok_get(node->nxt)->val, n, env);
			if (err)
				return (err);
			node = node->nxt;
		}
		node = node->nxt;
	}
	return (EXIT_SUCCESS);
}
