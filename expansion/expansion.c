/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:22:07 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/05 07:42:50 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	1-loop thru all the tokens and check if you can find a $ sign
	2-now we need to find the variable name in the enviroment
	
	2-We loop in the enviroment and check if the variable name found
	if we found the variable name we replace the token with the value
	 of the vairable name 

	so we need the enviroment to be passed to the function
	and the parse data to loop thru all the tokens strings
	except fot the string inside of the single quotes
	and check if we have a $ sign
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

char	*get_var_name(char *token_string, int *end_idx)
{
	int		i;
	char	*var_name;

	i = 1;
	while ((token_string[i])
		&& (ft_isalnum(token_string[i]) || token_string[i] == '_'))
		i++;
	if (end_idx)
		*end_idx = i;
	var_name = ft_substr(token_string, 1, i - 1);
	return (var_name);
}

/**
 * @brief this function itll process the env variable and
 * replace it with the value of the variable in the env list
 * @param str 
 * @param env 
 * @param start an int pointer to keep track of the index of the string
 * @return 
 */
char	*process_env_var(char *str, t_list *env, int *start, t_data *data)
{
	char	*expanded_str;
	char	*var_name;

	if (*(str + 1) == '?')
	{ 
		expanded_str = ft_itoa(data->g_exit_status);
		*start = 2;
	}
	else
	{
		var_name = get_var_name(str, start);
		expanded_str = find_env_var_name(env, var_name);
		free(var_name);
		if (!expanded_str)
			expanded_str = ft_strdup("");
	}
	return (expanded_str);
}

// Main function to replace environment variables in a string
/**
 * @brief this is the main function that will replace the env variable
 * @param str the string to be checked for $ sign
 * @param env env list to check for the variable name in it
 * @return char* 
 */
char	*replace_env_var(char *str, t_list *env, t_data *data)
{
	char	*result;
	char	*expanded_str;
	int		start;

	result = ft_strdup("");
	while (*str)
	{
		if (*str == '$' && (*(str + 1) != '\0' && *(str + 1) != ' '))
		{
			expanded_str = process_env_var(str, env, &start, data);
			result = ft_strjoin_free(result, expanded_str, 3);
			str += start;
		}
		else
			result = ft_strjoin_free(result, ft_substr(str++, 0, 1), 3);
	}
	if (result[0] == '\0')
	{
		free(result);
		result = ft_strdup("");
	}
	return (result);
}

t_token	**check_expandable_var(t_token **tokens, t_data *data)
{
	int		i;
	char	*expanded_str;
	t_list	*env;

	env = data->env;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->expandable == true && tokens[i]->type != REDIRECT_APPEND
			&& tokens[i]->type != REDIRECT_INPUT
			&& tokens[i]->type != REDIRECT_OUTPUT
			&& tokens[i]->type != PIPE && tokens[i]->type != SQOUTES)
		{
			if (ft_strchr(tokens[i]->token_string, '$'))
			{
				expanded_str = replace_env_var(tokens[i]->token_string, env, data);
				free(tokens[i]->token_string);
				tokens[i]->token_string = expanded_str;
			}
		}
		i++;
	}
	return (tokens);
}
