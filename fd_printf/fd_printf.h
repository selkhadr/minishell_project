/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 23:09:37 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/23 20:27:08 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_PRINTF_H
# define FD_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		fd_printf(int fd, const char *s, ...);
void	fd_printf_char(int fd, char c, int *i);
void	fd_printf_string(int fd, char *str, int *i);
void	fd_printf_pointer(int fd, unsigned long n, int *i);
void	fd_printf_decimal(int fd, long n, int *i);
void	fd_printf_unsigned(int fd, unsigned int n, int *i);
void	fd_printf_lowercase_hexa(int fd, unsigned int n, int *i);
void	fd_printf_upercase_hexa(int fd, unsigned int n, int *i);

#endif
