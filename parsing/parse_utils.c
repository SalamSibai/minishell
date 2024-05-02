
#include "../includes/minishell.h" 

int			ft_panic(char *message, int ret)
{
    //add a function call to cleanup and exit program (if needed)
	return (ft_putstr_fd(message, 2),  ret);
}

void	*ft_safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (ft_panic("ERROR: MALLOC FAILED IN\n", 0), NULL);
	return (ptr);
}