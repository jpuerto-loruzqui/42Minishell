/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:59:20 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/05 13:08:08 by jpuerto          ###   ########.fr       */
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
	char		*input;
	t_lexer		*tokens;
	t_parser	*commands;
	int			num_commands;
	char		**env;

	(void)argc;
	(void)argv;
	env = ft_strdup_matrix(envp);
	signal(SIGQUIT, SIG_IGN); //SIGQUIT es el Ctrl '\' y SIG_IGN es para ignorar esa señal
	signal(SIGINT, sigint_handler); //SIGINT es el Ctrl C
	num_commands = 0;
	while (1)
	{
		input = readline(COLOR_BANNER "bash> " COLOR_RESET);
		if (!input) //para el Ctrl D
		{
			printf(COLOR_USERS "\nSaliendo de la shell...\n" COLOR_RESET);
			break ;
		}
		if (*input)
			add_history(input);
		tokens = lexer(input);
		print_tokens(tokens);
		commands = parser(tokens);
		free_lexer(tokens);
		print_commands(commands);
		num_commands = ft_parserlen(commands);
		if (num_commands == 1 && !is_built_in(commands, &env))
			exec_one_command(commands, env);
		else if (num_commands > 1)
		exec_pipes(commands, env, num_commands);
		free(input);
		free_parser(commands);
	}
	if (env && env[0])
		ft_free_split(env);
	return (0);
}
