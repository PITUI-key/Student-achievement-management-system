#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct _STU//定义节点
{
    char arrStuNum[10];
    char arrStuName[10];
    int nStuscore;
    struct _STU* pNext;
}STUNODE;
STUNODE* g_phead = NULL;
STUNODE* g_pend = NULL;


 void AddStuMSG(char *arrStuNum,char arrStuName[10],int nStuscore);

 //清空链表
 void FreeLinkDate();


 //打印数据
 void ShowStuMSG();
 //链表头添加一个节点
 void AddStuMSGToLinkHead(char *arrStuNum,char arrStuName[10],int nStuscore);
 //查找指定学生
 STUNODE*FindStuByNum(char*arrStuNum);
 //指定位置插入节点
 void InserNode(STUNODE*pTemp,char *arrStuNum,char arrStuName[10],int nStuscore);
 //显示目录
 void Showlist();
 //删除指定学生信息
 void DeleteStuNode(STUNODE*pNode);
 //保存到文件
 void SaveStuToFile();
 //载入学生信息
 void ReadStuFromFile();



int main(void)
{
    int nOrder = -1;  //初始化
    int nFirstorder = -1;
    int nSecondorder = -1;
    char arrStuNum[10] = {0};
    char arrStuName[10] = {0};
    int nStuscore = -1;
    int nFlag = 1;


    STUNODE*pTemp = NULL;
    ReadStuFromFile();
	printf("************欢迎使用学生成绩管理系统***************\n");
        printf("            1.录入信息\n");
        printf("            2.打印信息\n");
        printf("            3.查找信息\n");
        printf("            4.修改信息\n");
        printf("            5.删除信息\n");
        printf("            6.保存信息\n");
        printf("            7.载入信息\n");
        printf("            0.退出系统\n");
        while(nFlag)
        {
             printf("输入指令(输入10查看目录)：");
             scanf("%d",&nOrder);
        switch(nOrder)
        {
        case 1://创建链表以及插入节点

            printf("输入1从尾添加信息、2从头添加信息、3在指定位置添加信息\n");
            scanf("%d",&nFirstorder);
            switch(nFirstorder)
            {
            case 1://尾添加节点
                 printf("输入学号：\n");
            scanf("%s",arrStuNum);
            printf("输入姓名：\n");
            scanf("%s",arrStuName);
            printf("输入分数：\n");
            scanf("%d",&nStuscore);


            AddStuMSG( arrStuNum, arrStuName, nStuscore);
            break;

            case 2://头插入节点
                 printf("输入学号：\n");
            scanf("%s",arrStuNum);
            printf("输入姓名：\n");
            scanf("%s",arrStuName);
            printf("输入分数：\n");
            scanf("%d",&nStuscore);

           AddStuMSGToLinkHead(arrStuNum,arrStuName, nStuscore);
           break;

            case 3://指定位置插入节点
                 printf("输入指定学号：\n");
            scanf("%s",arrStuNum);
            pTemp = FindStuByNum(arrStuNum);
            if(NULL !=pTemp)
            {
                printf("输入学号：\n");
                scanf("%s",arrStuNum);
                printf("输入姓名：\n");
                scanf("%s",arrStuName);
                printf("输入分数：\n");
                scanf("%d",&nStuscore);
                InserNode(pTemp,arrStuNum,arrStuName, nStuscore);
            }
            break;
             default:
            printf("输入有误！\n");
            }
            break;

        case 2: //打印学生信息
             ShowStuMSG();
            break;
        case 3: //打印指定学生信息
            printf("输入指定学号：\n");
                 scanf("%s",arrStuNum);
                 //查找
                  pTemp = FindStuByNum(arrStuNum);

                  //打印信息
                  if(NULL != pTemp)
            {
                printf("学号：%s,姓名： %s, 分数：%d\n",pTemp->arrStuNum,pTemp->arrStuName,pTemp->nStuscore);
            }

            break;
        case 4: //修改指printf("删除成功！\n");定学生信息
            printf("输入指定学号：\n");
            scanf("%s",arrStuNum);
            pTemp = FindStuByNum(arrStuNum);
            if(NULL != pTemp)
            {
                //修改学号
                printf("输入学号：\n");
                scanf("%s",arrStuNum);
                strcpy(pTemp->arrStuNum,arrStuNum);

                //修改姓名
                printf("输入姓名：\n");
                scanf("%s",arrStuName);
                strcpy(pTemp->arrStuName,arrStuName);

                //修改分数
                printf("输入分数：\n");
                scanf("%d",&nStuscore);
                pTemp->nStuscore = nStuscore;
            }
            break;
        case 5:
             printf("输入要删除的学号：\n");
             scanf("%s",arrStuNum);
                 //查找
             pTemp = FindStuByNum(arrStuNum);
             //删除节点
             if(NULL != pTemp)
             {
                 //调用删除信息的函数
                 DeleteStuNode(pTemp);
                 printf("删除成功！\n");
             }


            break;
        case 6:
            //爆粗学生信息
            SaveStuToFile();
            break;
        case 7:
            //载入学生信息
          ReadStuFromFile();
          break;
        case 10:
            Showlist();
            break;
        case 0:
            nFlag = 0;
            break;
        default:
            printf("输入有误！\n");
        }
    }
    //保存到文件
    SaveStuToFile();

        //释放链表
        FreeLinkDate();
	system("pause");
	return 0;
 }

 //显示目录
 void Showlist()
 {
   printf("************欢迎使用学生成绩管理系统***************\n");
        printf("            1.录入信息\n");
        printf("            2.打印信息\n");
        printf("            3.查找信息\n");
        printf("            4.修改信息\n");
        printf("            5.删除信息\n");
        printf("            6.保存信息\n");
        printf("            7.载入信息\n");
        printf("            0.退出系统\n");
 }
 //添加学生信息
 void AddStuMSG(char *arrStuNum,char arrStuName[10],int nStuscore)
 {
     STUNODE * pTemp =(STUNODE*)malloc(sizeof (STUNODE));//申请内存
     //检验参数合法性
     if(NULL == arrStuNum || NULL == arrStuName || nStuscore<0)
     {
         printf("学生信息输入错误！\n");
         return ;
     }
     //创建节点

     //给一个初始值
     strcpy(pTemp->arrStuNum,arrStuNum);
     strcpy(pTemp->arrStuName,arrStuName);
     pTemp->nStuscore = nStuscore;
     pTemp->pNext = NULL;

     //链表连接
     if(NULL == g_phead)
     {
         g_phead = pTemp;

     }
     else
        {
          g_pend->pNext = pTemp; //连接
          g_pend = pTemp;        //向后移动
        }
        g_pend  = pTemp;
 }
