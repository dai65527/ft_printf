/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:26:26 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/13 15:39:04 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "libftprintf.h"

size_t		ft_putstrn_fd(char *s, int fd, size_t n)
{
	size_t	count;

	count = 0;
	while (s[count] && count < n)
		write(fd, s + count++, 1);
	return (count);
}

int			ft_printf_putstr(va_list ap, t_printf_flags *flags)
{
	int			len;
	char		*s;
	const char	strnull[] = "(null)";

	ft_printf_getwidth_prec(ap, flags);
	s = (char *)va_arg(ap, t_ullong);
	if (!s)
		s = (char *)strnull;
	len = ft_strlen(s);
	if (flags->precision >= 0)
	{
		flags->flag = flags->flag & ~FLAG_ZEROPADDING;
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
