#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable : 4996)
//创建商品
struct good
{
    int number, importCount, sellCount;
    float importPrice, exportPrice;
    char name[10];
    struct good* next;
};

//创建节点
struct good* createNode(int number, const char* name, int importCount, int sellCount,
    float importPrice, float exportPrice)
{
    struct good* newNode = (struct good*)malloc(sizeof(struct good));
    if (newNode == NULL)
    {
        printf("错误");
        exit(1);
    }
    strcpy(newNode->name, name);
    newNode->exportPrice = exportPrice;
    newNode->importCount = importCount;
    newNode->importPrice = importPrice;
    newNode->number = number;
    newNode->sellCount = sellCount;
    newNode->next = NULL;
    return newNode;
}

//尾部插入节点
void insertNode(struct good** head, int number, const char* name, int importCount, int sellCount,
    float importPrice, float exportPrice)
{
    struct good* newNode = createNode(number, name, importCount, sellCount,
        importPrice, exportPrice);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    struct good* temp = (*head);
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

//打印链表
void printList(struct good* head)
{
    if (head == NULL)
        return;
    while (head != NULL)
    {
        printf("编号%d 品名%s 进价%.2f 售价%.2f 进货量%d 销售量%d 销售额%.2f 剩余数%d 毛利%.2f\n", head->number,
            head->name, head->importPrice, head->exportPrice, head->importCount, head->sellCount,
            head->exportPrice * head->sellCount, head->importCount - head->sellCount, head->exportPrice * head->sellCount - head->importPrice * head->sellCount);
        head = head->next;
    }
}

//释放链表
void freeList(struct good* head)
{
    if (head == NULL)
        return;
    struct good* temp;
    while (head != NULL)
    {
        temp = head;
        head = temp->next;
        free(temp);
    }
}

//创建商品信息
void createGood(struct good** head)
{
    int number, importCount, sellCount;
    float importPrice, exportPrice;
    char name[10];
    printf("请输入品名: ");
    scanf("%9s", name);
    printf("请输入编号: ");
    scanf("%d", &number);
    printf("请输入进价: ");
    scanf("%f", &importPrice);
    printf("请输入售价: ");
    scanf("%f", &exportPrice);
    printf("请输入进货量: ");
    scanf("%d", &importCount);
    printf("请输入销售量: ");
    scanf("%d", &sellCount);
    insertNode(head, number, name, importCount, sellCount, importPrice, exportPrice);
    while (getchar() != '\n');
}

//删除商品
void deleteGood(struct good* head)
{
    int key;
    printf("输入要删除商品编号：");
    scanf("%d", &key);
    struct good* temp = head, * current;
    while ((temp->next)->number != key)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("错误");
        exit(1);
    }
    current = temp;
    temp = temp->next;
    current->next = temp->next;
    free(temp);
}

//编辑商品信息
void changeGood(struct good* head)
{
    int key1;
    printf("输入要修改商品编号：");
    scanf("%d", &key1);
    struct good* temp = head;
    while (temp != NULL && temp->number != key1)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("错误");
        exit(1);
    }
    printf("请输入品名: ");
    scanf("%9s", temp->name);
    printf("请输入编号: ");
    scanf("%d", &(temp->number));
    printf("请输入进价: ");
    scanf("%f", &(temp->importPrice));
    printf("请输入售价: ");
    scanf("%f", &(temp->exportPrice));
    printf("请输入进货量: ");
    scanf("%d", &(temp->importCount));
    printf("请输入销售量: ");
    scanf("%d", &(temp->sellCount));
}

//统计销售情况
void statGood(struct good* head)
{
    while (head != NULL)
    {
        printf("%s销售 %d\n", head->name, head->sellCount);
        head = head->next;
    }
}

//按剩余数查询
void findCount(struct good* head)
{
    int key1;
    printf("输入要查询剩余数：");
    scanf("%d", &key1);
    while (head != NULL)
    {
        if (head->importCount - head->sellCount == key1)
            printf("编号%d 品名%s 进价%.2f 售价%.2f 进货量%d 销售量%d 销售额%.2f 剩余数%d 毛利%.2f\n", head->number,
                head->name, head->importPrice, head->exportPrice, head->importCount, head->sellCount,
                head->exportPrice * head->sellCount, head->importCount - head->sellCount, head->exportPrice * head->sellCount - head->importPrice * head->sellCount);
        head = head->next;
    }
}

//按品名查询
void findName(struct good* head)
{
    char key[10];
    printf("输入要查找品名：");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    while (strcmp(head->name, key) != 0 && head != NULL)
    {
        head = head->next;
    }
    if (head == NULL)
    {
        printf("输入错误");
        exit(0);
    }
    printf("编号%d 品名%s 进价%.2f 售价%.2f 进货量%d 销售量%d 销售额%.2f 剩余数%d 毛利%.2f\n", head->number,
        head->name, head->importPrice, head->exportPrice, head->importCount, head->sellCount,
        head->exportPrice * head->sellCount, head->importCount - head->sellCount, head->exportPrice * head->sellCount - head->importPrice * head->sellCount);
}

