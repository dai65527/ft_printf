# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 08:47:29 by dnakano           #+#    #+#              #
#    Updated: 2020/10/18 14:12:58 by dnakano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				:= gcc
CFLAGS			:= -Wall -Werror -Wextra
NAME			:= libftprintf.a
OUTPUTDIR		:= .
OUTPUTS			:= $(addprefix $(OUTPUTDIR)/,$(NAME))
COMMONSRCNAME	:= ft_printf.c ft_printf_util.c ft_printf_putnbr.c\
					ft_printf_findflags.c\
					ft_printf_putbyte.c ft_printf_putstr.c\
					ft_printf_putpadding.c\
					ft_printf_putpercent.c ft_printf_putpointer.c\
					ft_printf_putint.c\
					ft_printf_putint_signed.c ft_printf_putint_unsigned.c
MANDSRCNAME		:= ft_printf_putarg.c
BONUSSRCNAME	:= ft_printf_putarg_bonus.c\
					ft_printf_putfloat_bonus.c ft_store_iflt.c\
					ft_printf_floatutil_bonus.c ft_printf_floatutil2_bonus.c\
					ft_printf_putfloat_f_bonus.c\
					ft_printf_putfloat_e_bonus.c\
					ft_printf_putfloat_g_bonus.c\
					ft_printf_store_n_bonus.c
SRCDIR			:= .
MANDSRCS		:= $(addprefix $(SRCDIR)/,$(MANDSRCNAME))\
					$(addprefix $(SRCDIR)/,$(COMMONSRCNAME))
COMMONOBJNAME	:= $(COMMONSRCNAME:%.c=%.o)
MANDOBJNAME		:= $(MANDSRCNAME:%.c=%.o)
BONUSOBJNAME	:= $(BONUSSRCNAME:%.c=%.o)
OBJDIR			:= $(SRCDIR)
COMMONOBJS		:= $(addprefix $(OBJDIR)/,$(COMMONOBJNAME))
MANDOBJS		:= $(addprefix $(OBJDIR)/,$(MANDOBJNAME))
BONUSOBJS		:= $(addprefix $(OBJDIR)/,$(BONUSOBJNAME))
LIBNAME			:= libft.a
LIBHEADERNAME	:= libft.h
LIBDIR			:= libft
HEADERNAME		:= libftprintf.h
HEADERDIR		:= .
HEADERS			:= $(addprefix $(HEADERDIR)/,$(HEADERNAME))\
					$(addprefix $(LIBDIR)/,$(LIBHEADERNAME))

.SUFFIXES:		.o .c

.PHONY:			all
all:			$(NAME)

$(NAME):		$(COMMONOBJS) $(MANDOBJS) $(HEADERS)
				cd $(LIBDIR)/ && make $(LIBNAME)
				cp $(LIBDIR)/$(LIBNAME) $(OUTPUTDIR)/
				mv $(LIBNAME) $(NAME)
				ar r $(OUTPUTS) $(COMMONOBJS) $(MANDOBJS)

# $(NAME):		$(COMMONOBJS) $(BONUSOBJS) $(HEADERS)
# 				cd $(LIBDIR)/ && make $(LIBNAME)
# 				cp $(LIBDIR)/$(LIBNAME) $(OUTPUTDIR)/
# 				mv $(LIBNAME) $(NAME)
# 				ar r $(OUTPUTS) $(COMMONOBJS) $(BONUSOBJS)

.PHONY:			bonus
bonus:			$(COMMONOBJS) $(BONUSOBJS) $(HEADERS)
				cd $(LIBDIR)/ && make $(LIBNAME)
				cp $(LIBDIR)/$(LIBNAME) $(OUTPUTDIR)/
				mv $(LIBNAME) $(NAME)
				ar r $(OUTPUTS) $(COMMONOBJS) $(BONUSOBJS)

.c.o:
				$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $(patsubst %.c,%.o,$<)

.PHONY:			clean
clean:
				cd $(LIBDIR)/ && make fclean
				rm -f $(COMMONOBJS) $(MANDOBJS) $(BONUSOBJS)

.PHONY:			fclean
fclean:			clean
				cd $(LIBDIR)/ && make fclean
				rm -f $(OUTPUTS)

.PHONY:			re
re:				fclean all
