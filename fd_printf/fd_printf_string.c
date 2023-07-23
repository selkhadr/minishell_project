/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprint_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:27:46 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/14 11:16:54 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

void	fd_printf_string(int fd, char *str, int *i)
{
	if (!str)
	{
		fd_printf_string(fd, "(null)", i);
		return ;
	}
	while (*str)
	{
		fd_printf_char(fd, *str, i);
		str++;
	}
}
