/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putpointer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 10:13:09 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/13 15:38:46 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "libftprintf.h"

int			ft_printf_putpointer(va_list ap, t_printf_flags *flags)
{
	int			nbrwidth;
	t_ullong	pt;

	ft_printf_getwidth_prec(ap, flags);
	pt = va_arg(ap, t_ullong);
	nbrwidth = 2 + ft_printf_putnbr_unsigned_width_digit(pt, 16, flags);
	if (flags->precision >= 0)
		flags->flag = flags->flag & ~FLAG_ZEROPADDING;
	if (nbrwidth < flags->width && !(flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	write(1, "0x", 2);
	if (!(pt == 0 && flags->precision == 0))
		ft_printf_putnbr_unsigned_base_digit(pt, 16, flags->precision, 0);
	if (nbrwidth < flags->width && (flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	return (nbrwidth < flags->width ? flags->width : nbrwidth);
}
