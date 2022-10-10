/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:42:44 by schuah            #+#    #+#             */
/*   Updated: 2022/10/10 11:12:14 by maliew           ###   ########.fr       */
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

/* Builtin functions struct */
typedef struct s_main
{
	char	**envp;
	char	**func_name;
	t_func	func[MS_MAX_BIFUNC];
	int		syntax_error;
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
extern t_global	g_global;

typedef struct s_executor
{
	t_list	*heredoc;
	int		**pipe_fd;
	int		pipe_count;
	int		infile;
	int		outfile;
	int		tmpstdin;
	int		tmpstdout;
	int		runtime_error;
}	t_executor;

/**
 * @brief 	Lexer struct.\
 * @brief	input - Input string to lex.\
 * @brief	len - Length of string.\
 * @brief	c - Pointer to current position of input.
 */
typedef struct s_lexer
{
	char	*input;
	int		len;
	char	*c;
}	t_lexer;

/**
 * @brief 	Token struct.\
 * @brief	e_type - Enum of token type.\
 * @brief	value - String value of token.
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
 * @brief 	Parser struct.\
 * @brief	lexer - Lexer struct that the parser is using.\
 * @brief	curr_token - Current token.\
 * @brief	syntax_error - 1 if syntax error is found.
 */
typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*curr_token;
	int		syntax_error;
}	t_parser;

/**
 * @brief 	Io modifier list struct. e.g. ">file <<eof"\
 * @brief	e_type - Type of io modifier. i.e. '<<','>>','<','>'\
 * @brief	value - String value of io modifier. i.e. filename / delimiter\
 * @brief	next - Pointer to next node in list.
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
 * @brief 	Pipe list struct. e.g. "cat <file|grep a|cat -e"\
 * @brief	argv - List of arguments for one pipe. e.g. "cat <file"\
 * @brief	io_list - Io list of pipe. e.g. "<file"\
 * @brief	next - Pointer to next node in list.
 */
typedef struct s_pipe_list
{
	t_list				*argv;
	t_io_list			*io_list;
	struct s_pipe_list	*next;
}	t_pipe_list;

/**
 * @brief 	Cmd list struct. e.g. "pipe_list && (pipe_list || pipe_list)"\
 * @brief	e_operator - Operator of cmd list node. i.e. START / AND / OR\
 * @brief	e_type - Type of struct it is holding. i.e. PIPE_LIST / CMD_LIST\
 * @brief	ptr - Pointer to struct it is holding.
 * @brief	next - Pointer to next node in list.
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

/* Error */
void		perror_and_exit(char *errormsg);
int			export_unset_error(char *arg, char *type);
void		ms_parser_syntax_error(t_parser *p);

/* Signal */
void		sigint_handler(int signo);
void		init_signal(void);

/* Helper */
char		*get_envp_value(char **envp, char *key);
char		**sort_doublearray(char **envp);
void		free_doublearray(char **split);
char		**dup_doublearray(char **src);
void		ft_lstsort(t_list **lst);

/* Parse Input */
char		**parse_input(t_main *main, char *input);

/* Executor */
void		executor(t_main *main, char **command);
void		executor_non_builtin(t_main *main, t_executor *exec, t_pipe_list *p,
				char **argv);

/* Expander */
t_list		*connect_cur_with_cur(t_list *current, t_list *files, char *output);
t_list		*check_output_dollar(t_list *current, char *output, int dollar);
void		expander(t_main *main, t_list **args);
char		*append_char(char *input, char c);

/* Expand First */
t_list		*expand_first_phase(t_main *main, t_expand *exp, t_list *current);

/* Expand Second */
t_list		*expand_second_phase(t_expand *exp, t_list *current);

/* Expand Star */
int			check_star(char *arg);
int			is_valid(char *tocheck, char *arg);

/* Expand Files */
DIR			*get_dir(char *path);
t_list		*get_files_from_dir(char *arg);

/* Expand Dollar */
int			expand_dlr(t_list **cur_in, t_expand *exp, char *dollar_expanded);
void		recurs_expand_dollar(t_main *main, t_expand *exp, int depth);
char		*dlr_val(t_main *main, char *arg);

/* Echo */
int			echo(t_main *main, char **args);

/* CD */
int			cd(t_main *main, char **args);

/* Pwd */
int			pwd(t_main *main, char **args);

/* Export */
int			export(t_main *main, char **args);

/* Export Utils */
int			check_valid_identifier(char *arg, char *str, char *type);
void		print_export(char **envp);
char		**envp_split(char *str);

/* Unset */
int			unset(t_main *main, char **args);

/* Env */
int			env(t_main *main, char **args);

/* Exit */
int			ms_exit(t_main *main, char **args);

/* Lexer */
t_lexer		*ms_lexer_init(char *input);
t_token		*ms_lexer_get_word_token(t_lexer *lexer);
t_token		*ms_lexer_get_spec_token(t_lexer *lexer);
t_token		*ms_lexer_next(t_lexer *lexer);
void		ms_lexer_free(t_lexer **lexer);

/* Lexer Utils */
int			ms_lexer_is_spec(char *s);

/* Token */
t_token		*ms_token_init(int type, char *value);
void		ms_token_free(t_token **token);

/* Parser */
t_parser	*ms_parser_init(t_lexer *lexer);
void		ms_parser_eat(t_parser *parser);
void		ms_parser_free(t_parser **parser);

/* Check dangling */
int			ms_check_dangling(char *str);

/* Cmd list */
t_cmd_list	*ms_cmd_list_init(int operator);
t_cmd_list	*ms_parser_parse_cmd_list(t_parser *p);
void		ms_cmd_list_free(t_cmd_list **cmd_list);

/* Pipe list */
t_pipe_list	*ms_pipe_list_init(void);
t_pipe_list	*ms_parser_parse_pipe_list(t_parser *p);
int			ms_parser_is_pipe_token(t_token *token);
void		ms_pipe_list_free(t_pipe_list **pipe_list);

/* Free args */
void		ms_free_args(void *content);

/* Io list */
t_io_list	*ms_io_list_init(int type);
void		ms_parser_parse_io_list(t_io_list **io_list, t_parser *p);
int			ms_parser_is_io_token(t_token *token);
void		ms_io_list_free(t_io_list **io_list);

/* Expander tree */
void		ms_expander_delete_null(t_list **list);

/* Executor struct */
t_executor	*ms_executor_init(void);
void		ms_executor_init_pipefd(t_executor *exec, t_pipe_list *p);
void		ms_executor_free_pipefd(t_executor *exec);
void		ms_executor_free(t_executor **exec);

/* Executor tree */
void		ms_executor_cmd_list(t_main *main, t_executor *e, t_cmd_list *cmd);

/* Executor io */
void		ms_executor_io_list(t_main *main, t_executor *exec, t_io_list *io);

/* Executor utils */
void		ms_executor(t_main *main, t_executor *exec, t_pipe_list *pipe);

/* Heredoc */
void		ms_heredoc_enqueue(t_list **heredoc, char *delimiter);
int			ms_heredoc_dequeue(t_list **heredoc);

/* Heredoc tree enqueue */
void		ms_heredoc_cmd_list_enqueue(t_executor *exec, t_cmd_list *cmd_list);

/* Heredoc tree dequeue */
void		ms_heredoc_pipe_list_dequeue(t_executor *exec,
				t_pipe_list *pipe_list);
void		ms_heredoc_cmd_list_dequeue(t_executor *exec, t_cmd_list *cmd_list);

/* Env path */
int			ms_get_path_env(char **envp, char **cmd);

#endif
