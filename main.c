/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- & loruzqui < >                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:53:21 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/07 17:28:23 by jpuerto- &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_commands(t_parser *head)
{
	int			i;
	int			j;
	t_parser	*curr;

	i = 0;
	curr = head;
	while (curr)
	{
		printf("Command %d:\n", i);
		printf("  args[0]: %s\n", curr->args[0]);
		j = 1;
		while (curr->args[j])
		{
			printf("  args[%d]: %s\n", j, curr->args[j]);
			j++;
		}
		printf("  infile: %s\n", curr->infile ? curr->infile : "NULL");
		printf("  outfile: %s\n", curr->outfile ? curr->outfile : "NULL");
		printf("  append: %d\n", curr->append);
		curr = curr->next;
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;

	(void)argc;
	(void)argv;
	data.env = ft_strdup_matrix(envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	data.num_commands = 0;
	while (1)
	{
		data.input = readline(COLOR_BANNER "bash> " COLOR_RESET);
		data.error = false;
		if (!data.input)
		{
			printf(COLOR_USERS "\nSaliendo de la shell...\n" COLOR_RESET);
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
		print_tokens(data.tokens);
		data.commands = parser(data.tokens);
		free_lexer(data.tokens);
		print_commands(data.commands);
		data.num_commands = ft_parserlen(data.commands);
		if (data.num_commands == 1 && !is_built_in(data.commands, &data.env))
			exec_one_command(data.commands, data.env);
		else if (data.num_commands > 1)
			exec_pipes(data.commands, data.env, data.num_commands);
		free(data.input);
		free_parser(data.commands);
	}
	if (data.env && data.env[0])
		ft_free_split(data.env);
	return (0);
}
