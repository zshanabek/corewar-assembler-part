/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhunissali <zhunissali@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 23:56:16 by zshanabe          #+#    #+#             */
/*   Updated: 2018/08/15 07:57:19 by zhunissali       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft.h"
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <wchar.h>
# include <locale.h>
# include <limits.h>
# include <string.h>

typedef struct	s_item
{
	int		fd;
	int		count;
	int		plus;
	int		space;
	int		minus;
	int		zero;
	int		hash;
	int		prefix;
	int		zer;
	int		pad;
	int		order;
	int		doubled;
	char	sign;
	char	spec;
	char	size;
	char	*hex_sign;
	char	*pad_str;
	char	*zer_str;
}				t_item;

int				ft_printf(int fd, const char *format, ...);
int				calculate_zeros(int len, t_item *form);
int				calculate_padding(int len, t_item *form);
int				is_specifier(char c);
int				is_modifier(char c);
int				is_flag(char c);
void			ft_analyze_d(intmax_t n, t_item *form);
void			ft_analyze_ls(wchar_t *str, t_item *form);
void			ft_analyze_s(char *str, t_item *form);
void			ft_analyze_u(uintmax_t n, t_item *form);
void			ft_analyze_c(wint_t c, t_item *form);
void			ft_analyze_percent(t_item *form);
void			ft_sign_order(t_item *form);
void			create_output(t_item *form);
char			*ft_itoa_max(intmax_t n);
wint_t			find_length_c(va_list ap, t_item *form);
t_item			*create_struct();
intmax_t		find_length(va_list ap, t_item *form);
uintmax_t		find_length_u(va_list ap, t_item *form);
void			count_return_value(t_item *form, int num, int len);
int				identify_color(const char *s, int fd, int i);
void			ft_format(const char *f, int fd, int *i, int *count);
#endif
