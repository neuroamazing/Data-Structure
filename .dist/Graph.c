#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Node 20
typedef struct
{
    int vex[Node];        //顶点数组
    int arcs[Node][Node]; //邻接矩阵
    int vexNum, arcNum;   //顶点数，弧数
} G, *Graph;

int GetNodePosition(Graph g, int inputNode)
{ //节点在数组的下标
    for (int i = 0; i < g->vexNum; i++)
    {
        if (g->vex[i] == inputNode)
            return i;
    }
    return -1;
}

void initGraph(Graph g)
{
    int i;
    printf("input the number of Nodes:\n");
    scanf("%d", &i);
    g->vexNum = i;
    g->arcNum = 0;
    for (int t = 0; t < i; t++)
    {
        g->vex[t] = -1;
    }
    for (int z = 0; z < i; z++)
    {
        for (int k = 0; k < i; k++)
        {
            g->arcs[z][k] = 0;
        }
    }
}
int inputValid(char *input, int *returnData)
{ //合法化判断 并且获得节点信息 这里设置的是int类型的数
    int i = 1, j = 0, number = 0;
    char getData[20];
    if (input[0] != '(' && input[0] != '<')
    {
        if (input[0] == '#')
            return 0;
        printf("Wrong input %c\n", input[0]);
        return 0;
    }
    while (input[i] != ',')
    {
        getData[j++] = input[i++];
    }
    for (int t = j - 1, z = 0; t >= 0; t--, z++)
    {
        number += (getData[t] - '0') * pow(10, z);
        getData[t] = 0;
    }
    *returnData = number;
    *returnData++;
    number = 0;
    i++;
    j = 0;
    while (input[i] != '>' && input[i] != ')')
    {
        getData[j++] = input[i++];
    }
    if (i > Node)
        return 0;
    for (int t = j - 1, z = 0; t >= 0; t--, z++)
    {
        number += (getData[t] - '0') * pow(10, z);
        getData[t] = 0;
    }
    *returnData = number;
    return 1;
}

void SetNode(Graph g)
{ //获得节点的去重集合 写入信息 主要是顺序存储节点 如果节点重复就不存在节点数组里了
    int i = 0, j = 0, data[2], status0 = 0, status1 = 0, position_i, position_j, typeOfGraph;
    char input[Node];
    printf("input data the form should be <,> or (,) And those numbers should bigger than 0\n"); //<)这种输入目前不支持
    printf("input # to quit\n");
    scanf("%s", &input);
    for (int i = 0; i < g->vexNum; i++)
    {
        g->arcs[0][i] = 0;
    }
    while (inputValid(input, data) && input[0] != '#')
    {
        if (input[0] == '<')
            typeOfGraph = 0; //有向图
        else if (input[0] == '(')
            typeOfGraph = 1; //无向图
        printf("%d %d\n", data[0], data[1]);
        for (int t = 0, count0 = 0, count1 = 0; t < g->vexNum; t++)
        {
            if (data[0] == g->vex[t])
                count0++;
            if (data[1] == g->vex[t])
                count1++;
            if (t == g->vexNum - 1 && count0 == 0)
                status0++, printf("create new node%d\n", data[0]);
            if (t == g->vexNum - 1 && count1 == 0)
                status1++, printf("create new node%d\n", data[1]);
        }

        if (status0 > 0)
        {
            for (int t = 0; t < g->vexNum; t++)
            {
                if (g->vex[t] == -1)
                {
                    g->vex[t] = data[0];
                    break;
                }
            }
            status0 = 0;
        }
        if (status1 > 0)
        {
            for (int t = 0; t < g->vexNum; t++)
            {
                if (g->vex[t] == -1)
                {
                    g->vex[t] = data[1];
                    break;
                }
            }
            status1 = 0;
        }
        position_i = GetNodePosition(g, data[0]); //节点位置i
        position_j = GetNodePosition(g, data[1]); //节点位置j    (i,j)
        if (typeOfGraph == 0)
        {
            g->arcs[position_i][position_j]++;
            g->arcNum++;
        }
        else if (typeOfGraph == 1)
        {
            g->arcs[position_i][position_j]++;
            g->arcs[position_j][position_i]++;
            g->arcNum++;
        }
        fflush(stdin);
        scanf("%s", &input);
    }
}

void printGraph(Graph g)
{
    for (int t = 0; t < g->vexNum; t++)
    {
        printf("Node%d:%d\n", t, g->vex[t]);
    }
    printf("\n");
    printf("       ");
    for (int n = 0; n < g->vexNum; n++)
    {
        printf("%d ", g->vex[n]);
    }
    printf("\n");
    printf("       ");
    for (int n = 0; n < g->vexNum; n++)
    {
        printf("- ", g->vex[n]);
    }
    printf("\n");
    for (int t = 0; t < g->vexNum; t++)
    {

        printf("Node:%d|", g->vex[t]);
        for (int z = 0; z < g->vexNum; z++)
        {
            printf("%d ", g->arcs[t][z]);
        }
        printf("\n");
    }
}

