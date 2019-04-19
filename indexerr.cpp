#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include<fstream>
#include<string.h>
using namespace std;
int  fcount=1;
char *words[1000];
int count=0;
class hash1;
class wordll;
class llurl;
char current_link[100];
void makingLinkList();
void addNode(int,int);
class hash1
{
public:
  wordll *node,*last;
  hash1()
  {
    node=NULL;
  }
};

class wordll
{
public:
  char word[100];
  wordll *prev,*next;
  llurl *node,*last;
  wordll()
  {
    prev=NULL;
    next=NULL;
    node=NULL;
  }
};

class llurl
{
public:
  char url[100];
  llurl *prev,*next;
  int count;
  llurl()
  {
  prev=NULL;
   next=NULL;
   count=1;
  }
};

hash1 hash_map[256];

int findFileSize(char *str)
{
  struct stat st;
  stat(str,&st);
  return st.st_size;
}


char* ltrim(char *string)
{
    char* original = string;
    char *p = original;
    int trimmed = 0;
    do
    {
        if (*original != ' ' || trimmed)
        {
            trimmed = 1;
            *p++ = *original;
        }
    }
    while (*original++ != '\0');
    return string;
}


void storingList()
{
  ofstream fout;
  fout.open("/home/hetesh/Desktop/se/wordlist.txt");
  for(int i=0;i<256;i++)
  {
    if(hash_map[i].node!=NULL)
    {
      wordll *p=hash_map[i].node;
      while(p!=NULL)
      {
        fout<<p->word;
        fout<<" ";
        llurl *u=p->node;
        while(u!=NULL)
        {
          fout<<u->url;
          fout<<" ";
          fout<<u->count;
          fout<<" ";
          u=u->next;
        }
        fout<<" ,";
        fout<<endl;
        p=p->next;
      }
    }
  }
  fout.close();
}

void checkWord(char *s)
{
  wordll *p=hash_map[s[0]].node;
  int f2=0,flag=0;
  while(p!=NULL)
  {
    if(!strcmp(s,p->word))
    {
      flag=1;
      break;
    }
    p=p->next;
  }
  if(flag==1)
  {
    llurl *a=p->last;
      if(!strcmp(a->url,current_link))
      {
        f2=1;
        (a->count)++;
      //  break;
      }
    //  a=a->next;
    if(f2==0)
    {
      llurl *u=new llurl();
      strcpy(u->url,current_link);
      p->last->next=u;
      u->prev=p->last;
      u->count=1;
      p->last=u;
    }
  }
  else
  {
    strcpy(words[0],s);
  addNode(0,1);
  }
}
void getWords(char str[],int k)
{
  char w[1000]="";
  int c=0;
  int i,j;
  for(i=0;i<k;i++)
  {
    if(str[i]==' '||str[i]==','||str[i]=='-')
    {
      w[c]='\0';
       words[count]=new char[100];
    //   strlwr(w);
  //  w=ltrim(w);
    if(strlen(w)>2)
    checkWord(w);
    //  strcpy(words[count],w);
      c=0;
      count++;
      i++;
      }
    w[c++]=str[i];
  }

  //  makingLinkList();
}


void addNode(int i,int c)
{
  wordll *ptr=new wordll();
  strcpy(ptr->word,words[i]);
  cout<<ptr->word<<" @ "<<c<<endl;

  llurl *u=new llurl();
  strcpy(u->url,current_link);
  if(ptr->node==NULL)
  {
      ptr->node=u;
      ptr->last=u;
      u->count=c;
  }
  else
  {
    ptr->last->next=u;
    u->prev=ptr->last;
    u->count+=c;
    ptr->last=u;
  }

  if(hash_map[ptr->word[0]].node==NULL)
  {
    hash_map[ptr->word[0]].last=ptr;
    hash_map[ptr->word[0]].node=ptr;


  }
  else
  {
    hash_map[ptr->word[0]].last->next=ptr;
    ptr->prev=hash_map[ptr->word[0]].last;
    hash_map[ptr->word[0]].last=ptr;
  }

}



