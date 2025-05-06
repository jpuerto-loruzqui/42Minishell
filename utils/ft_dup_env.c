/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:10:40 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/06 11:01:54 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*ft_envlast(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*ultimo;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ultimo = ft_envlast(*lst);
	ultimo->next = new;
}

t_env	*ft_new_node_env(void *content)
{
	t_env	*toreturn;

	toreturn = malloc(sizeof(t_env));
	if (!toreturn)
		return (NULL);
	toreturn->content = ft_strdup(content);
	toreturn->exported = true;
	toreturn->next = NULL;
	return (toreturn);
}

t_env	*ft_dup_env(char **envp)
{
	t_env	*new_env;
	t_env	*new_node;

	new_env = NULL;
	new_node = NULL;
	while (*envp)
	{
		new_node = ft_new_node_env(*envp);
		if (!new_node)
			return (NULL);
		ft_envadd_back(&new_env, new_node);
		envp++;
	}
	return (new_env);
}
