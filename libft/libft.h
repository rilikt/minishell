/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:19:31 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/16 12:51:55 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

extern size_t	ft_strlen(const char *str);
extern int		ft_atoi(const char *str);
extern void		ft_bzero(void *s, size_t n);
extern void		*ft_calloc(size_t num, size_t size);
extern int		ft_isalnum(int c);
extern int		ft_isascii(int c);
extern void		*ft_memchr(const void *buf, int c, size_t count);
extern int		ft_memcmp(const void *buffer, const void *buffer2,
					size_t count);
extern void		*ft_memcpy(void *dest, const void *src, size_t n);
extern void		*ft_memmove(void *dest, const void *src, size_t count);
extern void		*ft_memset(void *dest, int c, size_t len);
extern int		ft_isalpha(int c);
extern int		ft_isdigit(int c);
extern int		ft_isprint(int c);
extern char		*ft_strchr(const char *str, int c);
extern char		*ft_strdup(const char *src);
extern size_t	ft_strlcat(char *dest, const char *source, size_t size);
extern size_t	ft_strlcpy(char *dest, char *src, size_t size);
extern int		ft_tolower(int C);
extern int		ft_strncmp(const char *s1, const char *s2, size_t n);
extern char		*ft_strnstr(const char *str, const char *find, size_t count);
extern char		*ft_substr(char const *s, unsigned int start, size_t len);
extern char		*ft_strtrim(char const *s1, char const *set);
extern char		**ft_split(char const *s, char c);
extern char		*ft_itoa(int n);
extern void		ft_putnbr_fd(int n, int fd);
extern void		ft_putchar_fd(char c, int fd);
extern void		ft_putendl_fd(char *s, int fd);
extern int		ft_toupper(int c);
extern char		*ft_strrchr(const char *str, int c);
extern char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
extern char		*ft_strjoin(char const *s1, char const *s2);
extern void		ft_striteri(char *s, void (*f)(unsigned int, char *));
extern void		ft_putstr_fd(char *s, int fd);

#endif