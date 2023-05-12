/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 04:43:17 by himejjad          #+#    #+#             */
/*   Updated: 2023/05/12 05:48:42 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOFER_H
# define PHILOSOFER_H



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


typedef struct p_threads{
	int ac;
    int *array;

}t_threads;

void	ft_error(void);
int	ft_strlen(char *s);
void	ft_check_numbers(char *str, int i);
int	ft_atoi(char *str);
char	*ft_strjoin(char	*s1, char	*s2);
char	**ft_split(char *s, char c);
char	**get_stock2(char **av);


# endif