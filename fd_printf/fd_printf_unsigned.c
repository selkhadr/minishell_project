/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprint_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:45:07 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/14 11:18:02 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

void	fd_printf_unsigned(int fd, unsigned int n, int *i)
{
	if (n <= 9)
		fd_printf_char(fd, n + 48, i);
	else
	{
		fd_printf_decimal(fd, n / 10, i);
		fd_printf_char(fd, n % 10 + 48, i);
	}
}
