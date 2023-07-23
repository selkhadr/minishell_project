/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:08:54 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/13 18:19:33 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	length(int n)
{
	long	i;
	long	count;

	i = n;
	count = 0;
	if (i < 0)
	{
		i = i * (-1);
		count++;
	}
	if (i == 0)
		return (1);
	while (i > 0)
	{
		i = i / 10;
		count++;
	}
	return (count);
}

static char	*kteb(char *p, long len, long bo, long i)
{
	while (len >= bo)
	{
		p[len] = i % 10 + 48;
		i = i / 10;
		len--;
	}
	return (p);
}

char	*ft_itoa(int n)
{
	long	i;
	int		len;
	char	*p;
	int		bo;

	i = n;
	bo = 0;
	len = length(i);
	p = (char *) malloc (len + 1);
	if (p == NULL)
		return (NULL);
	p[len] = '\0';
	if (i < 0)
	{
		bo = 1;
		i = i * (-1);
		p[0] = '-';
	}
	len--;
	return (kteb(p, len, bo, i));
}
