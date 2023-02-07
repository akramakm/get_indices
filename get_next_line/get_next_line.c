/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 19:04:02 by mac               #+#    #+#             */
/*   Updated: 2023/02/07 19:24:21 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int ft_strlen(char *s)
{
    int i = 0;
    while(s[i])
        i++;
    return(i);
}

char *ft_strchr(char *s , int c)
{
    int i = 0;
    while(s[i])
    {
        if ( s[i] == c)
            return((char *) (s + i));
        i++;
    }
    return 0;
}
char *ft_strjoin(char *s1,char *s2)
{
    char *str;
    if(s1 ==  NULL)
        s1 = "";
    str  = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!str)
        return NULL;
    int i = 0;
    while(s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    int x = 0;
    while(s2[x])
    {
        str[i] = s2[x];
        i++;
        x++;
    }
    str[i]  = '\0';
    return(str);
}

char *read_line(int fd,char *text)
{
    char *buffer;
    int k;
    buffer = (char *)malloc(BUFFER_SIZE + 1);
    if(!buffer)
        return NULL;
    k = 1;
    while(!ft_strchr(text,'\n') && k != 0)
    {
        k = read(fd,buffer,BUFFER_SIZE);
        if( k == -1)
            return NULL;
        buffer[k] = '\0';
        text = ft_strjoin(text,buffer);
        // printf("%s\n",text);
    }
    return(text);
}

char *get_line_no_back_n(char *txt)
{
    int i = 0;
    while(txt[i] != '\0' && txt[i] != '\n')
        i++;
    if(txt[i] == '\n')
        i++;
    char *line;
    line = (char *)malloc(i + 1);
    int k = 0;
    while(k <= i)
    {
        line[k] = txt[k];
        k++;
    }
    line[k] = '\0';
    return(line);
}

char *get_save(char *txt)
{
    int i = 0;
    while(txt[i] != '\n' && txt[i] != '\0') 
        i++;
    if (txt[i] == '\n')
        i++;
    char *line;
    line = (char *) malloc(ft_strlen(txt) - i + 1);
    if(!line)
        return NULL;
    int k = 0;
    while( k <= ft_strlen(txt) - i )
    {
        line[k] = txt[i];
        k++;
        i++;
    }
    line[k] = '\0';
    return (line);
}

char *get_next_line(int fd)
{
    static char *text;
    char *line;
    text = "";
    text  = read_line(fd,text);
    line = get_line_no_back_n(text);
    text = get_save(text);
    return(line);
}

int main()
{
    int fd  = open("akram.txt" , O_CREAT | O_RDWR);
    static char *line;
    line  = get_next_line(fd);
    printf("%s",line);
    line  = get_next_line(fd);
    printf("%s",line);
    line  = get_next_line(fd);
    printf("%s",line);
    // line  = get_next_line(fd);
    // printf("%s",line);
    
}