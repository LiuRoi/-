#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include<ctype.h>
typedef struct account {
    char name[20] = {0}; //����
    char id[20] = { 0 }; //�˺�,����
    char password[20] = {0}; //����
    double balance; //���
    struct account* next;
} account;


void printf_menu();
void create_account();
void login();
void printf_login();
void admin();
int deposit(char* id, double amount);//�����˺ţ��������
int withdraw(char* id, char* password, double amount);//�����˻������룬��ȡ���
int transfer(char* id_out, char* password_out, char* id_in, double amount);//�����Լ��˻������룬Ҫת����˻������
double get_balance(account* head, char* id, char* password);//����ͷָ�룬�˻�������

void printf_admin();
int find_account(account* head, char* name, char* id);
void modify_account(char* user_id, char* user_password);