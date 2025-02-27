/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:41:25 by sravizza          #+#    #+#             */
/*   Updated: 2024/10/17 14:55:30 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//char_is_to
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
//str
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t n);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *str, unsigned int start, size_t len);
char	*ft_strjoin(char const *str1, char const *str2);
char	*ft_strtrim(char const *str, char const *set);
char	**ft_split(char const *str, char c);
char	*ft_strmapi(char const*str, char (*ft)(unsigned int, char));
void	ft_striteri(char *str, void (*ft)(unsigned int, char*));
//mem
void	*ft_memset(void *str, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
//other
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	*ft_calloc(size_t nel, size_t elsize);
void	ft_bzero(void *str, size_t n);
//put_fd
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putnbr_fd(int nbr, int fd);

#endif 