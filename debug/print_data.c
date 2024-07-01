/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:31:36 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/01 20:56:46 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_data(t_data *data)
{
	// t_token	**tokens;

	// tokens = data->tokens;
	
	int i;

	// i = -1;
	// printf("env_var: %s\n", data->env_var);
	// printf("buf: %s\n", data->buf);
	// while (data->env_var[++i])
	// {
	// 	printf("env[%d]: %s\n", i, data->env->content);
	// 	data->env = data->env->next;
	// }


	// i = 0;
	// printf("****************        After Validation       ****************\n");
	// while (tokens[i] != NULL)
	// {
	// 	if (tokens[i]->type == ID)
	// 		printf("Token_string: (%s)\n token_type: ID\n\n", tokens[i]->token_string);
	// 	else if (tokens[i]->type == CMDS)
	// 		printf("Token_string: (%s)\ntoken: cmd\n\n", tokens[i]->token_string);
	// 	else if (tokens[i]->type == PIPE)
	// 		printf("Token_string: (%s)\ntoken: pipe\n\n", tokens[i]->token_string);
	// 	else if (tokens[i]->type == LIMITER)
	// 		printf("Token_string: (%s)\ntoken: limiter\n\n", tokens[i]->token_string);
	// 	else if (tokens[i]->type == FILE_NAME)
	// 		printf("Token_string: (%s)\ntoken: file\n\n", tokens[i]->token_string);
	// 	else if (tokens[i]->type == REDIRECT_INPUT)
	// 		printf("Token_string: (%s)\ntoken: redirect_input\n\n", tokens[i]->token_string);
	// 	else if (tokens[i]->type == REDIRECT_OUTPUT)
	// 		printf("Token_string: (%s)\ntoken: redirect output\n\n", tokens[i]->token_string);
	// 	else if (tokens[i]->type == REDIRECT_APPEND)
	// 		printf("Token_string: (%s)\ntoken: redirect_append\n\n", tokens[i]->token_string);
	// 	else if (tokens[i]->type == FLAG)
	// 		printf("Token_string: (%s)\ntoken: flag\n\n", tokens[i]->token_string);
	// 	else if (tokens[i]->type == DQOUTES)
	// 		printf("Token_string: (%s)\ntoken: string in double quote\n\n", tokens[i]->token_string);
	// 	else if (tokens[i]->type == SQOUTES)
	// 		printf("Token_string: (%s)\ntoken: string in single qoute\n\n", tokens[i]->token_string);
	// 	else if (tokens[i]->type == HEREDOC)
	// 		printf("Token_string: (%s)\ntoken: heredoc\n\n", tokens[i]->token_string);
	// 	else
	// 		printf("Token_string: (%s)\ntoken: some wrong doesnt have a type (%d)\n\n", tokens[i]->token_string, tokens[i]->type);
	// 	i++;
	// }


	printf("****************        After Parsing cmds values       ****************\n\n");
	int k;
	t_list *temp;
	t_list *flag;
	
	i = 0;
	while (i < data->cmd_num)
	{
		printf("*********        CMD NUMBER %d    *********\n", i);
		printf("cmd[%d]->cmd: %s\n", i, data->cmds[i]->cmd_str);
		flag = data->cmds[i]->flag;
		while (data->cmds[i]->flag)
		{
			printf("cmd[%d]->flag: %s\n", i, (char *)data->cmds[i]->flag->content);
			data->cmds[i]->flag = data->cmds[i]->flag->next;
		}
		data->cmds[i]->flag = flag;
		k = 0;
		temp = data->cmds[i]->args;
		while (data->cmds[i]->args)
		{
			printf("cmd[%d]->arg[%d]: %s\n", i, k, (char *)data->cmds[i]->args->content);
			data->cmds[i]->args = data->cmds[i]->args->next;
			k++;
		}
		data->cmds[i]->args = temp;
			
		int j = 0;
		while (data->cmds[i]->redirection != NULL)
		{
			printf("__________________________________Redirections num %d for cmd[%d] *********\n\n", j, i);
			printf("redirection[%d]->type: %d\n", j, data->cmds[i]->redirection->type);
			// printf("redirection[%d]->fd: %d\n", j, data->cmds[i]->redirection->fd);
			printf("redirection[%d]->file_name: %s\n", j, data->cmds[i]->redirection->file_name);
			printf("redirection[%d]->limiter: %s\n", j, data->cmds[i]->redirection->limiter);
			data->cmds[i]->redirection = data->cmds[i]->redirection->next;
			j++;
		}
		printf("\n\n");
		i++;
	}

}
