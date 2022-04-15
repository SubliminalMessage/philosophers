/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:41:52 by dangonza          #+#    #+#             */
/*   Updated: 2022/02/16 14:12:16 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*new_string;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
	{
		new_string = malloc(sizeof(char));
		if (new_string != NULL)
			*new_string = 0;
		return (new_string);
	}
	if (len >= s_len)
		len = s_len - start;
	new_string = malloc(sizeof(char) * (len + 1));
	if (new_string != NULL)
	{
		ft_memcpy(new_string, (s + start), len);
		*(new_string + len) = '\0';
	}
	return (new_string);
}
