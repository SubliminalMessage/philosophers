/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:52:15 by dangonza          #+#    #+#             */
/*   Updated: 2022/02/16 14:18:18 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	get_total_words(const char *s, char c);
static void	inner_whiles(char *s, int *i, char c, size_t *slen);
static char	**free_all(char **words, int saved);

char	**ft_split(const char *s, char c)
{
	size_t	s_len;
	int		saved;
	int		i;
	char	**words;
	int		total_words;

	if (!s)
		return (NULL);
	total_words = get_total_words(s, c);
	words = malloc(sizeof(char *) * (total_words + 1));
	if (words == NULL)
		return (NULL);
	i = 0;
	saved = -1;
	s_len = 0;
	while (*(s + i) && ++saved < total_words)
	{
		inner_whiles((char *) s, &i, c, &s_len);
		words[saved] = ft_substr(s, i, (size_t) s_len);
		if (words[saved] == NULL)
			return (free_all(words, saved));
		i += s_len;
	}
	words[total_words] = NULL;
	return (words);
}

static char	**free_all(char **words, int saved)
{
	int	i;

	i = 0;
	while (i < saved)
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (NULL);
}

static void	inner_whiles(char *s, int *i, char c, size_t *slen)
{
	while (*(s + (*i)) == c)
		*i = *i + 1;
	*slen = 0;
	while (*(s + (*i) + (*slen)) != '\0' && *(s + (*i) + (*slen)) != c)
		*slen = *slen + 1;
}

static int	get_total_words(const char *s, char c)
{
	int	total;
	int	i;

	if (!(*s))
		return (0);
	total = 0;
	i = 0;
	if (*s != c)
		total++;
	while (*(s + i))
	{
		if (*(s + i) == c && *(s + i + 1) != c && *(s + i + 1) != '\0')
			total++;
		i++;
	}
	return (total);
}
