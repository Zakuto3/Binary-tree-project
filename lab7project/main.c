/* Kodning av Eibech Barakat DVA117 -
 HT17, Lärare: Caroline Uppsäll*/

 #include "C:\lab7project\shoppingList.c"
 #include "C:\lab7project\shoppingList.h"


 int main()
 {
   struct shoppinglist shoplist;
   char userchoice;
   bool run = true;
   shoplist.quantity = 0;

   while (run)
   {
     printf("Menu: \n\tpress 1-5\n\t[1]Add product\n\t[2]Show products\n\t[3]Remove a product\n\t[4]Change a product\n\t[5]Save list to file\n\t[6]Load list from file\n\t[7]Exit program\n");
     scanf("%c",&userchoice);
     fflush(stdin);
     switch (userchoice)
     {

       case '1':
         addproduct(&shoplist);
         break;
       case '2':
         printlist(&shoplist);
         break;
       case '3':
         removeproduct(&shoplist);
         break;
       case '4':
         changeproduct(&shoplist);
         break;
       case '5':
         savetofile(&shoplist);
         break;
       case '6':
         readfromfile(&shoplist);
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
