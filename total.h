#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include<ctype.h>
typedef struct account {
    char name[20] = {0}; //姓名
    char id[20] = { 0 }; //账号,卡号
    char password[20] = {0}; //密码
    double balance; //余额
    struct account* next;
} account;


void printf_menu();
void create_account();
void login();
void printf_login();
void admin();
int deposit(char* id, double amount);//传入账号，存款数额
int withdraw(char* id, char* password, double amount);//传入账户，密码，提取金额
int transfer(char* id_out, char* password_out, char* id_in, double amount);//传入自己账户，密码，要转入的账户，金额
double get_balance(account* head, char* id, char* password);//传入头指针，账户，密码

void printf_admin();
int find_account(account* head, char* name, char* id);
void modify_account(char* user_id, char* user_password);