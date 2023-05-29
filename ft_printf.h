/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:17:40 by sgodin            #+#    #+#             */
/*   Updated: 2023/05/29 13:08:40 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *s, ...);
void	ft_putnbr2(int nb);
int		ft_putnbr(int nb);
int		ft_nbrlen(int nb);
int		format(char *c, va_list vl);
int		ft_putstr(char *str);
size_t	ft_strlen(const char *str);

#endif