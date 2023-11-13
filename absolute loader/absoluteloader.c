#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    FILE *fp;
    int i,addr1,l,j,staddr1;
    char name[10],line[50],name1[10],addr[10];
    char rec[10],ch,staddr[10];
    printf("Enter name of program: ");
    scanf("%s",name);
    fp = fopen("input.txt","r");
    fscanf(fp,"%s",line);
    j=0;
    for(i=2;i<8;i++)
    {
        name1[j]=line[i];
        j++;
    }
    name1[j]='\0';
    printf("Name from object code = %s",name1);
    printf("\n");
    int hex;
    int last;
    int flag=0;
    if(strcmp(name,name1)==0)
    {
        do 
        {
            fscanf(fp,"%s",line);
            if(line[0]=='T')
            {
                j=0;
                for(i=2;i<8;i++)
                {
                    staddr[j++]=line[i];
                }
                staddr[j]='\0';
                staddr1=atoi(staddr);
                i=12;
                hex = (int)strtol(staddr,NULL,16);
                if(flag)
                {
                    for(int i=last;i<hex;i+=0x1)
                    {
                        printf("00%X \t %c\n",i,88);
                    }
                }
                while(line[i]!='$')
                {
                    if(line[i]!='^')
                    {
                        printf("00%X \t %c%c\n",hex,line[i],line[i+1]);
                        hex=hex+0x1;
                        i+=2;
                    }
                    else
                    {
                        i++;
                    }
                }
                last=hex;
                flag=1;
            }
        }while(!feof(fp));
    }
    fclose(fp);
}
