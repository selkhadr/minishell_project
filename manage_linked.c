/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_linked.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:48:31 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/21 18:04:09 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_token	*ft_lstnew1(char *content, int value)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = ft_strdup(content);
	node->type = value;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back1(t_token **lst, t_token *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while ((*lst)->next != NULL)
		lst = &(*lst)->next;
	(*lst)->next = new;
}

void	ft_lstaddback_final(t_all **lst, t_all *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while ((*lst)->next != NULL)
		lst = &(*lst)->next;
	(*lst)->next = new;
}

void	dollar_lhgar(t_token **all, char *s)
{
	int		i;
	char	**line;

	i = 0;
	line = mer_split(s);
	while (line[i])
	{
		ft_lstadd_back1(all, ft_lstnew1(line[i], WORD));
		i++;
	}
	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}
