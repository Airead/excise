#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    FILE *fp, *in, *out;
    char *fileName;
    char *p;
    int ch;
    char buf[500], temp[500];
    char senWord[100][20];
    int i, k;

    fileName = "sensitive";
    fp = fopen(fileName, "r");
    if(!fp){
	printf("cannot open %s\n", fileName);
	exit(0);
    }
    i = 1;   k = 0;
    ch = getc(fp);
    while(!feof(fp)){
	if(ch == '\n'){
	    k = 0;
	    strcpy(senWord[i++], senWord[0]);
	    ch = getc(fp);
	    continue;
	}
	//	putchar(ch);
	senWord[0][k++] = (char)ch;
	ch = getc(fp);
    }
    fclose(fp);
    k = i - 1;
    for(i = 1; i <= k; i++){
	printf("%s\n", senWord[i]);
    }

    in = fopen("test", "r");
    if(!in){
	printf("cannot open test\n");
	exit(0);
    }

    out = fopen("Ok", "w");
    if(!out){
	printf("cannot open OK\n");
	exit(0);
    }

    while(fgets(buf, sizeof(buf), in) != NULL){
	for(i = 1; i <= k;){
	    p = strstr(buf, senWord[i]);
	    if(p != NULL){
		strcpy(temp, p+3);
		strcpy(p+3, "|");
		strcat(p+3, temp);
	    }else{
		i++;
	    }
	}
	fprintf(out, "%s", buf);
    } 
    return 0;
}
