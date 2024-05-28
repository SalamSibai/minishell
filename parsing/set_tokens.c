
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

int		token_count(char *av)
{
	int i;
	int token_ctr;

	token_ctr = 0;
	i = ft_skipspaces(av);
	printf("av of i is %c\n", av[i]);
	while (av[i])
	{
		if (ft_isspace(av[i]))
			token_ctr ++;
		i ++;
	}
	printf("Token count: %d\n", token_ctr);
	return (token_ctr + 1);
}