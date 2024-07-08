

#include "../includes/minishell.h"

int	skip_spaces(int *token_ctr, int *in_token, char *av, int i)
{
	if (ft_isspace(av[i]))
	{
		if (*in_token)
		{
			*in_token = 0;
			return (*token_ctr + 1);
		}
	}
	return (0);
}

bool	is_pipe_or_redir(int *token_ctr, int *in_token, char *av, int i)
{
	if ((av[i] == '|' && av[i + 1] != '|')
		|| (av[i] == '>' && av[i + 1] != '>')
		|| (av[i] == '<' && av[i + 1] != '<'))
	{
		if (in_token)
		{
			*in_token = 0;
			*token_ctr += 1;
		}
		*token_ctr += 1;
		return (true);
	}
	return (false);
}

bool	is_append_or_heredoc(int *token_ctr, int *in_t, char *av, int *i)
{
	if ((av[*i] == '>' && av[*i + 1] == '>')
		|| (av[*i] == '<' && av[*i + 1] == '<'))
	{
		if (*in_t)
		{
			*in_t = 0;
			*token_ctr += 1;
		}
		*token_ctr += 1;
		*i += 1;
		return (true);
	}
	return (false);
}

bool	is_dquote_or_quote(int *token_ctr, int *in_t, char *av, int *i)
{
	if (av[*i] == '\"' || av[*i] == '\'')
	{
		if (*in_t)
		{
			*in_t = 0;
			*token_ctr += 1;
		}
		*token_ctr += 1;
		*i += 1;
		return (true);
	}
	return (false);
}

void	itir_tokens(int *token_ctr, int *in_t, char *av, int *i)
{
	if (skip_spaces(token_ctr, in_t, av, *i) != 0)
		*token_ctr += 1;
	if (is_pipe_or_redir(token_ctr, in_t, av, *i))
		return ;
	if (is_append_or_heredoc(token_ctr, in_t, av, i))
		return ;
	if (is_dquote_or_quote(token_ctr, in_t, av, i))
		return ;
	else
	{
		if (!*in_t)
			*in_t = 1;
	}
}
