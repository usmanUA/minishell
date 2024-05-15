/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:15:30 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/15 14:58:21 by mkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_failed_2d_array(t_shell *shell, char **envp, int i)
{
	i--;
	while (i >= 0)
	{
		free(envp[i]);
		i--;
	}
	free(envp);
	shell->envp = NULL;
}

int	ft_array_length(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		i++;
	}
	return (i);
}

char	**malloc_envp(t_shell *shell, char **envp)
{
	char	**new_envp;
	int		i;
	int		num_of_envs;

	num_of_envs = ft_array_length(envp);
	new_envp = malloc(sizeof(char *) * (num_of_envs + 1));
	if (!new_envp)
	{
		//free all
		exit (1);
	}
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (new_envp[i] == NULL)
		{
			free_failed_2d_array(shell, envp, i);
			//free all
			exit (1);
		}
		i++;
	}
	return (new_envp);
}

int	ft_init_shell(t_shell *shell, char **envp)
{
	t_vec	*pipes;
	t_vars	*vars;

	shell->envp = envp; // NOTE: shell->envp once gave segfault in ft_split, be careful carrying this pointer along
	pipes = (t_vec *)malloc(sizeof(t_vec));
	if (!pipes)
		return (MALLOC_FAIL);
	shell->pipes = pipes;
	vec_new(pipes, 0, sizeof(t_input **));
	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		return (ft_free_prompt(shell, YES));
	shell->vars = vars;
	// shell->envp = envp; // NOTE: shell->envp once gave segfault in ft_split, be careful carrying this pointer along
	shell->envp = malloc_envp(shell, envp);
	if (!shell->envp)// is this the same as shell->envp == NULL? or should there be parenthesis -> !(shell->envp)
	{
		//free all
		exit(1);//Should ths be done with return(MALLOC_FAIL);
	}
	return (MALLOC_SUCCESS);
}

void	ft_init_vars(t_vars *vars)
{
	// NOTE: Initialize vars struct
	vars->ind = 0;
	vars->end = 0;
	vars->len = 0;
	vars->exit_status = GREEN;
	vars->fd = 0;
	vars->file_fd = 0;
	vars->redirection_type = -42;
	vars->qontinue = NO;
	vars->expand_it = NO;
	vars->expanded = NO;
	vars->malloc_flag = GREEN;
	vars->s_quote = 0;
	vars->d_quote = 0;
	vars->increment = NO;
	vars->stop = NO;
	vars->file_error = 0;
	vars->unlink_here_doc = NO;
	vars->redirections = NO;
	vars->f_des = NULL;
	vars->file = NULL;
	vars->redir = NULL;
	vars->input_line = NULL;
	vars->redir_count = NULL;
	vars->redirect = NULL;
}

static int	ft_no_redirections(t_input **input, t_redir_count *redir_count)
{
	int	redirections;

	redirections = 0;
	(*input)->new_fds = NULL;
	(*input)->orig_fds = NULL;
	(*input)->fds_info = NULL;
	redirections = redir_count->in_redir + redir_count->out_redir;
	if (redirections == 0)
		return (YES);
	return (NO);
}

int	ft_init_redirect_vecs(t_shell *shell, t_redir_count *redir_count)
{
	t_vec	*new_fds;
	t_vec	*orig_fds;
	t_vec	*fds_info;

	if (ft_no_redirections(shell->input, redir_count) == YES)
		return (1);
	shell->vars->redirections = YES;
	new_fds = (t_vec *)malloc(sizeof(t_vec));
	if (!new_fds)
		return (ft_free_prompt(shell, YES));
	(*shell->input)->new_fds = new_fds;
	vec_new(new_fds, 0, sizeof(long));
	orig_fds = (t_vec *)malloc(sizeof(t_vec));
	if (!orig_fds)
		return (ft_free_prompt(shell, YES));
	(*shell->input)->orig_fds = orig_fds;
	vec_new(orig_fds, 0, sizeof(long));
	fds_info = (t_vec *)malloc(sizeof(t_vec));
	if (!fds_info)
		return (ft_free_prompt(shell, YES));
	(*shell->input)->fds_info = fds_info;
	vec_new(fds_info, 0, sizeof(long));
	return (MALLOC_SUCCESS);
}

void	ft_init_pipex(t_pipex *pipex, int tot_pipes)
{
	pipex->idx = -1;
	pipex->infile = 42;
	pipex->read_end = 100;
	pipex->write_end = 101;
	pipex->read_from_pipe = YES;
	pipex->output_to_pipe = YES;
	pipex->err_to_pipe = YES;
	pipex->cmd_flag = GREEN;
	pipex->exec_type = GREEN;
	pipex->command = NULL;
	pipex->tot_pipes = tot_pipes;
	pipex->input = NULL;
}
