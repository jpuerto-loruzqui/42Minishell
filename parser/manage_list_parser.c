/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:31:08 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/16 09:49:59 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*ft_new_node(void)
{
	t_parser	*node;

	node = malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->infile = NULL;
	node->outfiles = NULL;
	node->next = NULL;
	node->last_outfile = NULL;
	node->delim = NULL;
	node->here_fd = 0;
	return (node);
}

void	ft_add_node(t_parser **head, t_parser *node)
{
	t_parser	*tmp;

	if (!*head)
		*head = node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}
