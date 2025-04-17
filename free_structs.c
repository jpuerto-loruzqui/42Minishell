/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:10:13 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/17 10:28:19 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer)
	{
		tmp = lexer->next;
		if (lexer->data)
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

void	free_outfiles(t_outfile *outfiles)
{
	t_outfile	*tmp;

	while (outfiles)
	{
		tmp = outfiles->next;
		if (outfiles->data)
			free(outfiles->data);
		free(outfiles);
		outfiles = tmp;
	}
}

void	free_parser(t_parser *parser)
{
	t_parser	*tmp;

	while (parser)
	{
		tmp = parser->next;
		if (parser->args)
			ft_free_split(parser->args);
		if (parser->delim)
			free(parser->delim);
		free(parser->infile);
		free_outfiles(parser->outfiles);
		free(parser);
		parser = tmp;
	}
}
