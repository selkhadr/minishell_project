/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:03:35 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/21 17:54:39 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_the_whole_node(char *s, t_token **all)
{
	while (s[g_glo.i] != 32 && s[g_glo.i] != '\t' && s[g_glo.i] != '<' \
	&& s[g_glo.i] != '>' && s[g_glo.i] != '|' \
	&& s[g_glo.i] != 1 && s[g_glo.i] != '\0')
	{
		if (s[g_glo.i] != 32 && s[g_glo.i] != '\t' \
		&& s[g_glo.i] != '<' && s[g_glo.i] != '>' && s[g_glo.i] != '|'\
		&& s[g_glo.i] != 1 && s[g_glo.i] != 31 && s[g_glo.i] != '\0')
			take_the_word(s);
		if (s[g_glo.i] == 31)
			found_expand(s, all);
		if (!(s[g_glo.i] != 32 && s[g_glo.i] != '\t' \
		&& s[g_glo.i] != '<' && s[g_glo.i] != '>' \
		&& s[g_glo.i] != '|' && s[g_glo.i] != 1))
			break ;
	}
	take_node(all);
}

void	take_arg_heredoc(char *s, t_token **all)
{
	g_glo.tmp = single_double_quotes(s, 1, &g_glo.i);
	g_glo.str = mer_substr(g_glo.tmp, 1, ft_strlen(g_glo.tmp) - 2);
	ft_lstadd_back1(all, ft_lstnew1(g_glo.str, S_ARG));
	free(g_glo.tmp);
	free(g_glo.str);
	g_glo.tmp = NULL;
	g_glo.str = NULL;
}

void	take_pipe(t_token **all)
{
	ft_lstadd_back1(all, ft_lstnew1("|", PIPE));
	g_glo.i++;
}

void	take_append(char *s, t_token **all)
{
	if (s[g_glo.i + 1] == '>')
	{
		while (s[g_glo.i] == '>')
		{
			g_glo.len++;
			g_glo.i++;
		}
		if (g_glo.len == 2)
			ft_lstadd_back1(all, ft_lstnew1(">", APPEND));
		else
			ft_lstadd_back1(all, ft_lstnew1(">", APPEND_ERROR));
	}
	else
	{
		ft_lstadd_back1(all, ft_lstnew1(">", REDIR_OUT));
		g_glo.i++;
	}
	g_glo.len = 0;
}

void	take_heredoc(t_token **all, char *s)
{
	if (s[g_glo.i + 1] == '<')
	{
		while (s[g_glo.i] == '<')
		{
			g_glo.len++;
			g_glo.i++;
		}
		if (g_glo.len == 2)
			ft_lstadd_back1(all, ft_lstnew1("<", HEREDOC));
		else
			ft_lstadd_back1(all, ft_lstnew1("<", HEREDOC_ERROR));
	}
	else
	{
		ft_lstadd_back1(all, ft_lstnew1("<", REDIR_IN));
		g_glo.i++;
	}
	g_glo.len = 0;
}
