/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:42:44 by schuah            #+#    #+#             */
/*   Updated: 2022/09/30 11:24:29 by schuah           ###   ########.fr       */
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

# define MS_ECHO 0
# define MS_CD 1
# define MS_PWD 2
# define MS_EXPORT 3
# define MS_UNSET 4
# define MS_ENV 5
# define MS_EXIT 6
# define MS_MAX_BIFUNC 7

struct		s_main;
typedef int	(*t_func)(struct s_main *main, char **args);

/* Builtin functions struct */
typedef struct s_main
{
	char	**envp;
	char	**func_name;
	t_func	func[MS_MAX_BIFUNC];
}	t_main;

/* Global struct */
typedef struct s_global
{
	int	error_no;
}	t_global;

t_global	g_global;

/* CD */
int		cd(t_main *main, char **args);

/* Error */
void	perror_and_exit(char *errormsg);
int		export_unset_error(char *arg, char *type);

/* Signal */
void	sigint_handler(int signo);
void	init_signal(void);

/* Helper */
void	free_doublearray(char **split);
char	**dup_doublearray(char **src);
char	*get_envp_value(char **envp, char *key);

/* Parse Input */
char	**parse_input(t_main *main, char *input);

/* Executor */
void	executor(t_main *main, char **command);

/* Expander */
void	expander(t_main *main, t_list **args);

/* Expander Helper */
char	*append_char(char *input, char c);
void	print_ll(t_list *head);
char	**ft_list_to_charss(t_list *lst);

/* Expand Star */
void	star_wildcard(char *arg, t_list *current);

/* Echo */
int		echo(t_main *main, char **args);

/* Pwd */
int		pwd(t_main *main, char **args);

/* Export */
int		export(t_main *main, char **args);

/* Export Helper */
int		check_valid_identifier(char *arg, char *str, char *type);
void	print_envp(char **envp);
char	**sort_envp(char **envp);
char	**envp_split(char *str);

/* Unset */
int		unset(t_main *main, char **args);

/* Env */
int		env(t_main *main, char **args);

/* Exit */
int		ms_exit(t_main *main, char **args);

#endif
