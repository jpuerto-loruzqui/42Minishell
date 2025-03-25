/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:59:20 by loruzqui          #+#    #+#             */
/*   Updated: 2025/03/09 18:59:22 by loruzqui         ###   ########.fr       */
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

int	main(void)
{
	char		*input;
	t_lexer		*tokens;
	t_parser	*commands;

	while (1)
	{
		input = readline(COLOR_BANNER "bash> " COLOR_RESET);
		if (!input)
		{
			printf("\nSaliendo de la shell...\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = lexer(input);
		print_tokens(tokens);
		commands = parser(tokens);
		print_commands(commands);
		if (ft_strncmp(commands->args[0], "exit", 4) == 0)
			ft_exit();
		free(input);
		//free_lexer();
		//free_parser();
	}
	return (0);
}
