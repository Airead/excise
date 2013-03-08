#include <stdio.h>

#ifdef _DEBUG
#  define PRINFO(fmt, args...) fprintf(stderr, fmt, ##args)
#else                                                       
#  define PRINFO(fmt, args...)
#endif

int get_similarity(char *l, char *s)
{
    int similarity, i;

    similarity = 0;
    i = 0;

    while (s[i] != '\0') {
        if (l[i] != s[i]) {
            break;
        }
        similarity++;
        i++;
    }

    PRINFO("%s, %s, %d\n", l, s, similarity);

    return similarity;
}

int str_similarity_sum(char *str)
{
    int sum, i;

    sum = 0;
    i = 0;

    while (str[i] != '\0') {
        sum += get_similarity(str, str + i);
        i++;
    }

    return sum;
}

int main(int argc, char *argv[])
{
    int i, num;
    char str[100001];

    scanf("%d", &num);

    for (i = 0; i < num; i++) {
        int sum;
        scanf("%s", str);
        sum = str_similarity_sum(str);
        fprintf(stdout, "%d\n", sum);
    }

    return 0;
}