int isNeighbour(Graph g, int v, int w)
{ //邻接情况
    int position_i, position_j;
    position_i = GetNodePosition(g, v);
    position_j = GetNodePosition(g, w);
    if (position_j == -1 || position_i == -1)
        return -1;
    if (g->arcs[position_i][position_j] >= 1)
        return 1;
    return 0;
}

int getOutDegree(Graph g, int v)
{ //计算出度
    int position_v, sum = 0;
    position_v = GetNodePosition(g, v);
    if (position_v == -1)
        return -1;
    for (int i = 0; i < g->vexNum; i++)
    {
        sum += g->arcs[position_v][i];
    }
    return sum;
}

int getInDegree(Graph g, int v)
{ //计算入度
    int position_v, sum = 0;
    position_v = GetNodePosition(g, v);
    if (position_v == -1)
        return -1;
    for (int i = 0; i < g->vexNum; i++)
    {
        sum += g->arcs[i][position_v];
    }
    return sum;
}

void PrintMatrix(int depth, int (*a)[])
{
    int(*p)[depth];
    p = a;
    for (int i = 0; i < depth; i++)
    {
        for (int j = 0; j < depth; j++)
        {
            printf("%d ", *(*(p + i) + j));
        }
        printf("\n");
    }
}

void PrintNeighbourMatrix(Graph g)
{
    for (int i = 0; i < g->vexNum; i++)
    {
        for (int j = 0; j < g->vexNum; j++)
        {
            printf("%d ", g->arcs[i][j]);
        }
        printf("\n");
    }
}
void MatrixAdd(int depth, int (*a)[], int (*b)[])
{ //方阵加法 把后面的矩阵加到前面的矩阵
    int(*p)[depth], (*p2)[depth];
    p = a;
    p2 = b;
    for (int i = 0; i < depth; i++)
    {
        for (int j = 0; j < depth; j++)
        {
            *(*(p + i) + j) += *(*(p2 + i) + j);
        }
    }
}

void MatrixMultiple(int depth, int (*a)[], int (*b)[], int (*c)[])
{
    int(*p)[depth], (*p2)[depth], (*p3)[depth];
    p = a;
    p2 = b;
    p3 = c;
    for (int k = 0; k < depth; k++)
    {

        for (int i = 0; i < depth; i++)
        {
            for (int j = 0; j < depth; j++)
            {
                *(*(p3 + k) + i) += (*(*(p + k) + j)) * (*(*(p2 + j) + i));
            }
        }
    }
}

void getReachableMatrix(Graph g, int (*a)[])
{
    int(*p)[g->vexNum], i = 1;
    int b0[g->vexNum][g->vexNum], b1[g->vexNum][g->vexNum], b_init[g->vexNum][g->vexNum];
    p = a;
    for (int k = 0; k < g->vexNum; k++)
    {
        for (int z = 0; z < g->vexNum; z++)
        {
            b0[k][z] = g->arcs[k][z];
            b_init[k][z] = g->arcs[k][z];
            b1[k][z] = 0;
            *(*(p + k) + z) = 0;
        }
    }

    MatrixAdd(g->vexNum, p, b_init);
    PrintMatrix(g->vexNum, p);
    printf("****************\n");
    while (i < g->vexNum)
    {
        for (int k = 0; k < g->vexNum; k++)
        {
            for (int z = 0; z < g->vexNum; z++)
            {
                b1[k][z] = 0;
            }
        }
        MatrixMultiple(g->vexNum, b_init, b0, b1);
        MatrixAdd(g->vexNum, p, b1);
        for (int k = 0; k < g->vexNum; k++)
        {
            for (int z = 0; z < g->vexNum; z++)
            {
                b0[k][z] = b1[k][z];
            }
        }
        i++;
    }

    return;
}

int main()
{
    Graph g = (Graph)malloc(sizeof(Graph));
    int a[3][3] = {1, 1, 1, 2, 3, 2, 1, 1, 1};
    int b[3][3] = {3, 2, 1, 2, 1, 1, 1, 1, 1};
    int c[3][3] = {0};

    initGraph(g);
    SetNode(g);
    printGraph(g);
    //if(isNeighbour(g,1,2)>0)printf("is neighbour\n");
    //printf("Out:%d\n",getOutDegree(g,1));
    ///printf("In:%d\n",getInDegree(g,1));
    //MatrixMultiple(3,g->arcs,g->arcs,c);

    getReachableMatrix(g, c);
    PrintMatrix(g->vexNum, c);
}