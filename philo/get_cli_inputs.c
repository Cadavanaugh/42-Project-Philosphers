/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cli_inputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:12:53 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/13 19:26:41 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// if is not '-' or '+' neither a number return 0
static unsigned char	is_valid_for_atol(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i])
	{
		if (!(nptr[i] == 45 || nptr[i] == 43) && (nptr[i] < 48 || nptr[i] > 57))
			return (0);
		i++;
	}
	return (1);
}

static unsigned char	is_int_in_limit(long n)
{
	if (n > 2147483647)
		return (0);
	else if (n < -2147483648)
		return (0);
	else
		return (1);
}

long	ft_atol(const char *nptr)
{
	long	result;
	char	signal;

	if (!is_valid_for_atol(nptr))
		return (-1);
	result = 0;
	signal = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
		signal *= -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = (result * 10) + (*nptr - '0');
		nptr++;
	}
	if (is_int_in_limit(result * signal))
		return (result * signal);
	return (-1);
}

char	is_input_valid(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	while (i < argc)
	{
		if (ft_atol(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}
