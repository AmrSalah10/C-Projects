#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

struct user
{
   char user_name[50];
   char password[20];
};

struct account
{
   char account_number[15];
   char name[20];
   char address[50];
   float balance;
   char mobile[20];
   char date_opened[20];
};

int USER_LEN = 3;
int ACCOUNT_LEN = 2;
struct user users_arr[3];
struct account accounts_arr[2];
char line_buffer[100];
char cell_buffer[100];

// load users
struct users *load_users(){
   int usr_indx = 0;
   FILE *users_file;
   users_file = fopen("users.txt", "rb");
   if(users_file == NULL)
   {
      printf("Error opening file\n");
      exit(1);
   }

   while (fgets(line_buffer, sizeof(line_buffer), users_file) != NULL){
      struct user user;
      sscanf(line_buffer, "%s %s", user.user_name, user.password);
      users_arr[usr_indx] = user;
      usr_indx++;
   }

   fclose(users_file);
}

// login
int action_login(){
   char user_name[100];
   char password[100];
   int error_type;
   int password_try = 3;
   bool logged_in = false;

   while (password_try > 0 && logged_in == false)
   {
      printf("User Name: \n");
      scanf("%s", user_name);
      printf("Password: \n");
      scanf("%s", password);
      
      for(int i=0; i < USER_LEN; i++){
         error_type = -1;
         
         if(strcmp(user_name, users_arr[i].user_name) == 0 && strcmp(password, users_arr[i].password) == 0){
            logged_in = true;
            printf("Welcome Back %s!\n", user_name);
            return 1;
         }
         else if (strcmp(user_name, users_arr[i].user_name) == 0 && strcmp(password, users_arr[i].password) != 0)
         {
            error_type = 0;
            break;
         }
         else
         {
            error_type = 1;
            continue;
         }
      }
      if (error_type == 0){
         printf("Please Check Password!\n");
      }
      else if (error_type == 1){
         printf("Please Check User Name or Password!\n");
      }
   }
   return 0;
}

// load accounts
struct account *load_accounts(){
   int acc_indx = 0;
   FILE *accounts_file;
   accounts_file = fopen("accounts.txt", "rb");

   if(accounts_file == NULL)
   {
      printf("Error opening file\n");
      exit(1);
   }

   while (fgets(line_buffer, sizeof(line_buffer), accounts_file) != NULL){
      struct account acc;
      sscanf(line_buffer, "%50[^,],%50[^,],%50[^,],%f,%50[^,],%50[^,]", acc.account_number, acc.name, acc.address, &acc.balance, acc.mobile, acc.date_opened);
      accounts_arr[acc_indx] = acc;
      acc_indx++;
   }
   fclose(accounts_file);

   return accounts_arr;
}

// search
void validate_account_number(char account_number[]){
   int length = strlen(account_number);

   if (length != 10)
   {
      printf("Error: The account number not equal 10 characters!");
      return;
   }
   
   for (size_t i = 0; i < length; i++)
   {
      if (isdigit(account_number[i]) == 0)
      {
         printf("Error: The account number can't have undigit item!");
      }
   }
   return;
}

int action_search(struct account *ac_arr){
   // search
   char account_number[10];
   printf("Enter Account Number: \n");
   scanf("%s", account_number);
   validate_account_number(account_number);

   // for(int i=0; i < ACCOUNT_LEN; i++){
   //    printf("Account Number: %s\n", ac_arr[i].account_number);
   //    printf("Name: %s\n", ac_arr[i].name);
   //    printf("E-mail: %s\n", ac_arr[i].address);
   //    printf("Balance: %f $\n", ac_arr[i].balance);
   //    printf("Mobile: %s\n", ac_arr[i].mobile);
   //    printf("Date Opened: %s\n", ac_arr[i].date_opened);
   // }   
   return 0;
}

int main()
{
   printf("Bank Management System\n");
   printf("========================\n");
   // load users
   struct users *usr_arr;
   usr_arr = load_users();

   // login
   int login = action_login();

   // load accounts
   struct account *ac_arr;
   if (login){
      int action_no;
      ac_arr = load_accounts();

      printf("Actions menu, please choose action number: \n");
      printf("1- Search \n");
      scanf("%d", &action_no);
     
      switch (action_no)
      {
         case 1:
            action_search(ac_arr);
            break;
      }
   }
   return 0;
}
