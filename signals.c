/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:38:52 by loruzqui          #+#    #+#             */
/*   Updated: 2025/03/26 15:38:54 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line(); //le indica a Readline que el cursor está en una nueva línea, preparando el prompt para dibujarse de nuevo
	rl_replace_line("", 0); //sustituye el contenido actual del buffer de entrada por una cadena vacía (borra lo escrito).
	rl_redisplay(); //muestra un nuevo prompt
}
