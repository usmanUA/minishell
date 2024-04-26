/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_user.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:55:03 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/16 13:55:05 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "miniwell.h"
#include "vec/vec.h"
#include <stdio.h>

void	ft_init_vars(t_vars *vars)
{
    // NOTE: Initialize vars struct
    vars->ind = 0;
    vars->end = 0;
    vars->len = 0;
    vars->fd = 0;
    vars->qontinue = 0;
    vars->s_quote = 0;
    vars->d_quote = 0;
    vars->increment = 0;
    vars->stop = 0;
    vars->input_line = NULL;
}

static size_t	ft_user_ends(char *s)
{
    // NOTE: NOT used function
    while (*s)
    {
	if (!ft_isspace(*s))
	    return (0);
	s++;
    }
    return (1);
}

void ft_index_after_spaces(t_vars *vars)
{
    // NOTE: SKIPS all the spaces and moves the pointer to the non-space character 
    while (vars->input_line[vars->end] && ft_isspace(vars->input_line[vars->end]))
	vars->end++;
    vars->ind = vars->end; // NOTE: index updates here
    //                    '\0'
}


// static int ft_redirect_operator(char c)
// {
//     // NOTE: returns true if the current string is one of the redirect operators
// 	return (1);
//     if (!ft_strncmp(c, "<<", 2) || !ft_strncmp(c, ">>", 2))
// 	return (1);
//     return (0);
// }

void	ft_shift_pointer(t_vars *vars)
{
    // NOTE: moves the pointer either to the next | or null-terminator whatever comes first in the char *
    vars->ind = vars->end;
    while (vars->ind < vars->len)
    {
	if (vars->input_line[vars->ind] == '|') // NOTE: if encounters | stops.
	{
	    vars->ind++;
	    return ;
	}
	vars->ind++;
    }
}


int ft_redirection(t_vars *vars)
{
    // NOTE: checks the operator-first case
    int ind;

    ind = vars->ind;
    if (vars->input_line[ind] == '<' || vars->input_line[ind] == '>')
	return (1);
    while (ft_isdigit(vars->input_line[ind]))
	ind++;
    if (vars->input_line[ind] == '<' || vars->input_line[ind] == '>')
    {
	vars->fd = 1;
	return (1);
    }
    return (0);
}

int ft_parse_command_line(t_input *input, t_vars *vars)
{
    // NOTE: PARSES the WHOLE command line into two following vectors
    t_vec *cmd;
    t_vec *redirect;

    cmd = (t_vec *)malloc(sizeof(t_vec));
    if (!cmd)
	return (0);
    redirect = (t_vec *)malloc(sizeof(t_vec));
    if (!redirect)
	return (0);
    if (!vec_new(cmd, 2, sizeof(char *))) // NOTE: Initialize a vec and allocate some mem for command
	return (0); // NOTE: malloc fail
    if (!vec_new(redirect, 2, sizeof(t_redirect *))) // NOTE: Init a vec and alloc. some mem for redir.
	return (0);
    if (!ft_parsing_action(cmd, redirect, vars)) // TODO: Handle errors correctly
	return (0);
    // NOTE: saving addresses of cmd, redirect to input
    input->cmd = cmd;
    input->redirect = redirect;
    return (1);
}
int ft_save_input(t_vec *pipes, t_vars *vars)
{
    // NOTE: PARSE EVERYTHING
    t_input *input;

    ft_index_after_spaces(vars); 
    while (vars->input_line[vars->ind] != '\0') // NOTE: loop over the whole user input line
    {
	input = malloc(sizeof(t_input)); // NOTE: executed in the very beg. or the beg. of every pipe (|) if any
	if (!input)
	    return (0);
	if (!ft_parse_command_line(input, vars)) // TODO: Handle errors correctly
	    return (0); // WARN: Handle malloc
	if (!vec_push(pipes, input))
	    return (0); // NOTE: malloc fail
    }
    return (1);
}
