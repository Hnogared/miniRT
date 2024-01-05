/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:11:48 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/04 21:38:10 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>

# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	127
# endif

# ifndef ERROR
#  define ERROR	1
# endif

/* MANDATORY */
/*
 * Function to check if a character is alphabetic [a-zA-Z] or numeric [0-1].
 *
 * @param int c	-> character to check
 * @return int	-> 1 if true | 0 if false
 */
int		ft_isalnum(int c);

/*
 * Function to check if a character is alphabetical [a-zA-Z].
 *
 * @param int c	-> character to check
 * @return int	-> 1 if true | 0 if false
 */
int		ft_isalpha(int c);

/*
 * Function to check if a character is within the ascii table.
 *
 * @param int c	-> character to check
 * @return int	-> 1 if true | 0 if false
 */
int		ft_isascii(int c);

/*
 * Function to check if a character is a number [0-9].
 *
 * @param int c	-> character to check
 * @return int	-> 1 if true | 0 if false
 */
int		ft_isdigit(int c);

/*
 * Function to check if a character is displayable.
 *
 * @param int c	-> character to check
 * @return int	-> 1 if true | 0 if false
 */
int		ft_isprint(int c);

/*
 * Function to check if a character is a whitespace.
 *
 * @param int c	-> character to check
 * @return int	-> 1 if true | 0 if false
 */
int		ft_iswhitespace(int c);

/*
 * Function to change an alphabetical character to the lowercase.
 *
 * @param int c	-> character to change
 * @return int	-> the resulting character
 */
int		ft_tolower(int c);

/*
 * Function to change an alphabetical character to the uppercase.
 *
 * @param int c	-> character to change
 * @return int	-> the resulting character
 */
int		ft_toupper(int c);

/*
 * Function to convert a string into a float.
 * Whitespaces present at the beginning of the string are skipped. The conversion
 * ends at the last number character, the following ones are ignored.
 *
 * @param const char *nptr	-> pointer to the string to convert
 * @return float			-> the resulting float conversion
 *
 * @child_func is_neg		-> function to check if a string starts with '-'
 * @child_func create_nbr	-> function to convert a trimmd string into a float
 */
float	ft_atof(const char *nptr);

/*
 * Function to convert an untrimmed string into an int.
 * Whitespaces at the beginning of the string are skipped. The conversion ends
 * at the last digit of the number, following characters ar ignored.
 *
 * @param const char *nptr	-> pointer to the strong to convert
 * @return int				-> the resulting converted integer
 */
int		ft_atoi(const char *nptr);

/*
 * Function to convert an integer into an allocated string.
 *
 * @param int n		-> integer to convert
 * @return char *	-> teh resulting allocated string
 *
 * @child_func get_num_len -> function to get the character length of an int
 */
char	*ft_itoa(int n);

/*
 * Function to convert and store an integer inside a buffer array string.
 *
 * @param int n			-> the integer to store
 * @param char *buf		-> pointer to the array string to store the int into
 * @param size_t bufsize-> size in bytes of the buffer to store the int into
 * @return size_t		-> character size of the number saved inside the buffer
 *
 * @child_func get_num_len	-> function to get the character length of an int
 */
size_t	ft_itoab(int n, char *buf, size_t bufsize);

int		ft_min(int n1, int n2);
int		ft_max(int n1, int n2);
float	ft_fmin(float n1, float n2);
float	ft_fmax(float n1, float n2);

int		ft_strncmp(const char *str, const char *str2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t n);

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchrnul(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t n);
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, size_t size);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	**ft_split(char const *s, char c);
char	**ft_split_set(char const *s, char const *set);

void	ft_bzero(void *s, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

/* BONUS */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int		ft_lstsize(t_list *lst);

void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

/* PRINTF */
int		ft_printf(const char *str, ...);
int		ft_fprintf(int fd, const char *str, ...);

int		ft_check_char(const char c, const char *set);
int		ft_check_input(const char *input);

int		ft_print_input(char *input, va_list args, int fd);
int		ft_print_nbrconv(const char conv, va_list args, int fd);
int		ft_print_chrconv(const char conv, va_list args, int fd);

int		ft_putchar_fdout(char c, int fd);
int		ft_putstr_fdout(char *s, int fd);
int		ft_putnbr_fdout(int n, int len, int fd);
int		ft_putunsigned_fdout(unsigned int n, int len, int fd);
int		ft_puthex_fdout(unsigned long n, int len, char cap, int fd);

int		ft_putnbits_fdout(int nbr, int fd);

/* GET_NEXT_LINE */
char	*get_next_line(int fd);
#endif
