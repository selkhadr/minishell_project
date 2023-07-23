/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:04:41 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/21 18:02:30 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	closed_double_quotes(char *s)
{
	int		i;
	char	c;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
				i++;
			if (s[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

char	*arg_heredoc(char *s, int *i)
{
	char	*arg;
	int		j;

	arg = NULL;
	j = *i;
	while (s[j] == 32 || s[j] == '\t')
	{
		(j)++;
	}
	if (!s[j])
		return (NULL);
	while (s[j] != '|' && s[j] != '\t' \
	&& s[j] != 32 && s[j] != '>' \
	&& s[j] != '<' && s[j])
	{
		arg = mini_strjoin(arg, s[j]);
		(j)++;
	}
	if (arg)
		*i = j;
	return (arg);
}

void	*mer_calloc(int count, int size)
{
	char	*p;
	int		i;

	i = 0;
	p = (char *) malloc (count * size);
	if (p == NULL)
		return (NULL);
	while (i < (count * size))
	{
		p[i] = 0;
		i++;
	}
	return (p);
}
