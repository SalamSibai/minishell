

#include "../includes/minishell.h"
/*
int    execute_cmd(t_cmd *cmd, t_data *data, int i, int j)
{
    int pid;

    data->origin_fds[0] = dup(STDIN_FILENO);
    data->origin_fds[1] = dup(STDOUT_FILENO);
    pid = fork();
    if (pid == -1)
        return (error_handler(FORK_ER_MSG, FORK_ER, data, false), pid);
    if (pid == 0)
    {
        if (!redirect_fds(data, cmd, i, j))
        {
            close_origin_fds(data);
            exit (1);
        }
        close_origin_fds(data);
        if (i != 0 )
            close_pipe(data->pipe, 0, true);
        //executing inside child then exiting
        if (is_builtin(cmd->cmd_str) && (data->cmd_num >= 1))
        {
            if (!close_fds(data, i, true))
                printf("close failed!\n");
            exec_builtin(cmd, data);
            free_cmd(data);
            set_env_and_path(data, FREE);
            cleanup(data);
            exit(2);
        }
        //exiting the child (after closing and all)
        else if (is_env_builtin(cmd->cmd_str))
        {
            if (!close_fds(data, i, true))
                printf("close failed!\n");
            free_cmd(data);
            set_env_and_path(data, FREE);
            cleanup(data);
            exit (2);
        }
        else
        {
            if (join_cmd_and_flag)
            {
                if (get_path(data, cmd))
				{
					close_fds(data, i, true);
					execve(cmd->cmd_path, cmd->cmd_with_flag, data->env_var);
				}
				else
                {
                    close_fds(data, i, true);
					error_handler(PATH_ER_MSG, PATH_ER, data, true);
                }
            }
            else
            {
                close_fds(data, i, true);
                error_handler(CMD_ER_MSG, CMD_ER, data, true);
            }
        }
        exit(1);
    }
    else
    {
        if (is_env_builtin(cmd->cmd_str) && data->cmd_num == 1)
        {
            pid = getpid();
            if(!redirect_fds(data, cmd, i, j))
                return (pid);
            close_fds(data, i, false);
            exec_builtin(cmd, data);
        }
		if (i > 0)
			close(data->pipe->fd[!j][0]);
		if (i < data->cmd_num - 1)
			close(data->pipe->fd[j][1]);
    }
    return (pid);
}

bool    execute(t_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;

    if (data->cmds[0]->cmd_str == NULL && data->cmd_num == 1)
    {
        if (data->cmds[0]->redirection != NULL)
            close_fds(data, 0, false);
        return (true);
    }
    alloc_pids(data);
    if (data->cmd_num == 1)
        data->pipe->pid[0] = exec_cmd(data->cmds[0], data, 0, 0);
    else
    {
        if (!make_pipes(data->pipe))
            return (error_handler(PIPE_ER_MSG, PIPE_ER, data, false), false);
        while (i < data->cmd_num)
        {
            data->pipe->pid[i] = execute_cmd(data->cmds[i], data, i, j);
            close_origin_fds(data);
            if (i >= 1 && i < data->cmd_num - 1)
            {
                close_pipe(data->pipe, !j, false);
              	if (pipe(data->pipe->fd[!j]) == -1)
					return (error_handler(PIPE_ER_MSG, PIPE_ER, data, false), false);
            }
            i ++;
            j = !j;
        }
        i = -1;
    }
    while (++i < data->cmd_num)
    {
        if (i == 0)
            close_fds(data, i, true);
        else
            close_fds(data, i, false);
    }
    i = -1;
	while (++i < data->cmd_num)
		waitpid(data->pipe->pid[i],  &g_exit_status, 0);
    dup2(STDIN_FILENO, data->origin_fds[0]);
	dup2(STDOUT_FILENO, data->origin_fds[1]);
	return (true);
}






*/

















