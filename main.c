/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:53:21 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/10 14:31:22 by jpuerto          ###   ########.fr       */
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
		if (curr->args != NULL)
			printf("  args[0]: %s\n", curr->args[0]);
		j = 1;
		while (curr->args != NULL && curr->args[j])
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
	t_data	data;
	char	*temp;

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
		if (!data.input )
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
		print_tokens(data.tokens);
		data.commands = parser(data.tokens, data);
		temp = get_heredoc_delimiter(data.tokens);
		if (temp)
			data.delim = ft_strdup(temp);
		else
			data.delim = NULL;
		free_lexer(data.tokens);
		print_commands(data.commands);
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
