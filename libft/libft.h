/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:45:25 by jheat             #+#    #+#             */
/*   Updated: 2020/10/19 17:45:16 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define INT_MIN -2147483648

# include "../minishell.h"

void					*ft_memcpy(void *dest, const void *src, size_t n);
size_t					ft_strlen(const char *s);
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_atoi(const char *nptr);
int						ft_isdigit(int c);
char					*ft_strdup(const char *s);
char					*ft_strjoin(char const *s1, char const *s2);
char					**ft_split(char const *s, char c);
char					*ft_itoa(int n);
void					ft_putchar_fd(char c, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					addback(t_list **lst, t_list *new);
t_list					*lstnew(void *content);

#endif
