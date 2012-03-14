#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int sum;
    int i[10], j, count, t;

    sum = 45;

    count = 0;
    for (i[1] = 0; i[1] <= sum; i[1]++) {
        for (i[2] = 0; i[2] <= sum; i[2]++) {
            for (i[3] = 0; i[3] <= sum; i[3]++) {
                for (i[4] = 0; i[4] <= sum; i[4]++) {
                    for (i[5] = 0; i[5] <= sum; i[5]++) {
                        for (i[6] = 0; i[6] <= sum; i[6]++) {
                            for (i[7] = 0; i[7] <= sum; i[7]++) {
                                for (i[8] = 0; i[8] <= sum; i[8]++) {
                                    for (i[9] = 0; i[9] <= sum; i[9]++) {
                                        for (i[10] = 0; i[10] <= sum; i[10]++) {
                                            t = 0;
                                            for (j = 0; j < 10; j++) {
                                                t += i[j];
                                            }
                                            if (t == sum) {
                                                count++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%d\n",count);

	return 0;
}

