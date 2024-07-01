

#include "../includes/minishell.h"

void    ft_exit(t_data *data)
{
    error_handler(NULL, -1, data, true);
}
