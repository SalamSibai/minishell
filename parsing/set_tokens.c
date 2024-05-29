
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

// t_token	*set_token(char *str)
// {
// 	//t_token *token;

// 	// printf("im here");
// 	//skip spaces etc
// 	//save av into token->token_string;

// //	token->token_string = ft_strdup(str);

// 	//set type
// 	return (NULL);
// }

int	token_count(char *av)
	{
	int i = -1;
	int token_ctr = 0;
	int in_token = 0;

	i = ft_skipspaces(av);
	while (av[++i])
	{
		if (ft_isspace(av[i]))
		{
			if (in_token)
			{
				in_token = 0;
				token_ctr++;
			}
		}
		else
		{
			if (!in_token)
				in_token = 1;
		}
	}
	if (in_token)
		token_ctr++;
	return (token_ctr);
}
