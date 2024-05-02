

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

t_token	*set_token(char *str)
{
	t_token *token;

	token = malloc(sizeof(token));
	if (!token)
		return (NULL);
	
	//set type
	return (token);
}

bool	pasre_setup(t_parsing *parse)
{
	//t_parsing *parse;

	parse =  ft_safe_malloc(sizeof(t_parsing));
	if (!parse)
		return (false);
	//parse->lexer = ft_safe_malloc(sizeof(t_lexer));
	//if (!parse->lexer)
	//{
	//	//cleanup and free for parse
	//	return (false);
	//}
	// create our lexer and then malloc and setup for our tokens

	parse->tokens = ft_safe_malloc(sizeof(t_token *));
	if (!parse->tokens)
	{
		//cleanup and free for both lexer and parse
		return (false);
	}
	return (true);
}

void	scan(char **av, t_parsing *parse)
{
	/*
		go through the input (av)
			1- until there's a space, tab, etc... 
			2- once a set of characters are grouped, send them to set token
				a- set token mallocs for the token
				b- sets the type of the token

	gradually fill in tokens within the tokens struct
	*/
	int i;
	int j;
	int c;
	int token_ctr;
	char *str;

	c = 0;
	token_ctr = 0;
	i = -1;
	while (av[++i] != NULL)
	{
		j = 0;
		//skip spaces of av[i][j]; (returns an int of where the string starts after skipping spaces)
		while (av[i][j] != '\0')
		{
			/*
				1- store character into str[c] = av[i][j];
					if we find a space, we break
			*/
		}
		parse->tokens[token_ctr] = set_token(str);
		/*
			if (!parse->tokens[token_ctr])
				free, cleanup, empty, exit
		*/
		//empty str;
		token_ctr ++;
	}

}

int main(int ac, char **av, char **env)
{
	//init and store data in t_data variable

	t_parsing *parse;

	pasre_setup(parse);
	scan(av, parse);
}
					