/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:53:21 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/16 18:10:15 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	control_args(int argc)
{
	if (argc != 1)
		exit(EXIT_FAILURE);
}

char *get_prompt(t_data *data)
{
	char	*env_prompt[3];
	char	*cwd;
	char	*colored;
	char	*final;

	cwd = getcwd(NULL, 0);
	colored = ft_strjoin("\001\033[0;32m\002", cwd);
	final = ft_strjoin(colored, COLOR_USERS " minishell> \001\033[0m\002");
	free(colored);
	data->prompt = final;
	env_prompt[0] = "export";
	env_prompt[1] = ft_strjoin("PROMPT=", final);
	env_prompt[2] = NULL;
	ft_export(env_prompt, data);
	free(env_prompt[1]);
	free(cwd);
	return (data->prompt);
}

static void	init_minishell(int argc, char **envp, t_data *data)
{
	control_args(argc);
	data->env = ft_dup_env(envp);
	data->env_arr = ft_strdup_matrix(envp);
	data->last_exit_code = 0;
	data->last_token_type = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	data->num_commands = 0;
}

void parse_syntax(t_data *data)
{
	t_parser  *tmp;

	tmp = data->commands;
	while (tmp)
	{
		if (!tmp->args && !tmp->delim && !tmp->infile && !tmp->last_outfile && !tmp->outfiles)
		{
			exit_error("Syntax error");
			data->error = true;
		}
		tmp = tmp->next;
	}
}

static int	lexer_parser_and_exec(t_data *data)
{
	char *aux;

	aux = data->input;
	data->input = ft_strtrim(data->input, " ");
	free(aux);
	data->tokens = lexer(data);
	data->commands = parser(data->tokens, *data);
	parse_syntax(data);
	if (data->error)
	{
		free_lexer(data->tokens);
		free_parser(data->commands);
		free(data->input);
		return (1);
	}
	free_lexer(data->tokens);
	data->num_commands = ft_parserlen(data->commands);
	if (data->error == false && data->num_commands == 1 && !is_built_in(data->commands, data))
		exec_one_command(data);
	else if (data->error == false && data->num_commands > 1)
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
			data.input = readline(get_prompt(&data));
		else
			data.input = get_next_line(STDIN_FILENO);
		free(data.prompt);
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
