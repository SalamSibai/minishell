#include "../includes/minishell.h"

char    *get_file_path(const char *file_name)
{
    char *path;
    char *file_path1;
    char *file_path;
    char cwd[PATH_MAX];

    path = getcwd(cwd, PATH_MAX);
    if (!path)
        return (NULL);
    file_path1 = ft_strjoin(path, "/");
    if (!file_path1)
        return (NULL);
    file_path = ft_strjoin(file_path1, file_name);
    ft_free(&file_path1, 'p');
    return (file_path);
}