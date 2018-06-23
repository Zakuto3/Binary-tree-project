#ifndef SHOPPINGLIST_H
#define SHOPPINGLIST_H
typedef int bool;
#define true 1
#define false 0
#define size1 20
#define size2 10

struct product{
  char nameOfproduct[size1];
  float amount;
  char units[size2];
};

struct shoppinglist{
  struct product *products;
  int quantity;
};

//allocates products size and adds userinput to it.
void addproduct(struct shoppinglist *templist);

//prints out current list of products.
void printlist(struct shoppinglist *templist);

//removes item from list, allocates new memory size.
void removeproduct(struct shoppinglist *templist);

//Changes element Unit of user's choice.
void changeproduct(struct shoppinglist *templist);

//Creates file and saves list to it.
void savetofile(struct shoppinglist *templist);

//takes existing file and saves to products.
void readfromfile(struct shoppinglist *templist);

//Checks if user inputs correct unit scale
//void checkunits(struct shoppinglist *templist);

//prints out right type of error message.
void fail(int error);
#endif
