/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:10:13 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/01 16:10:15 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer *lexer)
{
	while (lexer)
	{
		free(lexer->data);
		lexer = lexer->next;
	}
}

void	free_parser(t_parser *parser)
{
	while (parser)
	{
		free(parser->infile);
		free(parser->outfile);
		ft_free_split(parser->args);
		parser = parser->next;
	}
}
