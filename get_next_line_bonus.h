#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define MAX_FD 4096 
//system’s hard limit for the number of open file descriptors is 4096

# include <unistd.h> //read()
# include <fcntl.h> //open()
# include <stdlib.h> // malloc
# include <stdio.h> //printf

typedef struct s_list
{
    char *str_buf;
    struct s_list *next;
}t_list;





#endif