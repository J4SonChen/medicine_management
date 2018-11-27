#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define LEN sizeof(struct ALL)

struct date                    //日期格式
{
    int year;//年
    int month;//月
    int day;//日
}today={1998,3,1};

struct usage                   //用法与用量
{
    int way;//1.饭前口服 or 2.饭后口服 or 3.外用
    int frequence[2];
    int each[2];
    int most;
};
struct ALL                     //药品信息
{
     char ID[20];//编号
     char Name[20];//药品名
     struct date produced;//生产日期
     int valid;//保质期
     struct date invalid;//失效期
     int type;//1.感冒药 2.胃药 3.消炎药 4.滴眼药
     struct usage use;//用法与用量
     struct ALL *next;
};

struct ALL *head_1 = NULL;     //从文件读入信息时暂放链表
struct ALL *head_2 = NULL;     //从键盘读入信息时暂放链表
struct ALL *head_A = NULL;     //数据库链表头部
struct ALL *head_B = NULL;     //数据库连表尾部

void one();   // 声明各个子功能函数
void two();
void three();
void four();
void five();
void six();
void seven();
void eight();
void nine();
void ten();
void eleven();
void twelve();
void thirteen();

void prt(struct ALL *);
void print(struct ALL *);

void PAK(int z) //实现按任意键返回上级菜单
{
    if(z==0) printf("  请按任意键返回上级菜单");
    if(z==1) printf("  请按任意键开始重新输入");
    if(z==2) printf("  请按任意键继续");
    do
    {
        if(kbhit()) {getch();break;}
    }while(1);
}

struct ALL *findtail(struct ALL *hea)// 寻找链表尾部
{
    if(hea!=NULL)
    {
        while(hea->next!=NULL)
            hea = hea->next;
    }
    return hea;
}

void sort() //排序
{
    struct ALL *pfirst;      /* 排列后有序链的表头指针 */
    struct ALL *ptail;       /* 排列后有序链的表尾指针 */
    struct ALL *pminBefore;  /* 保留键值更小的节点的前驱节点的指针 */
    struct ALL *pmin;        /* 存储最小节点   */
    struct ALL *p;           /* 当前比较的节点 */
    pfirst = NULL;
    while (head_A != NULL)         /*在链表中找键值最小的节点。*/
    {                              /* 注意：这里for语句就是体现选择排序思想的地方 */
        for (p = head_A, pmin = head_A; p->next != NULL; p = p->next) /*循环遍历链表中的节点，找出此时最小的节点。*/
        {
            if (strcmp(p->next->ID,pmin->ID) < 0 ) /*找到一个比当前min小的节点。*/
            {
                pminBefore = p;           /*保存找到节点的前驱节点：显然p->next的前驱节点是p。*/
                pmin       = p->next;     /*保存键值更小的节点。*/
            }
        }

        /*上面for语句结束后，就要做两件事；一是把它放入有序链表中；二是根据相应的条件判断，安排它离开原来的链表。*/

        /*第一件事*/
        if (pfirst == NULL)     /* 如果有序链表目前还是一个空链表                      */
        {
            pfirst = pmin;      /* 第一次找到键值最小的节点。                          */
            ptail  = pmin;      /* 注意：尾指针让它指向最后的一个节点。                */
        }
        else                    /* 有序链表中已经有节点                                */
        {
            ptail->next = pmin; /* 把刚找到的最小节点放到最后，即让尾指针的next指向它。*/
            ptail = pmin;       /* 尾指针也要指向它。                                  */
        }
                                /*第二件事*/
        if (pmin == head_A)        /* 如果找到的最小节点就是第一个节点                    */
            head_A = head_A->next;   /* 显然让head指向原head->next,即第二个节点，就OK       */
        else /*如果不是第一个节点*/
            pminBefore->next = pmin->next; /*前次最小节点的next指向当前pmin的next,这样就让pmin离开了原链表。*/
    }
    if(pfirst != NULL)     /*循环结束得到有序链表first                */
        ptail->next = NULL; /*单向链表的最后一个节点的next应该指向NULL */
    head_A = pfirst;
}

int counth(struct ALL *hea) //计算链表内数据个数
{
    struct ALL *p = hea;
    int i;
    for(i=0;p!=NULL;p = p->next)
        i++;
    return i;
}

bool testID(struct ALL *p)
{
    bool flag = 0;
    int j;
    if(strlen(p->ID)!=12) return false;
    for(j=0;j<strlen(p->ID);j++)
    {
        if(!((p->ID[j]>='0'&&p->ID[j]<='9')||(p->ID[j]>='A'&&p->ID[j]<='Z')||(p->ID[j]>='a'&&p->ID[j]<='z')||(p->ID[j]=='_')))
            {flag = 1; break;}
        if (p->ID[0]>='0'&&p->ID[0]<='9'&&j==0)
            {flag = 1; break;}
    }
    if(flag==1) return false;
    return true;
}




