/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:42:44 by schuah            #+#    #+#             */
/*   Updated: 2022/10/12 11:33:51 by schuah           ###   ########.fr       */
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

/* Used to rename builtin functions into function pointers */
struct		s_main;
typedef int	(*t_func)(struct s_main *main, char **args);

/* Global errno is defined here */
int			g_errno;

/* Builtin function name in enums */
typedef enum bifname
{
	MS_ECHO = 0,
	MS_CD = 1,
	MS_PWD = 2,
	MS_EXPORT = 3,
	MS_UNSET = 4,
	MS_ENV = 5,
	MS_EXIT = 6,
	MS_MAX_BIFUNC = 7,
}	t_bifname;

/**
 * @brief Builtin functions struct
 * 
 * @param envp - Environment variable list
 * @param func_name - List of builtin-function names
 * @param syntax_error - Boolean variable for syntax error
 * @param func[] - List of builtin-function pointers
 */
typedef struct s_main
{
	char	**envp;
	char	**func_name;
	int		syntax_error;
	t_func	func[MS_MAX_BIFUNC];
}	t_main;

/**
 * @brief Expander struct
 * 
 * @param output - Current output for the current argument
 * @param arg - Current argument string in the current node of the argument
 * linked-list
 * @param i - Current i position of the argument string
 */
typedef struct s_expand
{
	char	*output;
	char	*arg;
	int		i;
}	t_expand;

/**
 * @brief Executor struct
 * 
 * @param heredoc List of heredocs
 * @param pipe_hd Pipes to filde descriptors
 * @param pipe_count Number of pipes
 * @param infile Fd to infile
 * @param outfile Fd to outfile
 * @param tmpstdin Temporary Fd to stdin
 * @param tempstdout Temporary Fd to stdout
 * @param runtime_error Boolean variable for when there is a runtime error
 */
typedef struct s_exe
{
	t_list	*heredoc;
	int		**pipe_fd;
	int		pipe_count;
	int		infile;
	int		outfile;
	int		tmpstdin;
	int		tmpstdout;
	int		runtime_error;
}	t_exe;

/**
 * @brief 	Lexer struct
 * 
 * @param	input Input string to lex
 * @param	len Length of string
 * @param	c Pointer to current position of input
 */
typedef struct s_lexer
{
	char	*input;
	int		len;
	char	*c;
}	t_lexer;

/**
 * @brief 	Token struct
 * 
 * @param	e_type Enum of token type
 * @param	value String value of token
 */
typedef struct s_token
{
	enum
	{
		TOKEN_WORD,
		TOKEN_AND,
		TOKEN_OR,
		TOKEN_AIN,
		TOKEN_AOUT,
		TOKEN_IN,
		TOKEN_OUT,
		TOKEN_PIPE,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_NL
	}	e_type;
	char	*value;
}	t_token;

/**
 * @brief 	Parser struct
 * 
 * @param	lexer Lexer struct that the parser is using
 * @param	curr_token Current token
 * @param	syntax_error - Boolean variable for syntax error
 */
typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*curr_token;
	int		syntax_error;
}	t_parser;

/**
 * @brief 	Io modifier list struct (e.g. ">file <<eof")
 * 
 * @param	e_type Type of io modifier (i.e. '<<','>>','<','>')
 * @param	value String value of io modifier (i.e. filename / delimiter)
 * @param	next Pointer to next node in list
 */
typedef struct s_io_list
{
	enum
	{
		IO_AIN,
		IO_AOUT,
		IO_IN,
		IO_OUT
	}	e_type;
	t_list				*value;
	struct s_io_list	*next;
}	t_io_list;

/**
 * @brief 	Pipe list struct (e.g. "cat <file | grep a | cat -e")
 * 
 * @param	argv List of arguments for one pipe (e.g. "cat <file")
 * @param	io_list Io list of pipe (e.g. "<file")
 * @param	next Pointer to next node in list
 */
typedef struct s_pipe_list
{
	t_list				*argv;
	t_io_list			*io_list;
	struct s_pipe_list	*next;
}	t_pipe_list;

/**
 * @brief 	Cmd list struct (e.g. "pipe_list && (pipe_list || pipe_list)")
 * 
 * @param	e_operator Operator of cmd list node (i.e. START / AND / OR)
 * @param	e_type Type of struct it is holding (i.e. PIPE_LIST / CMD_LIST)
 * @param	ptr Pointer to struct it is holding
 * @param	next Pointer to next node in list
 */
typedef struct s_cmd_list
{
	enum
	{
		OP_START,
		OP_AND,
		OP_OR
	}	e_operator;
	enum
	{
		PIPE_LIST,
		CMD_LIST
	}	e_type;
	void				*ptr;
	struct s_cmd_list	*next;
}	t_cmd_list;