/// @brief executes the commands
/// @param cmd pntr to cmd struct
/// @param data pntr to data struct
/// @param i cmd index
/// @param j "flip flop" for pipes
/// @return pid
int	exec_cmd(t_cmd *cmd, t_data *data, int i, int j)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (error_handler(FORK_ER_MSG, FORK_ER, data, false), pid);
	if (pid == 0)
	{
		data->origin_fds[0] = dup(STDIN_FILENO);
		data->origin_fds[1] = dup(STDOUT_FILENO);
		if (!redirect_fds(data, cmd, i, j))
		{
			close_origin_fds(data);
			exit(1);
			//return (pid);
		}
		close_origin_fds(data);
		if (i != 0)
			close_pipe(data->pipe, 0, true);
		if (is_builtin(cmd->cmd_str) && (data->cmd_num > 1))
		{
			printf("IS BUILTIN\n");
			close_fds(data, i, true);
			exec_builtin(cmd, data);
			free_cmd(data);
			set_env_and_path(data, FREE);
			cleanup(data);
			exit(2);
		}
		if (is_env_builtin(cmd->cmd_str))
		{
			close_fds(data, i, true);
			free_cmd(data);
			set_env_and_path(data, FREE);
			cleanup(data);
			exit (2);
		}
		else
		{
			if (join_cmd_and_flag(cmd))
			{
				if (get_path(data, cmd))
				{
					close_fds(data, i, true);
					execve(cmd->cmd_path, cmd->cmd_with_flag, data->env_var);
				}

				else
					error_handler(PATH_ER_MSG, PATH_ER, data, true);
			}
			else
				error_handler(CMD_ER_MSG, CMD_ER, data, true);
		}
		exit(1);
		//close_origin_fds(data); // Close in case of error
		//close_fds(data, i, true);
	}
	else
	{
		if (is_env_builtin(cmd->cmd_str) && data->cmd_num == 1)
		{
			pid = getpid();
			if (!redirect_fds(data, cmd, i, j))
				return (pid);
			close_fds(data, i, false);
			exec_builtin(cmd, data);
		}
		if (i > 0)
			close(data->pipe->fd[!j][0]);
		if (i < data->cmd_num - 1)
			close(data->pipe->fd[j][1]);
	}
	return (pid);
}

/**
 * @brief this function will execute the commands based on the type of command
 * 	SHOULD MAKE FUNCTION BOOL?
 * @param data
 */
bool	execution(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (data->cmds[0]->cmd_str == NULL)
		return (true);
	alloc_pids(data);
	if (data->cmd_num > 1)
	{
		printf("calling make pipes\n");
		if (!make_pipes(data->pipe))
			return (error_handler(PIPE_ER_MSG, PIPE_ER, data, false), false);
		while (data->cmds[i] != NULL)
		{
			data->pipe->pid[i] = exec_cmd(data->cmds[i], data, i, j);
			if (i >= 1 && i < data->cmd_num - 1)
			{
				close_pipe(data->pipe, !j, false);
				if (pipe(data->pipe->fd[!j]) == -1)
					return (error_handler(PIPE_ER_MSG, PIPE_ER, data, false), false);
			}
			i++;
			j = !j;
		}
		close_pipe(data->pipe, !j, false);
	}
	else
		data->pipe->pid[0] = exec_cmd(data->cmds[0], data, 0, 0);
	i = -1;
	while (++i < data->cmd_num)
	{
		printf("the current cmd is: %s\n", data->cmds[i]->cmd_str);
		close_fds(data, i, false);
	}
	close_pipe(data->pipe, 0, true);
	i = -1;
	while (++i < data->cmd_num)
		waitpid(data->pipe->pid[i],  &g_exit_status, 0);
	dup2(STDIN_FILENO, data->origin_fds[0]);
	dup2(STDOUT_FILENO, data->origin_fds[1]);
	return (true);
}









