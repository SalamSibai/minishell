
#include "../includes/minishell.h"

void    set_type(t_token *token)
{
	//strcmp
	if (ft_strcmp(token->token_string, "|"))
		token->type = PIPE;
	else if (ft_strncmp(token->token_string, "-", 1))
		token->type = FLAG;
	else if (ft_strcmp(token->token_string, "<"))
		token->type = REDIRECT_INPUT;
	else if (ft_strcmp(token->token_string, ">"))
		token->type = REDIRECT_OUTPUT;
	else if (ft_strcmp(token->token_string, "<<"))
		token->type = HEREDOC;
	else if (ft_strcmp(token->token_string, ">>"))
		token->type = REDIRECT_APPEND;
	else
		token->type = ID;
	//$ env variables
	//$? what
}

t_token	*set_token(char *str)
{
	t_token *token;

	// printf("im here");
	token = ft_safe_malloc(sizeof(t_token), "Token data");
	token->token_string = ft_strdup(str);

	//set type
	return (token);
}

int		token_count(char *av)
{
	int i;
	// int j;
	int token_ctr;

	token_ctr = 0;
	i = -1;
	while (av[++i])
	{
		while (av[i] && !ft_isspace(av[i]))
		{
			i++;
		}
		token_ctr ++;
	}
	printf("Token count: %d\n", token_ctr);
	return (token_ctr);
}