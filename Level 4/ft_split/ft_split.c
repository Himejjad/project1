#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

int is_sep(char c)
{
    if(c == ' ' || c == '\t' || c == '\n')
        return 0;
    return 1;
}

int count_words(char *str)
{
    int i = 0;
    int words = 0;
    if(str[i] && is_sep(str[i]))
        words = 1;
    while (str[i])
    {
        if(!is_sep(str[i]) && is_sep(str[i+1]) && str[i+1])
            words++;
        i++;
    }
    return words;
}

char    **ft_split(char *str)
{
    int i = 0;
    int j = 0;
    int len;
    int word = count_words(str);
    char **ret;
    ret = (char **)malloc((word + 1) * sizeof(char *));
    ret[word] = NULL;
    while (str[j] && i < word)
    {
        len = 0; 
        while (!is_sep(str[j]) && str[j])
            j++;
        while (is_sep(str[j]) && str[j])
        {
            len++;
            j++;
        }
        ret[i++] = (char *)malloc(sizeof(char *) * len);
    }

    i = 0;
    j = 0;
    while (str[i] && j < word)
    {
        while (str[i] && !is_sep(str[i]))
            i++;
        len = 0;
        while (str[i] && is_sep(str[i]))
        {
            ret[j][len] = str[i];
            i++;
            len++;
        }
        ret[j][len] = '\0';
        j++;
    }
    return ret;
}


