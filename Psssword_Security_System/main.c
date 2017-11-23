#include<stdio.h>
#include<memory.h>
#include<stdio.h>
#include<string.h>//strcmp(),strcat()
#include<stdlib.h>//rand()
#include<time.h>//time(0)
#include<ctype.h>
#include "PS_SHA_256.h"

#define MAX_LIMIT 1000


void signup(char *username, char *password);
int verifyPassword(int ,char *);
int verifyUsername(char *);
char* generateSalt();
char salt[5];
char* getSalt(int sNo);
//uc* struprr(uc *);
int hex_to_ascii(char c, char d);
int hex_to_int(char c);




int main()
{
    int choice;
    char username[50],password[50];

    printf("1. Signin \n");
    printf("2. Signup (New User) \n");
    scanf("%d",&choice);

    if(choice==1)
    {
        int sNo;
        printf("Username:\n");
        scanf("%s",username);
        sNo=verifyUsername(username);
        if(sNo)
        {
            printf("Username verified.\n");
            printf("Password:\n");
            scanf("%s",password);

           if(verifyPassword(sNo,password))
            {
                printf("Login Successful\n");
            }
            else
            {
                printf("Wrong Password\n");
            }
        }
        else
        {
            printf("No such user exists.\n");
        }

    }

    else if(choice==2)
    {
        printf("Username:\n");
        scanf("%s",username);

        printf("Password:\n");
        scanf("%s",password);

        signup(username,password);
    }

    else
    {
        printf("Invalid choice! Try again.");
    }
    return 0;
}




/*uc* struprr(uc *h1)
{
    int i;printf("Converting to upper case \n\n");char ch;
    for(i=0;i<32;i++)
    {
        h1[i]=toupper(h1[i]);
        printf("%02x ",ch);
        //printf("%c ",toupper("a"));
    }
        for(i=0;i<32;i++)
    {
        //h1[i]=toupper(h1[i]);
        printf("%02x ",h1[i]);
        //printf("%c ",toupper("a"));
    }

    return h1;
} */

int hex_to_int(char c)
{
if (c >= 97)
        c = c - 32;
    int first = c / 16 - 3;
    int second = c % 16;
    int result = first * 10 + second;
    if (result > 9) result--;
    return result;
}

int hex_to_ascii(char c, char d){
        int high = hex_to_int(c) * 16;
        int low = hex_to_int(d);
        return high+low;
}

