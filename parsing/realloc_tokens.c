

#include "../includes/minishell.h"

void    copy_token_info(t_token *new_entry, t_token *old_entry)
{
    new_entry->token_string = old_entry->token_string;
    new_entry->type = old_entry->type;
    new_entry->expandable = old_entry->expandable;
}

void    set_new_token(t_token *new_entry, char *token_str)
{
    new_entry->token_string = token_str;
    new_entry->type = ID;
    if (token_str[0] == '$')
        new_entry->expandable = true;
    else  
        new_entry->expandable = false;
}


/// @brief reallocates memory for the tokesn, adding whatever was between double quotes
/// @param data 
/// @param insertion_idx 
/// @param num_to_insert 
/// @return the index where the check continues.
int    realloc_tokens(t_data *data, int insertion_idx, int num_to_insert, char **new_strs)
{
    t_token **new_list;
    t_token **old_list;
    int     idx;
    int     i;
    int     j;

    i = 0;
    j = 0;
    old_list = data->tokens;
    new_list = ft_calloc(data->token_ctr + num_to_insert, sizeof(t_token *));
    while (i != insertion_idx)
    {
        copy_token_info(new_list[i], old_list[i]);
        i++;
    }
    while (j < num_to_insert + i)
    {
        set_new_token(new_list[j + i], new_strs[j]);
        j ++;
    }


    return (idx);
}