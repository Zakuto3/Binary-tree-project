/* Kodning av Eibech Barakat DVA117 -
 HT17, Lärare: Caroline Uppsäll*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
typedef int bool;
#define true 1
#define false 0
#define size 5

struct product{
  char nameOfproduct[30];
  char units[10];
  float amount;
};

struct shoppinglist{
  struct product products[size];
  int quantity;
};

void addproduct(struct shoppinglist *templist, int *index); //tar emot pekare till struct för tillsättning, och index som antal strukter
void printlist(struct shoppinglist *templist, int *index);  //tar emot pekare till struct för print, och index som antal strukter

int main()
{
  struct shoppinglist shoplist;
  shoplist.quantity = 0;
  char userchoice;
  bool run = true;
  setlocale(LC_ALL,"");

  while (run)
  {
    printf("Meny: \n\tTryck 1-3\n\t[1]Lägg till produkt\n\t[2]Visa produkter\n\t[3]Stäng program\n");
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
        run=false;
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
    printf("Listan är tom\n");
  }
  else
  {
    for (i = 0; i < *index; i++)
    {
      printf("%-10s",templist->products[i].nameOfproduct);
      printf("%-3g",templist->products[i].amount);
      printf("%s\n",templist->products[i].units);
    }

  }
}

void addproduct(struct shoppinglist *templist, int *index)
{
  char errorcheck, run='r';
  if (*index == 5)
  {
    printf("Listan är full\n");
  }
  else
  {
    printf("\nAnge namn på varan: ");
    gets(templist->products[*index].nameOfproduct);
    printf("\nAnge mått enhet: ");
    gets(templist->products[*index].units);
    printf("\nAnge mängd: ");
    while (run == 'r')
    {//följande ifsats kollar så att användaren anger antinge positivt heltal eller ett positivt decimaltal
      if (scanf("%f%c", &templist->products[*index].amount, &errorcheck) == 2 && isspace(errorcheck) && templist->products[*index].amount > 0)
      {
        run = 's';
        fflush(stdin);
      }
      else
      {
        printf("\nFelaktig inmatning, korrekt exempel: 3,14");
        printf("\nAnge mängd: ");
        fflush(stdin);
      }
    }
    *index = *index + 1;
  }
}
