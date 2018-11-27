#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define LEN sizeof(struct ALL)

struct date                    //���ڸ�ʽ
{
    int year;//��
    int month;//��
    int day;//��
}today={1998,3,1};

struct usage                   //�÷�������
{
    int way;//1.��ǰ�ڷ� or 2.����ڷ� or 3.����
    int frequence[2];
    int each[2];
    int most;
};
struct ALL                     //ҩƷ��Ϣ
{
     char ID[20];//���
     char Name[20];//ҩƷ��
     struct date produced;//��������
     int valid;//������
     struct date invalid;//ʧЧ��
     int type;//1.��ðҩ 2.θҩ 3.����ҩ 4.����ҩ
     struct usage use;//�÷�������
     struct ALL *next;
};

struct ALL *head_1 = NULL;     //���ļ�������Ϣʱ�ݷ�����
struct ALL *head_2 = NULL;     //�Ӽ��̶�����Ϣʱ�ݷ�����
struct ALL *head_A = NULL;     //���ݿ�����ͷ��
struct ALL *head_B = NULL;     //���ݿ�����β��

void one();   // ���������ӹ��ܺ���
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

void PAK(int z) //ʵ�ְ�����������ϼ��˵�
{
    if(z==0) printf("  �밴����������ϼ��˵�");
    if(z==1) printf("  �밴�������ʼ��������");
    if(z==2) printf("  �밴���������");
    do
    {
        if(kbhit()) {getch();break;}
    }while(1);
}

struct ALL *findtail(struct ALL *hea)// Ѱ������β��
{
    if(hea!=NULL)
    {
        while(hea->next!=NULL)
            hea = hea->next;
    }
    return hea;
}

void sort() //����
{
    struct ALL *pfirst;      /* ���к��������ı�ͷָ�� */
    struct ALL *ptail;       /* ���к��������ı�βָ�� */
    struct ALL *pminBefore;  /* ������ֵ��С�Ľڵ��ǰ���ڵ��ָ�� */
    struct ALL *pmin;        /* �洢��С�ڵ�   */
    struct ALL *p;           /* ��ǰ�ȽϵĽڵ� */
    pfirst = NULL;
    while (head_A != NULL)         /*���������Ҽ�ֵ��С�Ľڵ㡣*/
    {                              /* ע�⣺����for����������ѡ������˼��ĵط� */
        for (p = head_A, pmin = head_A; p->next != NULL; p = p->next) /*ѭ�����������еĽڵ㣬�ҳ���ʱ��С�Ľڵ㡣*/
        {
            if (strcmp(p->next->ID,pmin->ID) < 0 ) /*�ҵ�һ���ȵ�ǰminС�Ľڵ㡣*/
            {
                pminBefore = p;           /*�����ҵ��ڵ��ǰ���ڵ㣺��Ȼp->next��ǰ���ڵ���p��*/
                pmin       = p->next;     /*�����ֵ��С�Ľڵ㡣*/
            }
        }

        /*����for�������󣬾�Ҫ�������£�һ�ǰ����������������У����Ǹ�����Ӧ�������жϣ��������뿪ԭ��������*/

        /*��һ����*/
        if (pfirst == NULL)     /* �����������Ŀǰ����һ��������                      */
        {
            pfirst = pmin;      /* ��һ���ҵ���ֵ��С�Ľڵ㡣                          */
            ptail  = pmin;      /* ע�⣺βָ������ָ������һ���ڵ㡣                */
        }
        else                    /* �����������Ѿ��нڵ�                                */
        {
            ptail->next = pmin; /* �Ѹ��ҵ�����С�ڵ�ŵ���󣬼���βָ���nextָ������*/
            ptail = pmin;       /* βָ��ҲҪָ������                                  */
        }
                                /*�ڶ�����*/
        if (pmin == head_A)        /* ����ҵ�����С�ڵ���ǵ�һ���ڵ�                    */
            head_A = head_A->next;   /* ��Ȼ��headָ��ԭhead->next,���ڶ����ڵ㣬��OK       */
        else /*������ǵ�һ���ڵ�*/
            pminBefore->next = pmin->next; /*ǰ����С�ڵ��nextָ��ǰpmin��next,��������pmin�뿪��ԭ����*/
    }
    if(pfirst != NULL)     /*ѭ�������õ���������first                */
        ptail->next = NULL; /*������������һ���ڵ��nextӦ��ָ��NULL */
    head_A = pfirst;
}

int counth(struct ALL *hea) //�������������ݸ���
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




