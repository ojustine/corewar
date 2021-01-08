/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojustine <ukelly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:01:34 by ojustine          #+#    #+#             */
/*   Updated: 2020/11/26 12:04:11 by ukelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stddef.h>

size_t	ft_strlen(const char *s);
size_t	ft_strnlen(const char *s, size_t maxlen);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_words_count(char const *s, char c);
size_t	ft_chars_count(const char *str, const char c);
char	**ft_strsplit(char const *s, char c);
void	*ft_free_split(char **split);
int		ft_strequ(char const *s1, char const *s2);
int		ft_isint(char *str);

#endif
