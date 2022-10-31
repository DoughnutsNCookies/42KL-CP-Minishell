/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:47:30 by schuah            #+#    #+#             */
/*   Updated: 2022/10/31 15:57:11 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints out a new line and clears readline buffer
 * 
 * @param signo The signal (Should be SIGINT)
 */
void	ms_sigint_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_errno = 1;
}

/**
 * @brief Initializes the signals: CTRL-C and CTRL-\. Termios is get and set to
 * not print ^C or ^D. This is done by turning the ECHO flag off. When CTRL-\
 * (SIGQUIT) signal is received, it is ignored
 */
void	ms_init_signal(void)
{
	struct termios	termios_current;

	if (tcgetattr(STDIN_FILENO, &termios_current) == -1)
	{
		perror("Tcgetattr failed\n");
		exit(errno);
	}
	termios_current.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_current) == -1)
	{
		perror("Tcsetattr failed\n");
		exit(errno);
	}
	signal(SIGINT, ms_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
