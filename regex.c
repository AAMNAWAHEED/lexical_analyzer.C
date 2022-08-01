#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
#define NUMBER_OF_STRING 36
#define MAX_STRING_SIZE 30
typedef struct token
{
  int lno; //line no
  char cp[30];
  char vp[32];
}tokens;

void print(int line,char cp[],char vp[])
{
  tokens t1;
  t1.lno=line;
  strcpy(t1.cp,cp);
  strcpy(t1.vp,vp);
  printf("LINE NO %d\tCLASS PART %s\tVALUE PART %s\n",t1.lno,t1.cp,t1.vp);

  
}


int geta(char arr[])
{
  int i=0;
  while(arr[i]!='\0')
  {
    i++;
  }
  i=i-1;
  return i;
}
int invalid()
{
 // printf("INVALID IDENTIFIER");
  int in=1;
  return in;
}
int check(int in)
{
  if(in!=1)
    in=invalid();
  return in;
}
int iskeyword(char kk[])
{
  int flag=1;
    char key[NUMBER_OF_STRING][MAX_STRING_SIZE] =
    { "main","respondwith","stop","incase","otherwise","switch","event","default","nothing","carryon","none","consider","as_long_as","fixed","integer","char","boolean","right","wrong","if","double","float","jump","long","small","sizeof","signed","static","class","unsigned","auto","enum","extern","register","union","volatile"
    };
    for(int a=0;a<MAX_STRING_SIZE;a++)
    {
      if(strcmp(key[a],kk)==0)
      {
        flag=0;
        break;
      }
    }
    return flag;
}
int isidentifier(char arr[])
{
  int i=0,under=0,c,a=1;
    if(islower(arr[0])||isupper(arr[0])||arr[0]=='_') //||isdigit(arr[0]))
    {
      if(arr[0]=='_')
         under++;
    }
    else
      i=check(i);
    c=geta(arr);
    if(arr[c]=='_')
       i=check(i);      
    else if(islower(arr[c])==0&&isupper(arr[c])==0&&isdigit(arr[c])==0)
      i=check(i);
    while(a<c)
    {
      if(arr[a]=='_')
      {
        if(under==1)
        {
          i=check(i);
          break;
        }
        else
          under++;
      }
      else if(islower(arr[a])==0&&isupper(arr[a])==0&&isdigit(arr[a])==0)   //digits
      {
        i=check(i);
      }
      a++;
    }
    if(i==0)
    {
     // printf("%d",i);
      i=iskeyword(arr);
      if(i==0)
      {
        //printf("ooh");
        i++;
      }
      else if(i==1)
      {
        i--;
      }
     
    }
    return i;
}
int isdecimal(char arr[])
{

  int  a=0,flag=0;
  if(arr[a]=='+'||arr[a]=='-')
  {
   a++;
   if(arr[a]=='\0')   //so dont accept just +
    {
      flag=1;
      //flag+=1;
      return flag;
    }
  }
  int b,i=0;
  for(b=a;arr[b]!='\0';b++)
   {
     if(arr[b]=='.')
     {
       if(i==0)
          i++;
        else
          flag++;
     }
     else if(isdigit(arr[b])==0)
     {
        flag++;
        break;
     }
  }
  return flag;

}

int isinteger(char arr[])
{
  int  a=0,flag=0;
  if(arr[a]=='+'||arr[a]=='-')
  {
   a++;
   if(arr[a]=='\0')   //so dont accept just +
    {
      flag=1;
      //flag+=1;
      return flag;
    }
  }
  int b;
  for(b=a;arr[b]!='\0';b++)
   {
     if(isdigit(arr[b])==0)
     {
       flag=1;
      // printf("PJ");
        //flag++;
        break;
     }
  }
  return flag;
}
int ispunc(char c)
{
  int flag=0;
  if(c==','||c==':'||c==';'||c=='('||c==')'||c=='{'||c=='}'||c=='['||c==']'|| c=='.') 
    return flag;
  else
   flag=1;
  return flag;
}
int isoperator(char c)
{
  int flag=0;
  if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='&'||c=='|'||c=='<'||c=='>'||c=='='||c=='~'||c=='^')
  {
      return flag;
  }
    else
      flag++;
  return flag;
}
 
