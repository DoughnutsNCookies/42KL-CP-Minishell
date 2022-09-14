/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:42:44 by schuah            #+#    #+#             */
/*   Updated: 2022/09/14 14:27:55 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/srcs/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termios.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <term.h>

# define MAX_BIFUNC 7

struct		s_main;
typedef int	(*t_func)(char **args, struct s_main *data);

/* Builtin functions struct */
typedef struct s_main
{
	char	**envp;
	char	**func_name;
	t_func	func[MAX_BIFUNC];
}	t_main;

/* CD */
int		check_cd_command(int count, char **command);
int		cd(char **args, t_main *main);

/* Error */
void	perror_and_exit(char *errormsg);

/* Signal */
void	sigint_handler(int signo);
void	init_signal(void);

/* Helper */
void	free_ftsplit(char **split);

/* Parse Input */
char	**parse_input(char *input);

/* Bifunc */
void	init_main(t_main *main, char **envp);

/* Echo */
int		echo(char **args, t_main *main);

/* Pwd */
int		pwd(char **args, t_main *main);

/* Export */
int		export(char **args, t_main *main);

/* Unset */
int		unset(char **args, t_main *main);

/* Env */
int		env(char **args, t_main *main);

/* Exit */
int		ms_exit(char **args, t_main *main);

#endif
