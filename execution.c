/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:27:29 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/25 11:42:25 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_fnct(t_all *all)
{
	if (all->next)
	{
		all->next->prev_pip = 0;
		if (pipe(all->pip) == -1)
			exit (-1);
		all->next->prev_pip = all->pip[READ];
	}
}

int	use_builtins_sequel(t_all *all)
{
	if (!all || !all->cmds || !all->cmds[0])
		return (0);
	if (all->cmds[0] && compare(all->cmds[0], "export") == 0 && all->cmds[1])
	{
		export_fnct(all, 0);
		return (1);
	}
	else if (all->cmds[0] && compare(all->cmds[0], "unset") == 0)
	{
		unset_fnct(all, 0);
		return (1);
	}
	else if (compare(all->cmds[0], "cd") == 0)
	{
		chdir_fnct(all, 0);
		return (0);
	}
	else if (compare(all->cmds[0], "exit") == 0)
		return (exit_fnct(all));
	return (0);
}

void	use_builtins(t_all *all)
{
	char	pwd[1000];

	if (!all || !all->cmds || !all->cmds[0])
		return ;
	else if (compare(all->cmds[0], "export") == 0)
		export_fnct(all, 1);
	else if (compare(all->cmds[0], "unset") == 0)
		unset_fnct(all, 1);
	else if (compare(all->cmds[0], "cd") == 0)
		chdir_fnct(all, 1);
	else if (compare(all->cmds[0], "echo") == 0)
		echo_fnct(all, 1);
	else if (compare(all->cmds[0], "pwd") == 0)
	{
		if (getcwd(pwd, PATH_MAX) != NULL)
			printf("%s\n", pwd);
		exit (0);
	}
	else if (compare(all->cmds[0], "env") == 0)
		print_env(1);
}

void	execution_fnct_sequel(t_all *all, char **env)
{
	if (all->pid == -1)
		exit (-1);
	if (all->pid == 0)
	{
		signal (SIGQUIT, SIG_DFL);
		signal (SIGINT, SIG_DFL);
		out_redirect(all);
		in_redirect(all);
		if (all->next)
		{
			close(all->pip[WRIT]);
			close(all->pip[READ]);
		}
		if (all->prev_pip != 0)
			close(all->prev_pip);
		use_builtins(all);
		check_path(all);
		use_execve(all, env);
	}
	close_pipes(all);
}

void	handler_fnct(int sig)
{
	if (sig == SIGINT)
	{
		printf ("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_glo.exitstatus = 1;
	}
}

void	waiting_norm(t_all *glo)
{
	int	tmp;

	if (compare(glo->cmds[0], "exit") == 0)
	{
		printf("ddd = %d\n", g_glo.exitstatus);
		if (!glo->cmds[1])
		{	
			tmp = g_glo.old_exitstatus;
			error_message(0, NULL);
			exit (tmp);
		}
		if ((is_num(glo->cmds[1]) && !glo->cmds[2]) || !is_num(glo->cmds[1]))
		{
			tmp = g_glo.exitstatus;
			error_message(0, NULL);
			exit (tmp);
		}
	}
}

void	waiting_fnct(t_all *glo)
{
	int	status;

	g_glo.old_exitstatus = g_glo.exitstatus;
	while (glo)
	{
		waitpid(glo->pid, &status, 0);
		signal (SIGINT, handler_fnct);
		signal (SIGQUIT, SIG_IGN);
		if (WIFEXITED(status))
		{
			g_glo.exitstatus = WEXITSTATUS(status);
			if (glo->cmds != NULL)
				waiting_norm(glo);
		}
		else if (WIFSIGNALED(status))
			g_glo.exitstatus = WTERMSIG(status) + 128;
		glo = glo->next;
	}
}

void	execution_fnct(t_all *glo, char **env)
{
	t_all	*tmp;

	tmp = glo;
	heredoc_fnction(glo);
	if (g_glo.exitstatus == 1)
		return ;
	if (glo->next == NULL)
	{
		if (use_builtins_sequel(tmp) == 1)
			return ;
	}
	while (tmp)
	{
		pipe_fnct(tmp);
		signal (SIGINT, SIG_IGN);
		tmp->pid = fork();
		execution_fnct_sequel(tmp, env);
		tmp = tmp->next;
	}
	tmp = glo;
	close_heredoc(tmp);
	waiting_fnct(tmp);
}
