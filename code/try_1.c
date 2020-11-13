/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:05:53 by jinwkim           #+#    #+#             */
/*   Updated: 2020/11/13 16:28:56 by jinwkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

typedef struct	s_cmd
{
	int				is_pipe;
	int				fd[2];
	char			**args;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

int		ft_strlen(char *s)
{
	int		result;

	result = 0;
	while (s[result])
		result++;
	return (result);
}

void	ft_putstr(char *s)
{
	write(2, s, ft_strlen(s));
}

int		exit_fatal(void)
{
	ft_putstr("error: fatal\n");
	exit(1);
}

int		ft_strcmp(char *s1, char *s2)
{
	int		idx;

	idx = 0;
	while (s1[idx] || s2[idx])
	{
		if (s1[idx] != s2[idx])
			return (s1[idx] - s2[idx]);
		idx++;
	}
	return (0);
}

void	add_cmd(t_cmd **head, t_cmd *node)
{
	t_cmd	*tmp;

	if (*head == 0)
		*head = node;
	else
	{
		tmp = *head;
		while (tmp->next != 0)
			tmp = tmp->next;
		tmp->next = node;
		node->prev = tmp;
	}
}

t_cmd	*create_cmd(int start, int end, char **args, int is_pipe)
{
	t_cmd	*tmp;
	int		idx_start;
	int		idx;

	idx = 0;
	idx_start = start;
	if ((tmp = (t_cmd *)malloc(sizeof(t_cmd))) == 0)
		exit_fatal();
	if ((tmp->args = (char **)malloc(sizeof(char *) * (end - start + 1))) == 0)
		exit_fatal();
	while (idx_start < end)
	{
		tmp->args[idx] = args[idx_start];
		idx++;
		idx_start++;
	}
	tmp->args[idx] = 0;
	tmp->next = 0;
	tmp->prev = 0;
	tmp->is_pipe = is_pipe;
	return (tmp);
}

t_cmd	*make_pipe_cmd(int start, int end, char **args)
{
	int		idx;
	int		pipe_idx;
	t_cmd	*head;
	t_cmd	*tmp;

	idx = start;
	head = 0;
	tmp = 0;
	pipe_idx = start;
	while (idx < end)
	{
		if (ft_strcmp(args[idx], "|") == 0)
		{
			tmp = create_cmd(pipe_idx, idx, args, 1);
			add_cmd(&head, tmp);
			pipe_idx = idx + 1;
		}
		idx++;
	}
	if (pipe_idx - idx != 0)
	{
		tmp = create_cmd(pipe_idx, idx, args, 0);
		add_cmd(&head, tmp);
	}
	return (head);
}

void	print_cmd(t_cmd	*head)
{
	int		idx;

	while (head != 0)
	{
		idx = 0;
		while (head->args[idx])
		{
			printf("%s\n", head->args[idx]);
			idx++;
		}
		head = head->next;
	}
}

int		non_builtin(t_cmd *cmd, char **env)
{
	int		result;
	int		status;
	pid_t	id;

	result = 0;
	if (cmd->is_pipe)
		if (pipe(cmd->fd) < 0)
			exit_fatal();
	id = fork();
	if (id < 0)
		exit_fatal();
	else if (id == 0)
	{
		if (cmd->is_pipe && dup2(cmd->fd[1], 1) < 0)
			exit_fatal();
		if (cmd->prev && cmd->prev->is_pipe && dup2(cmd->prev->fd[0], 0) < 0)
			exit_fatal();
		if ((result = execve(cmd->args[0], cmd->args, env)) < 0)
		{
			ft_putstr("error: cannot execute ");
			ft_putstr(cmd->args[0]);
			ft_putstr("\n");
		}
		exit(result);
	}
	else
	{
		waitpid(id, &status, 0);
		if (WIFEXITED(status))
			result = WEXITSTATUS(status);
		if (cmd->is_pipe)
		{
			close(cmd->fd[1]);
			if (!cmd->next)
				close(cmd->fd[0]);
		}
		if (cmd->prev && cmd->prev->is_pipe)
			close(cmd->prev->fd[0]);
	}
	return (result);
}

int		ft_cd(t_cmd *cmd)
{
	int		cnt;
	int		result;

	cnt = 0;
	result = 0;
	while (cmd->args[cnt])
		cnt++;
	if (cnt != 2)
	{
		ft_putstr("error: cd: bad arguments\n");
		return(1);
	}
	else
	{
		if ((result = chdir(cmd->args[1])) < 0)
		{
			ft_putstr("error: cd: cannot change directory to ");
			ft_putstr(cmd->args[1]);
			ft_putstr("\n");
		}
	}
	return (result);
}

int		check_cmd(t_cmd *cmd, char **env)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
	{
		return (ft_cd(cmd));
	}
	else
	{
		return (non_builtin(cmd, env));
	}
}

int		execute(t_cmd *head, char **env)
{
	int		result;

	result = 0;
	while (head != 0)
	{
		result = check_cmd(head, env);
		head = head->next;
	}
	return (result);
}

void	clean_cmd(t_cmd **head)
{
	t_cmd	*node;
	t_cmd	*old;

	node = *head;
	while (node)
	{
		old = node;
		node = node->next;
		free(old);
	}
}

int		main(int argc, char **argv, char **env)
{
	int		start;
	int		end;
	t_cmd	*head;
	int		result;

	start = 1;
	end = 1;
	result = 0;
	while (end < argc)
	{
		head = 0;
		if (ft_strcmp(argv[end], ";") == 0)
		{
			head = make_pipe_cmd(start, end, argv);
			start = end + 1;
//			print_cmd(head);			
			printf("\n");
			result = execute(head, env);
			clean_cmd(&head);
		}
		end++;
	}
	if (end - start != 0)
	{
		head = make_pipe_cmd(start, end, argv);
//		print_cmd(head);
		result = execute(head, env);
		clean_cmd(&head);
	}
	return (result);
}
