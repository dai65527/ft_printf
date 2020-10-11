/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 12:01:52 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/11 16:16:52 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

# define FLAG_ZEROPADDING 0x00000001
# define FLAG_LEFTADJUST 0x00000010
# define FLAG_WIDTH_NEXTARG 0x00000100
# define FLAG_PRECISION_NEXTARG 0x00001000

typedef	struct	s_printf_flags
{
	int			flag;
	int			width;
	int			precision;
}				t_printf_flags;

int				ft_printf(const char *format, ...);

char			*ft_printf_findflags(const char *format, t_printf_flags *flags);

char			*ft_printf_putarg(const char *format, va_list ap, int *count);
int				ft_printf_putpercent(va_list ap, t_printf_flags *flags);
int				ft_printf_putint(char fc, va_list ap, t_printf_flags *flags);

void			ft_printf_putpadding(int width, t_printf_flags *flags);

#endif
