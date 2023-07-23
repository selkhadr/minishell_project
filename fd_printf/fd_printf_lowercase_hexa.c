/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf_lowercase_hexa.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:33:06 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/23 20:24:28 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

static void	print_lettre(int fd, unsigned int n, int *i)
{
	if (n <= 9)
		fd_printf_char(fd, n + 48, i);
	else if (n == 10)
		fd_printf_char(fd, 'a', i);
	else if (n == 11)
		fd_printf_char(fd, 'b', i);
	else if (n == 12)
		fd_printf_char(fd, 'c', i);
	else if (n == 13)
		fd_printf_char(fd, 'd', i);
	else if (n == 14)
		fd_printf_char(fd, 'e', i);
	else if (n == 15)
		fd_printf_char(fd, 'f', i);
}

void	fd_printf_lowercase_hexa(int fd, unsigned int n, int *i)
{
	if (n < 16)
		print_lettre(fd, n % 16, i);
	else
	{
		fd_printf_lowercase_hexa(fd, n / 16, i);
		print_lettre(fd, n % 16, i);
	}
}