void find(char new[],int line)      //size issue of new.
{

 // printf("%s",new);
  if(isidentifier(new)==0)
  {
    char iden[11]="IDENTIFIER";
    print(line,iden,new);
      return;

  }
  if(iskeyword(new)==0)
  {
    char ke[7]="KEYWORD";
     print(line,ke,new);
      return;
  }
  else if(isinteger(new)==0)
  {
     char inte[8]="INTEGER";
     print(line,inte,new);
    return ;

  }
  else if(isdecimal(new)==0)
  {
    char deci[7]="DECIMAL";
    print(line,deci,new);
    return ;
  }
  return ;
}
int bitwise_ope(char a,char b)
{
  int flag=0;
  if(a=='&'||a=='|'||a=='^'||a=='~')
    return flag;
  else if( (a=='<'&&b=='<') ||  (a=='>'&&b=='>') )
    return flag;
  else 
  {
    flag++;
    return flag;
  }
}
int ari_ope(char a)
{
  int flag=0;
  if(a=='+'||  a=='-'|| a=='*' ||a=='/'|| a=='%')
    return flag;
  else
    flag++;
  return flag;
}
int assign_ope(char a,char b)
{
  int flag=0;
  if(ari_ope(a)==0)     //+,-,*,/,%
  {
    if(b=='=')  //+=,-=,*=,...
      return flag;
  }
  if(a=='=')     //=
    return flag;
  else
    flag++;
  return flag;

}
int relational_ope(char a,char b)
{
  int flag=0;
  if(a=='<'||a=='>')
  {
    if(b=='=')
      return flag;
   else if(bitwise_ope(a,b)==0)
   {
     flag++;
     return flag;
   }
   else
    return flag;
  }
  if(a=='='&&b=='=')
    return flag;
  else if(a=='!'&&b=='=')
    return flag;
  else 
  {
    flag++;
    return flag;
  }

}
int unary_ope(char a,char b)
{
  int flag=0;
  if(a=='+'&&b=='+')
    return flag;
  else if(a=='-'&&b=='-')
    return flag;
  else
  {
    flag++;
    return flag;
  }
}
int logical_ope(char a,char b)
{
  int flag=0;
  if(a=='&'&&b=='&')
    return flag;
  else if(a=='|'&&b=='|')
    return flag;
  else if(a=='|')
    return flag;
  else 
  {
    flag++;
    return flag;
  }
}
 
 int iscomment(char ch,FILE *fp)
 {
   int flag=0;
   while(ch!='*')
   {
     ch=fgetc(fp);
     if(feof(fp))
     {
       flag++;
       return flag;
     }

   }
   ch=fgetc(fp);
   if(ch!='/')
   {
     flag=iscomment(ch,fp);
   }
   else
    return flag;
 }
