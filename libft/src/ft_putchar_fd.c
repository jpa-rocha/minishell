/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:44:44 by jrocha            #+#    #+#             */
/*   Updated: 2021/12/21 10:45:35 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// The ft_putchar_fd() function writes the given char to the selected
// file descriptor.
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
