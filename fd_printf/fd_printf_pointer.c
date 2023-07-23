/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:41:08 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/23 20:24:24 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

static void	fd_printf_pointer_letre(int fd, unsigned long n, int *i)
{
	if (n <= 9 && n >= 0)
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

static void	fd_printf_pointer_hexa(int fd, unsigned long n, int *i)
{
	if (n < 16 && n >= 0)
		fd_printf_pointer_letre(fd, n % 16, i);
	else
	{
		fd_printf_pointer_hexa(fd, n / 16, i);
		fd_printf_pointer_letre(fd, n % 16, i);
	}
}

void	fd_printf_pointer(int fd, unsigned long n, int *i)
{
	fd_printf_string(fd, "0x", i);
	fd_printf_pointer_hexa(fd, n, i);
}