char* generateSalt()
{
    srand(time(0));
    short index;
    int i;
    FILE *fp_salt_directory;
    char arr[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q'
    ,'r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9',
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    for (i=0;i<4;i++)
    {
        index=rand()%62;
        salt[i]=arr[index];
    }
    salt[4]='\0';
    fp_salt_directory=fopen("salt_directory.txt","a");
    fputs(salt,fp_salt_directory);
    fputs("\n",fp_salt_directory);
    fclose(fp_salt_directory);

    return salt;
}


void signup(char *username,char *password)
{
    char *salt_pointer,buf=0;;uc hash[32],h2[32], *h1, chh =' ';
    int i,num;
    SHA2 ptr;
    memset(hash,0,sizeof(hash));

    FILE *fp_user_directory,*fp_pwd_directory1;
    FILE *fp_pwd_directory;
    fp_user_directory=fopen("user_directory.txt","a");
    fputs(username,fp_user_directory);
    fputs("\n",fp_user_directory);
    fclose(fp_user_directory);

      salt_pointer=generateSalt();
    //printf("Salt pointer is initilized \n\n");

      strcat(password,salt_pointer);
    //printf("password is modified %s salt \n\n",password);
      fp_pwd_directory1=fopen("PWD.txt","a");
      fputs(password,fp_pwd_directory1);
      fputs("\n",fp_pwd_directory1);

    // Hash one
      initilize(&ptr);
      update(&ptr,password,strlen(password));
      data_final(&ptr,hash);
      printf("Printng the contents using standard hash function for storing purpose \n\n");
      h1=print_hash(hash);
      //h1= struprr(h1);


    fp_pwd_directory=fopen("pwd_directory.txt","a");
    fputs(h1,fp_pwd_directory);
    fputs("\n",fp_pwd_directory);
    //fprintf(fp_pwd_directory,"%02x",h1);
    fclose(fp_pwd_directory);
    fclose(fp_pwd_directory1);

    //fp_pwd_directory=fopen("pwd_directory.txt","r");

    //printf("Printing hash after returning from SHA2 function \n\n");

    /*for(i=0;i<32;i++)
    {
      //h1[i]= fscanf(fp_pwd_directory,"%02x",h2);
       chh+=h1[i];
       //strcat(chh,h1[i]);
       printf("%x ",chh);

      //printf("%02x",h1[i]);

    }
    printf("\n");

    /*for(i=0;i<32;i++)
    {
      //h1[i]= fscanf(fp_pwd_directory,"%02x",db_pwd);
      printf("%02x ",h1[i]);

    } */


}



int verifyUsername(char *user_query)
{
    int sNo=0;
    char db_username[50];
    FILE *fp_user_directory;
    fp_user_directory=fopen("user_directory.txt","r");

    while(fscanf(fp_user_directory,"%s",db_username)!=EOF)
    {
        sNo++;
        if(strcmp(db_username,user_query)==0)
        {
            fclose(fp_user_directory);
            return sNo;
        }
    }
    fclose(fp_user_directory);
    return 0;
}



int verifyPassword(int sNo,char *pwd_query)
{
    int i;
    char *hash_query;char db_salt[5];SHA2 ptr;uc hash[32],*h1 ,h2[32],db_pwd[50];
    FILE *fp_pwd_directory,*fp_pwd_directory1;FILE *fp_salt_directory;
    memset(hash,0,sizeof(hash));
    memset(h2,0,sizeof(h2));
    memset(db_pwd,0,sizeof(db_pwd));


    fp_salt_directory=fopen("salt_directory.txt","r" );
    fp_pwd_directory1=fopen("PWD.txt","r" );
    for(i=0;i<sNo;i++)
    {
            fscanf(fp_salt_directory,"%s",db_salt);
             fscanf(fp_pwd_directory1,"%s",db_pwd);
    }

    strcat(pwd_query,db_salt);
    //hash_query=generate_hash(pwd_query);

    // Hash one
      initilize(&ptr);
      update(&ptr,pwd_query,strlen(pwd_query));
      data_final(&ptr,hash);

      h1= print_hash(hash);
     // printf(" \n\n Printng the contents using standard hash function matching purpose in verification function \n\n");


    //fp_pwd_directory=fopen("pwd_directory.txt","r");
    //printf(" \n %s \n",h1);

    /*for(i=0;i<32;i++)
    {
      h2[i]= fscanf(fp_pwd_directory,"%02x",db_pwd);
      //printf("%02x",h1[i]);

    }*/
    //printf("\n\n printing contents from file \n\n");
    //fscanf(fp_pwd_directory,"%s",db_pwd);
    //printf("%s \n",db_pwd);

    /*for(i=0;i<32;i++)
    {
      //h1[i]= fscanf(fp_pwd_directory,"%02x",db_pwd);
      printf("%02x ",h2[i]);

    } */


    if(strcmp(pwd_query,db_pwd)==0)
        {
            fclose(fp_pwd_directory1);
            return 1;
        }

    /*for(i=0;i<sNo;i++)
    {
        fscanf(fp_pwd_directory,"%s",db_pwd);
        if(strcmp(db_pwd,hash)==0)
        {
            fclose(fp_pwd_directory);
            return 1;
        }
    } */
    fclose(fp_pwd_directory1);
    return 0;
}
/*int main()
{
    uc text1[MAX_LIMIT],hash[32];
    printf("Enter your data yo be hashed \n");
    gets(text1);


   int idx;
   SHA2 ptr;

   // Hash one
   //initilize(&ptr);
   //update(&ptr,text1,strlen(text1));
   //data_final(&ptr,hash);
   //print_hash(hash);

   signup("aryan",text1);


   getchar();
   return 0;
}
*/
