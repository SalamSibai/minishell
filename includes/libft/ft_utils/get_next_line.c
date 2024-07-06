/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:30:38 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/03 19:09:51 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_save_buffer(int fd, char *buffer_content)
{
	char	*ret;
	char	*buffer;
	int		bytes_read;

	ret = NULL;
	if (buffer_content)
		ret = ft_strjoin_gnl(ret, buffer_content);
	free(buffer_content);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && BUFFER_SIZE > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), NULL);
		buffer[bytes_read] = '\0';
		ret = ft_strjoin_gnl(ret, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (ret);
}

static char	*ft_line(char *buffer)
{
	int		i;
	char	*line;

	if (!*buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
	}
	else
		line[i] = '\0';
	return (line);
}

static char	*ft_update(char *buffer)
{
	int		i;
	int		length;
	char	*updated_str;

	i = 0;
	length = 0;
	updated_str = NULL;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i])
		i += 1;
	length = ft_strlen(buffer + i);
	updated_str = ft_strjoin_gnl(updated_str, buffer + (i));
	free(buffer);
	updated_str[length] = '\0';
	if (updated_str[0] == '\0')
		return (free(updated_str), NULL);
	return (updated_str);
}

char	*get_next_line(int fd)
{
	static char	*buffer_content;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buffer_content = ft_save_buffer(fd, buffer_content);
	if (!buffer_content)
		return (NULL);
	line = ft_line(buffer_content);
	buffer_content = ft_update(buffer_content);
	return (line);
}
