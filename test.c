#include "./includes/libft/libft.h"

char	*add_qoutes(char *value)
{
	char *env_value;
	char *tmp;
	char *tmp1;
	char *tmp2;
	
	if (ft_strchr(value, '='))
	{
		if (*ft_strchr(value, '=') + 1 == '\"')
			return (value);
		tmp = ft_strndup(value, (ft_strchr(value, '=') + 1 - value));
		tmp1 = ft_strjoin("\"", ft_strchr(value, '=')+ 1);
		tmp2 = ft_strjoin(tmp1, "\"");
		printf("tmp2 = %s\n", tmp2);
		env_value = ft_strjoin(tmp, tmp2);
	}
	free(tmp);
	free(tmp1);
	free(tmp2);
	return (env_value);
}

int main(int ac, char **av)
{
	char *str;
	(void)ac;
	str = add_qoutes(av[1]);
	printf("%s\n", str);
	free (str);
	return 0;
}