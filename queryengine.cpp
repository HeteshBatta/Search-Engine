#include<iostream>
#include<stdlib.h>
#include<map>
#include<stdio.h>
#include<cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include<fstream>
#include<string.h>
#include<cstdio>
#include<iterator>
//#include<algorithm>
using namespace std;
char ignore1[100][100]={"who","what","how","is","are","am","where","why","which","I","i","can","to"};
int ignore_count=13;
char query[100];
int flagprint=0;
class hash1;
class wordll;
class llurl;
char allLinks[100][100];
int ALCount=0;
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
char *words[100];
int count=0;


void addNewNode(char *s,char *link,int cou)
{
  wordll *ptr=new wordll();
  strcpy(ptr->word,s);

  llurl *u=new llurl();
  strcpy(u->url,link);

  if(ptr->node==NULL)
  {
      ptr->node=u;
      ptr->last=u;
      u->count=cou;
  }
  else
  {
    ptr->last->next=u;
    u->prev=ptr->last;
    u->count+=cou;
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

void storingList()
{
  ofstream fout;
  fout.open("/home/hetesh/Desktop/se/wordlistnew.txt");
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

void addNewNode1(char *s,char *link,int cou)
{
  wordll *ptr=hash_map[s[0]].last;
  llurl *ptr1 = new llurl();
  strcpy(ptr1->url,link);
  ptr1->count=cou;
  ptr->last->next=ptr1;
  ptr1->prev=ptr->last;
  ptr->last=ptr1;
}

void gettingList()
{
  ifstream fout;
  fout.open("/home/hetesh/Desktop/se/wordlist.txt");
  char s[100],link[1000],c[10],word[100];
  char a[10];
  int count;
  a[0]=',';
  a[1]='\0';
  s[0]=',';
  s[1]='\0';

  while(!fout.eof())
  {

  if(!strcmp(a,s))
  {
    fout>>s;
    fout>>link;
    fout>>c;
    count=atoi(c);
    word[0]='\0';
    strcpy(word,s);
    addNewNode(s,link,count);
  }
  else
  {
    link[0]='\0';
    strcpy(link,s);
    fout>>c;
    count=atoi(c);
    addNewNode1(word,link,count);
  }
  fout>>s;
  }
  fout.close();
}


void getWords(char *str)
{
  int k=strlen(str);
  char w[100]="";
  int c=0;
  int i,j;
  for(i=0;i<k;i++)
  {
    if(str[i]==' '||i==k-1)
    {
      if(i==k-1)
      {
          w[c++]=str[i];
      }
      w[c]='\0';
    if(strlen(w)>1)
    {
    words[count]=new char[100];
    int flag=0;
    for(int z=0;z<ignore_count;z++)
    {
      if(!strcmp(ignore1[z],w))
      {
        flag=1;
        break;
      }
    }
    if(flag==0)
    strcpy(words[count++],w);
    }
      c=0;
      i++;
      }
    w[c++]=str[i];
  }

  //  makingLinkList();
}

void removeDuplicates()
{
  for(int i=0;i<ALCount;i++)
  {
    for(int j=i+1;j<ALCount;j++)
    {
        if(!strcmp(allLinks[i],allLinks[j]))
        {
          allLinks[j][0]='\0';
        }
    }
  }
}

void searchWords()
{
  int i;
  for(i=0;i<count;i++)
  {
    cout << words[i] <<"*" << endl;
    int index=words[i][0];
    wordll *p = hash_map[index].node;
    while(p!=NULL)
    {
      if(!strcmp(p->word,words[i]))
      {
        llurl *ptr=p->node;
        while(ptr!=NULL)
        {
          strcpy(allLinks[ALCount],ptr->url);
          ALCount++;
          ptr=ptr->next;
        }
        break;
      }
      p=p->next;
    }
    removeDuplicates();
  }
}


int main()
{
  gettingList();
  storingList();
  cout<<"How can i help you?"<<endl;
  cin >> query;
  getWords(query);
  searchWords();
  for(int i=0;i<ALCount;i++)
  {
    if(allLinks[i][0]!='\0')
    {
      cout<<allLinks[i]<<endl;
      flagprint=1;
    }
  }
  if(flagprint==0)
  cout << "No Results Found" << endl;
}
