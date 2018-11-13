#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "kmp.h"


void newentry();
void display_all();
void search_and_edit();

void filter_by_anything();
void attendance_display_all();
void attendance();

int main()
{
    void (*f[6])()={newentry,display_all,search_and_edit,filter_by_anything,attendance,attendance_display_all};
    while(1)
    {
        puts("1. New student record");
        puts("2. Display all");
        puts("3. Search and edit");
        puts("4. Filter");
        puts("5. Attendance");
        puts("6. Display attendance");
        puts("7. Exit");

        int c;
        printf("Enter an option: ");
        scanf("%d", &c);
        if(c==7)
        exit(0);
        else
        (*f[c-1])();
    }

return 0;
}



void newentry()
{
    char name[50];
    char id[11];
    char hobbies[100];
    char bloodgroup[3];

    puts("Enter the following details");
    printf("Name: ");
    scanf(" %[^\n]s", name);

    printf("ID No.: ");
    scanf(" %s", id);

    printf("What hobbies does the person have?: ");
    scanf(" %[^\n]s", hobbies);

    printf("What's the person's blood group?: ");
    scanf("%s",bloodgroup);
    FILE  *fp,*fp1;
    fp=fopen("database.txt","a");
    fprintf(fp,"%s %s %s %s\n",id,name,hobbies,bloodgroup);
    fclose(fp);
    fp1=fopen("names.txt","a");
    fprintf(fp,"%s %s\n",id,name);
    fclose(fp1);

    FILE * fp_att;
    fp_att=fopen("attendance.txt","a");
    fprintf(fp_att, "0 %s %s\n",id,name);
    fclose(fp_att);

}



void display_all()
{
    FILE * fp;
    fp=fopen("database.txt","r");
    char line[150];
    printf("\n\n\n");
    while(1)
    {
        fgets(line,150,fp);
        if(feof(fp))
	         break;
            printf("%s",line);
    }
    fclose(fp);
    printf("\n\n\n");

}



void search_and_edit()
{
char query[50];
printf("Enter the search query: ");
scanf(" %[^\n]s", query);

FILE * fp;
fp=fopen("database.txt","r");
char singleline[150];
int count=0,line=0;
while(!feof(fp))
{

line+=1;
fgets(singleline,150,fp);
int i=kmp(singleline, strlen(singleline),query, strlen(query));

if (i==1)
{
count+=1;
if(!feof(fp))
  printf("%d. %s",line,singleline);
}

}

if(count==0)
puts("\n\n****No match found****\n\n");

else
{
char c;
printf("\nDo you want to edit the file?[Y/n]: ");
scanf(" %c", &c);
    if(c=='Y')
        {
        int s,linecount=0;
        char new_id[11],new_name[150],new_hobbies[150],new_bg[4],replace[150];

        printf("Which serial number would you like to edit?: ");
        scanf("%d", &s);

        puts("Enter the new details: ");

        printf("New name: ");
    	  scanf(" %[^\n]s", new_name);

        printf("New ID No.: ");
        scanf("%s", new_id);

        printf("New hobbies: ");
        scanf(" %[^\n]s", new_hobbies);

        printf("New bloodgroup: ");
        scanf("%s", new_bg);

        FILE * fp_att,* fp_att_copy;
        fp_att=fopen("attendance.txt","r");
        fp_att_copy=fopen("copy.txt","w");
        char data[150];
        int at_line=0;
        while(1)
        {
          fgets(data,150,fp_att);
          if(feof(fp_att))
          break;
          at_line+=1;

          if(at_line!=s)
          {
            fprintf(fp_att_copy, "%s",data);
          }
          else
          {
            fprintf(fp_att_copy,"0 %s %s",new_id,new_name);
          }
        }
        fclose(fp_att);
        fclose(fp_att_copy);
        remove("attendance.txt");
        rename("copy.txt","attendance.txt");


        strcat(new_id, " ");
        strcat(new_name, " ");
        strcat(new_hobbies, " ");
        strcat(new_id,new_name);
        strcat(new_id,new_hobbies);
        strcat(new_id,new_bg);
        rewind(fp);
        FILE * fp2;
        fp2 = fopen("copy.txt", "w");

        while (!feof(fp)) {

                fgets(replace, 150, fp);
                if (!feof(fp)){

                        linecount+=1;

                        if (linecount != s) {
                                fprintf(fp2, "%s", replace);
                        } else {

                                fprintf(fp2, "%s\n", new_id);
                        }
                }
        }


fclose(fp);
fclose(fp2);
remove("database.txt");
rename("copy.txt","database.txt");
}
}
//system("clear");
}



void filter_by_anything()
{
    printf("Filter by anything!: ");
    char filter[100],abg[4];
    scanf("%s",filter);

    abg[3]='\0';
    FILE * fp,* fp1;
    fp=fopen("database.txt","r");
    fp1=fopen("names.txt","r");
    char id[11];
    char singleline[150],lineinfile[150];
    id[10]='\0';
    while(!feof(fp) && !feof(fp1))
    {

        fgets(singleline,150,fp);
        fgets(lineinfile,150,fp1);


        char delimiter[] = " ";
        char *firstWord, *secondWord, *remainder, *context;

        int inputLength = strlen(singleline);
        char *inputCopy = (char*) calloc(inputLength + 1, sizeof(char));
        strncpy(inputCopy, singleline, inputLength);

        //firstWord = strtok_r (inputCopy, delimiter, &context);
        //secondWord = strtok_r (NULL, delimiter, &context);
        remainder = context;
        free(inputCopy);

        int i=kmp(singleline, strlen(singleline),filter, strlen(filter));
        if(i==1)
        {
            printf("%s",lineinfile);
        }
        }



}




