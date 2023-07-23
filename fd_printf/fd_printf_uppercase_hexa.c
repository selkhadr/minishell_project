/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf_uppercase_hexa.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:46:44 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/18 11:38:02 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

static void	print_uper_lettre(int fd, unsigned int n, int *i)
{
	if (n <= 9)
		fd_printf_char(fd, n + 48, i);
	else if (n == 10)
		fd_printf_char(fd, 'A', i);
	else if (n == 11)
		fd_printf_char(fd, 'B', i);
	else if (n == 12)
		fd_printf_char(fd, 'C', i);
	else if (n == 13)
		fd_printf_char(fd, 'D', i);
	else if (n == 14)
		fd_printf_char(fd, 'E', i);
	else if (n == 15)
		fd_printf_char(fd, 'F', i);
}

void	fd_printf_upercase_hexa(int fd, unsigned int n, int *i)
{
	if (n < 16)
		print_uper_lettre(fd, n % 16, i);
	else
	{
		fd_printf_upercase_hexa(fd, n / 16, i);
		print_uper_lettre(fd, n % 16, i);
	}
}
