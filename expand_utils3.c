/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:28:52 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/14 13:36:02 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	found_expand(char *s, t_token **all)
{
	take_expanded(s);
	if (check(g_glo.str) == 1)
		take_one_expanded();
	else
	{
		treatment(s, all);
		if (s[g_glo.i] != 32 && s[g_glo.i] != '\t' \
		&& s[g_glo.i] != '<' && s[g_glo.i] != '>' \
		&& s[g_glo.i] != '|' && s[g_glo.i] != 1 \
		&& s[g_glo.i] != '\0')
		{
			g_glo.curr = ft_lstlast(*all);
			take_a_lot_expanded(s);
		}
		free(g_glo.node);
		g_glo.node = NULL;
	}
}
