#include"total.h"
#pragma warning(disable:4996)
#pragma warning(disable:6011)
#pragma warning(disable:6031)
//******************************************************
void create_account() {
    account* new_account = (account*)malloc(sizeof(account));
    if (new_account == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    system("cls");
    printf("          *******银行账户管理系统*******\n\n\n");
    printf("请输入姓名：\n");
    scanf_s("%s", new_account->name,20);
    printf("请输入账号：\n");
    scanf_s("%s", new_account->id,20);
    printf("请输入密码：\n");
    scanf_s("%s", new_account->password,20);
    printf("请输入存入余额：\n");
    scanf_s("%lf", &new_account->balance);
    FILE* fp = fopen("account.txt", "a");
    if (fp == NULL) {
        printf("文件打开失败！\n");
        free(new_account);
        return;
    }
    fprintf(fp, "%s %s %s %.2f\n", new_account->name, new_account->id, new_account->password, new_account->balance);
    fclose(fp); 
    free(new_account); 
    printf("您的账户已创建成功！\n");
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
        printf("文件不存在\n");
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


    printf("请输入您的id：\n");
    scanf_s("%s", id,20);
    printf("请输入您的密码：\n");
    scanf_s("%s", password,20);
    p = head; 
    while (p != NULL) {
        if (strcmp(p->id, id) == 0) { 
            if (strcmp(p->password, password) == 0) { 
                system("cls");
                printf("**********************登录成功***************************\n\n\n\n");
                printf("                    尊敬的客户 %s 您好！ \n", p->name);
                printf_login();
                flag = 1;
                break;
                //return; 
            }
            else { //如果密码不正确
                count++; 
                if (count < 3) {
                    printf("密码错误，请重新输入：\n");
                    scanf_s("%s", password,20);
                }
                else { 
                    printf("密码错误次数过多，退出程序\n");
                    exit(0); 
                }
            }
        }
        else { 
            p = p->next;
        }
       
    }
   if (p == NULL) {
        printf("id不存在\n");
    }
   while (flag == 1) {
       int chose = 0;
       scanf_s("%d", &chose);
       if (chose == 1) {
           printf("您的余额是 %.2lf\n",get_balance(head, p->id, p->password));
       }
       else if (chose == 2) {
           printf("请输入存款金额");
           double amount = 0;
           scanf_s("%lf", &amount);
           if (deposit(p->id, amount) == 1) {
               printf("存款成功\n");
           }
           else
               printf("存款失败，请联系管理员\n");
       }
       else if (chose == 3) {
           printf("请输入取款金额\n");
           double amount = 0;
           scanf_s("%lf", &amount);
           if (withdraw(p->id, p->password, amount) == 1) {
               printf("取款成功！\n");
           }
           else
               printf("取款失败\n");
       }
       else if (chose == 4) {
           printf("请输入对方账户\n");
           char id[20];
           double amount;
           scanf_s("%s",id,20);
           printf("请输入转账金额\n");
           scanf_s("%lf", &amount);
           if (transfer(p->id, p->password, id, amount) == 1) {
               printf("转账成功！");
           }
           else
               printf("转账失败");
       }
       else if (chose == 5) {
           break;
       }
       else {
           printf("输入错误！！！\n");
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
    printf("获取失败\n");
    return -1.0;
}
//******************************************************
int deposit(char* id, double amount) {
    FILE* fp = fopen("account.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件\n");
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
        //如果找到目标账号
        if (strcmp(temp.id, id) == 0) {
            node->balance += amount;
            flag = 1;
        }
    }

    fclose(fp);
    //如果没有找到目标账号
    if (flag == 0) {
        printf("没有找到该账号\n");
        return 0;
    }
    fp = fopen("account.txt", "w");
    if (fp == NULL) {
        printf("无法打开文件\n");
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
        printf("无法打开文件\n");
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
        printf("账号或密码错误或余额不足\n");
        return 0;
    }
  
    fp = fopen("account.txt", "w");
    if (fp == NULL) {
        printf("无法打开文件\n");
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
    //打开文件
    FILE* fp = fopen("account.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件\n");
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
        printf("转出账号或密码错误或余额不足或没有找到转入账号\n");
        return 0;
    }
    fp = fopen("account.txt", "w");
    if (fp == NULL) {
        printf("无法打开文件\n");
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
    printf("请输入账户\n");
    scanf_s("%s", admin_id,20);
    printf("请输入密码\n");
    scanf_s("%s", admin_password,20);
    if (strcmp(admin_id, "admin") != 0){
        if (strcmp(admin_password, "123456") != 0) {
            printf("账号或密码错误,即将退出程序。。。\n");
            system("pause");
            return;
        }
        printf("账号错误\n");
        return;
    }
    while (1) {
        printf_admin();
        struct account* p;
        FILE* fp = fopen("account.txt", "r");
        if (fp == NULL) {
            printf("文件不存在\n");
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
            printf("请输入需查询账户名以及id\n");
            scanf_s("%s",name,20);
            getchar();
            scanf_s("%s", id,20);
            getchar();
            if (find_account(head, name, id) == 1) {
               // printf("***********************************");
            }
            else
                printf("用户不存在\n");
        }
        else if (flag == 2) {
            char password[20] = { 0 }, id[20] = { 0 };
            printf("请输入需修改账户id\n");
            scanf_s("%s", id, 20);
            printf("请输入需修改账户密码\n");
            scanf_s("%s", password, 20);
            modify_account(id,password);
        }
        else if (flag == 3) {
            return;
        }
        else
            printf("输入错误");
    }
}

int find_account(account* head, char* name, char* id) {
    account* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->id, id) == 0) {
            printf("名字: %s\n", current->name);
            printf("账户: %s\n", current->id);
            printf("密码: %s\n", current->password);
            printf("余额: %.2f\n", current->balance);
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
        printf("无法打开文件\n");
        return;
    }

    account temp;
    int found = 0;
    while (fread(&temp, sizeof(account), 1, fp)) {
        if (strcmp(temp.id, user_id) == 0 && strcmp(temp.password, user_password) == 0) {
            found = 1;

            printf("用户信息:\n");
            printf("姓名: %s\n", temp.name);
            printf("账号: %s\n", temp.id);
            printf("密码: %s\n", temp.password);
            printf("余额: %.2lf\n", temp.balance);

            char input[100];
            printf("请输入新的姓名: ");
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("输入错误\n");
                break;
            }
            sscanf(input, "%s", temp.name);
            printf("请输入新的密码: ");
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("输入错误\n");
                break;
            }
            sscanf(input, "%s", temp.password);
            printf("请输入新的余额: ");
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("输入错误\n");
                break;
            }
            sscanf(input, "%lf", &temp.balance);

            fseek(fp, -(long)sizeof(account), SEEK_CUR);
            fwrite(&temp, sizeof(account), 1, fp); 
            fseek(fp, 0, SEEK_CUR);
        }
    }

    if (!found) {
        printf("未找到用户\n");
    }

    fclose(fp);
}