char* isstring(char ch,FILE *fp)
{
  //int flag=0;
  int n=100; 
  char *starr;
  starr=(char*)calloc(n,sizeof(char));
  int a=0;
  while(ch!='\"')
  {
    starr[a]=ch;
    //printf(" %c",starr[a]);
    a++;

    ch=fgetc(fp);
    if(feof(fp))
    {
      starr=NULL;
      return starr;

    }
  }
  return starr;
}
int isescape(char ch)
{
  if(ch=='r'|| ch=='t' || ch=='v' || ch=='\\' || ch=='a' ||ch=='b'|| ch=='e'|| ch=='f'|| ch=='\''|| ch=='\"' || ch=='?' )
  {
    return 0;
  }
  else
    return 1;

}
void tokenization(FILE *fp)
{
  //char arr[3];
  int a;
  char str[7]="string";
  char punc[11]="punctuator";
  char assi[11]="assignment";
  char rel[20]="Relational operator";
  char unar[15]="UNARY OPERATOR";
  char arri[20]="Arithmetic operator";
  char logi[17]="Logical operator";
  char bit[17]="Bitwise Operator";
  char ch,ch2;
  int n=100,qwe=0,line=1;
  char *newt,*arr;
  newt=(char*)calloc(n,sizeof(char));
  int i=0;
  printf("\n********LEXICAL ANALIZER********\n\n");
  while( !feof(fp) )                                                                   
  {
    if(qwe==0)
    {   
      ch=fgetc(fp);
      //printf("ok");
    }
    else 
      ch=ch2;
    if(ch=='\n')
    {
      line++;
       qwe=0;
       continue;
    }
    if((isspace(ch)==0)  &&   (ispunc(ch)!=0) &&  (isoperator(ch)!=0) &&  ch!='\"' && ch!='\n'  && ch!='\\' )               //isspace =0 means it's not space
    {
      if(i==0)
      {
         newt=(char*)calloc(n,sizeof(char));       //now new array.
      } 
      newt[i]=ch;                                    //initialized n
      n++;
      i++;
      if(qwe!=0)
      {
        qwe=0;
      }
    }
    else
    {
      if(ch=='.')
      {
       // printf("point");
        ch2=fgetc(fp);
        if(isdigit(ch2)!=0)
        {
          newt[i]=ch;
          n++;
         newt[i+1]=ch2;
         i++;
        qwe=0;
        continue;
        }
      }
      if(newt!=NULL)
      {
        //printf("j");
        find(newt,line);
        free(newt);
        i=0;
      }
     
    }
    if(i==0)
    {
      //printf("r");
      if(isspace(ch)!=0)
      {
        //printf("space\t");
          continue;

      }
      else if(ch=='\\')
      {
        ch=fgetc(fp);
        if(isescape(ch)==0)
          printf("escape seq");
      }
      //for string.
      else if(ch=='\"')
      {
        ch=fgetc(fp);
        arr=(char*)calloc(n,sizeof(char));
        arr=isstring(ch,fp);
        if(arr==NULL)
        {
          printf("ERROR\n");
          break;
        } 
        print(line,str,arr);
        free(arr);
        ch2=fgetc(fp);
        free(newt);
       // printf(" %c",ch2);
       // ch=fgetc(fp);
        qwe++;
      }
      else if(ispunc(ch)==0)
      {
        arr=(char*)calloc(n,sizeof(char));
        a=0;
        arr[a]=ch;
        print(line,punc,arr);
        free(arr);
        qwe=0;

      }
      else if(isoperator(ch)==0)                                        
      {
       // printf("OPERATOR\t");
        ch2=fgetc(fp);
        
        //if(comment)
        if(ch=='/'&&ch2=='*')
        {
          ch2=fgetc(fp);
          if(iscomment(ch2,fp)==0)
          {
            printf("\nCOMMENT\n");
            qwe=0;
           
          }
          else
          {
            printf("\nERROR\n");
            
            return;
          }
        }
        else if(ch=='/' && ch2=='/')
        {
          while(ch2!='\n')
          {
            ch2=fgetc(fp);
            if(feof(fp))
            {
              printf("\nERROR\t");
            }
          }

          printf("\nCOMMENT\n");
          qwe=0;
        }
          else if(assign_ope(ch,ch2)==0)      
          {
            arr=(char*)calloc(n,sizeof(char));
            a=0;
            arr[a]=ch;
            if(ch=='=')
            {
                qwe++;
            }
            else 
            {
              a++;
                arr[a]=ch2;
                qwe=0;

            }
           print(line,assi,arr);
           free(arr);
          }
        
          else if(relational_ope(ch,ch2)==0 )
          {
           arr=(char*)calloc(n,sizeof(char));
            a=0;
            arr[a]=ch;
            if(ch2=='=')   //that means we have <=...thus inc.
             {
               a++;
               arr[a]=ch2;
                qwe=0;
             }
             print(line,rel,arr);
             free(arr);

          }
          else if(unary_ope(ch,ch2)==0)
          {
           arr=(char*)calloc(n,sizeof(char));
           a=0;
           arr[a]=ch;
           a++;
           arr[a]=ch2;
           print(line,unar,arr);
            qwe=0;
           free(arr);

          }
          else if(ari_ope(ch)==0)    //after assign
          {
             arr=(char*)calloc(n,sizeof(char));
            a=0;
            arr[a]=ch;
            print(line,arri,arr);
            qwe++;
            free(arr);
           // printf("ARITHMETIC OPERATOR\t");
          }
          else if(logical_ope(ch,ch2)==0)
          {
            arr=(char*)calloc(n,sizeof(char));
            a=0;
            arr[a]=ch;
            arr[a+1]=ch2;
            print(line,logi,arr);
            //printf("LOGICAL OPERATOR\t");
            if(ch2=='&'||ch2=='|')
              qwe=0;
            free(arr);
          }
          else if(bitwise_ope(ch,ch2)==0)
          {
            arr=(char*)calloc(n,sizeof(char));
            a=0;
            arr[a]=ch;
            arr[a+1]=ch2;
            print(line,bit,arr);
            if(ch2=='<'||ch2=='>')
              qwe=0;
            free(arr);
          }

        
      }
    }
  }
  return;
}
int main()
{ 
     FILE *fp=NULL;
   char *new;
   int n;
    fp=fopen("abc.txt","r");
    tokenization(fp);
   fclose(fp);
    return 0;
}