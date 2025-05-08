/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:04:08 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/08 13:53:00 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_com(int i, t_parser *curr)
{
	int	j;

	printf("Command %d:\n", i);
	if (curr->args != NULL)
		printf("  args[0]: %s\n", curr->args[0]);
	j = 1;
	while (curr->args != NULL && curr->args[j])
	{
		printf("  args[%d]: %s\n", j, curr->args[j]);
		j++;
	}
}

void	ft_print_outfiles(t_parser *curr)
{
	t_outfile	*file;

	printf("  outfiles:\n");
	file = curr->outfiles;
	while (file)
	{
		printf("    - %s (append: %d)\n", file->data, file->append);
		file = file->next;
	}
}

void	ft_print_commands(t_parser *head)
{
	int			i;
	t_parser	*curr;

	i = 0;
	curr = head;
	while (curr)
	{
		ft_print_com(i, curr);
		if (curr->infile)
			printf("  infile: %s\n", curr->infile);
		else
			printf("  infile: %s\n", "NULL");
		ft_print_outfiles(curr);
		if (curr->delim)
			printf("  heredoc: %s\n", curr->delim);
		else
			printf("  heredoc: NULL\n");
		curr = curr->next;
		i++;
	}
}

void	ft_print_tokens(t_lexer *lexer)
{
	while (lexer)
	{
		printf("Token %d: [%s] -> Tipo %d\n", lexer->index,
			lexer->data, lexer->type_token);
		lexer = lexer->next;
	}
}
