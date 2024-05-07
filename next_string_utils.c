/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_string_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:34:48 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/07 16:34:50 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "miniwell.h"

int	ft_valid_char(char next, int check_digits)
{
	if (next == '\0')
		return (INVALID);
	if (check_digits == YES)
	{
		if (ft_isdigit(next))
			return (INVALID);
	}
	if (next == '-')
		return (INVALID);
	if (ft_isspace(next))
		return (INVALID);
	return (VALID);
}

int	ft_status_expansion(t_vars *vars, char c, int *ind)
{
	char	next;

	next = vars->input_line[vars->ind + 2];
	if (c == '?')
	{
		(*ind) += 2;
		if (ft_valid_char(vars->input_line[vars->ind + 2], NO) == VALID)
			vars->qontinue = YES;
		return (YES);
	}
	return (NO);
}

