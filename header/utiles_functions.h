/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_functions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:47:36 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/04 14:26:46 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILES_FUNCTIONS_H
#define UTILES_FUNCTIONS_H

# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>


//unsigned int  ft_strlen(char *src);
char	*ft_h_strjoin(char *s1, char *s2);
char	*ft_strdup( char *s1);
char    **ft_realloc_char(char **str);
int     *ft_realloc_int(int *tab, char **str);

#endif
