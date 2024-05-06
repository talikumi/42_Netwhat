/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-marc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:17:07 by edi-marc          #+#    #+#             */
/*   Updated: 2021/01/31 16:45:25 by edi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: libft
** SYNOPSIS: convert ASCII string to integer
**
** DESCRIPTION:
** 		The atoi() function converts the initial portion of the string pointed
**	to by str to int representation.
**
**	The function has an undefined behavior if the representation of the string
**	overflows the type int
*/

static	const char		*jump_space(const char *str)
{
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	return (str);
}

static	const char		*jump_sign(const char *str, int *sign)
{
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			*sign = *sign * -1;
		str++;
	}
	return (str);
}

static	int				calculate(const char *str)
{
	int nbr;
	int k;

	nbr = 0;
	k = 0;
	while (*str > 47 && *str < 58)
	{
		nbr = nbr * 10;
		k = *str;
		nbr = nbr + (k - 48);
		str++;
	}
	return (nbr);
}

int						ft_atoi(const char *str)
{
	int sign;
	int nbr;
	int *s;

	sign = 1;
	s = &sign;
	str = jump_space(str);
	str = jump_sign(str, s);
	nbr = calculate(str);
	nbr = nbr * sign;
	return (nbr);
}
