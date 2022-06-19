/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <hjrifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:47:45 by hjrifi            #+#    #+#             */
/*   Updated: 2022/05/30 17:47:48 by hjrifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/utiles_functions.h"

unsigned int  ft_strlen(char *src)
{
    unsigned int    i;

    i = 0;
    while(src && src[i])
        i++;
    return(i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	lendst;
	size_t	len_s;

	j = 0;
	len_s = 0;
	lendst = ft_strlen(dst);
	i = ft_strlen(dst); 
	while (src[len_s] != '\0')
		len_s++;
	if (dstsize == 0 || dstsize <= lendst)
		return (dstsize + len_s);
	while (src[j] && ((dstsize - lendst > 1)))
	{
		dst[i] = src[j];
		i++;
		j++;
		dstsize--;
	}
	dst[i] = '\0';
	return (lendst + len_s);
}

char	*ft_h_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		len;
	int		len1;

	if (s2 == NULL)
		return ((char *)s1);
	len = ft_strlen((char *)s1);
	len1 = ft_strlen((char *)s2);
	ptr = (char *)malloc(sizeof(char) * (len + len1 + 1));
	if (!ptr)
		return (NULL);
	*ptr = '\0';
    if (s1)
	    ft_strlcat(ptr, (char *)s1, len + 1);
	ft_strlcat(ptr, (char *)s2, len + len1 + 1);
	if (s1)
		free(s1);
	return (ptr);
}

char	*ft_strdup(char *s1)
{
	char	*ptr;
	int		i;
	int		len_s1;

	len_s1 = ft_strlen((char *)s1);
	i = 0;
	ptr = (char *)malloc(len_s1 * sizeof(char) + 1);
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char **ft_realloc_char(char **str)
{
	char  **tab;
	int		i;
	
	i = 0;
	while(str[i])
		i++;
	tab = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (str[i])
	{
		tab[i] = ft_strdup(str[i]);
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	tab[i + 1] = NULL;
	return (tab);
}

int *ft_realloc_int(int *tab, char **str)
{
	int		i;
	int  	*new_tab;

	i = 0;
	while(str[i])
		i++;
	new_tab = malloc(sizeof(int *) * i);
	i = 0;
	while (str[i])
	{
		new_tab[i] = tab[i];
		i++;
	}
	free(tab);
	return (new_tab);
}
