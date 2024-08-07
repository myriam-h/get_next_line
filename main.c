#include "get_next_line.h"

int main()
{
    int fd;
    char *line;
    
    fd = open("file.txt", O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break;
        printf("%s", line);
        free(line);
    }
}