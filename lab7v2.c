/* Kodning av Eibech Barakat DVA117 -
 HT17, Lärare: Caroline Uppsäll*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include<conio.h>
typedef int bool;
#define true 1
#define false 0
#define sineofunits 10
#define sizeofname 20

struct product{
  char nameOfproduct[sizeofname];
  float amount;
  char units[sineofunits];
};

struct shoppinglist{
  struct product *products;
  int quantity;
};


void addproduct(struct shoppinglist *templist, int *index);
void printlist(struct shoppinglist *templist, int *index);
void removeproduct(struct shoppinglist *templist, int *index);
void changeproduct(struct shoppinglist *templist, int *index);
void savetofile(struct shoppinglist *templist, int *index);
void readfromfile(struct shoppinglist *templist, int *index);
void fail(int error);
void savetofileCheck();


int main()
{
  //setlocale(LC_ALL,""); //<-- hur berör denna en malloc?
  struct shoppinglist shoplist;
  char userchoice;
  bool run = true;
  shoplist.quantity = 0;
  shoplist.products = (struct product*)calloc(1,sizeof(struct product));
  if (shoplist.products == NULL)
  fail(1);


  while (run)
  {
    //printf("%.1f\n",shoplist.products[0].amount);
    //printf("%d\n",shoplist.quantity );
    printf("Menu: \n\tpress 1-5\n\t[1]Add product\n\t[2]Show products\n\t[3]Remove a product\n\t[4]Change a product\n\t[5]Save list to file\n\t[6]Load list from file\n\t[7]Exit program\n");
    scanf("%c",&userchoice);
    fflush(stdin);
    switch (userchoice)
    {
      case '1':
        addproduct(&shoplist,&shoplist.quantity);
        break;
      case '2':
        printlist(&shoplist,&shoplist.quantity);
        break;
      case '3':
        removeproduct(&shoplist,&shoplist.quantity);
        break;
      case '4':
        changeproduct(&shoplist,&shoplist.quantity);
        break;
      case '5':
        savetofile(&shoplist,&shoplist.quantity);
        break;
      case '6':
        readfromfile(&shoplist,&shoplist.quantity);
        break;
      case '7':
        run=false;
        free(shoplist.products);
        shoplist.products=NULL;
        break;
        default:
        printf("Error, Try again...\n");
        break;
    }
  }
  return 0;
}
void printlist(struct shoppinglist *templist, int *index)
{
  int i;
  if (*index == 0)
  {
    printf("The list is empty\n");
  }
  else
  {
    for (i = 0; i < *index; i++)
    {
      printf("%d.%-10s",i+1,templist->products[i].nameOfproduct);
      printf("%-3g",templist->products[i].amount);
      printf("%s\n",templist->products[i].units);
    }

  }
}

void addproduct(struct shoppinglist *templist, int *index)
{
  char errorcheck, run='r',tempname[sizeofname],tempunits[sineofunits];
  int lencheck;
  if (*index != 0)
  {
    templist->products = (struct product*)realloc(templist->products,sizeof(struct product)*(*index+1));
    if(templist->products==NULL)
    fail(1);
  }

  printf("\nName of product: ");
  scanf("%s",tempname);
  fflush(stdin);
  lencheck = strlen(tempname);
  while (run == 'r')
  {
    if (lencheck>sizeofname)
    {
      printf("\nGiven name was to long");
      printf("\nName of product: ");
      scanf("%s",tempname);
      fflush(stdin);
      lencheck = strlen(tempname);
    }
    else
    {
      strcpy(templist->products[*index].nameOfproduct,tempname);
      run = 's';
    }
  }
  run = 'r';
  printf("\nAmount of product: ");

  while (run == 'r') //Kollar så att det är en positiv tal + "." och inget annat, dvs decimaltal.
  {
    if (scanf("%f%c", &templist->products[*index].amount, &errorcheck) == 2 && isspace(errorcheck) && templist->products[*index].amount > 0)
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
  run = 'r';
  printf("\nUnits of product: ");
  scanf("%s",tempunits);
  fflush(stdin);
  lencheck = strlen(tempunits);
  while (run == 'r')
  {
    if (lencheck>sineofunits)
    {
      printf("\nGiven unit was to long");
      printf("\nUnits of product: ");
      scanf("%s",tempunits);
      fflush(stdin);
      lencheck = strlen(tempunits);
    }
    else
    {
      strcpy(templist->products[*index].units,tempunits);

      run = 's';
    }
  }
  run = 'r';
  *index = *index + 1;
}

void removeproduct(struct shoppinglist *templist, int *index)
{
  int userchoice,i;
  if (*index==0)
  {
    printlist(templist,index);
  }
  else
  {
    printlist(templist,index);
    printf("Which product do you want to remove?: ");
    scanf("%d",&userchoice);
    fflush(stdin);
    printf("%d.%-10s",userchoice+1,templist->products[userchoice-1].nameOfproduct);
    printf("%-3g",templist->products[userchoice-1].amount);
    printf("%s",templist->products[userchoice-1].units);
    printf(" got removed.\n");

    if(userchoice <= *index)
    {
      for (i = userchoice; i <= *index; i++)
      {
        templist->products[i-1] = templist->products[i];
      }

      *index = *index - 1;
    }
    else
    {
      printf("The list have only %d Products.\n",*index);
    }
  }
}

void changeproduct(struct shoppinglist *templist, int *index)
{
  int userchoice;
  if (*index==0)
  {
    printlist(templist,index);
  }
  else
  {
    printlist(templist,index);
    printf("which item do you wish to change?\n");
    scanf("%d",&userchoice);
    userchoice--;
    fflush(stdin);
    printf("Current product: ");
    printf("%d.%-10s",userchoice+1,templist->products[userchoice].nameOfproduct);
    printf("%-3g",templist->products[userchoice].amount);
    printf("%s\n",templist->products[userchoice].units);

    addproduct(templist,&userchoice);
  }
}

void savetofile(struct shoppinglist *templist, int *index)
{
  if (*index == 0)
  {
    printf("No list to save.\n");
  }
  else
  {
  int i;
  struct product tempProduct[*index];
  printf("index:%d\n",*index);
  for (i = 0; i < *index; i++)
  {
    tempProduct[i] = templist->products[i];
    printf("products: %d\n",i);
  }
  char fileName[20];
  FILE *fp;
  printf("FILE *FP HAPPENED\n");
  /*printf("Name your file: ");
  gets(fileName);
  fflush(stdin);
   = NULL;
  fp = fopen("OPEN","wb");
  if(fp == NULL)
  fail(2);*/

  if((fp= fopen("OPEN", "wb"))==NULL)
    printf("Failed to open File,\n");
    else
    {
      printf("Writing to binary file...\n");
      fwrite(index, sizeof(int),1,fp);
      fwrite(tempProduct,sizeof(struct product),*index,fp);
      printf("Writing to binary successful\n");
      fclose(fp);
    }

  for (i = 0; i < *index; i++)
  {
    templist->products[i] = tempProduct[i];
  }
}
}

void readfromfile(struct shoppinglist *templist, int *index)
{
  char fileName[20],savecheck = 'y';
  if (*index>0)
  {
    printf("Press 0 to save the current list.");
    scanf("%c",&savecheck);
    fflush(stdin);
      if (savecheck == '0')
      {
        savetofile(templist,index);
      }
  }
  printf("Which file would you like to load?\n");
   gets(fileName);
   fflush(stdin);
  FILE *fp;
  fp = fopen(fileName, "rb");
  if(fp == NULL)
    fail(2);

  printf("Reading from textfile... \n");
  fread(index, sizeof(*index), 1, fp);
  printf("Index: %d\n",*index );
  templist->products = (struct product*)realloc(templist->products,sizeof(struct product)*10);
  if(templist->products == NULL)
    fail(1);

  fread(templist->products, sizeof(struct product), *index, fp);
  printf("Reading complete\n");
  fclose(fp);
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
void savetofileCheck()
{

  FILE *fp = NULL;
  fp = fopen("OPEN","wb");
  if(fp == NULL)
  fail(2);

  printf("Writing to binary file...\n");

    printf("Writing to binary successful\n");


  fclose(fp);

}
