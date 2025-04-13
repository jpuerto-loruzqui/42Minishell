/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jp_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:59:48 by jpuerto           #+#    #+#             */
/*   Updated: 2025/04/13 14:12:50 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/ioctl.h>
#include <termios.h>

void	set_raw_mode(int fd)
{
	struct termios	term;

	tcgetattr(fd, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(fd, TCSANOW, &term);
}

void	restore_terminal(int fd)
{
	struct termios	term;

	tcgetattr(fd, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(fd, TCSANOW, &term);
}

char	read_key(void)
{
	char	c;

	read(STDIN_FILENO, &c, 1);
	if (c == 'q' || c == '\n')
		return (c);
	else
		return ('z');
}