int main() //  ������
{
    int choice;
    system("color F0");

    do
    {

        choice = 99;
        sort();
        system("CLS");
        printf("\n");
        if(head_A != NULL) printf("                                                   ******��ǰ���ݿ���%d�����ݣ�******\n",counth(head_A));
        else printf("                                                    ******��ǰ���ݿ��������ݣ�******\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�                                                                                                    ��ǰ���ڣ�%4d��%2d��%2d��  ��\n",today);
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        1.����                  ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        2.�޸�                  ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        3.ɾ��                  ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        4.����ʧЧ����          ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        5.����ÿ������          ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        6.��ѯ                  ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        7.����鿴              �����������������������������ߩ��������ߩ�������������\n");
        printf("��                                                                                                        ������������������          ��\n");
        printf("��������������������������������������������������        8.ȫ����Ϣ              ��������������������������      ��      ��������������\n");
        printf("��                                                                                                        ��  �ש�������  ��          ��\n");
        printf("��������������������������������������������������        9.�洢                  ��������������������������              ��������������\n");
        printf("��                                                                                                        ��      ��      ��          ��\n");
        printf("��������������������������������������������������       10.����ҩƷ��Ϣ          ������������������������������      ������������������\n");
        printf("��                                                                                                            ��      ��              ��\n");
        printf("��������������������������������������������������       11.��������ҩƷ��Ϣ      ������������������������������      ������������������\n");
        printf("��                                                                                                            ��      ����������      ��\n");
        printf("��������������������������������������������������       12.�޸ĵ�ǰ����          ������������������������������    �����ˣ�  �ǩ�������\n");
        printf("��                                                                                                            ��              ��      ��\n");
        printf("��������������������������������������������������       13.�������              ������������������������������ ������ ����������������\n");
        printf("��                                                                                                            �����������ש�����      ��\n");
        printf("��������������������������������������������������        0.����                  ���������������������������������ϩ�  ���ϩϩ���������\n");
        printf("��                                                                                                              ���ߩ�  ���ߩ�        ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("  ����������ѡ��:");
        if(scanf("%d",&choice)==0||getchar()!='\n'||choice>13||choice<0)
            {MessageBox(NULL,TEXT("�����ѡ����������롣"),TEXT("���棡"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
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
                    switch(MessageBox(NULL,TEXT("�������Ƿ��ѽ����ݿⱣ����ļ��У�"),TEXT("���棡"),MB_ICONWARNING|MB_YESNO))
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

void one() //����1.����
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
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>����                                                                                                                        ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        1.���ļ�����            ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        2.�ֶ�����              ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        3.�����ϼ��˵�          ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("  ����������ѡ��:");
        if(scanf("%d",&choice1)==0||getchar()!='\n'||choice1>3||choice1<0)
            {MessageBox(NULL,TEXT("�����ѡ����������롣"),TEXT("���棡"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
        switch(choice1)
        {
            case 1: one_1();break;
            case 2: one_2();break;
            case 3: flag = false;break;
            default: {MessageBox(NULL,TEXT("�����ѡ����������롣"),TEXT("���棡"),MB_ICONWARNING|MB_OK);fflush(stdin);}

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
                {printf("  �ļ���ĳ�������Ѵ��������ݿ���\n");PAK(0);return (head);}
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
void one_1()  //���ļ�����
{
    FILE *fp;
    bool flag1 = true;
    bool flag1_1 = true;
    char filename[99];
    do                                               /*���ļ�*/
    {
        system("CLS");
        fflush(stdin);
        flag1 = true;
        fp = NULL;
        printf("\n\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>����>>���ļ�����                                                                                                            ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("  �������ļ�����");
        gets(filename);
        if((fp=fopen(filename,"r+"))==NULL)
        {
            if(MessageBox(NULL,TEXT("�����ڴ��ļ����Ƿ�������ļ���"),TEXT("���ļ�ʧ��!"),MB_ICONINFORMATION|MB_YESNO)!=IDNO)  flag1 = false;
        }
    }while (!flag1);
    if(fp!=NULL)
    {
        head_1 = read(fp);

        MessageBox(NULL,TEXT("������ļ����룬����ȷ���鿴�Ѷ������Ϣ"),TEXT("��ʾ"),MB_ICONINFORMATION|MB_OK);
        fflush(stdin);
        print(head_1);
        do
        {
            switch(MessageBox(NULL,TEXT("��ȷ����Ϣ�����Ƿ���Щ���ݵ������ݿ��У�"),TEXT("��ʾ"),MB_ICONINFORMATION|MB_YESNO))
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
                    switch(MessageBox( NULL , TEXT("��ȷ��Ҫ������Щ��Ϣ��") , TEXT("���棡") , MB_ICONINFORMATION|MB_YESNO))
                    {
                        case IDYES : flag1_1 = false ; break ;
                        case IDNO  : break ;
                    }
                    break;
                }
                default: MessageBox( NULL , TEXT("�����ѡ����������롣") , TEXT("���棡") , MB_ICONINFORMATION|MB_OK);
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
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>����>>�ֶ�����                                               ����ʾ���밴����ʾ�����µ�ҩƷ��Ϣ������ĳ����Ϣ�������롰-1�� ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
        printf("������ҩƷ��ţ���12λ�ı�ʶ����\n      ");
        scanf("%s",p1->ID);
        if(testID(p1)==false)
            {printf("   ҩƷ���Υ������");PAK(1);continue;}
        if(head_A != NULL)
        {
            struct ALL *p = head_A;
            while( (strcmp(p->ID,p1->ID)) && (p->next != NULL))
                p = p->next;
            if(strcmp(p->ID,p1->ID)==0)
                {printf("  ���ݿ����Ѵ��ڴ�ҩƷ���\n");PAK(1);continue;}
        }
        fflush(stdin);
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
        printf("������ҩƷ���ƣ���ƴ����\n      ");
        scanf("%s",p1->Name);
        fflush(stdin);
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
        printf("�������������ڣ����������м��ÿո����������1997 02 09��\n      ");
        if(scanf("%d%d%d",&p1->produced.year,&p1->produced.month,&p1->produced.day)==0||getchar()!='\n'||p1->produced.year>9999||p1->produced.year<-1||
           p1->produced.month>12||p1->produced.month<-1||p1->produced.month==0||p1->produced.day>30||p1->produced.day<-1||p1->produced.day==0)
            {printf("  ��������Υ������\n");PAK(1);continue;}
        fflush(stdin);
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
        printf("��������Ч�ڣ�����λ���£�\n      ");
        if(scanf("%d",&p1->valid)==0||getchar()!='\n'||p1->valid<-1)
            {printf("  ��Ч��Υ������\n");PAK(1);continue;}
        fflush(stdin);
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
        printf("������ʧЧ�ڣ�      ");
        if(p1->produced.year!=-1&&p1->valid!=-1) printf("��ʾ������������Ϣ��ʧЧ��ӦΪ��%4d %2d %2d\n      ",p1->produced.year+((p1->produced.month+p1->valid)/12),
                                                        (p1->produced.month+p1->valid)%12,p1->produced.day);
        else printf("\n      ");
        if(scanf("%d%d%d",&p1->invalid.year,&p1->invalid.month,&p1->invalid.day)==0||getchar()!='\n'||p1->invalid.year>9999||p1->invalid.year<-1||
           p1->invalid.month>12||p1->invalid.month<-1||p1->invalid.month==0||p1->invalid.day>30||p1->invalid.day<-1||p1->invalid.month==0)
            {printf("  ʧЧ��Υ������\n");PAK(1);continue;}
        else if(p1->invalid.year!=-1&&p1->produced.year!=-1&&p1->valid!=-1)
        {
            int y = p1->produced.year+((p1->produced.month+p1->valid)/12);
            int m = (p1->produced.month+p1->valid)%12;
            int d = p1->produced.day;
            if(p1->invalid.year!=y||p1->invalid.month!=m||p1->invalid.day!=d) {printf("  ʧЧ�����������ں���Ч�ڲ�ƥ��\n");PAK(1);continue;}
        }
        if(p1->invalid.year==-1)
        {
            if(p1->produced.year==-1&&p1->valid==-1) {printf("  �������������ڡ���Ч�ڡ�ʧЧ���ھ�Ϊ��\n");PAK(1);continue;}
            if(p1->produced.year!=-1&&p1->valid==-1) {printf("  ������ֻ����������\n");PAK(1);continue;}
            if(p1->produced.year==-1&&p1->valid!=-1) {printf("  ������ֻ����Ч��\n");PAK(1);continue;}
        }
        fflush(stdin);
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
        printf("������ҩƷ���β�֢��𣺣�1.��ðҩ 2.θҩ 3.����ҩ 4.����ҩ��\n      ");
        if(scanf("%d",&p1->type)==0||getchar()!='\n'||p1->type<-1||p1->type>4)
            {printf("  ҩƷ���β�֢���Υ������\n");PAK(1);continue;}
        fflush(stdin);
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
        printf("������ҩƷʹ�÷�ʽ����1.��ǰ�ڷ� 2.����ڷ� 3.���ã�\n      ");
        if(scanf("%d",&p1->use.way)==0||getchar()!='\n'||p1->use.way<-1||p1->use.way>3)
            {printf("  ҩƷʹ�÷�ʽΥ������\n");PAK(1);continue;}
        fflush(stdin);
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
        printf("������ҩƷÿ��ʹ�ô������������ޣ����ÿո������\n      ");
        if(scanf("%d%d",&p1->use.frequence[0],&p1->use.frequence[1])==0||getchar()!='\n'||p1->use.frequence[0]<-1||p1->use.frequence[1]<-1||
           p1->use.frequence[0]>p1->use.frequence[1])
            {printf("  ҩƷÿ��ʹ�ô���Υ������\n");PAK(1);continue;}
        fflush(stdin);
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
        printf("������ҩƷÿ���������������ޣ����ÿո������\n      ");
        if(scanf("%d%d",&p1->use.each[0],&p1->use.each[1])==0||getchar()!='\n'||p1->use.each[0]<-1||p1->use.each[1]<-1||
           p1->use.each[0]>p1->use.each[1])
            {printf("  ҩƷÿ������Υ������\n");PAK(1);continue;}
        fflush(stdin);
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
        printf("������ҩƷÿ���������ޣ�\n      ");
        if(scanf("%d",&p1->use.most)==0||getchar()!='\n'||(p1->use.most!=-1&&p1->use.most<p1->use.each[0]*p1->use.frequence[0])||(p1->use.most!=-1&&p1->use.most>p1->use.each[1]*p1->use.frequence[1]))
            {printf("  ҩƷÿ����������Υ������");PAK(1);continue;}
        fflush(stdin);
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
        if(n==0)    head = p1;
        else        p2->next = p1;
        p2 = p1;
        p1 = (struct ALL *)malloc(LEN);
        switch(MessageBox(NULL,TEXT("�Ƿ���������µ�ҩƷ��Ϣ��"),TEXT("��ʾ"),MB_ICONINFORMATION|MB_YESNO))
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
void one_2() //�ֶ�����
{
    int result;
    head_2=creat();
    bool flag2 = true;
    print(head_2);
    do
    {
        switch(MessageBox(NULL ,TEXT("��ȷ����Ϣ�����Ƿ���Щ���ݵ������ݿ��У�"),TEXT("��ʾ"),MB_ICONINFORMATION|MB_YESNO))
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
                switch(MessageBox( NULL , TEXT("��ȷ��Ҫ������Щ��Ϣ��") , TEXT("���棡") , MB_ICONINFORMATION|MB_YESNO))
                {
                    case IDYES : flag2 = false ; break ;
                    case IDNO  : break ;
                }
                break;
            }
            default: MessageBox( NULL , TEXT("�����ѡ����������롣") , TEXT("���棡") , MB_ICONINFORMATION|MB_OK);
        }
    }while(flag2);

}

void two() //����2.�޸�
{
    system("CLS");
    fflush(stdin);
    if(head_A==NULL)
    {
        printf("\n\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>�޸�                                                                                                                        ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ���ݿ��������ݣ�                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        PAK(0);return ;
    }

    if(head_A!=NULL)
    {
        char ID[13];
        struct ALL *p1 = head_A;
        printf("\n\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>�޸�                                                                                                                        ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("  ������Ҫ�޸ĵ�ҩƷ��ţ�");
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
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("�����˵�>>�޸�                                                     ����ʾ���밴����ʾ�����µ�ҩƷ��Ϣ����Ҫɾ��ĳ����Ϣ�������롰-1�� ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
                prt(p1);
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��                                                       ��ѡ����Ҫ�޸ĵ���Ϣ                                                         ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��                                                                                                                                    ��\n");
                printf("��������������������������������������������������        1.ҩƷ���              ������������������������������������������������������\n");
                printf("��                                                                                                                                    ��\n");
                printf("��������������������������������������������������        2.ҩƷ����              ������������������������������������������������������\n");
                printf("��                                                                                                                                    ��\n");
                printf("��������������������������������������������������        3.��������              ������������������������������������������������������\n");
                printf("��                                                                                                                                    ��\n");
                printf("��������������������������������������������������        4.��Ч��                ������������������������������������������������������\n");
                printf("��                                                                                                                                    ��\n");
                printf("��������������������������������������������������        5.ʧЧ����              ������������������������������������������������������\n");
                printf("��                                                                                                                                    ��\n");
                printf("��������������������������������������������������        6.���β�֢���          ������������������������������������������������������\n");
                printf("��                                                                                                                                    ��\n");
                printf("��������������������������������������������������        7.�÷�����              ������������������������������������������������������\n");
                printf("��                                                                                                                                    ��\n");
                printf("��������������������������������������������������        8.�޸����              ������������������������������������������������������\n");
                printf("��                                                                                                                                    ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("  ����������ѡ��:");
                if(scanf("%d",&choice2)==0||getchar()!='\n'||choice2>8||choice2<0)
                    {MessageBox(NULL,TEXT("�����ѡ����������롣"),TEXT("���棡"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
                switch(choice2)
                {
                    case 1:
                        {
                            bool flag = true;
                            int j;
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
                            printf("������ҩƷ��ţ���12λ�ı�ʶ����\n      ");
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
                                {printf("   ҩƷ���Υ������");PAK(1);continue;}
                            if(head_A != NULL)
                            {
                                struct ALL *p = head_A;
                                while( (strcmp(p->ID,temp.ID)) && (p->next != NULL))
                                    p = p->next;
                                if(strcmp(p->ID,temp.ID)==0)
                                {printf("  ���ݿ����Ѵ��ڴ�ҩƷ���\n");PAK(1);continue;}
                            }
                            strcpy(p1->ID,temp.ID);
                            fflush(stdin);
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                            printf("   �޸�����Ч��3 ���ˢ��ҳ��\n");
                            Sleep(3000);break;
                        }
                    case 2:
                        {
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                            printf("   ������ҩƷ���ƣ���ƴ����\n      ");
                            scanf("%s",p1->Name);
                            fflush(stdin);
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                            printf("   �޸�����Ч��3 ���ˢ��ҳ��\n");
                            Sleep(3000);break;
                        }
                    case 3:
                        {
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                            printf("   �������������ڣ����������м��ÿո����������1997 02 09��\n      ");
                            if(scanf("%d%d%d",&temp.produced.year,&temp.produced.month,&temp.produced.day)==0||getchar()!='\n'||temp.produced.year>9999||temp.produced.year<-1||
                                temp.produced.month>12||temp.produced.month<-1||temp.produced.month==0||temp.produced.day>30||temp.produced.day<-1||temp.produced.day==0)
                                {printf("  ��������Υ������\n");PAK(1);continue;}
                            p1->produced.year = temp.produced.year;
                            p1->produced.month = temp.produced.month;
                            p1->produced.day = temp.produced.day;
                            fflush(stdin);
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                            printf("   �޸�����Ч��3 ���ˢ��ҳ��\n");
                            Sleep(3000);break;
                        }
                    case 4:
                        {
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                            printf("   ��������Ч�ڣ�����λ���£�\n      ");
                            if(scanf("%d",&temp.valid)==0||getchar()!='\n'||temp.valid<-1)
                                {printf("  ��Ч��Υ������\n");PAK(1);continue;}
                            p1->valid = temp.valid;
                            fflush(stdin);
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                            printf("   �޸�����Ч��3 ���ˢ��ҳ��\n");
                            Sleep(3000);break;
                        }
                    case 5:
                        {
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                            printf("   ������ʧЧ�ڣ����������м��ÿո����������1997 02 09��\n      ");
                            if(p1->produced.year!=-1&&p1->valid!=-1) printf("��ʾ������������Ϣ��ʧЧ��ӦΪ��%4d %2d %2d\n      ",p1->produced.year+((p1->produced.month+p1->valid)/12),
                                                        (p1->produced.month+p1->valid)%12,p1->produced.day);
                            else printf("\n      ");
                            if(scanf("%d%d%d",&temp.invalid.year,&temp.invalid.month,&temp.invalid.day)==0||getchar()!='\n'||temp.invalid.year>9999||temp.invalid.year<-1||
                                temp.invalid.month>12||temp.invalid.month<-1||temp.invalid.month==0||temp.invalid.day>30||temp.invalid.day<-1||temp.invalid.day==0)
                                    {printf("  ʧЧ��Υ������\n");PAK(1);continue;}
                            else if(p1->produced.year!=-1&&p1->valid!=-1)
                            {
                                int y = p1->produced.year+((p1->produced.month+p1->valid)/12);
                                int m = (p1->produced.month+p1->valid)%12;
                                int d = p1->produced.day;
                                if(temp.invalid.year!=y||temp.invalid.month!=m||temp.invalid.day!=d) {printf("  ʧЧ�����������ں���Ч�ڲ�ƥ��\n");PAK(1);continue;}
                            }
                            if(temp.invalid.year==-1)
                            {
                                if(p1->produced.year==-1&&p1->valid==-1) {printf("  �������������ڡ���Ч�ڡ�ʧЧ���ھ�Ϊ��\n");PAK(1);continue;}
                                if(p1->produced.year!=-1&&p1->valid==-1) {printf("  ������ֻ����������\n");PAK(1);continue;}
                                if(p1->produced.year==-1&&p1->valid!=-1) {printf("  ������ֻ����Ч��\n");PAK(1);continue;}
                            }
                            fflush(stdin);
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                            printf("   �޸�����Ч��3 ���ˢ��ҳ��\n");
                            Sleep(3000);break;
                        }
                    case 6:
                        {
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                            printf("   ������ҩƷ���β�֢��𣺣�1.��ðҩ 2.θҩ 3.����ҩ 4.����ҩ��\n      ");
                            if(scanf("%d",&temp.type)==0||getchar()!='\n'||temp.type<-1||temp.type>4)
                                {printf("  ҩƷ���β�֢���Υ������\n");PAK(1);continue;}
                            p1->type = temp.type;
                            fflush(stdin);
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                            printf("   �޸�����Ч��3 ���ˢ��ҳ��\n");
                            Sleep(3000);break;
                        }
                    case 7:
                        {
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                            printf("   ������ҩƷʹ�÷�ʽ����1.��ǰ�ڷ� 2.����ڷ� 3.���ã�\n      ");
                            if(scanf("%d",&temp.use.way)==0||getchar()!='\n'||temp.use.way<-1||temp.use.way>3)
                                {printf("  ҩƷʹ�÷�ʽΥ������\n");PAK(1);continue;}
                            fflush(stdin);
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
                            printf("������ҩƷÿ��ʹ�ô������������ޣ����ÿո������\n      ");
                            if(scanf("%d%d",&temp.use.frequence[0],&temp.use.frequence[1])==0||getchar()!='\n'||temp.use.frequence[0]<-1||temp.use.frequence[1]<-1||
                                temp.use.frequence[0]>temp.use.frequence[1])
                                    {printf("  ҩƷÿ��ʹ�ô���Υ������\n");PAK(1);continue;}
                            fflush(stdin);
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
                            printf("������ҩƷÿ���������������ޣ����ÿո������\n      ");
                            if(scanf("%d%d",&temp.use.each[0],&temp.use.each[1])==0||getchar()!='\n'||temp.use.each[0]<-1||temp.use.each[1]<-1||
                                temp.use.each[0]>temp.use.each[1])
                                    {printf("  ҩƷÿ������Υ������\n");PAK(1);continue;}
                            fflush(stdin);
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n   ");
                            printf("������ҩƷÿ���������ޣ�\n      ");
                            if(scanf("%d",&temp.use.most)==0||getchar()!='\n'||temp.use.most<temp.use.each[0]*temp.use.frequence[0])
                                {printf("  ҩƷÿ����������Υ������");PAK(1);continue;}
                            fflush(stdin);
                            p1->use.way = temp.use.way;
                            p1->use.frequence[0] = temp.use.frequence[0];
                            p1->use.frequence[1] = temp.use.frequence[1];
                            p1->use.each[0] = temp.use.each[0];
                            p1->use.each[1] = temp.use.each[1];
                            p1->use.most = temp.use.most;
                            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                            printf("   �޸�����Ч��3 ���ˢ��ҳ��\n");
                            Sleep(3000);break;
                        }
                    case 8:  return;
                    default: {MessageBox(NULL,TEXT("�����ѡ����������롣"),TEXT("���棡"),MB_ICONINFORMATION|MB_OK);fflush(stdin);}
                }
            }
        }
        else
        {
            system("CLS");
            printf("\n\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            printf("�����˵�>>�޸�                                                                                                                        ��\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            printf("��                                                          δ�ҵ���ҩƷ��                                                            ��\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            PAK(0);
            return;
        }
    }
    PAK(0);
}

void three() //����3.ɾ��
{
    system("CLS");
    fflush(stdin);
    if(head_A==NULL)
    {

        printf("\n\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>ɾ��                                                                                                                        ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ���ݿ��������ݣ�                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
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
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>ɾ��                                                                                                                        ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("  ������Ҫɾ����ҩƷ��ţ�");
        gets(ID);
        if(!strcmp(p1->ID,ID))//����һ���ڵ��Ƿ���Ҫɾ���Ľڵ�
        {
            system("CLS");
            printf("\n\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            printf("�����˵�>>ɾ��                                                                                                                        ��\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
            prt(p1);
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            switch(MessageBox( NULL , TEXT("�����Ǽ���Ҫɾ����ҩƷ��Ϣ���Ƿ�ȷ��Ҫɾ����") , TEXT("��ʾ") , MB_ICONINFORMATION|MB_YESNO))
            {
                case IDYES :
                {
                    head_A = p2;
                    p = p1;
                    free(p);
                    printf("  ��ɾ����ҩƷ��Ϣ��");
                    PAK(0);
                    return;
                }
                case IDNO  : return ;
            }
        }
        if(p1->next==NULL)   //��ֹ����ֻ��һ���ڵ�����
        {
            system("CLS");
            printf("\n\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            printf("�����˵�>>ɾ��                                                                                                                        ��\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            printf("��                                                          δ�ҵ���ҩƷ��                                                            ��\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            PAK(0);
            return;
        }
        if(strcmp(p1->ID,ID))//Ѱ��Ҫɾ���Ľڵ�
        {

            while( (p3 != NULL) && (strcmp(p2->ID,ID)) )
            {
                p1 = p2;
                p2 = p1->next;
                p3 = (p2!=NULL)?p2->next:NULL;
            }
            system("CLS");
            printf("\n\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            printf("�����˵�>>ɾ��                                                                                                                        ��\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            if(strcmp(p2->ID,ID))
            {
                printf("��                                                          δ�ҵ���ҩƷ��                                                            ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                PAK(0);
                break;
            }
            printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
            prt(p2);
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            switch(MessageBox( NULL , TEXT("�����Ǽ���Ҫɾ����ҩƷ��Ϣ���Ƿ�ȷ��Ҫɾ����") , TEXT("��ʾ") , MB_ICONINFORMATION|MB_YESNO))
            {
                case IDYES : {p1->next = p3;p = p2;break;}
                case IDNO  : return ;
            }
        }
        if(p!=NULL) //�ͷ��ڴ�
        {
            free(p);
            printf("  ��ɾ����ҩƷ��Ϣ��");
        }
        PAK(0);
        return ;
    }
}

void four() //����ʧЧ����
{
    if(head_A==NULL)
    {
        system("CLS");
        fflush(stdin);
        printf("\n\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>����ʧЧ����                                                                                                                ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ���ݿ��������ݣ�                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
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
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>����ʧЧ����                                                                                                                ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        1.����ż���            ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        2.�����Ƽ���            ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        3.�����ϼ��˵�          ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("  ����������ѡ��:");
        if(scanf("%d",&choice4)==0||getchar()!='\n'||choice4>3||choice4<0)
            {MessageBox(NULL,TEXT("�����ѡ����������롣"),TEXT("���棡"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
        switch(choice4)
        {
        case 1 :
            {
                char ID[13];
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("�����˵�>>����ʧЧ����>>����ż���                                                                                                    ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("  ������Ҫ����ʧЧ���ڵ�ҩƷ��ţ�");
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
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("�����˵�>>����ʧЧ����>>����ż���                                                                                                    ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
                    prt(p1);
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                          ����������Ϣ����ҩƷ��ʧЧ����Ϊ��%4d��%2d��%2d��                                          ��\n",y,m,d);
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    PAK(0);break;
                }
                else
                {
                    system("CLS");
                    printf("\n\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("�����˵�>>����ʧЧ����>>����ż���                                                                                                    ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                          δ�ҵ���ҩƷ��                                                            ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
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
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("�����˵�>>����ʧЧ����>>�����Ƽ���                                                                                                    ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("  ������Ҫ��ѯ��ҩƷ���ƣ�");
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
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("�����˵�>>����ʧЧ����>>�����Ƽ���                                                                                                    ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
                    prt(p1);
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                          ����������Ϣ����ҩƷ��ʧЧ����Ϊ��%4d��%2d��%2d��                                          ��\n",y,m,d);
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    PAK(0);break;
                }
                else
                {
                    system("CLS");
                    printf("\n\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("�����˵�>>����ʧЧ����>>�����Ƽ���                                                                                                    ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                          δ�ҵ���ҩƷ��                                                            ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    PAK(0);break;
                }
            }
        case 3 : return;
        }
    }

}

void five() //����ÿ������
{
    if(head_A==NULL)
    {
        system("CLS");
        fflush(stdin);
        printf("\n\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>����ÿ������                                                                                                                ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ���ݿ��������ݣ�                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
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
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>����ÿ������                                                                                                                ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        1.����ż���            ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        2.�����Ƽ���            ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        3.�����ϼ��˵�          ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("  ����������ѡ��:");
        if(scanf("%d",&choice5)==0||getchar()!='\n'||choice5>3||choice5<0)
            {MessageBox(NULL,TEXT("�����ѡ����������롣"),TEXT("���棡"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
        switch(choice5)
        {
        case 1 :
            {
                p1 = head_A;
                char ID[13];
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("�����˵�>>����ÿ������>>����ż���                                                                                                    ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("  ������Ҫ��ѯ��ҩƷ��ţ�");
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
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("�����˵�>>����ÿ������>>����ż���                                                                                                    ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
                    prt(p1);
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                             ����������Ϣ����ҩƷ��ÿ������Ϊ��%2d-%2dmg                                              ��\n",least,most);
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    PAK(0);break;
                }
                else
                {
                    system("CLS");
                    printf("\n\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("�����˵�>>����ÿ������>>����ż���                                                                                                    ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                          δ�ҵ���ҩƷ��                                                            ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
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
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("�����˵�>>����ÿ������>>�����Ƽ���                                                                                                    ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("  ������Ҫ��ѯ��ҩƷ���ƣ�");
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
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("�����˵�>>����ÿ������>>�����Ƽ���                                                                                                    ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
                    prt(p1);
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                             ����������Ϣ����ҩƷ��ÿ������Ϊ��%2d-%2dmg                                              ��\n",least,most);
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    PAK(0);break;
                }
                else
                {
                    system("CLS");
                    printf("\n\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("�����˵�>>����ÿ������>>�����Ƽ���                                                                                                    ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                          δ�ҵ���ҩƷ��                                                            ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    PAK(0);break;
                }
            }
        case 3 : return;
        }
    }


}

void six() //��ѯ
{
    if(head_A==NULL)
    {
        system("CLS");
        fflush(stdin);
        printf("\n\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>��ѯ                                                                                                                        ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ���ݿ��������ݣ�                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
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
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>��ѯ                                                                                                                        ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        1.����ż���            ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        2.�����Ƽ���            ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        3.�����ϼ��˵�          ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("  ����������ѡ��:");
        if(scanf("%d",&choice6)==0||getchar()!='\n'||choice6>3||choice6<0)
            {MessageBox(NULL,TEXT("�����ѡ����������롣"),TEXT("���棡"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
        switch(choice6)
        {
        case 1 :
            {
                char ID[13];
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("�����˵�>>��ѯ>>����ż���                                                                                                            ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("  ������Ҫ��ѯ��ҩƷ��ţ�");
                gets(ID);
                while( (strcmp(p1->ID,ID)) && (p1->next != NULL))
                    p1 = p1->next;
                if(!strcmp(p1->ID,ID))
                {
                    system("CLS");
                    printf("\n\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("�����˵�>>��ѯ>>����ż���                                                                                                            ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
                    prt(p1);
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    PAK(0);break;
                }
                else
                {
                    system("CLS");
                    printf("\n\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("�����˵�>>��ѯ>>����ż���                                                                                                            ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                          δ�ҵ���ҩƷ��                                                            ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    PAK(0);break;
                }
            }
        case 2 :
            {
                char Name[20];
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("�����˵�>>��ѯ>>�����Ƽ���                                                                                                            ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("  ������Ҫ��ѯ��ҩƷ���ƣ�");
                gets(Name);
                while( (strcmp(p1->Name,Name)) && (p1->next != NULL))
                    p1 = p1->next;
                if(!strcmp(p1->Name,Name))
                {
                    system("CLS");
                    printf("\n\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("�����˵�>>��ѯ>>�����Ƽ���                                                                                                            ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
                    prt(p1);
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    PAK(0);break;
                }
                else
                {
                    system("CLS");
                    printf("\n\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("�����˵�>>��ѯ>>�����Ƽ���                                                                                                            ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��                                                          δ�ҵ���ҩƷ��                                                            ��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                    PAK(0);break;
                }
            }
        case 3 : return;
        }
    }
}

void seven() //����鿴
{
    if(head_A==NULL)
    {
        system("CLS");
        fflush(stdin);
        printf("\n\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>����鿴                                                                                                                    ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ���ݿ��������ݣ�                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
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
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>����鿴                                                                                                                    ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        1.��ðҩ                ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        2.θҩ                  ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        3.����ҩ                ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        4.����ҩ                ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        5.δ����ҩƷ            ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("��������������������������������������������������        6.�����ϼ��˵�          ������������������������������������������������������\n");
        printf("��                                                                                                                                    ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("  ����������ѡ��:");
        if(scanf("%d",&choice7)==0||getchar()!='\n'||choice7>6||choice7<0)
            {MessageBox(NULL,TEXT("�����ѡ����������롣"),TEXT("���棡"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
        switch(choice7)
        {
        case 1 :
            {
                p1 = head_A;
                n = 0;
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("�����˵�>>����鿴>>��ðҩ                                                                                                            ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
                while(p1 != NULL)
                {
                    if(p1->type==1) {prt(p1);n++;}
                    p1 = p1->next;
                }
                if(n==0)
                    printf("��                                                         δ�ҵ�����ҩƷ��                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                PAK(0);break;
            }
        case 2 :
            {
                p1 = head_A;
                n = 0;
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("�����˵�>>����鿴>>θҩ                                                                                                              ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
                while(p1 != NULL)
                {
                    if(p1->type==2) {prt(p1);n++;}
                    p1 = p1->next;
                }
                if(n==0)
                    printf("��                                                         δ�ҵ�����ҩƷ��                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                PAK(0);break;
            }
        case 3 :
            {
                p1 = head_A;
                n = 0;
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("�����˵�>>����鿴>>����ҩ                                                                                                            ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
                while(p1 != NULL)
                {
                    if(p1->type==3) {prt(p1);n++;}
                    p1 = p1->next;
                }
                if(n==0)
                    printf("��                                                         δ�ҵ�����ҩƷ��                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                PAK(0);break;
            }
        case 4 :
            {
                p1 = head_A;
                n = 0;
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("�����˵�>>����鿴>>����ҩ                                                                                                            ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
                while(p1 != NULL)
                {
                    if(p1->type==4) {prt(p1);n++;}
                    p1 = p1->next;
                }
                if(n==0)
                    printf("��                                                         δ�ҵ�����ҩƷ��                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                PAK(0);break;
            }
        case 5 :
            {
                p1 = head_A;
                n = 0;
                system("CLS");
                fflush(stdin);
                printf("\n\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("�����˵�>>����鿴>>δ����ҩƷ                                                                                                        ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
                while(p1 != NULL)
                {
                    if((p1->type!=1)&&(p1->type!=2)&&(p1->type!=3)&&(p1->type!=4)) {prt(p1);n++;}
                    p1 = p1->next;
                }
                if(n==0)
                    printf("��                                                         δ�ҵ�����ҩƷ��                                                           ��\n");
                printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
                PAK(0);break;
            }
        case 6 :return;
        }
    }
    PAK(0);
}

void prt(struct ALL *p) //��ӡ�����ڵ�}
{
    printf("��%14s |",p->ID);
    printf("%17s | ",p->Name);
    if((p->produced.year==-1)||(p->produced.month==-1)) printf("****/**/** | ");
    else printf("%4d/%2d/%2d | ",p->produced.year,p->produced.month,p->produced.day);
    if (p->valid==-1) printf(" *���� | ");
    else printf("%2d���� | ",p->valid);
    if((p->invalid.year==-1)||(p->invalid.month==-1)) printf("****/**/** | ");
    else printf("%4d/%2d/%2d | ",p->invalid.year,p->invalid.month,p->invalid.day);
    if(p->type==1)    printf("     ��ðҩ  | ");
    else if(p->type==2)    printf("       θҩ  | ");
    else if(p->type==3)    printf("     ����ҩ  | ");
    else if(p->type==4)    printf("     ����ҩ  | ");
    else                   printf("     δ˵��  | ");
    if(p->use.way==1)      printf("��ǰ�ڷ� ");
    else if(p->use.way==2) printf("��ǰ�ڷ� ");
    else if(p->use.way==3) printf("    ���� ");
    else                   printf("  δ˵�� ");
    if(p->use.frequence[0]==-1) printf("ÿ�� *-");
    else printf("ÿ��%2d-",p->use.frequence[0]);
    if(p->use.frequence[1]==-1) printf(" *�� ");
    else printf("%2d�� ",p->use.frequence[1]);
    if(p->use.each[0]==-1) printf("ÿ�� *-");
    else printf("ÿ��%2d-",p->use.each[0]);
    if(p->use.each[1]==-1) printf(" *mg ");
    else printf("%2dmg ",p->use.each[1]);
    if(p->use.most==-1) printf("ÿ����� ���ީ�\n");
    else printf("ÿ����� %2dmg��\n",p->use.most);
}
void print(struct ALL *head) //�ṩ����ͷ����ӡ�����������нڵ�
{
    fflush(stdin);
    system("CLS");
    struct ALL *p;
    p = head;
    printf("\n\n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
    while(p!=NULL)
    {
        prt(p);
        p = p->next;
    }
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
}
void eight() //ȫ����Ϣ
{
    fflush(stdin);
    system("CLS");
    if(head_A==NULL)
    {
        printf("\n\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>ȫ����Ϣ                                                                                                                    ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ���ݿ��������ݣ�                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    }
    if(head_A!=NULL)
        print(head_A);
    PAK(0);
}

void nine() //�洢
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
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>�洢                                                                                                                        ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ���ݿ��������ݣ�                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    }
    if(head_A!=NULL)
    {
        do                                               /*���ļ�*/
        {
            system("CLS");
            fflush(stdin);
            flag1 = true;
            printf("\n\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            printf("�����˵�>>�洢                                                                                                                        ��\n");
            printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
            printf("  �������ļ�����");
            gets(filename);
            if((fp=fopen(filename,"a+"))==NULL)
            {
                if(MessageBox(NULL,TEXT("�����ڴ��ļ����Ƿ�������ļ���"),TEXT("���ļ�ʧ��!"),MB_ICONINFORMATION|MB_YESNO)!=IDNO)  flag1 = false;
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
        printf("  �ѳɹ������ݿ���Ϣ����%s",filename);
    }
    PAK(0);
}

void ten() //����ҩƷ��Ϣ
{
    system("CLS");
    fflush(stdin);
    if(head_A==NULL)
    {

        printf("\n\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>����ҩƷ��Ϣ                                                                                                                ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ���ݿ��������ݣ�                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        PAK(0);return ;
    }
    struct ALL *p1 = head_A;
    printf("\n\n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("�����˵�>>����ҩƷ��Ϣ                                                                                      ��ǰ���ڣ�%4d��%2d��%2d��  ��\n",today);
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
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
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    PAK(0);
}

void eleven() //��������ҩƷ��Ϣ
{
    while(1)
    {
    system("CLS");
    fflush(stdin);
    if(head_A==NULL)
    {

        printf("\n\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>��������ҩƷ��Ϣ                                                                                                            ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ���ݿ��������ݣ�                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        PAK(0);return ;
    }
    int pvalid;
    struct ALL *p1 = head_A;
    system("CLS");
    fflush(stdin);
    printf("\n\n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("�����˵�>>��������ҩƷ��Ϣ                                                                                  ��ǰ���ڣ�%4d��%2d��%2d��  ��\n",today);
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("  ���ʣ�����Ϊ��Ч�ڽ�ʣ����������ʱ��ҩƷ����Ϊ��������ҩƷ��");
    if(scanf("%d",&pvalid)==0||getchar()!='\n'||pvalid<1)
            {MessageBox(NULL,TEXT("ֻ����������"),TEXT("���棡"),MB_ICONWARNING|MB_OK);fflush(stdin);continue;}
    system("CLS");
    fflush(stdin);
    printf("\n\n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("�����˵�>>��������ҩƷ��Ϣ                                                                                  ��ǰ���ڣ�%4d��%2d��%2d��  ��\n",today);
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��          ��� |         ҩƷ���� |   �������� | ��Ч�� |   ʧЧ���� | ���β�֢��� |                   �÷�������                  ��\n");
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
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    PAK(0);
    return;
    }
}

void twelve() //�޸ĵ�ǰ����
{
    while(1)
    {
    int y = 0;
    int m = 0;
    int d = 0;
    system("CLS");
    fflush(stdin);
    printf("\n\n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("�����˵�>>�޸ĵ�ǰ����                                                                                      ��ǰ���ڣ�%4d��%2d��%2d��  ��\n",today);
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("  �������µ����ڣ����������м��ÿո����������1997 02 09��\n  ");
    if(scanf("%d%d%d",&y,&m,&d)==0||getchar()!='\n'||y>9999||y<-1||m>12||m<-1||m==0||d>30||d<-1||d==0)
            {printf("  ����Υ������\n");PAK(1);return;}
    today.year = y;
    today.month = m;
    today.day = d;
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf(" ��ǰ�������޸ĳɹ���");
    fflush(stdin);
    PAK(0);
    return;
    }
}

void thirteen() //�������
{
    struct ALL *p1,*p2;
    system("CLS");
    fflush(stdin);
    if(head_A==NULL)
    {

        printf("\n\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("�����˵�>>�������                                                                                                                    ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��                                                         ���ݿ��������ݣ�                                                           ��\n");
        printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
        PAK(0);return ;
    }
    printf("\n\n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��                                                         ҩƷ��Ϣ����ϵͳ                                                           ��\n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("�����˵�>>�������                                                                                                                    ��\n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    switch(MessageBox( NULL , TEXT("�˲�����������ݿ��е�������Ϣ���Ƿ�ȷ��������ݿ⣿") , TEXT("���棡") , MB_ICONINFORMATION|MB_YESNO))
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
            printf("  �ѳɹ�������ݿ�");
        }
    }
    PAK(0);
}
