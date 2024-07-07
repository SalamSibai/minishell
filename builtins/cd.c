/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:05:21 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/07 04:00:59 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * @brief this function get a string that contains the path specifed 
 * 	in the const var and it looks for it in it env sturcture if ts in there
 * and if found it start copying the rest of the path from the env
 * @param env A pointer to a structure (`t_env`) containing information
 *  about the shell environment.
 * @param var is the path_name to look for
 * in the env sturcture mainly "HOME" OR "OLDPWD"
 * @param size is the size of the path name to be searched in the env
 * @return 
 */
char	*get_env_path(t_list *env, const char *var, size_t size)
{
	char	*env_path;
	char	*env_content;
	int		iter[3];

	while (env && env->next)
	{
		env_content = (char *)env->content;
		if (ft_strncmp(env->content, var, size) == 0)
		{
			iter[2] = ft_strlen(env->content) - (int)size;
			env_path = ft_calloc(1, iter[2] + 1);
			iter[0] = 0;
			iter[1] = 0;
			while (env_content[iter[0]])
			{
				if (iter[0] > (int)size)
					env_path[iter[1]++] = env_content[iter[0]];
				iter[0]++;
			}
			env_path[iter[1]] = '\0';
			return (env_path);
		}
		env = env->next;
	}
	return (NULL);
}

/**
 * @brief this function changes the path based on the option 
 * given from the cd function
 * if option is 0 itll go to the home path as 0 represent
 * no arguments were given
 * else if option is 1 itll go to the oldpwd as 1 represent
 * that the argument '-' were recieved
 * @param option a flag to change the path to HOME or OLDPWD
 * @param env A pointer to a structure (`t_env`) containing 
 * information about the shell environment.
 * @return it frees the env_path allocated for the path and 
 * then returns zero on succses and -1 if an error occured
 */
int	goto_path(int option, t_list *env)
{
	char	*env_path;
	int		ret;

	env_path = NULL;
	if (option == 0)
	{
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
			return (ft_putendl_fd("minishell : cd: HOME not set", 2), 42);
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			return (ft_putendl_fd("minishell : cd: OLDPWD not set", 2), 42);
		ft_putendl_fd(env_path, 1);
	}
	ret = chdir(env_path);
	return (free(env_path), ret);
}

void	update_pwds(t_list *env, t_list *export_env)
{
	char	*pwd;
	char	*oldpwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	oldpwd = get_env_path(env, "PWD", 3);
	tmp = ft_strjoin("OLDPWD=", oldpwd);
	ft_export_pwds(tmp, env, export_env);
	free(tmp);
	tmp = ft_strjoin("PWD=", pwd);
	ft_export_pwds(tmp, env, export_env);
	free(tmp);
	free(pwd);
	free(oldpwd);
}

//i need to update the enviroment content for pwd and oldpwd
/**
 * @brief this function changes the current directory 
 * @param args An array of strings representing the
 *  command and its arguments.
 * @param env A pointer to a structure (`t_env`) 
 * containing information about the shell environment.
 * @return Returns 0 on success or -1 
 * if there was an error changing the directory.
 */
int	ft_cd(t_cmd *cmd, t_list *env, t_list *export_env)
{
	int	cd_ret;

	cd_ret = 0;
	if (!cmd->args)
		return (goto_path(0, env));
	else if (ft_lstsize(cmd->args) > 1)
		error_handler(NULL, -1, NULL, false);
	else if (cmd->args && (ft_strcmp(cmd->args->content, "-") == 0))
	{
		cd_ret = goto_path(1, env);
	}
	else
	{
		cd_ret = chdir(cmd->args->content);
		if (cd_ret == -1)
		{
			error_handler("No such file or directory",
				IN_REDIR_ER, NULL, false);
			return (1);
		}
	}
	update_pwds(env, export_env);
	g_exit_status = 0;
	return (cd_ret);
}
