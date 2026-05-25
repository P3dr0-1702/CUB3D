/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:37:40 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/21 15:01:03 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

/**
 * @brief Allocates memory for an array and initializes it to zero.
 *
 * @param nmemb Number of elements.
 * @param size Size of each element in bytes.
 * @return Pointer to the allocated memory, or NULL on failure.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	if ((nmemb == 0 || size == 0))
		return (malloc(0));
	if (nmemb > (SIZE_MAX) / size)
		return (NULL);
	buffer = malloc(nmemb * size);
	if (buffer == NULL)
		return (NULL);
	ft_bzero(buffer, nmemb * size);
	return (buffer);
}
