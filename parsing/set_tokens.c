
#include "../includes/minishell.h"

/*
	execution flow:
		1) create t_data struct and initialize
			- split the PATH into the **path variable
			- store env in **envp
			- initialize and set t_env variable
		2) malloc for and initialize parse_data
		3) scan and fill in lexer & tokens
			- check the tokens, sets the type, and the string that represents the token.
			- increments the lexer (based on the token type)
			- this function also cleans up the string, making sure there are no spaces etc
		4) start filling in **cmd variable from the tokens
		5) if we have pipes:
			- initialzie and set the *pipe varibale from the lexer and the tokenizer
		6) if we have redirections:
			- "> outfile_name" we check the syntax correctness (has a filename or limiter after)
			- if everything is fine, we initialize and store
*/

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

	token = ft_safe_malloc(sizeof(t_token), "Token data");
	token->token_string = ft_strdup(str);

	//set type
	return (token);
}

int		token_count(char **av)
{
	int i;
	int j;
	int token_ctr;

	token_ctr = 0;
	i = -1;
	while (av[++i] != NULL)
	{
		j = skip_spaces(av[i][j]);
		while (av[i][j] != '\0')
		{
			j ++;
		}
		token_ctr ++;
	}
	return (token_ctr);
}