#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int prefixArray(char * query,int lenOfQuery);
int kmp(char * target, int lenOfTarget,char * query, int lenOfQuery);

int prefixArray(char * query,int lenOfQuery)
{
    int * ret=malloc(sizeof(int)*lenOfQuery);

    ret[0]=0;
    int i=1,j=0;
    for(i=1;i<lenOfQuery;)
    {
        if(query[i]==query[j])
        {
            ret[i]=j+1;
            j+=1;
            i+=1;
        }
        else
        {
            if(j!=0)
            {
                j=ret[j-1];
            }
            else
            {
                ret[i]=0;
                i+=1;
            }

        }
    }
    return ret;
}



int kmp(char * target, int lenOfTarget,char * query, int lenOfQuery)
{
    int * pArray=prefixArray(query,lenOfQuery);
    int i=0,j=0;

    while(i<lenOfTarget && j<lenOfQuery)
    {
        if(target[i]==query[j])
        {
            i+=1;
            j+=1;
        }
        else
        {
            if(j==0)
            {
                i+=1;
            }
            else
            {
                j=pArray[j-1];
            }
        }
    }
    if(j==lenOfQuery)
    {
        return 1;
    }
    return 0;
}




