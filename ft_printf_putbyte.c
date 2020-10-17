/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putbyte.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 11:52:05 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/17 09:06:38 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

int			ft_printf_putbyte(va_list ap, t_printf_flags *flags)
{
	t_uchar	c;

	if (flags->width == -1)
		flags->width = 0;
	ft_printf_getwidth_prec(ap, flags);
	c = (t_uchar)va_arg(ap, t_ullong);
	if (flags->flag & FLAG_LEFTADJUST)
		write(1, &c, 1);
	ft_printf_putpadding(flags->width - 1, flags);
	if (!(flags->flag & FLAG_LEFTADJUST))
		write(1, &c, 1);
	return (flags->width ? flags->width : 1);
}