int main() //  主函数
{
    int choice;
    system("color F0");

    do
    {

        choice = 99;
        sort();
        system("CLS");
        printf("\n");
        if(head_A != NULL) printf("                                                   ******当前数据库有%d条数据！******\n",counth(head_A));
        else printf("                                                    ******当前数据库中无数据！******\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单                                                                                                    当前日期：%4d年%2d月%2d日  │\n",today);
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        1.增加                  ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        2.修改                  ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        3.删除                  ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        4.计算失效日期          ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        5.计算每日用量          ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        6.查询                  ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        7.分类查看              ┄┄┄┄┄┄┄┄┄┄┄┄┏┛┻━━━┛┻┓┄┄┄┄┄┤\n");
        printf("│                                                                                                        ┃｜｜｜｜｜｜｜┃          │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        8.全部信息              ┄┄┄┄┄┄┄┄┄┄┄┄┃      ━      ┃┄┄┄┄┄┤\n");
        printf("│                                                                                                        ┃  ┳┛　┗┳  ┃          │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        9.存储                  ┄┄┄┄┄┄┄┄┄┄┄┄┃              ┃┄┄┄┄┄┤\n");
        printf("│                                                                                                        ┃      ┻      ┃          │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄       10.过期药品信息          ┄┄┄┄┄┄┄┄┄┄┄┄┗━┓      ┏━┛┄┄┄┄┄┤\n");
        printf("│                                                                                                            ┃      ┃              │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄       11.即将过期药品信息      ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┃      ┃┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                            ┃      ┗━━━┓      │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄       12.修改当前日期          ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┃    制作人：  ┣┓┄┄┤\n");
        printf("│                                                                                                            ┃              ┃      │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄       13.清空数据              ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┃ 陈明岩 伊高立┃┄┄┄┤\n");
        printf("│                                                                                                            ┗┓┓┏━┳┓┏┛      │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        0.结束                  ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┃┫┫  ┃┫┫┄┄┄┄┤\n");
        printf("│                                                                                                              ┗┻┛  ┗┻┛        │\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        printf("  请输入您的选择:");
        if(scanf("%d",&choice)==0||getchar()!='\n'||choice>13||choice<0)
            {MessageBox(NULL,TEXT("错误的选项，请重新输入。"),TEXT("警告！"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
        switch(choice)
        {
            case 1:  one();break;
            case 2:  two();break;
            case 3:  three();break;
            case 4:  four();break;
            case 5:  five();break;
            case 6:  six();break;
            case 7:  seven();break;
            case 8:  eight();break;
            case 9:  nine();break;
            case 10: ten();break;
            case 11: eleven();break;
            case 12: twelve();break;
            case 13: thirteen();break;
            case 0:
            {
                if(head_A!=NULL)
                {
                    switch(MessageBox(NULL,TEXT("请问您是否已将数据库保存进文件中？"),TEXT("警告！"),MB_ICONWARNING|MB_YESNO))
                    {
                        case IDYES: exit(0);
                        case IDNO : nine();
                    }
                }
                else exit(0);
            }
            default:;
        }
    }while(1);
    return 0;
}

void one() //功能1.增加
{
    void one_1();
    void one_2();
    int choice1;
    bool flag = true;
    do
    {
        choice1 = 0;
        system("CLS");
        fflush(stdin);
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>增加                                                                                                                        │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        1.从文件读入            ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        2.手动输入              ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        3.返回上级菜单          ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        printf("  请输入您的选择:");
        if(scanf("%d",&choice1)==0||getchar()!='\n'||choice1>3||choice1<0)
            {MessageBox(NULL,TEXT("错误的选项，请重新输入。"),TEXT("警告！"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
        switch(choice1)
        {
            case 1: one_1();break;
            case 2: one_2();break;
            case 3: flag = false;break;
            default: {MessageBox(NULL,TEXT("错误的选项，请重新输入。"),TEXT("警告！"),MB_ICONWARNING|MB_OK);fflush(stdin);}

        }
    }while(flag);
}
struct ALL *read(FILE *fp)
{
    struct ALL *head;
    struct ALL *p1,*p2;
    int n=0;
    bool flag_creat = true;
    p1 = p2 = (struct ALL *)malloc(LEN);
    head = NULL;
    while(!feof(fp))
    {
        fscanf(fp,"%s",p1->ID);
        if(head_A!=NULL)
        {
            struct ALL *p = head_A;
            while(strcmp(p->ID,p1->ID) && p->next != NULL)
                p = p->next;
            if(strcmp(p->ID,p1->ID)==0)
                {printf("  文件中某项数据已存在于数据库中\n");PAK(0);return (head);}
        }
        fscanf(fp,"%s",p1->Name);
        fscanf(fp,"%d%d%d",&p1->produced.year,&p1->produced.month,&p1->produced.day);
        fscanf(fp,"%d",&p1->valid);
        fscanf(fp,"%d%d%d",&p1->invalid.year,&p1->invalid.month,&p1->invalid.day);
        fscanf(fp,"%d",&p1->type);
        fscanf(fp,"%d",&p1->use.way);
        fscanf(fp,"%d%d",&p1->use.frequence[0],&p1->use.frequence[1]);
        fscanf(fp,"%d%d",&p1->use.each[0],&p1->use.each[1]);
        fscanf(fp,"%d",&p1->use.most);
        if(n==0)    head = p1;
        else        p2->next = p1;
        p2 = p1;
        p1 = (struct ALL *)malloc(LEN);
        n++;
    }
    free(p1);
    p2->next = NULL;
    return (head);
};
void one_1()  //从文件读入
{
    FILE *fp;
    bool flag1 = true;
    bool flag1_1 = true;
    char filename[99];
    do                                               /*打开文件*/
    {
        system("CLS");
        fflush(stdin);
        flag1 = true;
        fp = NULL;
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>增加>>从文件读入                                                                                                            │\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        printf("  请输入文件名：");
        gets(filename);
        if((fp=fopen(filename,"r+"))==NULL)
        {
            if(MessageBox(NULL,TEXT("不存在此文件，是否继续打开文件？"),TEXT("打开文件失败!"),MB_ICONINFORMATION|MB_YESNO)!=IDNO)  flag1 = false;
        }
    }while (!flag1);
    if(fp!=NULL)
    {
        head_1 = read(fp);

        MessageBox(NULL,TEXT("已完成文件读入，单击确定查看已读入的信息"),TEXT("提示"),MB_ICONINFORMATION|MB_OK);
        fflush(stdin);
        print(head_1);
        do
        {
            switch(MessageBox(NULL,TEXT("请确认信息无误，是否将这些数据导入数据库中？"),TEXT("提示"),MB_ICONINFORMATION|MB_YESNO))
            {
                case IDYES:
                {
                    fflush(stdin);
                    if(head_A==NULL) head_A = head_1;
                    else
                    {
                        head_B = findtail(head_A);
                        head_B->next = head_1;
                    }
                    flag1_1 = false;
                    break;
                }
                case IDNO:
                {
                    fflush(stdin);
                    switch(MessageBox( NULL , TEXT("您确定要舍弃这些信息？") , TEXT("警告！") , MB_ICONINFORMATION|MB_YESNO))
                    {
                        case IDYES : flag1_1 = false ; break ;
                        case IDNO  : break ;
                    }
                    break;
                }
                default: MessageBox( NULL , TEXT("错误的选项，请重新输入。") , TEXT("警告！") , MB_ICONINFORMATION|MB_OK);
            }
        }while(flag1_1);
        fclose(fp);
    }
}
struct ALL *creat()
{
    struct ALL *head;
    struct ALL *p1,*p2;
    int n=0;
    bool flag_creat = true;
    p1 = p2 = (struct ALL *)malloc(LEN);
    head = NULL;
    while(flag_creat)
    {
        system("CLS");
        fflush(stdin);
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>增加>>手动输入                                               ！提示：请按照提示输入新的药品信息，若无某项信息，请输入“-1” │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n   ");
        printf("请输入药品编号：（12位的标识符）\n      ");
        scanf("%s",p1->ID);
        if(testID(p1)==false)
            {printf("   药品编号违反规则");PAK(1);continue;}
        if(head_A != NULL)
        {
            struct ALL *p = head_A;
            while( (strcmp(p->ID,p1->ID)) && (p->next != NULL))
                p = p->next;
            if(strcmp(p->ID,p1->ID)==0)
                {printf("  数据库中已存在此药品编号\n");PAK(1);continue;}
        }
        fflush(stdin);
        printf("├──────────────────────────────────────────────────────────────────┤\n   ");
        printf("请输入药品名称：（拼音）\n      ");
        scanf("%s",p1->Name);
        fflush(stdin);
        printf("├──────────────────────────────────────────────────────────────────┤\n   ");
        printf("请输入生产日期：（年月日中间用空格隔开，例：1997 02 09）\n      ");
        if(scanf("%d%d%d",&p1->produced.year,&p1->produced.month,&p1->produced.day)==0||getchar()!='\n'||p1->produced.year>9999||p1->produced.year<-1||
           p1->produced.month>12||p1->produced.month<-1||p1->produced.month==0||p1->produced.day>30||p1->produced.day<-1||p1->produced.day==0)
            {printf("  生产日期违反规则\n");PAK(1);continue;}
        fflush(stdin);
        printf("├──────────────────────────────────────────────────────────────────┤\n   ");
        printf("请输入有效期：（单位：月）\n      ");
        if(scanf("%d",&p1->valid)==0||getchar()!='\n'||p1->valid<-1)
            {printf("  有效期违反规则\n");PAK(1);continue;}
        fflush(stdin);
        printf("├──────────────────────────────────────────────────────────────────┤\n   ");
        printf("请输入失效期：      ");
        if(p1->produced.year!=-1&&p1->valid!=-1) printf("提示：根据已有信息，失效期应为：%4d %2d %2d\n      ",p1->produced.year+((p1->produced.month+p1->valid)/12),
                                                        (p1->produced.month+p1->valid)%12,p1->produced.day);
        else printf("\n      ");
        if(scanf("%d%d%d",&p1->invalid.year,&p1->invalid.month,&p1->invalid.day)==0||getchar()!='\n'||p1->invalid.year>9999||p1->invalid.year<-1||
           p1->invalid.month>12||p1->invalid.month<-1||p1->invalid.month==0||p1->invalid.day>30||p1->invalid.day<-1||p1->invalid.month==0)
            {printf("  失效期违反规则\n");PAK(1);continue;}
        else if(p1->invalid.year!=-1&&p1->produced.year!=-1&&p1->valid!=-1)
        {
            int y = p1->produced.year+((p1->produced.month+p1->valid)/12);
            int m = (p1->produced.month+p1->valid)%12;
            int d = p1->produced.day;
            if(p1->invalid.year!=y||p1->invalid.month!=m||p1->invalid.day!=d) {printf("  失效期与生产日期和有效期不匹配\n");PAK(1);continue;}
        }
        if(p1->invalid.year==-1)
        {
            if(p1->produced.year==-1&&p1->valid==-1) {printf("  不允许生产日期、有效期、失效日期均为空\n");PAK(1);continue;}
            if(p1->produced.year!=-1&&p1->valid==-1) {printf("  不允许只有生产日期\n");PAK(1);continue;}
            if(p1->produced.year==-1&&p1->valid!=-1) {printf("  不允许只有有效期\n");PAK(1);continue;}
        }
        fflush(stdin);
        printf("├──────────────────────────────────────────────────────────────────┤\n   ");
        printf("请输入药品主治病症类别：（1.感冒药 2.胃药 3.消炎药 4.滴眼药）\n      ");
        if(scanf("%d",&p1->type)==0||getchar()!='\n'||p1->type<-1||p1->type>4)
            {printf("  药品主治病症类别违反规则\n");PAK(1);continue;}
        fflush(stdin);
        printf("├──────────────────────────────────────────────────────────────────┤\n   ");
        printf("请输入药品使用方式：（1.饭前口服 2.饭后口服 3.外用）\n      ");
        if(scanf("%d",&p1->use.way)==0||getchar()!='\n'||p1->use.way<-1||p1->use.way>3)
            {printf("  药品使用方式违反规则\n");PAK(1);continue;}
        fflush(stdin);
        printf("├──────────────────────────────────────────────────────────────────┤\n   ");
        printf("请输入药品每日使用次数下限与上限：（用空格隔开）\n      ");
        if(scanf("%d%d",&p1->use.frequence[0],&p1->use.frequence[1])==0||getchar()!='\n'||p1->use.frequence[0]<-1||p1->use.frequence[1]<-1||
           p1->use.frequence[0]>p1->use.frequence[1])
            {printf("  药品每日使用次数违反规则\n");PAK(1);continue;}
        fflush(stdin);
        printf("├──────────────────────────────────────────────────────────────────┤\n   ");
        printf("请输入药品每次用量下限与上限：（用空格隔开）\n      ");
        if(scanf("%d%d",&p1->use.each[0],&p1->use.each[1])==0||getchar()!='\n'||p1->use.each[0]<-1||p1->use.each[1]<-1||
           p1->use.each[0]>p1->use.each[1])
            {printf("  药品每次用量违反规则\n");PAK(1);continue;}
        fflush(stdin);
        printf("├──────────────────────────────────────────────────────────────────┤\n   ");
        printf("请输入药品每日用量上限：\n      ");
        if(scanf("%d",&p1->use.most)==0||getchar()!='\n'||(p1->use.most!=-1&&p1->use.most<p1->use.each[0]*p1->use.frequence[0])||(p1->use.most!=-1&&p1->use.most>p1->use.each[1]*p1->use.frequence[1]))
            {printf("  药品每日用量上限违反规则");PAK(1);continue;}
        fflush(stdin);
        printf("└──────────────────────────────────────────────────────────────────┘\n   ");
        if(n==0)    head = p1;
        else        p2->next = p1;
        p2 = p1;
        p1 = (struct ALL *)malloc(LEN);
        switch(MessageBox(NULL,TEXT("是否继续输入新的药品信息？"),TEXT("提示"),MB_ICONINFORMATION|MB_YESNO))
        {
            case IDYES: {flag_creat = true;n++;break;}
            case IDNO : flag_creat = false;break;
        }
    }
    free(p1);
    p2->next = NULL;
    fflush(stdin);
    return (head);
};
void one_2() //手动输入
{
    int result;
    head_2=creat();
    bool flag2 = true;
    print(head_2);
    do
    {
        switch(MessageBox(NULL ,TEXT("请确认信息无误，是否将这些数据导入数据库中？"),TEXT("提示"),MB_ICONINFORMATION|MB_YESNO))
        {
            case IDYES:
            {
                fflush(stdin);
                if(head_A==NULL) head_A = head_2;
                else
                {
                    head_B = findtail(head_A);
                    head_B->next = head_2;
                }
                flag2 = false;
                break;
            }
            case IDNO:
            {
                fflush(stdin);
                switch(MessageBox( NULL , TEXT("您确定要舍弃这些信息？") , TEXT("警告！") , MB_ICONINFORMATION|MB_YESNO))
                {
                    case IDYES : flag2 = false ; break ;
                    case IDNO  : break ;
                }
                break;
            }
            default: MessageBox( NULL , TEXT("错误的选项，请重新输入。") , TEXT("警告！") , MB_ICONINFORMATION|MB_OK);
        }
    }while(flag2);

}

void two() //功能2.修改
{
    system("CLS");
    fflush(stdin);
    if(head_A==NULL)
    {
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>修改                                                                                                                        │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("├                                                         数据库中无数据！                                                           ┤\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        PAK(0);return ;
    }

    if(head_A!=NULL)
    {
        char ID[13];
        struct ALL *p1 = head_A;
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>修改                                                                                                                        │\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        printf("  请输入要修改的药品编号：");
        gets(ID);
        while( (strcmp(p1->ID,ID)) && (p1->next != NULL))
            p1 = p1->next;
        if(!strcmp(p1->ID,ID))
        {
            int choice2;
            while(1)
            {
                struct ALL temp;
                fflush(stdin);
                choice2 = 99;
                system("CLS");
                printf("\n\n");
                printf("┌──────────────────────────────────────────────────────────────────┐\n");
                printf("│                                                         药品信息管理系统                                                           │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│主菜单>>修改                                                     ！提示：请按照提示输入新的药品信息，若要删除某项信息，请输入“-1” │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
                prt(p1);
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│                                                       请选择您要修改的信息                                                         │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│                                                                                                                                    │\n");
                printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        1.药品编号              ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
                printf("│                                                                                                                                    │\n");
                printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        2.药品名称              ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
                printf("│                                                                                                                                    │\n");
                printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        3.生产日期              ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
                printf("│                                                                                                                                    │\n");
                printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        4.有效期                ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
                printf("│                                                                                                                                    │\n");
                printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        5.失效日期              ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
                printf("│                                                                                                                                    │\n");
                printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        6.主治病症类别          ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
                printf("│                                                                                                                                    │\n");
                printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        7.用法用量              ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
                printf("│                                                                                                                                    │\n");
                printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        8.修改完成              ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
                printf("│                                                                                                                                    │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("  请输入您的选择:");
                if(scanf("%d",&choice2)==0||getchar()!='\n'||choice2>8||choice2<0)
                    {MessageBox(NULL,TEXT("错误的选项，请重新输入。"),TEXT("警告！"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
                switch(choice2)
                {
                    case 1:
                        {
                            bool flag = true;
                            int j;
                            printf("├──────────────────────────────────────────────────────────────────┤\n   ");
                            printf("请输入药品编号：（12位的标识符）\n      ");
                            scanf("%s",temp.ID);
                            if(strlen(temp.ID)!=12) flag = false;
                            for(j=0;j<strlen(temp.ID);j++)
                            {
                                if(!((temp.ID[j]>='0'&&temp.ID[j]<='9')||(temp.ID[j]>='A'&&temp.ID[j]<='Z')||(temp.ID[j]>='a'&&temp.ID[j]<='z')||(temp.ID[j]=='_')))
                                    {flag = false; break;}
                                if (temp.ID[0]>='0'&&temp.ID[0]<='9'&&j==0)
                                    {flag = false; break;}
                            }
                            if(flag==false)
                                {printf("   药品编号违反规则");PAK(1);continue;}
                            if(head_A != NULL)
                            {
                                struct ALL *p = head_A;
                                while( (strcmp(p->ID,temp.ID)) && (p->next != NULL))
                                    p = p->next;
                                if(strcmp(p->ID,temp.ID)==0)
                                {printf("  数据库中已存在此药品编号\n");PAK(1);continue;}
                            }
                            strcpy(p1->ID,temp.ID);
                            fflush(stdin);
                            printf("└──────────────────────────────────────────────────────────────────┘\n");
                            printf("   修改已生效，3 秒后将刷新页面\n");
                            Sleep(3000);break;
                        }
                    case 2:
                        {
                            printf("├──────────────────────────────────────────────────────────────────┤\n");
                            printf("   请输入药品名称：（拼音）\n      ");
                            scanf("%s",p1->Name);
                            fflush(stdin);
                            printf("└──────────────────────────────────────────────────────────────────┘\n");
                            printf("   修改已生效，3 秒后将刷新页面\n");
                            Sleep(3000);break;
                        }
                    case 3:
                        {
                            printf("├──────────────────────────────────────────────────────────────────┤\n");
                            printf("   请输入生产日期：（年月日中间用空格隔开，例：1997 02 09）\n      ");
                            if(scanf("%d%d%d",&temp.produced.year,&temp.produced.month,&temp.produced.day)==0||getchar()!='\n'||temp.produced.year>9999||temp.produced.year<-1||
                                temp.produced.month>12||temp.produced.month<-1||temp.produced.month==0||temp.produced.day>30||temp.produced.day<-1||temp.produced.day==0)
                                {printf("  生产日期违反规则\n");PAK(1);continue;}
                            p1->produced.year = temp.produced.year;
                            p1->produced.month = temp.produced.month;
                            p1->produced.day = temp.produced.day;
                            fflush(stdin);
                            printf("└──────────────────────────────────────────────────────────────────┘\n");
                            printf("   修改已生效，3 秒后将刷新页面\n");
                            Sleep(3000);break;
                        }
                    case 4:
                        {
                            printf("├──────────────────────────────────────────────────────────────────┤\n");
                            printf("   请输入有效期：（单位：月）\n      ");
                            if(scanf("%d",&temp.valid)==0||getchar()!='\n'||temp.valid<-1)
                                {printf("  有效期违反规则\n");PAK(1);continue;}
                            p1->valid = temp.valid;
                            fflush(stdin);
                            printf("└──────────────────────────────────────────────────────────────────┘\n");
                            printf("   修改已生效，3 秒后将刷新页面\n");
                            Sleep(3000);break;
                        }
                    case 5:
                        {
                            printf("├──────────────────────────────────────────────────────────────────┤\n");
                            printf("   请输入失效期：（年月日中间用空格隔开，例：1997 02 09）\n      ");
                            if(p1->produced.year!=-1&&p1->valid!=-1) printf("提示：根据已有信息，失效期应为：%4d %2d %2d\n      ",p1->produced.year+((p1->produced.month+p1->valid)/12),
                                                        (p1->produced.month+p1->valid)%12,p1->produced.day);
                            else printf("\n      ");
                            if(scanf("%d%d%d",&temp.invalid.year,&temp.invalid.month,&temp.invalid.day)==0||getchar()!='\n'||temp.invalid.year>9999||temp.invalid.year<-1||
                                temp.invalid.month>12||temp.invalid.month<-1||temp.invalid.month==0||temp.invalid.day>30||temp.invalid.day<-1||temp.invalid.day==0)
                                    {printf("  失效期违反规则\n");PAK(1);continue;}
                            else if(p1->produced.year!=-1&&p1->valid!=-1)
                            {
                                int y = p1->produced.year+((p1->produced.month+p1->valid)/12);
                                int m = (p1->produced.month+p1->valid)%12;
                                int d = p1->produced.day;
                                if(temp.invalid.year!=y||temp.invalid.month!=m||temp.invalid.day!=d) {printf("  失效期与生产日期和有效期不匹配\n");PAK(1);continue;}
                            }
                            if(temp.invalid.year==-1)
                            {
                                if(p1->produced.year==-1&&p1->valid==-1) {printf("  不允许生产日期、有效期、失效日期均为空\n");PAK(1);continue;}
                                if(p1->produced.year!=-1&&p1->valid==-1) {printf("  不允许只有生产日期\n");PAK(1);continue;}
                                if(p1->produced.year==-1&&p1->valid!=-1) {printf("  不允许只有有效期\n");PAK(1);continue;}
                            }
                            fflush(stdin);
                            printf("└──────────────────────────────────────────────────────────────────┘\n");
                            printf("   修改已生效，3 秒后将刷新页面\n");
                            Sleep(3000);break;
                        }
                    case 6:
                        {
                            printf("├──────────────────────────────────────────────────────────────────┤\n");
                            printf("   请输入药品主治病症类别：（1.感冒药 2.胃药 3.消炎药 4.滴眼药）\n      ");
                            if(scanf("%d",&temp.type)==0||getchar()!='\n'||temp.type<-1||temp.type>4)
                                {printf("  药品主治病症类别违反规则\n");PAK(1);continue;}
                            p1->type = temp.type;
                            fflush(stdin);
                            printf("└──────────────────────────────────────────────────────────────────┘\n");
                            printf("   修改已生效，3 秒后将刷新页面\n");
                            Sleep(3000);break;
                        }
                    case 7:
                        {
                            printf("├──────────────────────────────────────────────────────────────────┤\n");
                            printf("   请输入药品使用方式：（1.饭前口服 2.饭后口服 3.外用）\n      ");
                            if(scanf("%d",&temp.use.way)==0||getchar()!='\n'||temp.use.way<-1||temp.use.way>3)
                                {printf("  药品使用方式违反规则\n");PAK(1);continue;}
                            fflush(stdin);
                            printf("├──────────────────────────────────────────────────────────────────┤\n   ");
                            printf("请输入药品每日使用次数下限与上限：（用空格隔开）\n      ");
                            if(scanf("%d%d",&temp.use.frequence[0],&temp.use.frequence[1])==0||getchar()!='\n'||temp.use.frequence[0]<-1||temp.use.frequence[1]<-1||
                                temp.use.frequence[0]>temp.use.frequence[1])
                                    {printf("  药品每日使用次数违反规则\n");PAK(1);continue;}
                            fflush(stdin);
                            printf("├──────────────────────────────────────────────────────────────────┤\n   ");
                            printf("请输入药品每次用量下限与上限：（用空格隔开）\n      ");
                            if(scanf("%d%d",&temp.use.each[0],&temp.use.each[1])==0||getchar()!='\n'||temp.use.each[0]<-1||temp.use.each[1]<-1||
                                temp.use.each[0]>temp.use.each[1])
                                    {printf("  药品每次用量违反规则\n");PAK(1);continue;}
                            fflush(stdin);
                            printf("├──────────────────────────────────────────────────────────────────┤\n   ");
                            printf("请输入药品每日用量上限：\n      ");
                            if(scanf("%d",&temp.use.most)==0||getchar()!='\n'||temp.use.most<temp.use.each[0]*temp.use.frequence[0])
                                {printf("  药品每日用量上限违反规则");PAK(1);continue;}
                            fflush(stdin);
                            p1->use.way = temp.use.way;
                            p1->use.frequence[0] = temp.use.frequence[0];
                            p1->use.frequence[1] = temp.use.frequence[1];
                            p1->use.each[0] = temp.use.each[0];
                            p1->use.each[1] = temp.use.each[1];
                            p1->use.most = temp.use.most;
                            printf("└──────────────────────────────────────────────────────────────────┘\n");
                            printf("   修改已生效，3 秒后将刷新页面\n");
                            Sleep(3000);break;
                        }
                    case 8:  return;
                    default: {MessageBox(NULL,TEXT("错误的选项，请重新输入。"),TEXT("警告！"),MB_ICONINFORMATION|MB_OK);fflush(stdin);}
                }
            }
        }
        else
        {
            system("CLS");
            printf("\n\n");
            printf("┌──────────────────────────────────────────────────────────────────┐\n");
            printf("│                                                         药品信息管理系统                                                           │\n");
            printf("├──────────────────────────────────────────────────────────────────┤\n");
            printf("│主菜单>>修改                                                                                                                        │\n");
            printf("├──────────────────────────────────────────────────────────────────┤\n");
            printf("├                                                          未找到此药品！                                                            ┤\n");
            printf("└──────────────────────────────────────────────────────────────────┘\n");
            PAK(0);
            return;
        }
    }
    PAK(0);
}

void three() //功能3.删除
{
    system("CLS");
    fflush(stdin);
    if(head_A==NULL)
    {

        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>删除                                                                                                                        │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("├                                                         数据库中无数据！                                                           ┤\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        PAK(0);
        return ;
    }
    char ID[13];
    struct ALL *p1 = head_A;
    struct ALL *p2 = p1->next;
    struct ALL *p3 = (p2!=NULL)?p2->next:NULL;
    struct ALL *p = NULL;
    while(head_A!=NULL)
    {
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>删除                                                                                                                        │\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        printf("  请输入要删除的药品编号：");
        gets(ID);
        if(!strcmp(p1->ID,ID))//检测第一个节点是否是要删除的节点
        {
            system("CLS");
            printf("\n\n");
            printf("┌──────────────────────────────────────────────────────────────────┐\n");
            printf("│                                                         药品信息管理系统                                                           │\n");
            printf("├──────────────────────────────────────────────────────────────────┤\n");
            printf("│主菜单>>删除                                                                                                                        │\n");
            printf("├──────────────────────────────────────────────────────────────────┤\n");
            printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
            prt(p1);
            printf("└──────────────────────────────────────────────────────────────────┘\n");
            switch(MessageBox( NULL , TEXT("以上是即将要删除的药品信息，是否确认要删除？") , TEXT("提示") , MB_ICONINFORMATION|MB_YESNO))
            {
                case IDYES :
                {
                    head_A = p2;
                    p = p1;
                    free(p);
                    printf("  已删除该药品信息，");
                    PAK(0);
                    return;
                }
                case IDNO  : return ;
            }
        }
        if(p1->next==NULL)   //防止链表只有一个节点的情况
        {
            system("CLS");
            printf("\n\n");
            printf("┌──────────────────────────────────────────────────────────────────┐\n");
            printf("│                                                         药品信息管理系统                                                           │\n");
            printf("├──────────────────────────────────────────────────────────────────┤\n");
            printf("│主菜单>>删除                                                                                                                        │\n");
            printf("├──────────────────────────────────────────────────────────────────┤\n");
            printf("├                                                          未找到此药品！                                                            ┤\n");
            printf("└──────────────────────────────────────────────────────────────────┘\n");
            PAK(0);
            return;
        }
        if(strcmp(p1->ID,ID))//寻找要删除的节点
        {

            while( (p3 != NULL) && (strcmp(p2->ID,ID)) )
            {
                p1 = p2;
                p2 = p1->next;
                p3 = (p2!=NULL)?p2->next:NULL;
            }
            system("CLS");
            printf("\n\n");
            printf("┌──────────────────────────────────────────────────────────────────┐\n");
            printf("│                                                         药品信息管理系统                                                           │\n");
            printf("├──────────────────────────────────────────────────────────────────┤\n");
            printf("│主菜单>>删除                                                                                                                        │\n");
            printf("├──────────────────────────────────────────────────────────────────┤\n");
            if(strcmp(p2->ID,ID))
            {
                printf("├                                                          未找到此药品！                                                            ┤\n");
                printf("└──────────────────────────────────────────────────────────────────┘\n");
                PAK(0);
                break;
            }
            printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
            prt(p2);
            printf("└──────────────────────────────────────────────────────────────────┘\n");
            switch(MessageBox( NULL , TEXT("以上是即将要删除的药品信息，是否确认要删除？") , TEXT("提示") , MB_ICONINFORMATION|MB_YESNO))
            {
                case IDYES : {p1->next = p3;p = p2;break;}
                case IDNO  : return ;
            }
        }
        if(p!=NULL) //释放内存
        {
            free(p);
            printf("  已删除该药品信息，");
        }
        PAK(0);
        return ;
    }
}

void four() //计算失效日期
{
    if(head_A==NULL)
    {
        system("CLS");
        fflush(stdin);
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>计算失效日期                                                                                                                │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("├                                                         数据库中无数据！                                                           ┤\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        PAK(0);
        return ;
    }
    int choice4;
    struct ALL *p1;
    while(1)
    {
        p1 = head_A;
        choice4 = 99;
        system("CLS");
        fflush(stdin);
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>计算失效日期                                                                                                                │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        1.按编号检索            ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        2.按名称检索            ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        3.返回上级菜单          ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        printf("  请输入您的选择:");
        if(scanf("%d",&choice4)==0||getchar()!='\n'||choice4>3||choice4<0)
            {MessageBox(NULL,TEXT("错误的选项，请重新输入。"),TEXT("警告！"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
        switch(choice4)
        {
        case 1 :
            {
                char ID[13];
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("┌──────────────────────────────────────────────────────────────────┐\n");
                printf("│                                                         药品信息管理系统                                                           │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│主菜单>>计算失效日期>>按编号检索                                                                                                    │\n");
                printf("└──────────────────────────────────────────────────────────────────┘\n");
                printf("  请输入要计算失效日期的药品编号：");
                gets(ID);
                while( (strcmp(p1->ID,ID)) && (p1->next != NULL))
                    p1 = p1->next;
                if(!strcmp(p1->ID,ID))
                {
                    int y = (p1->invalid.year==-1) ? (p1->produced.year+((p1->produced.month+p1->valid)/12)) : p1->invalid.year;
                    int m = (p1->invalid.year==-1) ? (p1->produced.month+p1->valid)%12 : p1->invalid.month;
                    int d = (p1->invalid.year==-1) ? p1->produced.day : p1->invalid.day;
                    system("CLS");
                    printf("\n\n");
                    printf("┌──────────────────────────────────────────────────────────────────┐\n");
                    printf("│                                                         药品信息管理系统                                                           │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│主菜单>>计算失效日期>>按编号检索                                                                                                    │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
                    prt(p1);
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│                                          根据已有信息，该药品的失效日期为：%4d年%2d月%2d日                                          │\n",y,m,d);
                    printf("└──────────────────────────────────────────────────────────────────┘\n");
                    PAK(0);break;
                }
                else
                {
                    system("CLS");
                    printf("\n\n");
                    printf("┌──────────────────────────────────────────────────────────────────┐\n");
                    printf("│                                                         药品信息管理系统                                                           │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│主菜单>>计算失效日期>>按编号检索                                                                                                    │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("├                                                          未找到此药品！                                                            ┤\n");
                    printf("└──────────────────────────────────────────────────────────────────┘\n");
                    PAK(0);
                    break;
                }
            }
        case 2 :
            {
                char Name[20];
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("┌──────────────────────────────────────────────────────────────────┐\n");
                printf("│                                                         药品信息管理系统                                                           │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│主菜单>>计算失效日期>>按名称检索                                                                                                    │\n");
                printf("└──────────────────────────────────────────────────────────────────┘\n");
                printf("  请输入要查询的药品名称：");
                gets(Name);
                while( (strcmp(p1->Name,Name)) && (p1->next != NULL))
                    p1 = p1->next;
                if(!strcmp(p1->Name,Name))
                {
                    int y = (p1->invalid.year==-1) ? (p1->produced.year+((p1->produced.month+p1->valid)/12)) : p1->invalid.year;
                    int m = (p1->invalid.year==-1) ? (p1->produced.month+p1->valid)%12 : p1->invalid.month;
                    int d = (p1->invalid.year==-1) ? p1->produced.day : p1->invalid.day;
                    system("CLS");
                    printf("\n\n");
                    printf("┌──────────────────────────────────────────────────────────────────┐\n");
                    printf("│                                                         药品信息管理系统                                                           │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│主菜单>>计算失效日期>>按名称检索                                                                                                    │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
                    prt(p1);
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│                                          根据已有信息，该药品的失效日期为：%4d年%2d月%2d日                                          │\n",y,m,d);
                    printf("└──────────────────────────────────────────────────────────────────┘\n");
                    PAK(0);break;
                }
                else
                {
                    system("CLS");
                    printf("\n\n");
                    printf("┌──────────────────────────────────────────────────────────────────┐\n");
                    printf("│                                                         药品信息管理系统                                                           │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│主菜单>>计算失效日期>>按名称检索                                                                                                    │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("├                                                          未找到此药品！                                                            ┤\n");
                    printf("└──────────────────────────────────────────────────────────────────┘\n");
                    PAK(0);break;
                }
            }
        case 3 : return;
        }
    }

}

void five() //计算每日用量
{
    if(head_A==NULL)
    {
        system("CLS");
        fflush(stdin);
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>计算每日用量                                                                                                                │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("├                                                         数据库中无数据！                                                           ┤\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        PAK(0);
        return ;
    }
    int choice5;
    struct ALL *p1;
    while(1)
    {
        choice5 = 99;
        p1 = head_A;
        system("CLS");
        fflush(stdin);
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>计算每日用量                                                                                                                │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        1.按编号检索            ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        2.按名称检索            ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        3.返回上级菜单          ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        printf("  请输入您的选择:");
        if(scanf("%d",&choice5)==0||getchar()!='\n'||choice5>3||choice5<0)
            {MessageBox(NULL,TEXT("错误的选项，请重新输入。"),TEXT("警告！"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
        switch(choice5)
        {
        case 1 :
            {
                p1 = head_A;
                char ID[13];
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("┌──────────────────────────────────────────────────────────────────┐\n");
                printf("│                                                         药品信息管理系统                                                           │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│主菜单>>计算每日用量>>按编号检索                                                                                                    │\n");
                printf("└──────────────────────────────────────────────────────────────────┘\n");
                printf("  请输入要查询的药品编号：");
                gets(ID);
                while( (strcmp(p1->ID,ID)) && (p1->next != NULL))
                    p1 = p1->next;
                if(!strcmp(p1->ID,ID))
                {
                    int least = p1->use.frequence[0] * p1->use.each[0];
                    int most = p1->use.frequence[1] * p1->use.each[1];
                    if((p1->use.most!=-1)&&(most > p1->use.most)) most = p1->use.most;
                    system("CLS");
                    printf("\n\n");
                    printf("┌──────────────────────────────────────────────────────────────────┐\n");
                    printf("│                                                         药品信息管理系统                                                           │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│主菜单>>计算每日用量>>按编号检索                                                                                                    │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
                    prt(p1);
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│                                             根据已有信息，该药品的每日用量为：%2d-%2dmg                                              │\n",least,most);
                    printf("└──────────────────────────────────────────────────────────────────┘\n");
                    PAK(0);break;
                }
                else
                {
                    system("CLS");
                    printf("\n\n");
                    printf("┌──────────────────────────────────────────────────────────────────┐\n");
                    printf("│                                                         药品信息管理系统                                                           │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│主菜单>>计算每日用量>>按编号检索                                                                                                    │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("├                                                          未找到此药品！                                                            ┤\n");
                    printf("└──────────────────────────────────────────────────────────────────┘\n");
                    PAK(0);break;
                }
            }
        case 2 :
            {
                p1 = head_A;
                char Name[20];
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("┌──────────────────────────────────────────────────────────────────┐\n");
                printf("│                                                         药品信息管理系统                                                           │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│主菜单>>计算每日用量>>按名称检索                                                                                                    │\n");
                printf("└──────────────────────────────────────────────────────────────────┘\n");
                printf("  请输入要查询的药品名称：");
                gets(Name);
                while( (strcmp(p1->Name,Name)) && (p1->next != NULL))
                    p1 = p1->next;
                if(!strcmp(p1->Name,Name))
                {
                    int least = p1->use.frequence[0]*p1->use.each[0];
                    int most = p1->use.frequence[1]*p1->use.each[1];
                    if((p1->use.most!=-1)&&(most > p1->use.most)) most = p1->use.most;
                    system("CLS");
                    printf("\n\n");
                    printf("┌──────────────────────────────────────────────────────────────────┐\n");
                    printf("│                                                         药品信息管理系统                                                           │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│主菜单>>计算每日用量>>按名称检索                                                                                                    │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
                    prt(p1);
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│                                             根据已有信息，该药品的每日用量为：%2d-%2dmg                                              │\n",least,most);
                    printf("└──────────────────────────────────────────────────────────────────┘\n");
                    PAK(0);break;
                }
                else
                {
                    system("CLS");
                    printf("\n\n");
                    printf("┌──────────────────────────────────────────────────────────────────┐\n");
                    printf("│                                                         药品信息管理系统                                                           │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│主菜单>>计算每日用量>>按名称检索                                                                                                    │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("├                                                          未找到此药品！                                                            ┤\n");
                    printf("└──────────────────────────────────────────────────────────────────┘\n");
                    PAK(0);break;
                }
            }
        case 3 : return;
        }
    }


}

void six() //查询
{
    if(head_A==NULL)
    {
        system("CLS");
        fflush(stdin);
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>查询                                                                                                                        │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("├                                                         数据库中无数据！                                                           ┤\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        PAK(0);return ;
    }
    int choice6;
    struct ALL *p1 = head_A;
    while(1)
    {
        p1 = head_A;
        choice6 = 99;
        system("CLS");
        fflush(stdin);
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>查询                                                                                                                        │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        1.按编号检索            ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        2.按名称检索            ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        3.返回上级菜单          ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        printf("  请输入您的选择:");
        if(scanf("%d",&choice6)==0||getchar()!='\n'||choice6>3||choice6<0)
            {MessageBox(NULL,TEXT("错误的选项，请重新输入。"),TEXT("警告！"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
        switch(choice6)
        {
        case 1 :
            {
                char ID[13];
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("┌──────────────────────────────────────────────────────────────────┐\n");
                printf("│                                                         药品信息管理系统                                                           │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│主菜单>>查询>>按编号检索                                                                                                            │\n");
                printf("└──────────────────────────────────────────────────────────────────┘\n");
                printf("  请输入要查询的药品编号：");
                gets(ID);
                while( (strcmp(p1->ID,ID)) && (p1->next != NULL))
                    p1 = p1->next;
                if(!strcmp(p1->ID,ID))
                {
                    system("CLS");
                    printf("\n\n");
                    printf("┌──────────────────────────────────────────────────────────────────┐\n");
                    printf("│                                                         药品信息管理系统                                                           │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│主菜单>>查询>>按编号检索                                                                                                            │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
                    prt(p1);
                    printf("└──────────────────────────────────────────────────────────────────┘\n");
                    PAK(0);break;
                }
                else
                {
                    system("CLS");
                    printf("\n\n");
                    printf("┌──────────────────────────────────────────────────────────────────┐\n");
                    printf("│                                                         药品信息管理系统                                                           │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│主菜单>>查询>>按编号检索                                                                                                            │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("├                                                          未找到此药品！                                                            ┤\n");
                    printf("└──────────────────────────────────────────────────────────────────┘\n");
                    PAK(0);break;
                }
            }
        case 2 :
            {
                char Name[20];
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("┌──────────────────────────────────────────────────────────────────┐\n");
                printf("│                                                         药品信息管理系统                                                           │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│主菜单>>查询>>按名称检索                                                                                                            │\n");
                printf("└──────────────────────────────────────────────────────────────────┘\n");
                printf("  请输入要查询的药品名称：");
                gets(Name);
                while( (strcmp(p1->Name,Name)) && (p1->next != NULL))
                    p1 = p1->next;
                if(!strcmp(p1->Name,Name))
                {
                    system("CLS");
                    printf("\n\n");
                    printf("┌──────────────────────────────────────────────────────────────────┐\n");
                    printf("│                                                         药品信息管理系统                                                           │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│主菜单>>查询>>按名称检索                                                                                                            │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
                    prt(p1);
                    printf("└──────────────────────────────────────────────────────────────────┘\n");
                    PAK(0);break;
                }
                else
                {
                    system("CLS");
                    printf("\n\n");
                    printf("┌──────────────────────────────────────────────────────────────────┐\n");
                    printf("│                                                         药品信息管理系统                                                           │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("│主菜单>>查询>>按名称检索                                                                                                            │\n");
                    printf("├──────────────────────────────────────────────────────────────────┤\n");
                    printf("├                                                          未找到此药品！                                                            ┤\n");
                    printf("└──────────────────────────────────────────────────────────────────┘\n");
                    PAK(0);break;
                }
            }
        case 3 : return;
        }
    }
}

void seven() //分类查看
{
    if(head_A==NULL)
    {
        system("CLS");
        fflush(stdin);
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>分类查看                                                                                                                    │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("├                                                         数据库中无数据！                                                           ┤\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        PAK(0);return ;
    }
    int choice7;
    struct ALL *p1 = head_A;
    while(1)
    {
        system("CLS");
        fflush(stdin);
        int n;
        choice7 = 99;
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>分类查看                                                                                                                    │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        1.感冒药                ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        2.胃药                  ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        3.消炎药                ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        4.滴眼药                ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        5.未分类药品            ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄        6.返回上级菜单          ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
        printf("│                                                                                                                                    │\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        printf("  请输入您的选择:");
        if(scanf("%d",&choice7)==0||getchar()!='\n'||choice7>6||choice7<0)
            {MessageBox(NULL,TEXT("错误的选项，请重新输入。"),TEXT("警告！"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
        switch(choice7)
        {
        case 1 :
            {
                p1 = head_A;
                n = 0;
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("┌──────────────────────────────────────────────────────────────────┐\n");
                printf("│                                                         药品信息管理系统                                                           │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│主菜单>>分类查看>>感冒药                                                                                                            │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
                while(p1 != NULL)
                {
                    if(p1->type==1) {prt(p1);n++;}
                    p1 = p1->next;
                }
                if(n==0)
                    printf("├                                                         未找到此类药品！                                                           ┤\n");
                printf("└──────────────────────────────────────────────────────────────────┘\n");
                PAK(0);break;
            }
        case 2 :
            {
                p1 = head_A;
                n = 0;
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("┌──────────────────────────────────────────────────────────────────┐\n");
                printf("│                                                         药品信息管理系统                                                           │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│主菜单>>分类查看>>胃药                                                                                                              │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
                while(p1 != NULL)
                {
                    if(p1->type==2) {prt(p1);n++;}
                    p1 = p1->next;
                }
                if(n==0)
                    printf("├                                                         未找到此类药品！                                                           ┤\n");
                printf("└──────────────────────────────────────────────────────────────────┘\n");
                PAK(0);break;
            }
        case 3 :
            {
                p1 = head_A;
                n = 0;
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("┌──────────────────────────────────────────────────────────────────┐\n");
                printf("│                                                         药品信息管理系统                                                           │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│主菜单>>分类查看>>消炎药                                                                                                            │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
                while(p1 != NULL)
                {
                    if(p1->type==3) {prt(p1);n++;}
                    p1 = p1->next;
                }
                if(n==0)
                    printf("├                                                         未找到此类药品！                                                           ┤\n");
                printf("└──────────────────────────────────────────────────────────────────┘\n");
                PAK(0);break;
            }
        case 4 :
            {
                p1 = head_A;
                n = 0;
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("┌──────────────────────────────────────────────────────────────────┐\n");
                printf("│                                                         药品信息管理系统                                                           │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│主菜单>>分类查看>>滴眼药                                                                                                            │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
                while(p1 != NULL)
                {
                    if(p1->type==4) {prt(p1);n++;}
                    p1 = p1->next;
                }
                if(n==0)
                    printf("├                                                         未找到此类药品！                                                           ┤\n");
                printf("└──────────────────────────────────────────────────────────────────┘\n");
                PAK(0);break;
            }
        case 5 :
            {
                p1 = head_A;
                n = 0;
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("┌──────────────────────────────────────────────────────────────────┐\n");
                printf("│                                                         药品信息管理系统                                                           │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│主菜单>>分类查看>>未分类药品                                                                                                        │\n");
                printf("├──────────────────────────────────────────────────────────────────┤\n");
                printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
                while(p1 != NULL)
                {
                    if((p1->type!=1)&&(p1->type!=2)&&(p1->type!=3)&&(p1->type!=4)) {prt(p1);n++;}
                    p1 = p1->next;
                }
                if(n==0)
                    printf("├                                                         未找到此类药品！                                                           ┤\n");
                printf("└──────────────────────────────────────────────────────────────────┘\n");
                PAK(0);break;
            }
        case 6 :return;
        }
    }
    PAK(0);
}

void prt(struct ALL *p) //打印单个节点}
{
    printf("│%14s |",p->ID);
    printf("%17s | ",p->Name);
    if((p->produced.year==-1)||(p->produced.month==-1)) printf("****/**/** | ");
    else printf("%4d/%2d/%2d | ",p->produced.year,p->produced.month,p->produced.day);
    if (p->valid==-1) printf(" *个月 | ");
    else printf("%2d个月 | ",p->valid);
    if((p->invalid.year==-1)||(p->invalid.month==-1)) printf("****/**/** | ");
    else printf("%4d/%2d/%2d | ",p->invalid.year,p->invalid.month,p->invalid.day);
    if(p->type==1)    printf("     感冒药  | ");
    else if(p->type==2)    printf("       胃药  | ");
    else if(p->type==3)    printf("     消炎药  | ");
    else if(p->type==4)    printf("     滴眼药  | ");
    else                   printf("     未说明  | ");
    if(p->use.way==1)      printf("饭前口服 ");
    else if(p->use.way==2) printf("饭前口服 ");
    else if(p->use.way==3) printf("    外用 ");
    else                   printf("  未说明 ");
    if(p->use.frequence[0]==-1) printf("每日 *-");
    else printf("每日%2d-",p->use.frequence[0]);
    if(p->use.frequence[1]==-1) printf(" *次 ");
    else printf("%2d次 ",p->use.frequence[1]);
    if(p->use.each[0]==-1) printf("每次 *-");
    else printf("每次%2d-",p->use.each[0]);
    if(p->use.each[1]==-1) printf(" *mg ");
    else printf("%2dmg ",p->use.each[1]);
    if(p->use.most==-1) printf("每日最多 不限│\n");
    else printf("每日最多 %2dmg│\n",p->use.most);
}
void print(struct ALL *head) //提供链表头，打印该链表内所有节点
{
    fflush(stdin);
    system("CLS");
    struct ALL *p;
    p = head;
    printf("\n\n");
    printf("┌──────────────────────────────────────────────────────────────────┐\n");
    printf("│                                                         药品信息管理系统                                                           │\n");
    printf("├──────────────────────────────────────────────────────────────────┤\n");
    printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
    while(p!=NULL)
    {
        prt(p);
        p = p->next;
    }
    printf("└──────────────────────────────────────────────────────────────────┘\n");
}
void eight() //全部信息
{
    fflush(stdin);
    system("CLS");
    if(head_A==NULL)
    {
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>全部信息                                                                                                                    │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("├                                                         数据库中无数据！                                                           ┤\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
    }
    if(head_A!=NULL)
        print(head_A);
    PAK(0);
}

void nine() //存储
{
    system("CLS");
    fflush(stdin);
    FILE *fp;
    bool flag1 = true;
    char filename[99];
    struct ALL *p = NULL;
    if(head_A==NULL)
    {
        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>存储                                                                                                                        │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("├                                                         数据库中无数据！                                                           ┤\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
    }
    if(head_A!=NULL)
    {
        do                                               /*打开文件*/
        {
            system("CLS");
            fflush(stdin);
            flag1 = true;
            printf("\n\n");
            printf("┌──────────────────────────────────────────────────────────────────┐\n");
            printf("│                                                         药品信息管理系统                                                           │\n");
            printf("├──────────────────────────────────────────────────────────────────┤\n");
            printf("│主菜单>>存储                                                                                                                        │\n");
            printf("└──────────────────────────────────────────────────────────────────┘\n");
            printf("  请输入文件名：");
            gets(filename);
            if((fp=fopen(filename,"a+"))==NULL)
            {
                if(MessageBox(NULL,TEXT("不存在此文件，是否继续打开文件？"),TEXT("打开文件失败!"),MB_ICONINFORMATION|MB_YESNO)!=IDNO)  flag1 = false;
            }
            fp = NULL;
        }while (!flag1);
        if(fp!=NULL)
        {
            p = head_A;
            fseek(fp,0L,SEEK_END);
            do
            {
                if(ftell(fp)!=0)  fprintf(fp,"\n");
                fprintf(fp,"%12s ",p->ID);
                fprintf(fp,"%20s ",p->Name);
                fprintf(fp,"%4d %2d %2d ",p->produced.year,p->produced.month,p->produced.day);
                fprintf(fp,"%2d ",p->valid);
                fprintf(fp,"%4d %2d %2d ",p->invalid.year,p->invalid.month,p->invalid.day);
                fprintf(fp,"%2d ",p->type);
                fprintf(fp,"%2d ",p->use.way);
                fprintf(fp,"%2d %2d %2d %2d %2d",p->use.frequence[0],p->use.frequence[1],p->use.each[0],p->use.each[1],p->use.most);
                p = p->next;
            }while(p!=NULL);
            fclose(fp);
        }
        printf("  已成功将数据库信息导入%s",filename);
    }
    PAK(0);
}

void ten() //过期药品信息
{
    system("CLS");
    fflush(stdin);
    if(head_A==NULL)
    {

        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>过期药品信息                                                                                                                │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("├                                                         数据库中无数据！                                                           ┤\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        PAK(0);return ;
    }
    struct ALL *p1 = head_A;
    printf("\n\n");
    printf("┌──────────────────────────────────────────────────────────────────┐\n");
    printf("│                                                         药品信息管理系统                                                           │\n");
    printf("├──────────────────────────────────────────────────────────────────┤\n");
    printf("│主菜单>>过期药品信息                                                                                      当前日期：%4d年%2d月%2d日  │\n",today);
    printf("├──────────────────────────────────────────────────────────────────┤\n");
    printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
    for(;p1!=NULL;p1=p1->next)
    {
        int y = (p1->invalid.year==-1) ? (p1->produced.year+((p1->produced.month+p1->valid)/12)) : p1->invalid.year;
        if(y<today.year) {prt(p1);continue;}
        else
        {
            int m = (p1->invalid.year==-1) ? (p1->produced.month+p1->valid)%12 : p1->invalid.month;
            if((y==today.year)&&(m<today.month)) {prt(p1);continue;}
            else
            {
                int d = (p1->invalid.year==-1) ? p1->produced.day : p1->invalid.day;
                if((y==today.year)&&(m==today.month)&&(d<today.day)) {prt(p1);continue;}
            }
        }
    }
    printf("└──────────────────────────────────────────────────────────────────┘\n");
    PAK(0);
}

void eleven() //即将过期药品信息
{
    while(1)
    {
    system("CLS");
    fflush(stdin);
    if(head_A==NULL)
    {

        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>即将过期药品信息                                                                                                            │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("├                                                         数据库中无数据！                                                           ┤\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        PAK(0);return ;
    }
    int pvalid;
    struct ALL *p1 = head_A;
    system("CLS");
    fflush(stdin);
    printf("\n\n");
    printf("┌──────────────────────────────────────────────────────────────────┐\n");
    printf("│                                                         药品信息管理系统                                                           │\n");
    printf("├──────────────────────────────────────────────────────────────────┤\n");
    printf("│主菜单>>即将过期药品信息                                                                                  当前日期：%4d年%2d月%2d日  │\n",today);
    printf("├──────────────────────────────────────────────────────────────────┤\n");
    printf("  请问，您认为有效期仅剩几个月以下时，药品被视为即将过期药品？");
    if(scanf("%d",&pvalid)==0||getchar()!='\n'||pvalid<1)
            {MessageBox(NULL,TEXT("只能输入整数"),TEXT("警告！"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
    system("CLS");
    fflush(stdin);
    printf("\n\n");
    printf("┌──────────────────────────────────────────────────────────────────┐\n");
    printf("│                                                         药品信息管理系统                                                           │\n");
    printf("├──────────────────────────────────────────────────────────────────┤\n");
    printf("│主菜单>>即将过期药品信息                                                                                  当前日期：%4d年%2d月%2d日  │\n",today);
    printf("├──────────────────────────────────────────────────────────────────┤\n");
    printf("│          编号 |         药品名称 |   生产日期 | 有效期 |   失效日期 | 主治病症类别 |                   用法与用量                  │\n");
    for(;p1!=NULL;p1=p1->next)
    {
        int y = (p1->invalid.year==-1) ? (p1->produced.year+((p1->produced.month+p1->valid)/12)) : p1->invalid.year;
        int m = (p1->invalid.year==-1) ? (p1->produced.month+p1->valid)%12 : p1->invalid.month;
        int d = (p1->invalid.year==-1) ? p1->produced.day : p1->invalid.day;
        int ymd = y*10000+m*100+d;
        int y1 = y + (m-pvalid-12)/12;
        int m1 = (m+12-pvalid)%12;
        int ymd1 = y1*10000+m1*100+d;
        if(ymd>(today.year*10000+today.month*100+today.day)&&ymd1<(today.year*10000+today.month*100+today.day)) prt(p1);
    }
    printf("└──────────────────────────────────────────────────────────────────┘\n");
    PAK(0);
    return;
    }
}

void twelve() //修改当前日期
{
    while(1)
    {
    int y = 0;
    int m = 0;
    int d = 0;
    system("CLS");
    fflush(stdin);
    printf("\n\n");
    printf("┌──────────────────────────────────────────────────────────────────┐\n");
    printf("│                                                         药品信息管理系统                                                           │\n");
    printf("├──────────────────────────────────────────────────────────────────┤\n");
    printf("│主菜单>>修改当前日期                                                                                      当前日期：%4d年%2d月%2d日  │\n",today);
    printf("├──────────────────────────────────────────────────────────────────┤\n");
    printf("  请输入新的日期：（年月日中间用空格隔开，例：1997 02 09）\n  ");
    if(scanf("%d%d%d",&y,&m,&d)==0||getchar()!='\n'||y>9999||y<-1||m>12||m<-1||m==0||d>30||d<-1||d==0)
            {printf("  日期违反规则\n");PAK(1);return;}
    today.year = y;
    today.month = m;
    today.day = d;
    printf("└──────────────────────────────────────────────────────────────────┘\n");
    printf(" 当前日期已修改成功，");
    fflush(stdin);
    PAK(0);
    return;
    }
}

void thirteen() //清空数据
{
    struct ALL *p1,*p2;
    system("CLS");
    fflush(stdin);
    if(head_A==NULL)
    {

        printf("\n\n");
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│                                                         药品信息管理系统                                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│主菜单>>清空数据                                                                                                                    │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("├                                                         数据库中无数据！                                                           ┤\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        PAK(0);return ;
    }
    printf("\n\n");
    printf("┌──────────────────────────────────────────────────────────────────┐\n");
    printf("│                                                         药品信息管理系统                                                           │\n");
    printf("├──────────────────────────────────────────────────────────────────┤\n");
    printf("│主菜单>>清空数据                                                                                                                    │\n");
    printf("└──────────────────────────────────────────────────────────────────┘\n");
    switch(MessageBox( NULL , TEXT("此操作将清空数据库中的所有信息！是否确认清空数据库？") , TEXT("警告！") , MB_ICONINFORMATION|MB_YESNO))
    {
        case IDYES :
        {
            p1 = head_A;
            head_A = NULL;
            while(p1->next!=NULL)
            {
                p2 = p1->next;
                free(p1);
                p1 = p2;
            }
            free(p1);
            printf("  已成功清空数据库");
        }
    }
    PAK(0);
}
