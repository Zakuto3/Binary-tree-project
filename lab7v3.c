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

struct product{
  char nameOfproduct[30];
  float amount;
  char units[30];
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
void fail(void);


int main()
{
  //setlocale(LC_ALL,""); //<-- hur berör denna en malloc?
  struct shoppinglist shoplist;
  char userchoice;
  bool run = true;
  shoplist.quantity = 0;
  shoplist.products = calloc(1,sizeof(shoplist.products));
  if (shoplist.products == NULL) fail();

  while (run)
  {
    //printf("%.1f\n",shoplist.products[0].amount);
    printf("Menu: \n\tpress 1-5\n\t[1]Add product\n\t[2]Show products\n\t[3]Remove a product\n\t[4]Change a product\n\t[5]Save list to file\n\t[6]Load list from file\n\t[7]Exit program\n");
    scanf("%c",&userchoice);
    fflush(stdin);
    switch (userchoice)
    {
      case '1':
        shoplist.products = realloc(shoplist.products, 1*sizeof(shoplist.products));
        if(shoplist.products==NULL) fail();
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
  char errorcheck, run='r';
  //templist.products = realloc(templist.products, 1*sizeof(templist.products)); <-- fråga vf detta int funkar, ngt med pekare?
  printf("\nName of product: ");
  gets(templist->products[*index].nameOfproduct);

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

  printf("\nUnits of product: ");
  gets(templist->products[*index].units);
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
    printf("%-3.1f",templist->products[userchoice].amount);
    printf("%s\n",templist->products[userchoice].units);

    addproduct(templist,&userchoice);
  }
}

void savetofile(struct shoppinglist *templist, int *index)
{
  int i, j=0;
  FILE * fPointer;
  fPointer = fopen("fileName", "w");

      //Sparar structens innehåll i den nyss skapade filen.
      for(i=0; i < *index; i++){
          fprintf(fPointer, "\t%s\t%f\t%s\n\n", templist->products[i].nameOfproduct, templist->products[i].amount, templist->products[i].units);
          j++;
      }

  //Stänger filens stream.
  fclose(fPointer);

      //Om length stämmer överens med antalet loopar är det lyckat, annars inte.
      if(*index == j){
          printf("Transfer successful!\n");
      }       else{
                  printf("Something went wrong, try again\n");
              }
}

void readfromfile(struct shoppinglist *templist, int *index)
{
  FILE *fp;
  fp = fopen("bugtest", "rb");
  if(fp == NULL)
    fail();

  printf("Reading from textfile... \n");
  fread(index, sizeof(int), 1, fp);
  printf("%d",*index);

  templist->products = malloc(sizeof(templist->products)*(*index));
  if(templist->products == NULL)
    fail();

  fread(templist->products, sizeof(templist->products), *index, fp);
  printf("Reading complete\n");
  fclose(fp);
}
void fail(void) {printf("Failed to allocate memory."); exit(EXIT_FAILURE);}