//按毛利高低显示
void orderProfit(struct good* head)
{

    if (head == NULL)
        return;
    struct good* i, * j;
    int temp1, temp3;
    float temp4, temp2;
    for (i = head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->sellCount * i->exportPrice - i->sellCount * i->importPrice < j->sellCount * j->exportPrice - j->sellCount * j->importPrice)
            {
                temp1 = i->sellCount;
                temp2 = i->exportPrice;
                temp3 = i->importCount;
                temp4 = i->importPrice;
                i->sellCount = j->sellCount;
                i->exportPrice = j->exportPrice;
                i->importCount = j->importCount;
                i->importPrice = j->importPrice;
                j->sellCount = temp1;
                j->exportPrice = temp2;
                j->importCount = temp3;
                j->importPrice = temp4;
            }
        }
    }
}

//按销售额高低显示
void orderSellmoney(struct good* head) {
    struct good* i, * j;
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->sellCount * i->exportPrice < j->sellCount * j->exportPrice) {
                int temp1, temp3;
                float temp4, temp2;
                temp1 = i->sellCount;
                temp2 = i->exportPrice;
                temp3 = i->importCount;
                temp4 = i->importPrice;
                i->sellCount = j->sellCount;
                i->exportPrice = j->exportPrice;
                i->importCount = j->importCount;
                i->importPrice = j->importPrice;
                j->sellCount = temp1;
                j->exportPrice = temp2;
                j->importCount = temp3;
                j->importPrice = temp4;
            }
        }
    }
}

//菜单
void showMenu()
{
    printf("|------------------|\n");
    printf("|请输入选项编号 0-5:|\n");
    printf("|--1--创建商品档案--|\n");
    printf("|--2--编辑商品信息--|\n");
    printf("|--3--统计销售情况--|\n");
    printf("|--4--查询商品信息--|\n");
    printf("|--5--显示商品信息--|\n");
    printf("|--0--  退出系统  --|\n");
    printf("|-------------------|\n");
}

//编辑商品
void editGood(struct good* head)
{
    while (1)
    {
        printf("|-------------------|\n");
        printf("|请输入选项编号  0-4:|\n");
        printf("|--1-----添加新商品--|\n");
        printf("|--2----删除原有商品-|\n");
        printf("|--3--修改原有商品信息|\n");
        printf("|--4--------返回-----|\n");
        printf("|--0------退出系统---|\n");
        printf("|--------------------|\n");
        int command;
        printf("输入指令:");
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            createGood(&head); break;
        case 2:
            deleteGood(head);
            break;
        case 3:
            changeGood(head);
            break;
        case 4:
            return;
        case 0:
            exit(0);
        default:
            printf("错误");
            break;
        }
    }
}

//查询商品信息
void findGood(struct good* head)
{
    while (1)
    {
        printf("|-------------------|\n");
        printf("|请输入选项编号  0-3:|\n");
        printf("|--1-----按品名查询--|\n");
        printf("|--2----按剩余数查询-|\n");
        printf("|--3--------返回-----|\n");
        printf("|--0--------退出-----|\n");
        printf("|--------------------|\n");
        int command;
        printf("输入指令");
        scanf("%d", &command);
        while (getchar() != '\n');
        switch (command)
        {
        case 1:
            findName(head);
            break;
        case 2:
           
            findCount(head);
            break;
        case 3:
            return;
        case 0:
            exit(0);
        default:
            printf("指令错误");
            break;
        }
    }
}

//显示商品信息
void showGood(struct good* head)
{
    while (1)
    {
        printf("|-----------------------|\n");
        printf("|--请输入选项编号  0-4:--|\n");
        printf("|--1-----按原来顺序显示--|\n");
        printf("|--2----按销售额高低显示-|\n");
        printf("|--3----按毛利高低显示---|\n");
        printf("|--4--------返回--------|\n");
        printf("|--0--------退出---------|\n");
        printf("|-----------------------|\n");
        int command;
        printf("输入指令:");
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            printList(head); break;
        case 2:
            orderSellmoney(head);
            printList(head);
            break;
        case 3:
            orderProfit(head);
            printList(head);
            break;
        case 4:
            return;
        case 0:
            exit(0);
        default:
            printf("指令错误!");
            break;
        }
    }
}

int main()
{
    struct good* head = NULL;
    while (1)
    {
        int command;
        showMenu();
        scanf("%d", &command);
        switch (command)
        {
        case 1:createGood(&head); break;
        case 2:editGood(head); break;
        case 3:statGood(head); break;
        case 4:findGood(head); break;
        case 5:showGood(head); break;
        case 0:freeList(head); exit(0);
        default:printf("指令错误！"); break;
        }

    }
}
