#include <stdio.h>
#include <string.h>

#ifdef _DEBUG
#  define PRINFO(fmt, args...) fprintf(stderr, fmt, ##args)
#else                                                       
#  define PRINFO(fmt, args...)
#endif

int m(char *s1, char *s2, int i, int j, int l)
{
    int count, x, len;

    count = 0;
    x = 0;
    len = strlen(s1);

    while ((i + x) <= len && (j + x) <= len && x < l) {
        if (s1[i + x - 1] != s2[j + x - 1]) {
            count++;
        }
        x++;
    }

    return count;
}

int sub_maxl(char *s1, char *s2, int i, int j, int k)
{
    int submaxl, n, min;
    int s1_avail_len, s2_avail_len;

    submaxl = 0;
    s1_avail_len = strlen(s1) - i + 1;
    s2_avail_len = strlen(s2) - j + 1;
    min = s1_avail_len < s2_avail_len ? s1_avail_len : s2_avail_len;
    
    n = 1;
    while (n <= min) {
        PRINFO("m(%d, %d, %d): %d\n", i, j, n, m(s1, s2, i, j, n));
//        PRINFO("%s, %s, m(%d, %d, %d): %d\n", s1 + i - 1, s2 + j - 1, i, j, n, m(s1, s2, i, j, n));
        if (m(s1, s2, i, j, n) > k) {
            break;
        }
        if (submaxl < n) {
            submaxl = n;
        }
        n++;
    }
    
    return submaxl;
}

int maxl(char *s1, char *s2, int k)
{
    int maxl, i, j, tmpmaxl;
    int len;                    /* the length of s1 is equal to s2 */

    len = strlen(s1);
    maxl = 0;

    for (i = 1; i < len; i++) {
        PRINFO("(l:%5d, i:%5d, j:%5d, k:%5d\n", tmpmaxl, i, j, k);
        for (j = 1; j < len; j ++) {
            tmpmaxl = sub_maxl(s1, s2, i, j, k);
//            PRINFO("(l:%d, s1:%s, s2:%s, i:%d, j:%d, k:%d\n", tmpmaxl, s1 + i - 1, s2 + j - 1, i, j, k);
            if (maxl < tmpmaxl) {
                maxl = tmpmaxl;
            }
        }
    }

    return maxl;
}

int main(int argc, char *argv[])
{
    int i, num, k, l;
    char s1[1501], s2[1501];

    scanf("%d", &num);
    
    for (i = 0; i < num; i++) {
        scanf("%d %s %s", &k, s1, s2);
        l = maxl(s1, s2, k);
        fprintf(stdout, "%d\n", l);
    }
    return 0;
}
