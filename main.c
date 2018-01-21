#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "list.h"

int
show(Link *list);

Link *
load(char *file);

int
save(char *file, Link *list);

int
main(int argc, char *argv[])
{
  char * file = (argc > 2) ? argv[2] : "file";
  if (argc <= 1)
    { 
      printf("there is no argument\n");
      return 1;     
    }
  Link *list = NULL;
  list = load(file);
  if (list = NULL)
    return 1;
  char * str = NULL;
  if (strcmp(argv[1],"add") == 0)
    {
      getline(&str, &0, stdin);
      if (list_add_order(&list, str, strcmp) != 0)
	free(str);
    }
  else if (strcmp(argv[1],"remove") == 0)
    {
      getline(&str, &0, stdin);
      list_delete_item(&list, str, strcmp, free);
      free(str);
    }
  else if (strcmp(argv[1],"show") == 0)
    {
      show(list);
    }
  else
    {
      printf("%s is not a valid option\n",argv[1]);
      return 2;
    }
  save(file,list);

  return 0;
}
int
show(Link *list)
{
  Link **lp;

  for (lp = &list; (*lp)->next != NULL; lp = &(*lp)->next)
    {
      printf("%s\n",(*lp)->text);
    }
  return 0;
}

Link *
load(char*file)
{
  FILE *fp;
  char s[MAXLINE];
  if ((fp = fopen(file,"r")) == NULL)
    {
      printf("could not open file\n");
      return newLink("",NULL);
    }
  Link **lp;
  Link *start;
  for (lp = &start; fscanf(fp,"%99s",s)==1; lp = &(*lp)->next)
    {
      if ((*lp = newLink(s,NULL)) == NULL)
	{
	  printf("no more memory\n");
	}
    }
  if ((*lp = newLink("",NULL)) == NULL)
    {
      printf("no more memory\n");
    }
  fclose(fp);
  return start;
}

int
save(char *file,Link *list)
{
  FILE *fp;
  Link **lp;
  fp = fopen(file,"w");
  for (lp = &list; (*lp)->next != NULL; lp = &(*lp)->next)
    {
      fprintf(fp,"%s\n", (*lp)->text);
      //if error on fp close and return 1
    }
  fprintf(fp,"%s\n", (*lp)->text);
  fclose(fp);
  return 0;
}