/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:45:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/04 06:36:22 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int    execute_cmd(t_cmd *cmd, t_data *data, int i, int j)
{
    int pid;

    data->origin_fds[0] = dup(STDIN_FILENO);
    data->origin_fds[1] = dup(STDOUT_FILENO);
    pid = fork();
    if (pid == -1)
        return (error_handler(FORK_ER_MSG, FORK_ER, data, false), pid);
    if (pid == 0)
    {
        if (!redirect_fds(data, cmd, i, j))
        {
            close_origin_fds(data);
            exit (1);
        }
        close_origin_fds(data);
//        if (i != 0 )
//            close_pipe(data->pipe, 0, true);
        if (cmd->cmd_str != NULL)
        {
            if ((cmd->cmd_str) && (data->cmd_num > 1))
            {
                if (!close_fds(data, i, true))
                    printf("builtin close failed!\n");
                exec_builtin(cmd, data);
                free_cmd(data);
                set_env_and_path(data, FREE);
                cleanup(data);
                exit(2);
            }
            if (is_env_builtin(cmd->cmd_str))
            {
                if (!close_fds(data, i, true))
                    printf("env builtin close failed!\n");
                free_cmd(data);
                set_env_and_path(data, FREE);
                cleanup(data);
                exit (2);
            }
            else
            {
                if (join_cmd_and_flag(cmd))
                {
                    if (get_path(data, cmd))
                    {
                        close_fds(data, i, true);
                        execve(cmd->cmd_path, cmd->cmd_with_flag, data->env_var);
                    }
                    else
                    {
                        close_fds(data, i, true);
                        error_handler(PATH_ER_MSG, PATH_ER, data, true);
                    }
                }
                else
                {
                    close_fds(data, i, true);
                    error_handler(CMD_ER_MSG, CMD_ER, data, true);
                }
            }
            exit(1);
        }
        close_fds(data, i, false);
        exit(1);
    }
    else
    {
        if ((cmd->cmd_str != NULL) && (cmd->cmd_str) && data->cmd_num == 1)
        {
            pid = getpid();
            if(!redirect_fds(data, cmd, i, j))
                return (pid);
            close_fds(data, i, false);
            exec_builtin(cmd, data);
        }
		if (i > 0)
			close(data->pipe->fd[!j][0]);
		if (i < data->cmd_num - 1)
			close(data->pipe->fd[j][1]);
    }
    return (pid);
}

bool	execution(t_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
/*
	if (data->cmds[0]->cmd_str == NULL)
		{
			if (data->cmds[0]->redirection != NULL)
				close_fds(data, 0, false);
			if (data->cmd_num == 1)
				return (true);
		}
*/    
    alloc_pids(data);
    if (data->cmd_num == 1)
        data->pipe->pid[0] = execute_cmd(data->cmds[0], data, 0, 0);
    else
    {
        if (!make_pipes(data->pipe))
            return (error_handler(PIPE_ER_MSG, PIPE_ER, data, false), false);
        while (data->cmds[i] != NULL)
        {
            data->pipe->pid[i] = execute_cmd(data->cmds[i], data, i, j);
            close_origin_fds(data);
            if (i >= 1 && i < data->cmd_num - 1)
            {
                close_pipe(data->pipe, !j, false);
              	if (pipe(data->pipe->fd[!j]) == -1)
					return (error_handler(PIPE_ER_MSG, PIPE_ER, data, false), false);
            }
            i ++;
            j = !j;
        }
		close_pipe(data->pipe, !j, false);
    }
	i = -1;
    while (++i < data->cmd_num)
    {
        if (i == 0)
            close_fds(data, i, true);
        else
            close_fds(data, i, false);
    }
    i = -1;
	while (++i < data->cmd_num)
		waitpid(data->pipe->pid[i],  &g_exit_status, 0);
    dup2(STDIN_FILENO, data->origin_fds[0]);
	dup2(STDOUT_FILENO, data->origin_fds[1]);
	return (true);
}
