#include "../includes/minishell.h"

bool	pasre_setup(t_parsing *parse, int token_ctr)
{
	//t_parsing *parse;

	parse =  ft_safe_malloc(sizeof(t_parsing), "PARSING");

/*
	parse =  ft_safe_malloc(sizeof(t_parsing));
	if (!parse)
		return (false);
*/

	//parse->lexer = ft_safe_malloc(sizeof(t_lexer));
	//if (!parse->lexer)
	//{
	//	//cleanup and free for parse
	//	return (false);
	//}
	// create our lexer and then malloc and setup for our tokens

	if (!(parse->tokens = ft_safe_malloc(sizeof(t_token *) * token_ctr, "TOKENS")))
	{
		//cleanup and free for both lexer and parse
		return (false);
	}
	parse->tokens[token_ctr] = NULL;
	return (true);
}

	/*
		go through the input (av)
			1- until there's a space, tab, etc... 
			2- once a set of characters are grouped, send them to set token
				a- set token mallocs for the token
				b- sets the type of the token

	gradually fill in tokens within the tokens struct
	*/
void	scan(char **av, t_parsing *parse)
{
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
		j = skip_spaces(av[i][j]);
		//skip spaces of av[i][j]; (returns an int of where the string starts after skipping spaces)
		while (av[i][j] != '\0')
		{
			/*
				1- store character into str[c] = av[i][j];
					if we find a space, we break
			*/
			str[c] = av[i][j++];
			//if (ft_isspace(av[i][j]))
			//	break;

			//NOTE: CHECK IF USERS ARE ALLOWED TO SEND MULTIPLE COMMANDS BETWEEN TWO ""
			//IF YES, WE MUST HAVE AN OUTER LOOP TOO TO STORE EACH TOKEN WITHIN ONE VARIABLE SENT TO MAIN
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

	pasre_setup(parse, token_count(av));
	scan(av, parse);
}
