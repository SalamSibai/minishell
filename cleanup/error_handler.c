
#include "../includes/minishell.h"

/**
 * @brief where error msgs are printed, and data is redirected to the necessary
 *        functions depending on what is needed to be freed.. etc
 * @param err_str the error msg (that have been defined in the header)
 * @param err_type the type of the error (to check what should be freed, also defined in the header)
 * @param data reference to data
 * @param done whether minishell program should be terminated or not
 */
void    error_handler(char *err_str, int err_type, t_data *data, bool done)
{
    perror(err_str);
    /*
        if the error is within input or output:
            MAKE SURE: frees everything
    */
    
    
}