
#include "../includes/minishell.h"




int main(int ac, char **av, char **env)
{
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

}
					