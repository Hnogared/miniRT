/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:42:43 by hnogared          #+#    #+#             */
/*   Updated: 2023/06/06 22:32:43 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/libft.h"

static int	ft_get_wordcnt(char const *s, char const *set)
{
	int	i;
	int	cnt;
	int	in_word;

	i = 0;
	cnt = 0;
	in_word = 0;
	while (s[i])
	{
		if (!ft_strchr(set, s[i]) && in_word == 0)
		{
			cnt++;
			in_word = 1;
		}
		if (ft_strchr(set, s[i]) && in_word != 0)
			in_word = 0;
		i++;
	}
	return (cnt);
}

static char	*ft_strndup(const char *str, int n)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i] && i < n)
		i++;
	dup = (char *) malloc((i + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	**ft_split_set(char const *s, char const *set)
{
	int		i;
	int		start;
	int		word_cnt;
	char	**words_tab;

	if (!s)
		return (NULL);
	words_tab = (char **) malloc((ft_get_wordcnt(s, set) + 1) * sizeof(char *));
	if (!words_tab)
		return (NULL);
	i = 0;
	word_cnt = 0;
	while (s[i])
	{
		start = i;
		while (!ft_strchr(set, s[i]) && s[i])
			i++;
		if (start != i)
			words_tab[word_cnt++] = ft_strndup(s + start, i - start);
		if (s[i])
			i++;
	}
	words_tab[word_cnt] = NULL;
	return (words_tab);
}
