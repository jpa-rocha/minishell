/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_other_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:48:10 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/05 12:30:27 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/* finds  dollar sign in the string
 + if env comes after we need to get env variable
 + if ? comes after we need to get exit status of the previous command call
 + if '$ENV' prints $ENV but if "$ENV" , print env variable
 + same also for $?
 */
/* char	*check_d_sign(char *str)
{
	int	i;
	i = 0;
	while (str[i])
	{
		if (str[i] == DOLLAR)
			return (&str[i]);
		i++;	
	}
	return (0);
} */