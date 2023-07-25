/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:02:23 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/25 12:00:45 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*adrs_substr(char *s, int start, char *t)
{
	char	*p;
	int		i;
	int		len;

	i = 0;
	if (!t)
		return (ft_strdup(s));
	len = t - s;
	if (!s)
		return (NULL);
	if (start >= (int)ft_strlen(s))
		return (ft_calloc(1, 1));
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

void	unset_norm(char *str)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	g_glo.exitstatus = 1;
}

void	unset_norm_two(t_env *temp, t_env *prev)
{
	if (prev != NULL)
		prev->next = temp->next;
	else
		g_glo.env = temp->next;
	free(temp->env);
	free(temp);
}

void	unset_fnct_sequel(char *str)
{
	t_env	*temp;
	t_env	*prev;
	char	*tmp;

	temp = g_glo.env;
	prev = NULL;
	tmp = NULL;
	while (temp != NULL)
	{
		tmp = adrs_substr(temp->env, 0, ft_strchr(temp->env, '='));
		if (compare(tmp, str) == 0)
		{
			free (tmp);
			break ;
		}
		free (tmp);
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	unset_norm_two(temp, prev);
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

void	take_env(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_lstadd_back(ft_lstnew(arr[i]));
		i++;
	}
}

void	ft_lstadd_back(t_env *new)
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

t_env	*ft_lstnew(char *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->env = ft_strdup(content);
	node->next = NULL;
	return (node);
}

int	valid_identifier(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '_')
	{
		if (ft_isalpha(str[0]) == 0)
			return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	export_fnct_norm(void)
{
	t_env	*tmp;
	char	*key;
	char	*value;

	tmp = g_glo.env;
	key = NULL;
	while (tmp)
	{
		if (!ft_strchr(tmp->env, '='))
			printf("declare -x %s\n", tmp->env);
		else
		{
			key = adrs_substr(tmp->env, 0, ft_strchr(tmp->env, '='));
			printf("declare -x %s", key);
			value = expanded_value(key);
			printf("=\"%s\"\n", value);
			free (value);
			value = NULL;
			free (key);
			key = NULL;
		}
		tmp = tmp->next;
	}
}

void	export_fnct(t_all *all, int flag)
{
	int		i;

	i = 1;
	if (!all->cmds[1])
		export_fnct_norm();
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

int	export_norm(t_export_var *var, t_all *all, int n)
{
	if (valid_identifier(all->cmds[n]) == 1)
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(all->cmds[n], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		g_glo.exitstatus = 1;
		return (1);
	}
	if (!ft_strchr(all->cmds[n], '='))
		var->variable = ft_strdup(all->cmds[n]);
	else
		var->variable = adrs_substr(all->\
		cmds[n], 0, ft_strchr(all->cmds[n], '='));
	if (var->variable == NULL)
		return (1);
	return (0);
}

void	export_norm_two(char **env, t_export_var *var, t_all *all, int n)
{
	free ((*env));
	(*env) = NULL;
	(*env) = ft_strdup(all->cmds[n]);
	free(var->var);
	var->var = NULL;
	free(var->variable);
	var->variable = NULL;
}

void	export_norm_three(t_all *all, int n, t_export_var *var)
{
	free (var->variable);
	var->variable = NULL;
	ft_lstadd_back(ft_lstnew(all->cmds[n]));
}

void	export_fnct_sequel(t_all *all, int n)
{
	extern char		**environ;
	int				i;
	t_env			*tmp;
	t_export_var	var;

	i = 0;
	tmp = g_glo.env;
	if (export_norm(&var, all, n) == 1)
		return ;
	while (tmp)
	{
		var.var = \
		adrs_substr(tmp->env, 0, ft_strchr(tmp->env, '='));
		if (!ft_strchr(all->cmds[n], '=') && expanded_value(all->cmds[n]))
			return ;
		if (compare(var.var, var.variable) == 0)
		{
			export_norm_two(&tmp->env, &var, all, n);
			return ;
		}
		free (var.var);
		var.var = NULL;
		tmp = tmp->next;
	}
	export_norm_three(all, n, &var);
}
