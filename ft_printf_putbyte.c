/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putbyte.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 11:52:05 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/12 12:18:05 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

int			ft_printf_putbyte(va_list ap, t_printf_flags *flags)
{
	char	c;

	if (flags->width == -1)
		flags->width = 0;
	if (flags->flag & FLAG_WIDTH_NEXTARG)
		flags->width = va_arg(ap, int);
	if (flags->flag & FLAG_PRECISION_NEXTARG)
		flags->precision = va_arg(ap, int);
	c = va_arg(ap, int);
	if (flags->flag & FLAG_LEFTADJUST)
		write(1, &c, 1);
	ft_printf_putpadding(flags->width - 1, flags);
	if (!(flags->flag & FLAG_LEFTADJUST))
		write(1, &c, 1);
	return (flags->width ? flags->width : 1);
}
