// TEMPORARY FOR DEBUGGING PURPOSES

#include "minishell.h"

int tabs;

void	print_tabs()
{
	for (int i = 0; i < tabs; i++)
		printf("    ");
}

char	*io_list_get_type(int i)
{
	if (i == 0)
		return ("HEREDOC");
	else if (i == 1)
		return ("APPEND_OUT");
	else if (i == 2)
		return ("INFILE");
	else if (i == 3)
		return ("OUTFILE");
	else
		return ("INVALID");
}

void	print_io_list(t_io_list *io_list)
{
	while (io_list)
	{
		printf("{%s,%d,%s}->",
			io_list_get_type(io_list->e_type),
			ft_lstsize(io_list->value),
			*(char **)io_list->value->content);
		io_list = io_list->next;
	}
}

void	iter_print_char(void *content)
{
	printf("{%s}->", *(char **)content);
}

void	print_pipe_list(t_pipe_list *pipe_list)
{
	while (pipe_list)
	{
		print_tabs();
		printf("pipe:\n");
		print_tabs();
		pipe_list->next ? printf("|   ") : printf("    ");
		printf("argv: ");
		ft_lstiter(pipe_list->argv, &iter_print_char);
		printf("\n");
		print_tabs();
		pipe_list->next ? printf("V   ") : printf("    ");
		printf("io: ");
		print_io_list(pipe_list->io_list);
		printf("\n");
		pipe_list = pipe_list->next;
	}
}

char	*cmd_list_get_operator(int i)
{
	if (i == 0)
		return ("START");
	else if (i == 1)
		return ("AND");
	else if (i == 2)
		return ("OR");
	else
		return ("INVALID");
}

void	print_cmd_list(t_cmd_list *cmd_list)
{
	while (cmd_list)
	{
		print_tabs();
		printf("cmd: (%s)\n", cmd_list_get_operator(cmd_list->e_operator));
		if (cmd_list->e_type == PIPE_LIST)
		{
			tabs++;
			print_pipe_list(cmd_list->ptr);
			tabs--;
		}
		else
		{
			tabs++;
			print_cmd_list(cmd_list->ptr);
			tabs--;
		}
		cmd_list = cmd_list->next;
	}
}

void	iter_print_token(void *content)
{
	t_token	*token = (t_token *)content;
	printf("TOKEN type: %d, value: %s\n", token->e_type, token->value);
}