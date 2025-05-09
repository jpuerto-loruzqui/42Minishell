/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:53:21 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/09 13:08:43 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_env(char ***env, char *var, char *new_entry)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, 6) == 0)
		{
			(*env)[i] = new_entry;
			return ;
		}
		i++;
	}
	i = 0;
	while ((*env)[i])
		i++;
	(*env)[i] = new_entry;
	(*env)[i + 1] = NULL;
}

static void	ft_init_minishell(int argc, char **envp, t_data *data, char **argv)
{
	char	*newpwd;
	char	*export_str;

	if (argc != 1)
		exit(EXIT_FAILURE);
	if (!ft_getenv("PWD", envp))
	{
		newpwd = getcwd(NULL, 0);
		export_str = ft_strjoin("PWD=", newpwd);
		ft_export_env(&envp, "PWD=", export_str);
		free(newpwd);
	}
	ft_update_shlvl(&envp);
	data->program = argv[0];
	data->env = ft_dup_env(envp);
	data->env_arr = ft_strdup_matrix(envp);
	data->last_exit_code = 0;
	data->last_token_type = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sigint_handler);
	data->num_commands = 0;
}

void	ft_parse_syntax(t_data *data)
{
	t_parser	*tmp;

	tmp = data->commands;
	while (tmp)
	{
		if (ft_error_tokens(data))
		{
			ft_exit_error("Syntax error", data, 2);
			break ;
		}
		tmp = tmp->next;
	}
}

static int	ft_lexer_parser_and_exec(t_data *data)
{
	char	*aux;

	aux = data->input;
	data->input = ft_strtrim(data->input, " ");
	free(aux);
	data->tokens = ft_lexer(data);
	data->commands = ft_parser(data->tokens, *data);
	ft_parse_syntax(data);
	if (data->error)
	{
		ft_free_lexer(data->tokens);
		ft_free_parser(data->commands);
		free(data->input);
		return (1);
	}
	ft_free_lexer(data->tokens);
	data->num_commands = ft_parserlen(data->commands);
	if (data->error == false && data->num_commands == 1
		&& !ft_is_built_in(data->commands, data))
		ft_exec_one_command(data);
	else if (data->error == false && data->num_commands > 1)
		ft_exec_pipes(data);
	free(data->input);
	ft_free_parser(data->commands);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_init_minishell(argc, envp, &data, argv);
	while (1)
	{
		data.last_token_type = 0;
		if (isatty(STDIN_FILENO))
			data.input = readline(ft_get_prompt(&data));
		else
			data.input = get_next_line(STDIN_FILENO);
		free(data.prompt);
		data.error = false;
		if (!data.input)
		{
			free(data.input);
			printf("exit\n");
			break ;
		}
		if (*data.input)
			add_history(data.input);
		if (ft_lexer_parser_and_exec(&data) == 1)
			continue ;
	}
	ft_free_env(&data);
	return (0);
}
