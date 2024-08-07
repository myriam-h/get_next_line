#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_list
{
    char *s;
    struct s_list *next;
} t_list;

char *get_next_line(int fd);
void read_reserve(int fd, t_list **reserve);
void add_to_reserve(t_list **reserve, char *buff, int read_char);
void get_line(t_list *reserve, char **line);
void free_reserve(t_list **reserve);
void create_line(t_list *reserve, char **line);
void clean_reserve(t_list *reserve);
int newline_is_found(t_list *reserve);
int ft_strlen(const char *str);
t_list  *get_last_element(t_list *reserve);

#endif