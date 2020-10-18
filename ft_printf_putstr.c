/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:26:26 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/18 13:00:54 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"

int			ft_printf_putstr(va_list ap, t_printf_flags *flags)
{
	int			len;
	char		*s;
	const char	strnull[] = "(null)";

	s = (char *)va_arg(ap, t_ullong);
	if (!s)
		s = (char *)strnull;
	len = ft_strlen(s);
	if (flags->precision >= 0)
	{
		if (flags->precision < len)
			len = flags->precision;
	}
	if (len < flags->width && !(flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - len, flags);
	ft_putstrn_fd(s, 1, len);
	if (len < flags->width && (flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - len, flags);
	return (len < flags->width ? flags->width : len);
}
