/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 19:23:44 by atlekbai          #+#    #+#             */
/*   Updated: 2018/08/14 16:37:27 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <wchar.h>
# include <locale.h>
# include <fcntl.h>
# include "pf/ft_printf.h"
# include "get_next_line.h"

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strstr(const char *big, const char *little);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);
size_t			ft_strlcat(char *dst, const char *src, size_t siz);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strcat(char *s1, const char *s2);
void			*ft_memset(void *ptr, int value, size_t num);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memcpy(void *destination, const void *source, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
int				ft_isprint(int c);
int				ft_isdigit(int c);
int				ft_isascii(int c);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
void			ft_bzero(void *s, size_t n);
int				ft_atoi(const char *str);
intmax_t		ft_atoimax(const char *str);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
int				ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(intmax_t n);
int				ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstaddend(t_list *head);
void			ft_nbrendl(intmax_t n);
int				ft_isempty(char const *str);
int				ft_intlen(intmax_t n);
int				ft_isws(char c);
int				ft_intmax(int a, int b);
char			*ft_itoa_base(long long value, int base);
char			*ft_itoa_base_u(uintmax_t value, int base);
wchar_t			*ft_wstrsub(wchar_t const *s, unsigned int start, size_t len);
wchar_t			*ft_wstrnew(size_t size);
wchar_t			*ft_wstrdup(wchar_t *src);
int				ft_wstrlen(wchar_t *str);
int				ft_charlen(wchar_t c);
int				ft_putsymbol(wchar_t c);
int				ft_putstrw(const wchar_t *str);
void			ft_wstrdel(wchar_t **as);
void			ft_strupcase(char *str);
void			ft_print2darr(char **matrix);
void			ft_print2dintarr(int **matrix, int len);
void			ft_print1dintarr(int *arr, int len);
char			**ft_create2darr(int n, int x);
int				**ft_create2dintarr(int n, int x);
void			ft_intcpy(int *arr1, const int *arr2, size_t n);
void			ft_del2darr(char **arr);
int				ft_2darrlen(char **arr);
char			*ft_strresub(char const *s, unsigned int start, size_t len);
long long		ft_atoi_base(const char *str, int str_base);
#endif
