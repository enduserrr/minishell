#include <stdio.h>


// char   *str_insert(char *s, char *c, size_t start, size_t end)
// {
// 	char    *new = 0;
//     size_t	i = 0;
//     size_t  j = 0;

// 	if (!s[i] || !c[i])
// 		return (NULL);
//     while (i < start){
//         new[i] = s[i];
//         i++;
//     }
//     i = start;
//     while (i < end)
// 		new[i++] = c[j++];
//     i = end;
//     while (s[end] != '\0')
//         new[i++] = s[end++];
//     return (new);
// }

// int main()
// {
//     char    new[11] = "HelloWorld";
//     // str_insert(new, " ", 5, 6);
//     printf("%s\n", str_insert(new, " ", 5, 6));
//     return (0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str_insert(char *s, char *c, size_t start, size_t end)
{
    if (!s || !c)
        return NULL;
    size_t s_len = strlen(s);
    size_t c_len = strlen(c);

    if (start > s_len || end > s_len || start > end)
        return NULL;

    size_t new_len = s_len - (end - start) + c_len;

    char *new = (char *)malloc(new_len + 1);
    if (!new)
        return NULL;
    size_t i = 0;
    size_t j = 0;

    while (i < start)
    {
        new[i] = s[i];
        i++;
    }
    while (j < c_len)
    {
        new[i++] = c[j++];
    }
    while (end < s_len)
    {
        new[i++] = s[end++];
    }

    new[i] = '\0';

    return new;
}

// Example usage
int main()
{
    char s[] = "Hello, World!";
    char c[] = "beautiful ";
    size_t start = 7;
    size_t end = 7;

    char *result = str_insert(s, c, start, end);
    if (result)
    {
        printf("Result: %s\n", result);
        free(result);
    }
    else
    {
        printf("Error inserting string\n");
    }

    return 0;
}
