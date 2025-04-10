/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:10:13 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/11 10:15:28 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer)
	{
		tmp = lexer->next;
		free(lexer->data);
		free(lexer);
		lexer = tmp;
	}
}

void	free_env(t_data *data)
{
	t_env	*tmp;

	if (!data->env)
		return ;
	while (data->env)
	{
		tmp = data->env->next;
		free(data->env->content);
		free(data->env);
		data->env = tmp;
	}
	ft_free_split(data->env_arr);
}

void	free_parser(t_parser *parser)
{
	t_parser *tmp;

	while (parser)
	{
		tmp = parser->next;
		if (parser->args)
			ft_free_split(parser->args);
		free(parser->infile);
		free(parser->outfile);
		free(parser);
		parser = tmp;
	}
}

// void	free_data(t_data data)
// {
// 	free_lexer(data.tokens);
// 	free(data.tokens);
// 	free_parser(data.commands);
// 	free(data.commands);
// 	free(data.input);
// 	if (data.env && data.env[0])
// 		ft_free_split(data.env);
// }
