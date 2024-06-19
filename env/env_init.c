/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:03:15 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/19 10:24:17 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*env_init(char **envp)
{
	t_list *env;
	t_list *new;

	int i = 0;
	env = ft_lstnew(envp[i]);
	while (envp[++i])
	{
		new = ft_lstnew(envp[i]);
		ft_lstadd_back(&env, new);
	}
	return (env);
}
/**
 * @brief copy the env list to the export env list
 * 
 * @param env 
 * @return 
 */
t_list	*export_env_init(t_list *env)
{
	t_list *export_env;
	t_list *new;

	export_env = ft_lstnew(env->content);
	while (env->next)
	{
		new = ft_lstnew(env->next->content);
		ft_lstadd_back(&export_env, new);
		env = env->next;
	}
	return (export_env);
}

/**
 * @brief function to transfers the list nodes into a double array
 * 
 * @param env 
 * @return char** 
 */
char	**env_to_str(t_list *env)
{
	int i;
	int j;
	char **env_str;
	char *tmp;

	i = 0;
	env_str = ft_calloc((ft_lstsize(env)), sizeof(char *));
	while (env && env->next)
	{
		env_str[i] = ft_calloc(ft_strlen(env->content) + 1, sizeof(char));
		tmp = ft_strdup(env->content);
		j = -1;
		while (tmp[++j])
			env_str[i][j] = tmp[j];
		env_str[i][j] = '\0';
		env = env->next;
		free(tmp);
		i++;
	}
	env_str[i] = NULL;
	return (env_str);
}
