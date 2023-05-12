#include"total.h"
#pragma warning(disable:4996)
#pragma warning(disable:6011)
#pragma warning(disable:6031)
//******************************************************
void create_account() {
    account* new_account = (account*)malloc(sizeof(account));
    if (new_account == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }
    system("cls");
    printf("          *******�����˻�����ϵͳ*******\n\n\n");
    printf("������������\n");
    scanf_s("%s", new_account->name,20);
    printf("�������˺ţ�\n");
    scanf_s("%s", new_account->id,20);
    printf("���������룺\n");
    scanf_s("%s", new_account->password,20);
    printf("�����������\n");
    scanf_s("%lf", &new_account->balance);
    FILE* fp = fopen("account.txt", "a");
    if (fp == NULL) {
        printf("�ļ���ʧ�ܣ�\n");
        free(new_account);
        return;
    }
    fprintf(fp, "%s %s %s %.2f\n", new_account->name, new_account->id, new_account->password, new_account->balance);
    fclose(fp); 
    free(new_account); 
    printf("�����˻��Ѵ����ɹ���\n");
}
//******************************************************
struct account* head = NULL;
//******************************************************
void login() {
    char id[20] = { 0 }; 
    char password[20] = { 0 };
    int count = 0; 
    int flag = 0;


    struct account* p; 
    FILE* fp = fopen("account.txt", "r"); 
    if (fp == NULL) { 
        printf("�ļ�������\n");
        return;
    }
    while (!feof(fp)) { 
        struct account* temp = (struct account*)malloc(sizeof(account));
            fscanf(fp, "%s %s %s %lf", temp->name, temp->id, temp->password, &temp->balance); 
        temp->next = NULL; 
        if (head == NULL) { 
            head = temp;
        }
        else { 
            p = head;
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = temp;
        }
    }
    fclose(fp);


    printf("����������id��\n");
    scanf_s("%s", id,20);
    printf("�������������룺\n");
    scanf_s("%s", password,20);
    p = head; 
    while (p != NULL) {
        if (strcmp(p->id, id) == 0) { 
            if (strcmp(p->password, password) == 0) { 
                system("cls");
                printf("**********************��¼�ɹ�***************************\n\n\n\n");
                printf("                    �𾴵Ŀͻ� %s ���ã� \n", p->name);
                printf_login();
                flag = 1;
                break;
                //return; 
            }
            else { //������벻��ȷ
                count++; 
                if (count < 3) {
                    printf("����������������룺\n");
                    scanf_s("%s", password,20);
                }
                else { 
                    printf("�������������࣬�˳�����\n");
                    exit(0); 
                }
            }
        }
        else { 
            p = p->next;
        }
       
    }
   if (p == NULL) {
        printf("id������\n");
    }
   while (flag == 1) {
       int chose = 0;
       scanf_s("%d", &chose);
       if (chose == 1) {
           printf("��������� %.2lf\n",get_balance(head, p->id, p->password));
       }
       else if (chose == 2) {
           printf("����������");
           double amount = 0;
           scanf_s("%lf", &amount);
           if (deposit(p->id, amount) == 1) {
               printf("���ɹ�\n");
           }
           else
               printf("���ʧ�ܣ�����ϵ����Ա\n");
       }
       else if (chose == 3) {
           printf("������ȡ����\n");
           double amount = 0;
           scanf_s("%lf", &amount);
           if (withdraw(p->id, p->password, amount) == 1) {
               printf("ȡ��ɹ���\n");
           }
           else
               printf("ȡ��ʧ��\n");
       }
       else if (chose == 4) {
           printf("������Է��˻�\n");
           char id[20];
           double amount;
           scanf_s("%s",id,20);
           printf("������ת�˽��\n");
           scanf_s("%lf", &amount);
           if (transfer(p->id, p->password, id, amount) == 1) {
               printf("ת�˳ɹ���");
           }
           else
               printf("ת��ʧ��");
       }
       else if (chose == 5) {
           break;
       }
       else {
           printf("������󣡣���\n");
       }
       //****************************************************
      


       printf_login();
   }
}
//******************************************************
double get_balance(account* head, char* id, char* password) {
    account* current = head;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0 && strcmp(current->password, password) == 0) {
            
            return current->balance;
        }
        current = current->next;
    }
    printf("��ȡʧ��\n");
    return -1.0;
}
//******************************************************
int deposit(char* id, double amount) {
    FILE* fp = fopen("account.txt", "r");
    if (fp == NULL) {
        printf("�޷����ļ�\n");
        return 0;
    }
   
    account* head = NULL;
    account* tail = NULL;
    account temp;
    int flag = 0;
    while (fscanf(fp, "%s %s %s %lf", temp.name, temp.id, temp.password, &temp.balance) != EOF) {
        account* node = (account*)malloc(sizeof(account));
        strcpy(node->name, temp.name);
        strcpy(node->id, temp.id);
        strcpy(node->password, temp.password);
        node->balance = temp.balance;
        node->next = NULL;
        if (head == NULL) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
        //����ҵ�Ŀ���˺�
        if (strcmp(temp.id, id) == 0) {
            node->balance += amount;
            flag = 1;
        }
    }

    fclose(fp);
    //���û���ҵ�Ŀ���˺�
    if (flag == 0) {
        printf("û���ҵ����˺�\n");
        return 0;
    }
    fp = fopen("account.txt", "w");
    if (fp == NULL) {
        printf("�޷����ļ�\n");
        return 0;
    }

    account* p = head;
    while (p != NULL) {
        fprintf(fp, "%-20s %-20s %-20s %-20.2lf\n", p->name, p->id, p->password, p->balance);
        p = p->next;
    }

    fclose(fp);
    return 1;
}
//******************************************************
int withdraw(char* id, char* password, double amount) {

    FILE* fp = fopen("account.txt", "r");
    if (fp == NULL) {
        printf("�޷����ļ�\n");
        return 0;
    }
    account* head = NULL;

    account* tail = NULL;

    account temp;

    int flag = 0;

    while (fscanf(fp, "%s %s %s %lf", temp.name, temp.id, temp.password, &temp.balance) != EOF) {

        account* node = (account*)malloc(sizeof(account));
        strcpy(node->name, temp.name);
        strcpy(node->id, temp.id);
        strcpy(node->password, temp.password);
        node->balance = temp.balance;
        node->next = NULL;
     
        if (head == NULL) {
            head = node;
            tail = node;
        }
  
        else {
            tail->next = node;
            tail = node;
        }
        
        if (strcmp(temp.id, id) == 0 && strcmp(temp.password, password) == 0 && temp.balance >= amount) {
            node->balance -= amount;
            flag = 1;
        }
    }

    fclose(fp);
 
    if (flag == 0) {
        printf("�˺Ż�������������\n");
        return 0;
    }
  
    fp = fopen("account.txt", "w");
    if (fp == NULL) {
        printf("�޷����ļ�\n");
        return 0;
    }
    account* p = head;
    while (p != NULL) {
        fprintf(fp, "%-20s %-20s %-20s %-20.2lf\n", p->name, p->id, p->password, p->balance);
        p = p->next;
    }

    fclose(fp);
    return 1;
}
//******************************************************
int transfer(char* id_out, char* password_out, char* id_in, double amount) {
    //���ļ�
    FILE* fp = fopen("account.txt", "r");
    if (fp == NULL) {
        printf("�޷����ļ�\n");
        return 0;
    }
    account* head = NULL;
    account* tail = NULL;
    account temp;
    int flag_out = 0;
    int flag_in = 0;
    while (fscanf(fp, "%s %s %s %lf", temp.name, temp.id, temp.password, &temp.balance) != EOF) {
     
        account* node = (account*)malloc(sizeof(account));
        strcpy(node->name, temp.name);
        strcpy(node->id, temp.id);
        strcpy(node->password, temp.password);
        node->balance = temp.balance;
        node->next = NULL;
     
        if (head == NULL) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
   
        if (strcmp(temp.id, id_out) == 0 && strcmp(temp.password, password_out) == 0 && temp.balance >= amount) {
            node->balance -= amount;
            flag_out = 1;
        }
  
        if (strcmp(temp.id, id_in) == 0) {
            node->balance += amount;
            flag_in = 1;
        }
    }

    fclose(fp);
    if (flag_out == 0 || flag_in == 0) {
        printf("ת���˺Ż��������������û���ҵ�ת���˺�\n");
        return 0;
    }
    fp = fopen("account.txt", "w");
    if (fp == NULL) {
        printf("�޷����ļ�\n");
        return 0;
    }
    account* p = head;
    while (p != NULL) {
        fprintf(fp, "%-20s %-20s %-20s %-20.2lf\n", p->name, p->id, p->password, p->balance);
        p = p->next;
    }
    fclose(fp);
    return 1;
}
//******************************************************
void admin() {
    char admin_id[20] = { 0 };
    char admin_password[20] = { 0 };
    printf("�������˻�\n");
    scanf_s("%s", admin_id,20);
    printf("����������\n");
    scanf_s("%s", admin_password,20);
    if (strcmp(admin_id, "admin") != 0){
        if (strcmp(admin_password, "123456") != 0) {
            printf("�˺Ż��������,�����˳����򡣡���\n");
            system("pause");
            return;
        }
        printf("�˺Ŵ���\n");
        return;
    }
    while (1) {
        printf_admin();
        struct account* p;
        FILE* fp = fopen("account.txt", "r");
        if (fp == NULL) {
            printf("�ļ�������\n");
            return;
        }
        while (!feof(fp)) {
            struct account* temp = (struct account*)malloc(sizeof(account));
           fscanf(fp, "%s %s %s %lf", temp->name, temp->id, temp->password, &temp->balance);
            temp->next = NULL;
            if (head == NULL) {
                head = temp;
            }
            else {
                p = head;
                while (p->next != NULL) {
                    p = p->next;
                }
                p->next = temp;
            }
        }
        fclose(fp);
        int flag = 0;
        scanf_s("%d", &flag);
        if (flag == 1) {
            char name[20] = { 0 }, id[20] = { 0 };
            printf("���������ѯ�˻����Լ�id\n");
            scanf_s("%s",name,20);
            getchar();
            scanf_s("%s", id,20);
            getchar();
            if (find_account(head, name, id) == 1) {
               // printf("***********************************");
            }
            else
                printf("�û�������\n");
        }
        else if (flag == 2) {
            char password[20] = { 0 }, id[20] = { 0 };
            printf("���������޸��˻�id\n");
            scanf_s("%s", id, 20);
            printf("���������޸��˻�����\n");
            scanf_s("%s", password, 20);
            modify_account(id,password);
        }
        else if (flag == 3) {
            return;
        }
        else
            printf("�������");
    }
}

