/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putpointer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 10:13:09 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/12 11:30:51 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "libftprintf.h"

int			ft_printf_putpointer(va_list ap, t_printf_flags *flags)
{
	int					nbrwidth;
	unsigned long long	pt;

	if (flags->flag & FLAG_WIDTH_NEXTARG)
		flags->width = va_arg(ap, int);
	if (flags->flag & FLAG_PRECISION_NEXTARG)
		flags->precision = va_arg(ap, int);
	pt = va_arg(ap, unsigned long long);
	nbrwidth = 2 + ((pt == 0 && flags->precision == 0)
		? 0 : ft_printf_putnbr_width_digit(pt, 16, flags->precision));
	if (flags->precision >= 0)
		flags->flag = flags->flag & ~FLAG_ZEROPADDING;
	if (nbrwidth < flags->width && !(flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	if (!(pt == 0 && flags->precision == 0))
	{
		write(1, "0x", 2);
		ft_printf_putnbr_unsigned_base_digit(pt, 16, flags->precision, 0);
	}
	if (nbrwidth < flags->width && (flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	return (nbrwidth < flags->width ? flags->width : nbrwidth);
}