//销毁列表
void FreeLinkDate()
 {
     STUNODE*pTemp = g_phead;
     while(g_phead != NULL)
     {
         pTemp = g_phead;
         g_phead = g_phead->pNext;//向后移动一个

         //删除节点
         free(pTemp);
     }
 }

 void ShowStuMSG()
 {
    STUNODE*pTemp = g_phead;
     while(pTemp!= NULL)
     {
         printf("学号：%s，姓名：%s，分数：%d\n",pTemp->arrStuNum,pTemp->arrStuName,pTemp->nStuscore);
         pTemp = pTemp->pNext;


     }
 }
 //从头添加节点
 void AddStuMSGToLinkHead(char *arrStuNum,char arrStuName[10],int nStuscore)
 {
     //检测合法性
     STUNODE * pTemp =(STUNODE*)malloc(sizeof (STUNODE));
     if(NULL == arrStuNum || NULL == arrStuName || nStuscore <0)
     {
          printf("学生信息输入错误！\n");
          return ;
     }
     //创建新节点

     strcpy(pTemp->arrStuNum,arrStuNum);
     strcpy(pTemp->arrStuName,arrStuName);
     pTemp->nStuscore = nStuscore;
     pTemp->pNext = NULL;

     if (NULL == g_phead || NULL == g_pend)
     {
         //链表为空
         g_phead = pTemp;
         g_pend = pTemp;
     }
     else
        {
            //新节点的下一个指向头
            pTemp->pNext = g_phead;
            g_phead = pTemp;
        }
        g_phead = pTemp;


 }
 // 查找学生信息
  STUNODE* FindStuByNum(char* arrStuNum)
{
    STUNODE*pTemp = g_phead;
    //检查参数合法性
    if(NULL == arrStuNum)
    {
        printf("学号输入错误！\n");
        return NULL;
    }
    //判断链表是否为空
    if(NULL == g_phead || NULL == g_pend)
    {
         printf("未查到数据\n");
        return NULL;
    }
    //遍历链表


    while(pTemp != NULL)
    {
        if(0 == strcmp(pTemp->arrStuNum,arrStuNum))
        {
            return pTemp;

        }
        pTemp = pTemp->pNext;
    }
    printf("未查到数据！\n");
    return NULL;
}
//指定位置插入学生信息
void InserNode(STUNODE*pTemp,char *arrStuNum,char arrStuName[10],int nStuscore)
{
    //创建节点
    STUNODE*pNewTemp = (STUNODE*)malloc(sizeof(STUNODE));


    //成员赋值
     strcpy(pNewTemp->arrStuNum,arrStuNum);
     strcpy(pNewTemp->arrStuName,arrStuName);
     pNewTemp->nStuscore = nStuscore;
     pNewTemp->pNext = NULL;


    //插入
    if(pTemp == g_pend)
    {
        g_pend->pNext = pNewTemp;
        g_pend = pNewTemp;
    }
    else
    {
        //
        pNewTemp->pNext = pTemp->pNext;
        pTemp->pNext = pNewTemp;
    }
}
//删除节点
void DeleteStuNode(STUNODE*pNode)
{
    //只有一个节点
    if(g_phead == g_pend)
    {
        free(g_phead);
        g_phead = NULL;
        g_pend = NULL;
    }
    //只有俩节点
    else if(g_phead->pNext == g_pend)
    {
        if(g_phead == pNode)
        {
            free(g_phead);
            g_phead = g_pend;
        }
        else
        {
            free(g_pend);
            g_pend = g_phead;
            g_phead->pNext = NULL;
        }
    }
    else//大于等于三个
    {
        STUNODE*pTemp = g_phead;
        //判断头节点是否是要删除的
        if(g_phead == pNode)
        {
            pTemp = g_phead;
            g_phead = g_phead->pNext;
            free(pTemp);
            pTemp = NULL;
            return ;
        }

        while(pTemp)
        {
            if(pTemp->pNext == pNode)
            {
                //删除
                if(pNode == g_pend)
                {

                    free(pNode);
                    pNode = NULL;
                    g_pend = pTemp;
                    g_pend->pNext=NULL;
                    return ;

                }
                else
                {
                   //申请一个节点来记住要删除的节点
                   STUNODE*pDel =pTemp->pNext;
                   pTemp->pNext = pNode->pNext->pNext;
                   free(pDel);
                   pDel = NULL;
                   return ;
                }
            }
            pTemp = pTemp->pNext;
        }
    }
}
//保存到文件
void SaveStuToFile()
{
    //判断链表是否为空
    FILE*pFILE = NULL;
    STUNODE*pTemp = g_phead;
    char strBuf[30] = {0};
    char strScore[10]= {0};

    if(NULL == g_phead || NULL == g_pend)
    {
        printf("目前没数据\n");
        return ;
    }
    //打开文件
    pFILE = fopen("dat.dat","wb+");
    if(NULL == pFILE)
    {
        printf("文件打开失败\n");
        return ;

    }

    //操作文件指针
    while(pTemp)
    {
       //学号复制
       strcpy(strBuf,pTemp->arrStuNum);
       strcat(strBuf,"-");
       //姓名
       strcat(strBuf,pTemp->arrStuName);
       strcat(strBuf,"-");
       //分数
       itoa(pTemp->nStuscore,strScore,10);
       strcat(strBuf,strScore);

       fwrite(strBuf,1,strlen(strBuf),pFILE);
       fwrite("\r\n",1,strlen("\r\n"),pFILE);
       pTemp = pTemp->pNext;
    }

    //关闭文件
    fclose(pFILE);
}
 //载入学生信息
 void ReadStuFromFile()
 {
     FILE*pFILE = fopen("dat.dat","rb+");
     char strBuf[30] = {0};
     char strStuNum[10]={0};
     char strStuName[10]={0};
     char strStuScore[10]={0};

     int nCount = 0;
    int j = 0;

     if(NULL == pFILE )
     {
         printf("文件打开失败\n");
         return ;
     }

     //载入函数

     while(EOF != fgets(strBuf,30,pFILE))
     {
         int i = 0;
         for(i = 0;strBuf[i] != '\r';i++)
         {
             if(0 == nCount)//每到“-”
             {
                 strStuNum[i] = strBuf[i];
                 if('-' == strBuf[i])
                    {
                        nCount++;
                    }
             }
             else if(1 == nCount)//第一个“-”
             {

                 strStuName[j]=strBuf[i];
                 if('-' == strBuf[i])
                    {
                        nCount++;
                        j = 0;
                        continue;
                    }
                j++;
             }
             else //第二个“-”
             {
                 int j = 0;
                 strStuScore[j] == strBuf[j];
                 j++;
             }
         }
     }


     fclose(pFILE);
 }



















