/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:53:21 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/06 10:13:55 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_prompt(t_data *data)
{
	char	*cwd;
	char	*colored;
	char	*final;

	cwd = ft_control_getcwd(data);
	colored = ft_strjoin("\001\033[0;32m\002", cwd);
	final = ft_strjoin(colored, COLOR_USERS " minishell> \001\033[0m\002");
	free(colored);
	data->prompt = final;
	free(cwd);
	return (data->prompt);
}

void ft_export_env(char ***env, char *var, char *new_entry)
{
	int i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, 6) == 0)
		{
			(*env)[i] = new_entry;
			return;
		}
		i++;
	}
	i = 0;
	while ((*env)[i])
		i++;
	(*env)[i] = new_entry;
	(*env)[i + 1] = NULL;
}

void update_shlvl(char ***env)
{
	char	*lvl_str;
	int		lvl;
	char	*new_lvl;
	char	*new_entry;
	
	lvl_str = ft_getenv("SHLVL", *env);
	if (lvl_str)
		lvl = ft_atoi(lvl_str);
	else
		lvl = 0;
	lvl++;
	new_lvl = ft_itoa(lvl);
	new_entry = ft_strjoin("SHLVL=", new_lvl);
	free(new_lvl);
	ft_export_env(env, "SHLVL=", new_entry);
}

static void	ft_init_minishell(int argc, char **envp, t_data *data, char **argv)
{
	if (argc != 1)
		exit(EXIT_FAILURE);
	update_shlvl(&envp);
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
			ft_exit_error("Syntax error");
			data->error = true;
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
