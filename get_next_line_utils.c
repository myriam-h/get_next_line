#include "get_next_line.h"

int newline_is_found(t_list *reserve)
{
    int j;
    t_list *current;
   
    if (reserve == NULL)
        return (0);
    current = get_last_element(reserve);
    j = 0;
    while (current->s[j])
    {
        if (current->s[j] == '\n')
            return (1);
        j++;
    }
    return (0);
}

t_list *get_last_element(t_list *reserve)
{
    t_list *current;

    current = reserve;
    while (current && current->next)
        current = current->next;
    return (current);
}

void create_line(t_list *reserve, char **line)
{
    int size;

    size = 0;
    while (reserve)
    {
        size += ft_strlen(reserve->s);
        reserve = reserve->next;
    }
    *line = malloc(sizeof(char) * (size + 1));
}

void clean_reserve(t_list *reserve)
{
    t_list *current;
    t_list *next;

    current = reserve;
    while (current)
    {
        free(current->s);
        next = current->next;
        free(current);
        current = next;
    }
}

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
        {
            i++;
            break;
        }
        i++;
    }
    return (i);
}