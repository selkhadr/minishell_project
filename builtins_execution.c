/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:02:23 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/23 14:21:09 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*adrs_substr(char *s, int start, char *t)
{
	char	*p;
	int		i;
	int		len;

	i = 0;
	len = t - s;
	if (!s || !t)
		return (NULL);
	if (start >= (int)ft_strlen(s))
	{
		p = malloc(1);
		p[0] = 0;
		return (p);
	}
	if ((int)ft_strlen(s) < len)
		p = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (s[start] && i < len)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}

//problem in deleting the last three elements of env 

void unset_fnct_sequel(char *str)
{
    t_env*	temp;
    t_env* prev = NULL;

	temp = g_glo.env;
    while (temp != NULL) 
    {
        if (ft_strncmp(temp->env, str, ft_strlen(str)) == 0)
            break;
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    if (prev != NULL)
        prev->next = temp->next;
    else 
        g_glo.env = temp->next;
    free(temp->env);
    free(temp);
}



void	unset_fnct(t_all *all, int flag)
{
	int			i;

	i = 1;
	while (all->cmds[i])
	{
		unset_fnct_sequel(all->cmds[i]);
		i++;
	}
	if (flag == 1)
		exit (0);
}
void    take_env(char **arr)
{
    int    i;

    i = 0;
    while (arr[i])
    {
        ft_lstadd_back(ft_lstnew(arr[i]));
        i++;
    }
}

void    ft_lstadd_back(t_env *new)
{
	t_env	*tmp;

	tmp = g_glo.env;
    if (g_glo.env == NULL)
    {
        g_glo.env = new;
        return ;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
}

t_env    *ft_lstnew(char *content)
{
    t_env    *node;

    node = malloc(sizeof(t_env));
    if (!node)
        return (NULL);
    node->env = ft_strdup(content);
    node->next = NULL;
    return (node);
}

void	export_fnct_sequel(t_all *all, int n)
{
	extern char		**environ;
	int				i;
	t_env			*tmp;
	t_export_var	var;

	i = 0;
	tmp = g_glo.env;
	var.variable = adrs_substr(all->\
	cmds[n], 0, ft_strchr(all->cmds[n], '='));
	if (var.variable == NULL)
		return ;
	while (tmp)
	{
		var.var = \
		adrs_substr(tmp->env, 0, ft_strchr(tmp->env, '='));
		if (ft_strncmp(var.var, var.variable, (int)ft_strlen(var.variable)) == 0)
		{
			free (tmp->env);
			tmp->env = NULL;
			tmp->env = ft_strdup(all->cmds[n]);
			free(var.var);
			var.var = NULL;
			free(var.variable);
			var.variable = NULL;
			return ;
		}
		free (var.var);
		var.var = NULL;
		tmp = tmp->next;
	}
	free (var.variable);
	var.variable = NULL;
	ft_lstadd_back(ft_lstnew(all->cmds[n]));
}

void	export_fnct(t_all *all, int flag)
{
	int		i;
	t_env	*tmp;

	i = 1;
	tmp = g_glo.env;
	if (!all->cmds[1])
	{
		while (tmp)
		{
			printf("declare -x %s\n", tmp->env);
			tmp = tmp->next;
		}
	}
	else
	{
		while (all->cmds[i])
		{
			export_fnct_sequel(all, i);
			i++;
		}
	}
	if (flag == 1)
		exit (0);
}