int			export_unset_error(char *arg, char *type);
void		ms_parser_syntax_error(t_parser *p);
void		perror_and_exit(char *errormsg);

void		sigint_handler(int signo);
void		init_signal(void);

char		*get_envp_value(char **envp, char *key);
char		**sort_doublearray(char **envp);
char		**dup_doublearray(char **src);
void		free_doublearray(char **split);

char		**parse_input(t_main *main, char *input);

void		exe_non_bi(t_main *main, t_exe *exec, t_pipe_list *p, char **argv);
void		executor(t_main *main, char **command);

t_list		*connect_cur_with_cur(t_list *current, t_list *files, char *output);
t_list		*expand_first_phase(t_main *main, t_expand *exp, t_list *current);
t_list		*check_output_dollar(t_list *current, char *output, int dollar);
t_list		*expand_second_phase(t_expand *exp, t_list *current);
t_list		*get_files_from_dir(char *arg);
DIR			*get_dir(char *path);
int			expand_dlr(t_list **cur_in, t_expand *exp, char *dollar_expanded);
int			is_valid(char *tocheck, char *arg);
int			val_in_quote(t_expand *exp);
int			check_star(char *arg);
char		*dlr_val(t_main *main, char *arg);
char		*append_char(char *input, char c);
void		recurs_expand_dollar(t_main *main, t_expand *exp, int depth);
void		ms_expander_delete_null(t_list **list);
void		expander(t_main *main, t_list **args);

int			echo(t_main *main, char **args);

int			cd(t_main *main, char **args);

int			pwd(t_main *main, char **args);

int			check_valid_identifier(char *arg, char *str, char *type);
int			export(t_main *main, char **args);
char		**envp_split(char *str);
void		print_export(char **envp);

int			unset(t_main *main, char **args);

int			env(t_main *main, char **args);

int			ms_exit(t_main *main, char **args);

t_token		*ms_lexer_get_word_token(t_lexer *lexer);
t_token		*ms_lexer_get_spec_token(t_lexer *lexer);
t_token		*ms_lexer_next(t_lexer *lexer);
t_lexer		*ms_lexer_init(char *input);
int			ms_lexer_is_spec(char *s);
void		ms_lexer_free(t_lexer **lexer);

t_token		*ms_token_init(int type, char *value);
void		ms_token_free(t_token **token);

t_parser	*ms_parser_init(t_lexer *lexer);
void		ms_parser_free(t_parser **parser);
void		ms_parser_eat(t_parser *parser);

int			ms_check_dangling(char *str);

t_cmd_list	*ms_parser_parse_cmd_list(t_parser *p);
t_cmd_list	*ms_cmd_list_init(int operator);
void		ms_cmd_list_free(t_cmd_list **cmd_list);

t_pipe_list	*ms_parser_parse_pipe_list(t_parser *p);
t_pipe_list	*ms_pipe_list_init(void);
int			ms_parser_is_pipe_token(t_token *token);
void		ms_pipe_list_free(t_pipe_list **pipe_list);

void		ms_free_args(void *content);
void		ft_lstsort(t_list **lst);
int			ms_cmd_list_parse_pipe_list(t_cmd_list *buffer, t_parser *p);

t_io_list	*ms_io_list_init(int type);
void		ms_parser_parse_io_list(t_io_list **io_list, t_parser *p);
void		ms_io_list_free(t_io_list **io_list);
int			ms_parser_is_io_token(t_token *token);

t_exe		*ms_executor_init(void);
void		ms_executor_cmd_list(t_main *main, t_exe *e, t_cmd_list *cmd);
void		ms_executor_io_list(t_main *main, t_exe *exec, t_io_list *io);
void		ms_executor(t_main *main, t_exe *exec, t_pipe_list *pipe);
void		ms_executor_init_pipefd(t_exe *exec, t_pipe_list *p);
void		ms_executor_free_pipefd(t_exe *exec);
void		ms_executor_free(t_exe **exec);
int			ms_get_abspath(char **envp, char **cmd);

void		ms_hd_pipe_list_dequeue(t_exe *exec, t_pipe_list *pipe_list);
void		ms_hd_cmd_list_dequeue(t_exe *exec, t_cmd_list *cmd_list);
void		ms_hd_cmd_list_enqueue(t_exe *exec, t_cmd_list *cmd_list);
void		ms_heredoc_enqueue(t_list **heredoc, char *delimiter);
int			ms_heredoc_dequeue(t_list **heredoc);

#endif
