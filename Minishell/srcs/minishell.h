/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:42:44 by schuah            #+#    #+#             */
/*   Updated: 2022/10/07 17:16:56 by schuah           ###   ########.fr       */
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

/* Used to rename builtin functions into function pointers */
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

/* Expander struct */
typedef struct s_expand
{
	char	*output;
	char	*arg;
	int		i;
}	t_expand;

/* Global struct is defined here */
t_global	g_global;

/* CD */
int		cd(t_main *main, char **args);

/* Error */
int		export_unset_error(char *arg, char *type);
void	perror_and_exit(char *errormsg);

/* Signal */
void	sigint_handler(int signo);
void	init_signal(void);

/* Helper */
char	*get_envp_value(char **envp, char *key);
char	**sort_doublearray(char **envp);
void	free_doublearray(char **split);
char	**dup_doublearray(char **src);
void	ft_lstsort(t_list **lst);

/* Parse Input */
char	**parse_input(t_main *main, char *input);

/* Executor */
void	executor(t_main *main, char **command);

/* Expander */
t_list	*connect_cur_with_cur(t_list *current, t_list *files, char *output);
t_list	*check_output_dollar(t_list *current, char *output, int dollar);
void	expander(t_main *main, t_list **args);
char	*append_char(char *input, char c);

/* Expand First */
t_list	*expand_first_phase(t_main *main, t_expand *exp, t_list *current);

/* Expand Second */
t_list	*expand_second_phase(t_expand *exp, t_list *current);

/* Expand Star */
int		check_star(char *arg);
int		is_valid(char *tocheck, char *arg);

/* Expand Files */
DIR		*get_dir(char *path);
t_list	*get_files_from_dir(char *arg);

/* Expand Dollar */
int		expand_dlr(t_list **cur_in, t_expand *exp, char *dollar_expanded);
void	recurs_expand_dollar(t_main *main, t_expand *exp, int depth);
char	*dlr_val(t_main *main, char *arg);

/* Echo */
int		echo(t_main *main, char **args);

/* Pwd */
int		pwd(t_main *main, char **args);

/* Export */
int		export(t_main *main, char **args);

/* Export Helper */
int		check_valid_identifier(char *arg, char *str, char *type);
void	print_envp(char **envp);
char	**envp_split(char *str);

/* Unset */
int		unset(t_main *main, char **args);

/* Env */
int		env(t_main *main, char **args);

/* Exit */
int		ms_exit(t_main *main, char **args);

/* Temp */
void	print_ll(t_list *head);

#endif
