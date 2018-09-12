/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_dspec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 23:55:30 by zshanabe          #+#    #+#             */
/*   Updated: 2018/08/14 16:42:10 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		make_output_d(intmax_t num, t_item *form)
{
	char *str;

	if (form->space)
	{
		ft_putchar_fd(' ', form->fd);
		(form->count)++;
	}
	if (form->order == 1)
		ft_putchar_fd(form->sign, form->fd);
	if (form->pad > 0 && form->minus == false)
		ft_putstr_fd(form->pad_str, form->fd);
	if (form->order == 2)
		ft_putchar_fd(form->sign, form->fd);
	if (form->zer > 0)
		ft_putstr_fd(form->zer_str, form->fd);
	if (form->order == 3)
		ft_putchar_fd(form->sign, form->fd);
	str = ft_itoa_max(num);
	if (num < 0)
		ft_putstr_fd(str + 1, form->fd);
	else if (num != 0 || form->zer != 0)
		ft_putstr_fd(str, form->fd);
	if (form->pad > 0 && form->minus == true)
		ft_putstr_fd(form->pad_str, form->fd);
	free(str);
}

void			ft_analyze_d(intmax_t num, t_item *form)
{
	int len;

	len = ft_intlen(num);
	if (num < 0)
	{
		len--;
		form->sign = '-';
	}
	if (form->plus && form->sign != '-')
		form->sign = '+';
	if (form->zero && form->zer != -1)
		form->zero = false;
	if (form->sign == '+' || form->sign == '-')
		form->space = false;
	form->zer = calculate_zeros(len, form);
	form->pad = calculate_padding(len, form);
	if (form->zer == 0 && num == 0 && form->pad > 0)
		form->pad++;
	create_output(form);
	if (form->sign == '+' || form->sign == '-')
		ft_sign_order(form);
	make_output_d(num, form);
	count_return_value(form, (num == 0) ? 1 : 0, ft_intlen(num));
}
