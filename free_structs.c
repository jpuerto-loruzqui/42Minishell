/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:10:13 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/10 15:56:16 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_lexer(t_lexer *lexer)
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

void	ft_free_env(t_data *data)
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

void	ft_free_outfiles(t_outfile *outfiles)
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

void	ft_free_parser(t_parser *parser)
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
		ft_free_outfiles(parser->outfiles);
		free(parser);
		parser = tmp;
	}
}
