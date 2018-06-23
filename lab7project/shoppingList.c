#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

#include "C:\lab7project\shoppingList.h"
void checkunits(struct shoppinglist *templist);
void printlist(struct shoppinglist *templist)
{
  int i;
  int index = templist->quantity;
  if (index == 0)
  {
    printf("The list is empty\n");
  }
  else
  {
    for (i = 0; i < index; i++)
    {
      printf("%d.%-10s",i+1,templist->products[i].nameOfproduct);
      printf("%-3g",templist->products[i].amount);
      printf("%s\n",templist->products[i].units);
    }

  }
}

void addproduct(struct shoppinglist *templist)
{
  char errorcheck, run='r';
  int index = templist->quantity;
  if (index != 0)
  {
    templist->products = (struct product*)realloc(templist->products,sizeof(struct product)*(index+1));
    if(templist->products==NULL)
    fail(1);
  }
  else
  {
    templist->products = (struct product*)calloc(1,sizeof(struct product));
  }

  printf("\nName of product: ");
  scanf("%s",templist->products[index].nameOfproduct);
  fflush(stdin);

  printf("\nAmount of product: ");
  while (run == 'r') //Kollar så att det är en positiv tal + "." och inget annat, dvs decimaltal.
  {
    if (scanf("%f%c", &templist->products[index].amount, &errorcheck) == 2 && isspace(errorcheck) && templist->products[index].amount > 0)
    {
      run = 's';
      fflush(stdin);

    }
    else
    {
      printf("\nError in input, Correct example: 3.5");
      printf("\nAmount of product: ");
      fflush(stdin);
    }

    checkunits(templist);
  }

  templist->quantity = templist->quantity+1;
}

void removeproduct(struct shoppinglist *templist)
{
  int index = templist->quantity;
  int userchoice,i;
  if (index==0)
  {
    printlist(templist);
  }
  else
  {
    printlist(templist);
    printf("Which product do you want to remove?: ");
    scanf("%d",&userchoice);
    fflush(stdin);
    printf("%d.%-10s",userchoice+1,templist->products[userchoice-1].nameOfproduct);
    printf("%-3g",templist->products[userchoice-1].amount);
    printf("%s",templist->products[userchoice-1].units);
    printf(" got removed.\n");

    if(userchoice <= index)
    {
      for (i = userchoice; i <= index; i++)
      {
        templist->products[i-1] = templist->products[i];
      }

      templist->quantity = templist->quantity - 1;// if 0, do something!!
      templist->products = (struct product*)realloc(templist->products,sizeof(struct product)*(templist->quantity));
      if (templist->products == NULL && templist->quantity != 0)
       fail(1);

    }
    else
    {
      printf("The list have only %d Products.\n",index);
    }
  }
}

void changeproduct(struct shoppinglist *templist)
{
  int index = templist->quantity;
  int userchoice;
  char errorcheck, run = 'r';
  if (index==0)
  {
    printlist(templist);
  }
  else
  {
    printlist(templist);
    printf("which item do you wish to change?\n");
    scanf("%d",&userchoice);
    userchoice--;
    fflush(stdin);
    printf("Current amount: ");
    printf("%-3g",templist->products[userchoice].amount);
    printf("\nAmount of product: ");
    while (run == 'r')
    {//Kollar så att det är en positiv tal + "." och inget annat, dvs decimaltal.
      if (scanf("%f%c", &templist->products[userchoice].amount, &errorcheck) == 2 && isspace(errorcheck) && templist->products[userchoice].amount > 0)
      {
        run = 's';
        fflush(stdin);
      }
      else
      {
        printf("\nError in input, Correct example: 3.5");
        printf("\nAmount of product: ");
        fflush(stdin);
      }
    }
  }
}

void savetofile(struct shoppinglist *templist)
{
  int index = templist->quantity;
  if (index == 0)
  {
    printf("No list to save.\n");
  }
  else
  {
  char fileName[20];
  printf("Name your file: ");
  gets(fileName);
  fflush(stdin);
  FILE *fp;
  fp = fopen(fileName,"wb");
  if(fp == NULL)
  fail(2);

  printf("Writing to binary file...\n");
  fwrite(&index, sizeof(int),1,fp);
  fwrite(templist->products,sizeof(struct product),index,fp);
  printf("Writing to binary file successful\n");
  fclose(fp);
  }
}

void readfromfile(struct shoppinglist *templist)
{
  int index = templist->quantity;
  char fileName[20],savecheck = '1';
  if (index>0)
  {
    printf("Press 0 to save the current list.");
    scanf("%c",&savecheck);
    fflush(stdin);
      if (savecheck == '0')
      {
        savetofile(templist);
      }
  }
  printf("Which file would you like to load?\n");
   gets(fileName);
   fflush(stdin);
  FILE *fp;
  fp = fopen(fileName, "rb");
  if(fp == NULL)
  {
    printf("Could not open file..\n");
    fclose(fp);
  }
  else
  {
  printf("Reading from textfile... \n");
  fread(&index, sizeof(index), 1, fp);
  templist->quantity = index;
  templist->products = (struct product*)calloc(index,sizeof(struct product));
  if(templist->products == NULL)
    fail(1);

  fread(templist->products, sizeof(struct product), index, fp);
  printf("Reading complete\n");
  fclose(fp);
  }
}

void checkunits(struct shoppinglist *templist)
{
  int run = 1, index = templist->quantity;

    printf("\nUnits of product: CHANGED?! ");
    //gets(templist->products[index].units);
    scanf("%s",templist->products[index].units);
    fflush(stdin);

}
void fail(int error)
{
  switch (error) {
  case 1:
  printf("Failed to allocate memory.");
    break;
  case 2:
  printf("could not open file.");
  break;
  default:
  printf("ERROR");
  break;
  }
  exit(EXIT_FAILURE);
}
