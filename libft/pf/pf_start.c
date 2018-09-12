/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhunissali <zhunissali@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 23:55:10 by zshanabe          #+#    #+#             */
/*   Updated: 2018/08/15 07:56:45 by zhunissali       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		identify_spec(t_item *form, va_list ap)
{
	if (form->spec == 'd' || form->spec == 'i' || form->spec == 'D')
		ft_analyze_d(find_length(ap, form), form);
	else if (form->spec == 'o' || form->spec == 'x' || form->spec == 'u')
		ft_analyze_u(find_length_u(ap, form), form);
	else if (form->spec == 'p' || form->spec == 'X')
		ft_analyze_u(find_length_u(ap, form), form);
	else if (form->spec == 'O' || form->spec == 'U')
		ft_analyze_u(va_arg(ap, unsigned long int), form);
	else if (form->spec == 'S' || (form->spec == 's' && form->size == 'l'))
		ft_analyze_ls(va_arg(ap, wchar_t *), form);
	else if (form->spec == 's')
		ft_analyze_s(va_arg(ap, char *), form);
	else if (form->spec == 'c' || form->spec == 'C')
		ft_analyze_c(find_length_c(ap, form), form);
	else if (form->spec == '%')
		ft_analyze_percent(form);
	else
		ft_analyze_c(form->spec, form);
}

static int		ft_flags(const char *format, int i, t_item *form)
{
	i++;
	while (is_flag(format[i]))
	{
		form->minus = (form->minus || format[i] == '-') ? 1 : 0;
		form->zero = ((form->zero || format[i] == '0')
		&& form->minus == 0) ? 1 : 0;
		form->plus = (form->plus || format[i] == '+') ? 1 : 0;
		form->space = ((form->space || format[i] == ' ')
		&& form->plus == 0) ? 1 : 0;
		form->prefix = (form->prefix || format[i] == '#') ? 1 : 0;
		i++;
	}
	return (i);
}

static int		get_inform(const char *format, int i, t_item *form)
{
	i = ft_flags(format, i, form);
	while (ft_isdigit(format[i]))
		form->pad = form->pad * 10 + (format[i++] - '0');
	if (format[i] == '.')
	{
		i++;
		form->zer = 0;
		while (ft_isdigit(format[i]))
			form->zer = form->zer * 10 + (format[i++] - '0');
	}
	if (is_modifier(format[i]))
	{
		form->size = format[i];
		i++;
	}
	if (!is_specifier(format[i]) && format[i] == form->size)
	{
		form->doubled = 1;
		i++;
	}
	form->spec = format[i];
	return (i);
}

static int		go_str(int i, t_item *form, va_list ap, const char *f)
{
	i = get_inform(f, i, form);
	if (form->spec == '\0')
		i = -2;
	if (i != -2)
		identify_spec(form, ap);
	if (form->count == -1)
		i = -1;
	if (form->pad > 0)
		free(form->pad_str);
	if (form->zer > 0)
		free(form->zer_str);
	free(form);
	form = NULL;
	return (i);
}

int				ft_printf(int fd, const char *format, ...)
{
	int			i;
	int			count;
	t_item		*form;
	va_list		ap;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i])
	{
		ft_format(format, fd, &i, &count);
		if (format[i] == '%')
		{
			form = create_struct(fd, count);
			if ((i = go_str(i, form, ap, format)) == -1)
				return (-1);
			else if (i == -2)
				return (form->count);
			count += form->count;
		}
		i++;
	}
	va_end(ap);
	return (count);
}
