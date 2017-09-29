#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

typedef struct Link{
  char *text;
  struct Link *next;
}Link;

int addl(Link **list);
int removel(Link **list);
int show(Link *list);

Link *load(char *file);
int save(char *file,Link *list);

int main(int argc, char *argv[])
{
  char * file = (argc > 2) ? argv[2] : "file";
  if (argc > 1){
    
  }
  else {
    printf("there is no argument\n");
    return 1;
  }

  Link *list = NULL;
  list = load(file);
  if (strcmp(argv[1],"add") == 0){
    addl(&list);
  }
  else if (strcmp(argv[1],"remove") == 0){
    removel(&list);
  }
  else if (strcmp(argv[1],"show") == 0){
    show(list);
  }
  else{
    printf("%s is not a valid option\n",argv[1]);
    return 2;
  }
  save(file,list);

  return 0;
}

Link *newLink(char *s,Link *n){
  Link *p;
  if ((p = malloc(sizeof(Link))) != NULL){
    if ((p->text = strdup(s)) != NULL){
      p->next = n;
      return p;
    }
    else
      free(p);
  }
  return NULL;
}

Link *load(char*file){
  FILE *fp;
  char s[MAXLINE];
  if ((fp = fopen(file,"r")) == NULL){
    printf("could not open file\n");
    return newLink("",NULL);
  }
  Link **lp;
  Link *start;
  for (lp = &start; fscanf(fp,"%99s",s)==1; lp = &(*lp)->next){
    if ((*lp = newLink(s,NULL)) == NULL){
      printf("no more memory\n");
    }
  }
  if ((*lp = newLink("",NULL)) == NULL){
    printf("no more memory\n");
  }
  fclose(fp);
  return start;
}

int save(char *file,Link *list){
  FILE *fp;
  Link **lp;
  fp = fopen(file,"w");
  for (lp = &list; (*lp)->next != NULL; lp = &(*lp)->next){
    fprintf(fp,"%s\n", (*lp)->text);
    //if error on fp close and return 1
  }
  fprintf(fp,"%s\n", (*lp)->text);
  fclose(fp);
  return 0;
}

int addl(Link  **list){
  char s[MAXLINE];
  Link **lp = list;
  scanf("%99s",s);
  for (lp = list; (*lp)->next != NULL; lp = &(*lp)->next){
    if (strcmp((*lp)->text,s)>0){
      break;
    }
  }
  if ((*lp = newLink(s,*lp)) == NULL){
    printf("no more memory\n");
    return 1;
  }
  return 0;
}

int removel(Link **list){
  Link **lp;
  Link *dl;
  char text[MAXLINE];
  scanf("%99s",text);
  for (lp = list; (*lp)->next != NULL; lp = &(*lp)->next){
    if(strcmp((*lp)->text,text) == 0){
      dl = *lp;
      *lp = (*lp)->next;
      free(dl->text);
      free(dl);
      return 0;
    }
  }
  return 1;
}

int show(Link *list){
  Link **lp;

  for (lp = &list; (*lp)->next != NULL; lp = &(*lp)->next){
    printf("%s\n",(*lp)->text);
  }
  return 0;
}
