/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:07:38 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/13 16:06:54 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static void	control_args(int argc)
{
	if (argc != 1)
		exit(EXIT_FAILURE);
}

static void	init_minishell(int argc, char **envp, t_data *data)
{
	control_args(argc);
	data->env = ft_dup_env(envp);
	data->env_arr = ft_strdup_matrix(envp);
	data->last_exit_code = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	data->num_commands = 0;
}

static int	lexer_parser_and_exec(t_data *data)
{
	data->tokens = lexer(data);
	if (data->error)
	{
		free(data->input);
		return (1);
	}
	data->commands = parser(data->tokens, *data);
	print_tokens(data->tokens);
	print_commands(data->commands);
	free_lexer(data->tokens);
	data->num_commands = ft_parserlen(data->commands);
	if (data->num_commands == 1 && !is_built_in(data->commands, data))
		exec_one_command(data);
	else if (data->num_commands > 1)
		exec_pipes(data);
	free(data->input);
	free_parser(data->commands);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	init_minishell(argc, envp, &data);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			data.input = readline(COLOR_BANNER "bash> " COLOR_RESET);
		else
			data.input = get_next_line(STDIN_FILENO);
		data.error = false;
		if (!data.input)
		{
			free(data.input);
			break ;
		}
		if (*data.input)
			add_history(data.input);
		if (lexer_parser_and_exec(&data) == 1)
			continue ;
	}
	free_env(&data);
	return (0);
}
