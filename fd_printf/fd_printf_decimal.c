/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf_decimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:31:42 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/23 20:27:16 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

void	fd_printf_decimal(int fd, long n, int *i)
{
	if (n < 0)
	{
		fd_printf_char(fd, '-', i);
		fd_printf_decimal(fd, -n, i);
	}
	else if (n > 9)
	{
		fd_printf_decimal(fd, n / 10, i);
		fd_printf_decimal(fd, n % 10, i);
	}
	else
		fd_printf_char(fd, n + 48, i);
}
