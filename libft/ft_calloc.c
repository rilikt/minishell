/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:39:52 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/15 15:12:36 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	ptr = malloc(num * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, num * size);
	return (ptr);
}

// int	main(void)
// {
// 	int *arr;
// 	size_t num_elements = 5;
// 	size_t element_size = sizeof(int);

// 	// Use my_calloc to allocate memory for an array of 5 integers
// 	arr = (int *)ft_calloc(num_elements, element_size);

// 	if (arr == NULL)
// 	{
// 		printf("Memory allocation failed!\n");
// 		return (1);
// 	}

// 	// Print the initialized array elements
// 	printf("Initialized array elements:\n");
// 	for (size_t i = 0; i < num_elements; i++)
// 	{
// 		printf("%d ", arr[i]); // Should print zeros
// 	}
// 	printf("\n");

// 	// Free the allocated memory
// 	free(arr);

// 	return (0);
// }