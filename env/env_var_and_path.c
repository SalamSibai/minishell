/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_and_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:48:27 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/03 17:04:10 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	set_env_and_path(t_data *data, t_cmd_type type)
{
	if (type == SET)
	{
		data->env_var = env_to_str(data->env);
		data->path = set_path(data->env_var, data);
	}
	if (type == FREE)
	{
		ft_free(&data->path, 'a');
		ft_free(&data->env_var, 'a');
	}
	return (true);
}