void attendance()
{
    int choice;
    printf("1.Take Attendance\n");
    printf("2.Filter\n");
    scanf("%d",&choice);
    // code for finding limit
    FILE * fp;
    fp=fopen("attendance.txt","r");
    char tmp[150];
    int limit=0;
    while(!feof(fp))
    {
        fgets(tmp,150,fp);
        limit++;
    }
    limit--;
    fclose(fp);
    //
    if(choice==1)
    {
   //
    FILE *fp2;
    fp2=fopen("days.txt","r");
    int var=0;
    fprintf(fp2,"%d",var);
    fscanf(fp2,"%d",&var);
    var++;
    FILE *fp3;
    fp3=fopen("copy1.txt","w");
    fprintf(fp3,"%d",var);
    fclose(fp2);
    fclose(fp3);
    remove("days.txt");
    rename("copy1.txt","days.txt");
   //
        int i=0,k=0;
        char arr1[50][10];
        {
            FILE * fp;
            fp=fopen("attendance.txt","r");
            FILE *fp1;
            fp1=fopen("copy.txt","w");
            char singleline[150];
            int line=0,at;
            while(!feof(fp))
             {
               if(line==limit)
                  break;
              line+=1;
              fscanf(fp,"%d %[^\n]s",&at,singleline);
              int j=kmp(singleline, strlen(singleline),arr1[k], strlen(arr1[k]));
              if(j<0)
              {
                   at++;
                  fprintf(fp1,"%d %s\n",at,singleline);
              }
              else
              {
                  at++;
                  fprintf(fp1,"%d %s\n",at,singleline);
              }
             }
           fclose(fp1);
           fclose(fp);
           remove("attendance.txt");
           rename("copy.txt","attendance.txt");
        }
        printf("Are all students present[Y/N]:\n");
        char c[2];
        scanf("%s",c);
        if(c[0]=='Y')
            return;
        printf("Enter the roll no.s of students which are absent:");
        while(1)
           {
            scanf("%s", arr1[i]);
               {
                   FILE *fp;
                   fp=fopen("attendance.txt","r");
                   char string[150];
                   int line_no=0,atnce,z,count=0;
                   while(!feof(fp))
                   {
                      if(line_no==limit)
                       break;
                       fscanf(fp,"%d %[^\n]s",&atnce,string);
                       line_no++;
                       z=kmp(string, strlen(string),arr1[i], strlen(arr1[i]));
                       if(z>0){
                        count++;
                        break;}
                   }
                   fclose(fp);
                   if(count==0){
                    printf("The roll no. you entered does not exist\n");
                    return;}
               }
            FILE * fp;
            fp=fopen("attendance.txt","r");
            FILE *fp1;
            fp1=fopen("copy.txt","w");
            char singleline[150];
            char temp[10];
            int line=0,at;
            while(!feof(fp))
             {
               if(line==limit)
                  break;
              line+=1;
              fscanf(fp,"%d %[^\n]s",&at,singleline);
              int j=kmp(singleline, strlen(singleline),arr1[k], strlen(arr1[k]));
              if(j==0)
              {
                  fprintf(fp1,"%d %s\n",at,singleline);
              }
              else
              {
                  at--;
                  fprintf(fp1,"%d %s\n",at,singleline);
              }
             }
           fclose(fp1);
           fclose(fp);
           remove("attendance.txt");
           rename("copy.txt","attendance.txt");
             k++;
            printf("Do you want to continue [Y/N]:");
            scanf("%s",temp);
            if(temp[0]=='N')
               break;
            printf("Enter another roll no :\n");
            i++;
           }
    }
    //
    if(choice==2)
    {
      printf("Enter the required amount by which you want to filter attendance:");
      int amount;
      scanf("%d",&amount);
      FILE *fp2;
      fp2=fopen("days.txt","r");
      int days;
      fscanf(fp2,"%d",&days);
      fclose(fp2);
      float  x=(amount/100.0)*days;
      FILE *fp;
      fp=fopen("attendance.txt","r");
      int cuday,line1=0;
      char str[150];
      while(!feof(fp))
      {
          line1++;
          fscanf(fp,"%d %[^\n]s",&cuday,str);
          if(cuday>=x)
            printf("%d %s\n",cuday,str);
          if(line1==limit)
           break;
      }
      fclose(fp);
    }
    //
}





 void attendance_display_all()
 {
  FILE * fp;
  fp=fopen("attendance.txt","r");
  char line[150];
  printf("\n");
  while(!feof(fp))
  {
  fgets(line,150,fp);
  if(!feof(fp))
   printf("%s",line);
  }
  printf("\n");
  fclose(fp);
 }
