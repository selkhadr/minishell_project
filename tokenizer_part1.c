/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_part1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:42:44 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/20 17:34:15 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_part_one(t_token **all, char *expanded)
{
	creating_linked(all, expanded);
	if (!ft_strcmp((*all)->token, ""))// not this 
		delete_first_node(all);
	setup_exact_type(all);
}

void	creating_linked(t_token **all, char *s)
{
	initialization_of_vars();
	while (s[g_glo.i])
	{
		if (s[g_glo.i] != 32 && s[g_glo.i] != '\t' \
		&& s[g_glo.i] != '<' && s[g_glo.i] != '>' \
		&& s[g_glo.i] != '|' && s[g_glo.i] != 1 \
		&& s[g_glo.i] != '\0')
			take_the_whole_node(s, all);
		if (s[g_glo.i] == 1)
			take_arg_heredoc(s, all);
		else if (s[g_glo.i] == '|')
			take_pipe(all);
		else if (s[g_glo.i] == '>')
			take_append(s, all);
		else if (s[g_glo.i] == '<')
			take_heredoc(all, s);
		else if (s[g_glo.i++] == '\0')
			break ;
	}
}
