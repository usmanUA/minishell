/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:50:16 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/16 13:50:18 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "miniwell.h"
#include <sys/_types/_size_t.h>

static int ft_token_error(char c)
{
    printf("bash: syntax error near unexpected token  '%c'\n",c); 
    return (1);
}

int ft_special_char(char s)
{
    // NOTE: checks for prohibited special characters and returns 1 if true 
    if (s == '(' || s == ')' || s == '|')
	return (1);
    if (s == '&' || s == ';' || s == '\\')
	return (1);
    return (0);
}

static int ft_prohibited_chars(t_vars *vars)
{
    // NOTE: loops over the user innput and checks for prohibited special characters and returns 1 if true 
    int ind;
    
    ind = -1;
    while (++ind < vars->len)
    {
	if (ft_special_char(vars->input_line[ind]))
	    return (ft_token_error(vars->input_line[ind]));
    }
    return (0);
}

int ft_space_until_end(char *s)
{
    // NOTE: check if all the characters after in s are spaces 
    // returns 1 if all spaces or 0 when encounters any other character than spaces.
    int ind;
    size_t len;

    ind = -1;
    len = ft_strlen(s);
    while (++ind < len)
    {
	if (!ft_isspace(s[ind])) //WARN: make sure should it be all whitespace chars or just ' ' (single space)
	    return (0);
    }
    return (1);
}

static int ft_unclosed_quote(t_vars *vars)
{
    int ind;
    int sgle;
    int dble;

    ind = -1;
    sgle = 0;
    dble = 0;
    while (++ind < vars->len)
    {
	if (vars->input_line[ind] == '\"')
	    dble++;
	else if (vars->input_line[ind] == '\'')
	    sgle++;
    }
    if (sgle%2 == 1)
	return (ft_token_error('\''));
    if (dble%2 == 1)
	return (ft_token_error('\"'));
    return (0);
}

int ft_syntax_error(t_vars *vars, size_t len)
{
    // NOTE: writes the errors message and returns 1 when there's error message
    // Errors: 1. if one of the operators come in the beginning or there's an unclosed quotation mark
    //	       2. OR if all the characters are spaces
    //	 TODO: RETURN EXIT STATUS IF THERE's SYNTAX ERROR
    int ind;

    ind = vars->end;
    if (!len)
    {
	vars->len = ft_strlen(vars->input_line);
	len = vars->len; 
    }
    if (ft_space_until_end(vars->input_line))
	return (1);
    if (ft_prohibited_chars(vars))
	return (1);
    if (ft_unclosed_quote(vars))
	return (1);
    return (0);
}
