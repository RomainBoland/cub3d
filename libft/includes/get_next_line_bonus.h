/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:50:11 by rboland           #+#    #+#             */
/*   Updated: 2025/01/30 10:52:43 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif
# if BUFFER_SIZE > 100000
#  undef BUFFER_SIZE
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

void		*ft_memcpy(void *dst, const void *src, size_t size);
size_t		ft_strlen_gnl(const char *str);
char		*ft_strjoin_gnl(char *s1, const char *s2);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup_gnl(char *src);
char		*get_next_line(int fd);

#endif