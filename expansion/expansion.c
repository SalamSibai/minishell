/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:22:07 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/02 20:29:17 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	1-loop thru all the tokens and check if you can find a $ sign
	2-now we need to find the variable name in the enviroment
	
	2-We loop in the enviroment and check if the variable name it found
	if we found the variable name we replace the token with the value of the vairable name 

	so we need the enviroment to be passed to the function
	and the parse data to loop thru all the tokens strings  except fot the string inside of the single quotes and check if we have a $ sign
*/

/**
 * @brief find the variable name in the enviroment
 * 
 * @param env 
 * @param var_name 
 * @return the expanded string if found and null if not found
 */
char	*find_env_var_name(t_list *env, char *var_name)
{
	char	*expanded_str;

	expanded_str = NULL;
	while (env)
	{
		if (ft_strncmp(env->content, var_name, ft_strlen(var_name)) == 0)
		{
			expanded_str = ft_strdup(ft_strchr(env->content, '=') + 1);
			return (expanded_str);
		}
		env = env->next;
	}
	return (expanded_str);
}

/**
 * @brief replace the token string with the vairable name from the env
 * 
 * 
 * @param token_string 
 * @return 
 */
char	*get_var_name(char *token_string)
{
	int		i;
	char	*var_name;

	i = 1;
	while (token_string[i])
		i++;
	var_name = ft_substr(token_string, 1, i - 1);
	return (var_name);
}

/**
 * @brief 
 * 
 * @param tokens 
 * @param env 
 * @return updated tokens with the expanded variables
 
 */
t_token		**check_expandable_var(t_token **tokens, t_list *env)
{
	int i;
	char *var_name;
	char *expanded_str;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type != REDIRECT_APPEND && tokens[i]->type != REDIRECT_INPUT 
			 && tokens[i]->type != REDIRECT_OUTPUT && tokens[i]->type != PIPE && tokens[i]->type != SQOUTES)
		{
			if (ft_strchr(tokens[i]->token_string, '$'))
			{
				var_name = get_var_name(ft_strchr(tokens[i]->token_string, '$')); //need to free this 
				expanded_str = find_env_var_name(env, var_name);
				if (expanded_str)
				{
					tokens[i]->token_string = ft_strjoin(ft_strndup(tokens[i]->token_string, ft_strchr(tokens[i]->token_string, '$') - tokens[i]->token_string), expanded_str);
					// free(tokens[i]->token_string); // i need to join first the token string with the expanded string //i need to join 
				}
				else
				{
					free(tokens[i]->token_string);
					tokens[i]->token_string = ft_strdup("");
				}
				free(var_name);
			}
		}
		i++;
	}
	return (tokens);
}
