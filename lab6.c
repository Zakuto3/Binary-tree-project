/* Kodning av Eibech Barakat DVA117 -
 HT17, Lärare: Caroline Uppsäll*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
typedef int bool;
#define true 1
#define false 0
#define size1 5
#define size2 5

struct product{
  char nameOfproduct[size1];
  char units[size2];
  float amount;
};

struct shoppinglist{
  struct product *products;
  int quantity;
};

void addproduct(struct shoppinglist *templist, int *index);
void printlist(struct shoppinglist *templist, int *index);
void removeproduct(struct shoppinglist *templist, int *index);
void changeproduct(struct shoppinglist *templist, int *index);
void fail(int error);


int main()
{
  //setlocale(LC_ALL,""); //<-- hur berör denna en malloc?
  struct shoppinglist shoplist;
  char userchoice;
  bool run = true;
  shoplist.quantity = 0;
  shoplist.products = (struct product*)calloc(1,sizeof(struct product));
  if (shoplist.products == NULL) fail(1);

  while (run)
  {
    printf("Menu: \n\tpress 1-5\n\t[1]Add Product\n\t[2]Show Products\n\t[3]remove a product\n\t[4]change a product\n\t[5]Exit program\n");
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

void addproduct(struct shoppinglist *templist, int *index)
{
  char errorcheck, run='r',tempname[size2],tempunits[size1];
  int lencheck;
  if (*index != 0)
  {
    templist->products = (struct product*)realloc(templist->products,sizeof(struct product)*1);
    if(templist->products==NULL)
    fail(1);
  }

  printf("\nName of product: ");
  scanf("%s",tempname);
  fflush(stdin);
  lencheck = strlen(tempname);
  while (run == 'r')
  {
    if (lencheck>size2)
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
    if (lencheck>size1)
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

    if(userchoice <= *index)
    {
      printf("%d.%-10s",userchoice+1,templist->products[userchoice-1].nameOfproduct);
      printf("%-3g",templist->products[userchoice-1].amount);
      printf("%s",templist->products[userchoice-1].units);
      printf(" got removed.\n");
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
