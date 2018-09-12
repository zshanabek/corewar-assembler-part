/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_spec_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 23:55:37 by zshanabe          #+#    #+#             */
/*   Updated: 2018/08/14 17:02:26 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_analyze_c(wint_t c, t_item *form)
{
	int		size;

	size = 1;
	if (c != 0 && (form->spec == 'C' || form->size == 'l'))
		size = ft_charlen(c);
	form->pad = form->pad - size;
	create_output(form);
	if (form->minus == false && form->pad > 0)
		ft_putstr_fd(form->pad_str, form->fd);
	if (form->spec != 'C' && form->size != 'l')
		ft_putchar_fd(c, form->fd);
	else if (ft_putsymbol(c) == -1)
		form->count = -1;
	if (form->minus == true && form->pad > 0)
		ft_putstr_fd(form->pad_str, form->fd);
	if (form->count != -1)
	{
		if (form->pad >= 0)
			form->count += form->pad;
		form->count += size;
	}
}

void	ft_analyze_percent(t_item *form)
{
	form->pad = form->pad - 1;
	create_output(form);
	if (form->minus == false && form->pad > 0)
		ft_putstr_fd(form->pad_str, form->fd);
	ft_putchar_fd('%', form->fd);
	if (form->minus == true && form->pad > 0)
		ft_putstr_fd(form->pad_str, form->fd);
	if (form->pad >= 0)
		form->count += form->pad;
	form->count += 1;
}

void	ft_analyze_ls(wchar_t *str, t_item *form)
{
	wchar_t		*output;
	wchar_t		*temp;

	if (str == NULL)
		output = ft_wstrdup(L"(null)");
	else
		output = ft_wstrdup(str);
	if (form->zer >= 0)
	{
		temp = output;
		output = ft_wstrsub(output, 0, form->zer);
		free(temp);
	}
	form->pad = calculate_padding(ft_wstrlen(output), form);
	create_output(form);
	if (form->minus == false && form->pad > 0)
		ft_putstr_fd(form->pad_str, form->fd);
	if (ft_putstrw(output) == -1)
		form->count = -1;
	if (form->minus == true && form->pad > 0)
		ft_putstr_fd(form->pad_str, form->fd);
	if (form->count != -1)
		count_return_value(form, 0, ft_wstrlen(output));
	free(output);
}

void	ft_analyze_s(char *str, t_item *form)
{
	char *output;
	char *temp;

	if (str == NULL)
		output = ft_strdup("(null)");
	else
		output = ft_strdup(str);
	if (form->zer >= 0)
	{
		temp = output;
		output = ft_strsub(output, 0, form->zer);
		free(temp);
	}
	form->pad = calculate_padding(ft_strlen(output), form);
	create_output(form);
	if (form->minus == false && form->pad > 0)
		ft_putstr_fd(form->pad_str, form->fd);
	ft_putstr_fd(output, form->fd);
	if (form->minus == true && form->pad > 0)
		ft_putstr_fd(form->pad_str, form->fd);
	if (form->pad >= 0)
		form->count += form->pad;
	form->count += ft_strlen(output);
	free(output);
}
