/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- & loruzqui < >                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:53:21 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/12 13:16:48 by jpuerto- &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_commands(t_parser *head)
{
	int			i;
	int			j;
	t_parser	*curr;
	t_outfile	*file;

	i = 0;
	curr = head;
	while (curr)
	{
		printf("Command %d:\n", i);
		if (curr->args != NULL)
			printf("  args[0]: %s\n", curr->args[0]);
		j = 1;
		while (curr->args != NULL && curr->args[j])
		{
			printf("  args[%d]: %s\n", j, curr->args[j]);
			j++;
		}
		printf("  infile: %s\n", curr->infile ? curr->infile : "NULL");
		printf("  outfiles:\n");
		file = curr->outfiles;
		while (file)
		{
			printf("    - %s (append: %d)\n", file->data, file->append);
			file = file->next;
		}
		if (curr->delim)
			printf("  heredoc: %s\n", curr->delim);
		else
			printf("  heredoc: NULL\n");
		curr = curr->next;
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.env = ft_dup_env(envp);
	data.env_arr = ft_strdup_matrix(envp);
	data.last_exit_code = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	data.num_commands = 0;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			data.input = readline(COLOR_BANNER "bash> " COLOR_RESET);
		else
			data.input = get_next_line(STDIN_FILENO);
		data.error = false;
		if (!data.input)
		{
			// printf(COLOR_USERS "\nSaliendo de la shell...\n" COLOR_RESET);
			free(data.input);
			break ;
		}
		if (*data.input)
			add_history(data.input);
		data.tokens = lexer(&data);
		if (data.error)
		{
			free(data.input);
			continue ;
		}
		data.commands = parser(data.tokens, data);
		print_tokens(data.tokens);
		print_commands(data.commands);
		free_lexer(data.tokens);
		data.num_commands = ft_parserlen(data.commands);
		if (data.num_commands == 1 && !is_built_in(data.commands, &data))
			exec_one_command(&data);
		else if (data.num_commands > 1)
			exec_pipes(&data);
		free(data.input);
		free_parser(data.commands);
	}
	free_env(&data);
	return (0);
}
