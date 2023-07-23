/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_printff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:52:49 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/14 12:15:09 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

static void	print(int fd, char s, va_list tmp, int *i)
{
	if (s == '%')
		fd_printf_char(fd, s, i);
	if (s == 'c')
		fd_printf_char(fd, va_arg(tmp, int), i);
	else if (s == 's')
		fd_printf_string(fd, va_arg(tmp, char *), i);
	else if (s == 'd' || s == 'i')
		fd_printf_decimal(fd, va_arg(tmp, int), i);
	else if (s == 'u')
		fd_printf_unsigned(fd, va_arg(tmp, int), i);
	else if (s == 'p')
		fd_printf_pointer(fd, va_arg(tmp, unsigned long), i);
	else if (s == 'x')
		fd_printf_lowercase_hexa(fd, va_arg(tmp, int), i);
	else if (s == 'X')
		fd_printf_upercase_hexa(fd, va_arg(tmp, int), i);
}

int	fd_printf(int fd, const char *s, ...)
{
	int		count;
	va_list	tmp;

	count = 0;
	va_start(tmp, s);
	while (*s)
	{
		if (*s == '%')
		{
			print(fd, *(s + 1), tmp, &count);
			s += 2;
		}
		else
		{
			fd_printf_char(fd, *s, &count);
			s++;
		}
	}
	va_end(tmp);
	return (count);
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main()
// {
// 	int	n;
// 	int fd;

// 	fd = open("fidle.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
// 	n = fd_printf(2, "here %d\n", 4);
// 	printf("%d\n", n);
// 	n = printf("here %d\n", 4);
// 	printf("%d\n", n);
// }
