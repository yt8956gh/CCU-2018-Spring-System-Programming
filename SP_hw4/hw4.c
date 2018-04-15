#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main ()
{
    int outfd=0,outnum=0,ID=0,grade[5],i=0,again=0,ret=0;
    char tmp[100+1],buffer[4096],*ptr=NULL;
    ssize_t numOut=0;

    fprintf(stderr,"## If there is not any response below ,\n");
    fprintf(stderr,"## it represents the Grade.txt is locked by another user\n\n");

    outfd = open("Grade.txt", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);

    if(outfd == -1)
    {
        perror("Cannot open the file for writing:");
        exit(-1);
    }

    ret = flock(outfd,LOCK_EX);

    if(ret==0) fprintf(stderr,"File is flocked!!\n<Enter any Key to Unlock>\n");

    if(fgets(tmp,100,stdin))
    {
        ret = flock(outfd,LOCK_UN);
        printf("Unlocked!!\n");
    }
    

    fflush(stdin);

    while(fgets(tmp,100,stdin))
    {
        again=0;

        ptr = strtok(tmp," ");

        if(ptr==NULL) 
        {
            printf("Syntax Error !\n");
            continue;
        }

        ID=atoi(ptr);

        for(i=0;i<5;i++)
        {
            ptr = strtok(NULL," ");

            if(ptr==NULL)
            {
                again=1;
                break;
            }

            grade[i]=atoi(ptr);
        }

        if(again==1)
        {
            printf("Syntax Error !\n");
            continue;
        }

        sprintf(buffer,"ID %d: %d %d %d %d %d\n",ID,grade[0],grade[1],grade[2],grade[3],grade[4]);

        numOut = write(outfd, buffer, sizeof(char)*strlen(buffer));

        if(numOut<=0){perror("Cannot write!");exit(-1);}
        else printf("Write Successully!\n");
    }

    return 0;

}