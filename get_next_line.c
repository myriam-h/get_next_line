#include "get_next_line.h"

char *get_next_line(int fd)
{
    static t_list *reserve = NULL;
    
    char *line;
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
        return NULL;
    line = NULL;
    read_reserve(fd, &reserve);
    if (reserve == NULL)
        return (NULL);
    get_line(reserve, &line);
    free_reserve(&reserve);
    if (line[0] == '\0')
    {
        clean_reserve(reserve);
        reserve = NULL;
        free(line);
        return (NULL);
    }
    return (line);
}

void read_reserve(int fd, t_list **reserve)
{
    char *buff;
    int read_char;

    read_char = 1;
    while (!newline_is_found(*reserve) && read_char != 0)
    {
       buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if (buff == NULL)
           return ;
        read_char = (int)read(fd, buff, BUFFER_SIZE);
        if ((*reserve == NULL && read_char == 0) || read_char == -1)
        {
            free(buff);
            return ;
        }
        buff[read_char] = '\0';
        add_to_reserve(reserve, buff, read_char);
        free(buff);
    }
}

void add_to_reserve(t_list **reserve, char *buff, int read_char)
{
    int i;
    t_list* recent;
    t_list* new_element;

    new_element = malloc(sizeof(t_list));
    if (new_element == NULL)
        return ;
    new_element->next = NULL;
    new_element->s = malloc(sizeof(char) * (read_char + 1));
    if (new_element->s == NULL)
        return ;
    i = 0;
    while (buff[i] && i < read_char)
    {
        new_element->s[i] = buff[i];
        i++;
    }
    new_element->s[i] = '\0';
    if (*reserve == NULL)
    {
        *reserve = new_element;
        return ;
    }
    recent = get_last_element(*reserve);
    recent->next = new_element;
}

void get_line(t_list *reserve, char **line)
{
    int i;
    int j;
    
    j = 0;
    if (reserve == NULL)
        return ;
    create_line(reserve, line);
    if (*line == NULL)
        return ;
    while (reserve)
    {
        i = 0;
        while (reserve->s[i])
        {
           
            if (reserve->s[i] == '\n')
            {
                (*line)[j++] = reserve->s[i];
                break;
            }
            (*line)[j++] = reserve->s[i++];
        }
        reserve = reserve->next;
    }
    (*line)[j] = '\0';
}

void free_reserve(t_list **reserve)
{
    t_list  *recent;
    t_list  *clean_element;
    int i;
    int j;
    
    clean_element = malloc(sizeof(t_list));
    if (reserve == NULL || clean_element == NULL)
        return ;
    clean_element->next = NULL;
    recent = get_last_element(*reserve);
    i = ft_strlen(recent->s);
    while (recent->s[i])
        i++;
    clean_element->s = malloc(sizeof(char) * ((i - ft_strlen(recent->s)) + 1));
    if (clean_element->s == NULL)
        return ;
    j = 0;
    i = ft_strlen(recent->s);
    while (recent->s[i])
        clean_element->s[j++] = recent->s[i++];
    clean_element->s[j] = '\0';
    clean_reserve(*reserve);
    *reserve = clean_element;
}