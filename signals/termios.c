/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:38:15 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/03 15:06:23 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief this function disables the ctrl+c echo
 *  bisaclly it sets old terminal settings to a new terminal settings
 * tcgetattr() get the atteributes of the terminal and then disable
 * the ECHOCTL flag then set the new terminal settings with tcsetattr()
 * TCSANOW is a flag that tells the function to apply the changes immediately
 * @param  
 */
void	disable_ctrl_c_echo(void)
{
	struct termios	term;

	term = (struct termios){0};
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
/**
 * @brief this function listens to the signals
 * SIGINT and SIGQUIT
 * SIGINT is the signal that is sent when the user presses ctrl+c
 * SIGQUIT is the signal that is sent when the user presses ctrl+\
 * @param sa 
 */
void	catch_sig(t_sigaction *sa)
{
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
}

/**
 * @brief this function handles the signals 
 * @param sig signal number
 * @param siginfo contains the signal information
 * @param ptr 
 */
void	signals_handler(int sig, siginfo_t *siginfo, void *ptr)
{
	(void) ptr;
	(void) siginfo;
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_catch_signals = 0; 
		rl_redisplay();
		g_exit_status = 1;
	}
}
/**
 * @brief this function masks the signals and by mask we mean 
 * that the signals is blocked temporarily and will be 
 * unblocked when the signal handler is done
 * @param sa 
 */
void	mask_sig(t_sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGINT);
	sigaddset(&sa->sa_mask, SIGQUIT);
}

/**
 * @brief this function will initialize the signals
 * and set the signal handler to the signals_handler function
 * and then mask the signals
 * and then catch the signals
 * (rl_catch_signals = 0) this is a readline function 
 * is used to disable the ctrl c signals unfortuantly 
 * its not allowed in the project
 * so we will use the term struct to disable the ctrl+c echo
 * @param data 
 */
void	init_sigaction(void)
{
	t_sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = &signals_handler;
	sa.sa_flags = 0;
	sa.sa_flags = SA_SIGINFO;
	g_exit_status = 0;
	mask_sig(&sa);
	catch_sig(&sa);
}
