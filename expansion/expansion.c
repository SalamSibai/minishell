/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:22:07 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/28 10:38:43 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	1-loop thru all the tokens and check if you can find a $ sign
	2-now we need to find the variable name in the enviroment
	
	2-We loop in the enviroment and check if the variable name found
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
//  */
// char	*find_env_var_name(t_list *env, char *var_name)
// {
// 	char	*expanded_str;

// 	expanded_str = NULL;
// 	while (env)
// 	{
// 		if (ft_strncmp(env->content, var_name, ft_strlen(var_name)) == 0)
// 		{
// 			expanded_str = ft_strdup(ft_strchr(env->content, '=') + 1);
// 			return (expanded_str);
// 		}
// 		env = env->next;
// 	}
// 	return (expanded_str);
// }

// /**
//  * @brief replace the token string with the vairable name from the env
//  * 
//  * 
//  * @param token_string 
//  * @return 
//  */
// char	*get_var_name(char *token_string)
// {
// 	int		i;
// 	char	*var_name;

// 	i = 1;
// 	while (token_string[i])
// 		i++;
// 	if (token_string[i - 1] == '\'')
// 		i--;
// 	var_name = ft_substr(token_string, 1, i - 1);
// 	return (var_name);
// }

// /**
//  * @brief 
//  * 
//  * @param tokens 
//  * @param env 
//  * @return updated tokens with the expanded variables
 
//  */
// t_token		**check_expandable_var(t_token **tokens, t_list *env)
// {
// 	int i;
// 	char *var_name;
// 	char *expanded_str;

// 	i = 0;
// 	while (tokens[i])
// 	{
// 		if (tokens[i]->expandable == true && tokens[i]->type != REDIRECT_APPEND && tokens[i]->type != REDIRECT_INPUT 
// 			 && tokens[i]->type != REDIRECT_OUTPUT && tokens[i]->type != PIPE && tokens[i]->type != SQOUTES)
// 		{
// 			if (ft_strchr(tokens[i]->token_string, '$'))
// 			{
// 				var_name = get_var_name(ft_strchr(tokens[i]->token_string, '$')); //need to free this 
// 				expanded_str = find_env_var_name(env, var_name);
// 				if (expanded_str)
// 				{
// 					if (tokens[i]->token_string[ft_strlen(tokens[i]->token_string) - 1]  == '\'')
// 						tokens[i]->token_string = ft_strjoin(ft_strjoin(ft_strndup(tokens[i]->token_string, ft_strchr(tokens[i]->token_string, '$') - tokens[i]->token_string), expanded_str), "'");
// 					else
// 						tokens[i]->token_string = ft_strjoin(ft_strndup(tokens[i]->token_string, ft_strchr(tokens[i]->token_string, '$') - tokens[i]->token_string), expanded_str);
// 				}
// 				else
// 				{
// 					free(tokens[i]->token_string);
// 					tokens[i]->token_string = ft_strdup("");
// 				}
// 				free(var_name);
// 			}
// 		}
// 		i++;
// 	}
// 	return (tokens);
// }

char    *ft_strjoin_free(char *s1, char *s2, int free_mode)
{
	char    *joined_str;
	size_t  len1;
	size_t  len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = strlen(s1);
	len2 = strlen(s2);
	joined_str = malloc(len1 + len2 + 1);
	if (!joined_str)
		return (NULL);
	strcpy(joined_str, s1);
	strcat(joined_str, s2);
	if (free_mode == 1 || free_mode == 3)
		free(s1);
	if (free_mode == 2 || free_mode == 3)
		free(s2);
	return (joined_str);
}

char    *find_env_var_name(t_list *env, char *var_name)
{
	char    *expanded_str;

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

char    *get_var_name(char *token_string, int *end_idx)
{
	int     i;
	char    *var_name;

	i = 1;
	while (token_string[i] && (ft_isalnum(token_string[i]) || token_string[i] == '_'))
		i++;
	if (end_idx)
		*end_idx = i;
	var_name = ft_substr(token_string, 1, i - 1);
	return (var_name);
}

char    *replace_env_var(char *str, t_list *env)
{
	char    *result;
	char    *var_name;
	char    *expanded_str;
	int     start;

	result = ft_strdup("");
	while (*str)
	{
		if (*str == '$')
		{
			if (*(str + 1) == '?')
			{
				expanded_str = ft_itoa(g_exit_status); // Assuming last_exit_code holds the value of $?
			}
			else
			{
				var_name = get_var_name(str, &start);
				expanded_str = find_env_var_name(env, var_name);
				free(var_name);
				if (!expanded_str)
					expanded_str = ft_strdup("");
			}
			result = ft_strjoin_free(result, expanded_str, 3);
			str += start;
		}
		else
		{
			result = ft_strjoin_free(result, ft_substr(str, 0, 1), 1);
			str++;
		}
	}
	return (result);
}

t_token **check_expandable_var(t_token **tokens, t_list *env)
{
	int     i;
	char    *expanded_str;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->expandable == true && tokens[i]->type != REDIRECT_APPEND && tokens[i]->type != REDIRECT_INPUT
			&& tokens[i]->type != REDIRECT_OUTPUT && tokens[i]->type != PIPE && tokens[i]->type != SQOUTES)
		{
			if (ft_strchr(tokens[i]->token_string, '$'))
			{
				expanded_str = replace_env_var(tokens[i]->token_string, env);
				free(tokens[i]->token_string);
				tokens[i]->token_string = expanded_str;
			}
		}
		i++;
	}
	return (tokens);
}