/*void makingLinkList()
{
  int i,j,k,c=0,flag=0;
  for(i=0;i<count;i++)
  {
    c=1;
    if(strlen(words[i])>2)
    {
      for(j=i+1;j<count;j++)
      {
        if(!strcmp(words[i],words[j]))
        {
            c++;
            words[j]=" ";
        }
      }
      wordll *p=hash_map[words[i][0]].node;
      while(p!=NULL)
      {
          if(!strcmp(p->word,words[i]))
          {
            flag=1;
            break;
          }
          p=p->next;
      }
      if(flag==0)
      addNode(i,c);
      else
      {
        llurl *u=new llurl();
        strcpy(u->url,current_link);
        p->last->next=u;
        u->prev=p->last;
        u->count+=c;
        p->last=u;
      }
      flag=0;
    }
    //free(words[i]);
  }
  //count=0;
}*/

void read_title(char *file,int file_size)
{
  char str[1000]="";
  int k=0;
    char *tstart,*tend;
    for(int i=0;i<file_size;i++)
    {
      if(file[i]=='<'&&file[i+1]=='t')
      {
        tstart = &file[i];
        tstart = strpbrk(tstart,">");
        tstart++;
        break;
      }
    }
    tend = strpbrk(tstart,"<");
    for(;tstart!=tend;tstart++)
    {
      str[k++]=*tstart;
    }
    getWords(str,k);
      //cout<<str<<endl;
}

void setMeta(char s[1000],int k)
{
  int i,z=0;
  char str[1000]="";
//  cout<<s<<endl;
  for(i=0;i<k;i++)
  {
    if(s[i]=='d'&&s[i+1]=='e'&&s[i+2]=='s')
    {
      for(int a=k-3;s[a]!='\"';a--)
      {
        str[z++]=s[a];
      }
      cout<<str<<endl;
    }
  }
}

void read_meta(char *file,int file_size)
{
  int k=0;
  char str[1000]="";
    char *tstart,*tend;
    for(int i=0;i<file_size;i++)
    {
      k=0;
      if(file[i]=='<'&&file[i+1]=='m')
      {
        tstart = &file[i];
        tstart++;

    tend = strpbrk(tstart,">");
    for(;tstart!=tend;tstart++)
    {
      str[k++]=*tstart;
    }
    setMeta(str,k);
    }
    }
}

void read_heading(char *file,int file_size)
{
  char str[1000]="";
  int k=0;
    char *tstart,*tend;
    for(int i=0;i<file_size;i++)
    {
      if(file[i]=='<'&&file[i+1]=='h')
      {
        k=0;
        tstart = &file[i];
        tstart = strpbrk(tstart,">");
        tstart++;
        tend = strpbrk(tstart,"<");
        for(;tstart!=tend;tstart++)
        {
            str[k++]=*tstart;
        }
        str[k]='\0';

        getWords(str,k);
      //  cout<<str<<endl;
      }
    }

}

void wordSearch(char *html_buffer,char linkame[100],char linkdept[20],int fsize )
{
read_title(html_buffer,fsize);
//read_meta(html_buffer,fsize);
read_heading(html_buffer,fsize);

}

void readFile()
{
  char link_name[100];
  char link_dept[10];
  ifstream fin;
  char str[200]="/home/hetesh/Desktop/sefiles/";
  char s[100];
  sprintf(s,"%d.txt",fcount);
  fcount++;
  strcat(str,s);
  //cout<<str;
  int fsize=findFileSize(str);
  //cout<<fsize;

  fin.open(str);

  char x[1000];
  char *html_buffer;
  html_buffer=(char *)malloc(fsize+1000);

  fin>>link_name;
  fin>>link_dept;
  fin>>html_buffer;
  while(!fin.eof())
  {
    fin>>x;
		strcat(html_buffer," ");
		strcat(html_buffer,x);
  }


  fin.close();
  html_buffer[fsize]='\0';
  fsize++;
  current_link[0]='\0';
  strcpy(current_link,link_name);
  //cout<<link_name<<endl<<link_dept<<endl<<html_buffer;
  wordSearch(html_buffer,current_link,link_dept,fsize);
  free(html_buffer);
  if(fcount<14)
  {
  count=0;
  readFile();
  }
}
int main()
{
  readFile();
  cout << count << "*" << endl;
  storingList();
  return 0;
}