int find_account(account* head, char* name, char* id) {
    account* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->id, id) == 0) {
            printf("����: %s\n", current->name);
            printf("�˻�: %s\n", current->id);
            printf("����: %s\n", current->password);
            printf("���: %.2f\n", current->balance);
            return 1;
        }
        current = current->next;
    }
    return 0;
}
//**************************************************************************************
void modify_account(char* user_id, char* user_password) {
    FILE* fp = fopen("account.txt", "r+");
    if (fp == NULL) {
        printf("�޷����ļ�\n");
        return;
    }

    account temp;
    int found = 0;
    while (fread(&temp, sizeof(account), 1, fp)) {
        if (strcmp(temp.id, user_id) == 0 && strcmp(temp.password, user_password) == 0) {
            found = 1;

            printf("�û���Ϣ:\n");
            printf("����: %s\n", temp.name);
            printf("�˺�: %s\n", temp.id);
            printf("����: %s\n", temp.password);
            printf("���: %.2lf\n", temp.balance);

            char input[100];
            printf("�������µ�����: ");
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("�������\n");
                break;
            }
            sscanf(input, "%s", temp.name);
            printf("�������µ�����: ");
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("�������\n");
                break;
            }
            sscanf(input, "%s", temp.password);
            printf("�������µ����: ");
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("�������\n");
                break;
            }
            sscanf(input, "%lf", &temp.balance);

            fseek(fp, -(long)sizeof(account), SEEK_CUR);
            fwrite(&temp, sizeof(account), 1, fp); 
            fseek(fp, 0, SEEK_CUR);
        }
    }

    if (!found) {
        printf("δ�ҵ��û�\n");
    }

    fclose(fp);
}