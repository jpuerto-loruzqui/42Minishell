/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- & loruzqui < >                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:10:13 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/07 17:31:49 by jpuerto- &       ###   ########.fr       */
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

void	free_parser(t_parser *parser)
{
	t_parser	*tmp;

	while (parser)
	{
		tmp = parser->next;
		free(parser->infile);
		free(parser->outfile);
		ft_free_split(parser->args);
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
