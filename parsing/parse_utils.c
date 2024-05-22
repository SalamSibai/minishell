
#include "../includes/minishell.h" 

int			ft_panic(char *message, int ret)
{
    //add a function call to cleanup and exit program (if needed)
	return (ft_putendl_fd(message, 2), free(message), ret);
}

void	*ft_safe_malloc(size_t size, char *msg)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (ft_panic(ft_strjoin("ERROR: MALLOC FAILED IN ", msg), 0), NULL);
 	return (ptr);
}
