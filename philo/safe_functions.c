/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:06:10 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/11 13:08:14 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*safe_malloc(long size)
{
	void	*memory;

	memory = malloc(size);
	if (!memory)
		perror("Failed to malloc");
	return (memory);
}
