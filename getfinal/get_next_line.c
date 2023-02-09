/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-akma <ael-akma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:35:43 by ael-akma          #+#    #+#             */
/*   Updated: 2023/02/09 03:00:00 by ael-akma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
    if (!s)
        return 0;
	while (s[i])
		i++;
	return (i);
}


char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
    if (!s)
        return NULL;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char) c)
			return ((char *)(s) + i);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((ft_strlen(s1) + 1));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
    
    if (s1 == NULL && s2 == NULL)
        return NULL;
    if (s1 == NULL)
        return s2;
    if (s2 == NULL)
        return s1;
        
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
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
    }
    if (k == 0 && text[0] == '\0')
        return NULL;
    return (text);
}

char *get_line_no_back_n(char *txt)
{
    int i = 0;
    while(txt[i] != '\n' && txt[i] != '\0')
        i++;
    if(txt[i] == '\n')
        i++;
    char *line;
    line = (char *)malloc(i + 1);
    int k = 0;
    while(k < i)
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
    while( k < ft_strlen(txt) - i)
    {
        line[k] = txt[i + k];
        k++;
    }
    line[k] = '\0';
    return (line);
}

char *get_next_line(int fd)
{
    static char *text;
    char *line;
    line = NULL;
    // line = (char *)malloc(BUFFER_SIZE + 1);
    text  = read_line(fd,text);
    if(!text)
        return NULL;
    line = get_line_no_back_n(text);
    text = get_save(text);
    return(line);
}

int main()
{
    int fd = open("akram.txt" ,O_CREAT | O_RDWR);
    char *txt;
    int i = 0;
    while (txt)
    {
        txt = get_next_line(fd);
        printf("%s", txt);
    }
}
