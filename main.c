#include <stdio.h>
#include <error.h>
#include <string.h>
#include <errno.h>

#define N 64

int main(int argc,char *argv[]) {
    int n;
    char buf[N];
    FILE *fps,*fpd;

    if(argc < 3)
    {
        printf("Usage: %s <src_file> <dst_file>\n",argv[0]);
        return -1;
    }

    if((fps = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "fail to fopen %s : %s\n",argv[1],strerror(errno));
        return -1;
    }

    if((fpd = fopen(argv[2], "w")) == NULL)
    {
        fprintf(stderr, "fail to fopen %s : %s\n",argv[2],strerror(errno));
        fclose(fps);
        return -1;
    }

    while ((n = fread(buf,1,N,fps))>0)
    {
        fwrite(buf,1,n,fpd);
    }

    fclose(fps);
    fclose(fpd);
    return 0;
}