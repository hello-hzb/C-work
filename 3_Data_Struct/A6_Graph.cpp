#include<stdio.h>
#include<stdlib.h>



//从153页开始
/*********************************************************
图是一种较线性表和树更为复杂的数据结构。
线性表：数据元素之间呈现一种线性关系，即每个元素只有一个直接前驱和一个直接的后继；
树：节点之间是一种层次关系，即每个节点只有一个直接前驱，但可以有多个直接后继；
图形结构：每个节点即可以由多个直接前驱，也可以由对个直接后继。

图是一种数据结构，图和树一样可以用二元组表示，可以表示为G=(V,E)，其中
V={x|x属于某个数据元素的集合}  也就是图顶点上的数据（Vertex）
E={<x,y>|x,y属于V}或者E={<x,y>|x,y属于V}    即两个顶点之间的关系集合
<x,y>：表示从x到y的一条弧（Arc),称为有向边，用于有向图中

(x,y)：表示x和y之间的一条边，用于无向图

图的基本术语：
1.完全图、稀疏图、稠密图
若n表示图的顶点数，e表示边的数目，若G是无向图，那么e的取值范围是0到n*(n-1)/2；若G是有向图，e的取值范围是0到n*(n-1)
当e取最大值得时候，图称为完全图
当一个图较少的边时，称为稀疏图；相反，则称它为稠密图

2.邻接点


3.顶点的度
顶点v的度是与他相关联的边的条数


5.权、网
在一个图的每条边或者弧上，优势可以标上具有某种含义的数值，这种和图的边相关的数据称为权。这种边或者弧上带权的图称为网





图的存储的结构
根据图的定义克制，图包括两部分信息：图的顶点和描述顶点之间关系的边信息。
1.邻接矩阵
表示顶点之间相邻关系的矩阵
***********************************************************/

#define MAX_VERTEX_NUM 50     //最大顶点个数
struct MGraph
{
	char vexs[MAX_VERTEX_NUM];
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum, arcnum;
};

/********************************************************************
建立无向图的邻接矩阵
1.输入图的顶点数和边数
2.输入顶点的字符信息，建立顶点数组
3.初始化邻接矩阵
4.输入边的信息，建立图的邻接矩阵。注意：无权图只需输入变得额两个顶点序号，而有权图还需要输入边的权值w。

该算法时间复杂度O(n^2+n*e), 其中（O(n^2))的时间耗费在邻接矩阵的初始化操作上，O(n*e)的时间耗费在邻接矩阵的创建操作上。
********************************************************************/
void Creat_MG(MGraph* MG)
{
	int k, m, w;
	int v1, v2;
	//输入顶点个数和边的数目
	printf("\ninput vexnum: ");
	scanf("%d", &MG->vexnum);
	printf("\ninput arcnum: ");
	scanf("%d", &MG->arcnum);
	//输入顶点信息，建立顶点数组
	for (int i = 1; i < MG->vexnum; i++)
	{
		printf("\ninput %dth vex(char): ", i);
		scanf("%c", &MG->vexs[i]);
		getchar();
	}
	//初始化邻接矩阵
	for (int i = 0; i < MG->vexnum; i++)
	{
		for (int j = 0; j < MG->vexnum; j++)
		{
			MG->arcs[i][j] = 0;
		}
	}
	//输入边的信息，建立邻接矩阵
	for (int i = 0; i < MG->arcnum; i++)
	{
		printf("\ninput %dth arc v1(int)  v2(int): ", k);
		scanf("%d%d", &v1, &v2);
		MG->arcs[v1][v2] = MG->arcs[v2][v1] = 1;
	}
}


/**********************************************************
使用链表存储邻接信息
头结点：   vexdata|firstarc         由顶点域(vexdata)和指向第一条邻接边的指针域(fisrstarc)构成      
表节点：   adjvex|nextarc		   由邻节点域(adjvex)和指向下一条邻接边的指针域(nextarc)构成
*********************************************************/

#define MAX_VERTEX_NUM 50      //定义最大顶点个数
typedef int vertextype;
struct ArcNode
{
	int adjvex;               //邻接点的位置
	int weight;               //权值域， 存储边的权值，为网的建立做准备
	struct ArcNode* nextarc;  //指向下一个邻接点
};

struct VNode
{
	vertextype vexdata;       //顶点信息
	int id;					  //存储该顶点的入度，为拓扑排序做准备
	ArcNode* firstarc;		  //指向第一个邻接顶点
};

struct ALGraph
{
	VNode vertices[MAX_VERTEX_NUM];   
	int vexnum, arcnum;     //图的当前顶点数
};



/********************************************************************
建立无向图的邻接表
1.输入图的顶点数、边数和图的种类
2.输入顶点的字符信息，并初始化所有链表的头指针和空指针NULL。
3.输入边的信息，生成边表节点，建立图的邻接表。注意：无权图只需要输入变量两个顶点序号i和j，而有权图还需要输入边的权值w

该算法时间复杂度O(n+e)
********************************************************************/
void Creat_AG(ALGraph* AG)
{
	//输入顶点和边的信息，建立图的邻接表
	ArcNode* p;
	printf("\ninput vexnum: ");
	scanf("%d", &AG->vexnum);
	printf("\ninput arcnum: ");
	scanf("%d", &AG->arcnum);

	for (int i = 0; i <= AG->arcnum; i++)
	{
		printf("\ninput %dth vex(char)", i);
		scanf("%c", &AG->vertices[i].vexdata);
		getchar();
		AG->vertices[i].firstarc = NULL;
	}
	//输入边信息，建立邻接表
	for (int k = 1; k <= AG->arcnum; k++)
	{
		int i, j;
		printf("\minput %dth arc i(int)   j(int)", k);
		scanf("%d%d", &i, &j);
		//在第i个链表上插入序号为j的表节点
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
		p->nextarc = AG->vertices[i].firstarc;
		AG->vertices[i].firstarc = p;
		//在第j个链表上插入序号为i的表节点

		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = i;
		p->nextarc = AG->vertices[j].firstarc;
		AG->vertices[j].firstarc = p;

	}
}



/********************************************************************
图的遍历：广度优先搜索遍历和深度优先搜索遍历
遍历算法需要考虑以下两个问题：
1.算法的参数除了指定遍历的图外，还需要指定遍历的第一个节点
2.一个顶点可能有若干邻节点，在算法中要确保一个顶点的所有邻点按照某种次序被访问
连通图：图中任一一对顶点是连通的称为连通图。   非连通图中的极大连通子图称为连通分量
********************************************************************/
/*******************************************************************
深度优先搜索遍历
1.访问出发点vi， 并将其标记为已经访问过
2.遍历vi的没哟呵邻接点vj， 若vj未曾被访问过，则以vj为新的出发点继续进行深度优先遍历。
********************************************************************/
#define MAX_VERTEX_NUM 50
int visited[MAX_VERTEX_NUM];
//n个顶点， e条边，
//DFS1中每一个顶点检查矩阵中所相应的所有n个元素，故时间复杂度为O(n^2)
void DFS1(MGraph* MG, int i)
{
	visited[i] = 1;
	printf("%3c", MG->vexs[i]);
	for (int j = 0; j < MG->vexnum; j++)
	{
		if(visited[j] == 0 && MG->arcs[i][j] == 1)
		{
			DFS1(MG, j);
		}
	}
}

//DFS2用邻接表表示图时，遍历n个顶点的所有邻接点即是对各边表节点扫描一遍，时间复杂度为O(n+e)
void DFS2(ALGraph* G, int i)
{
	ArcNode* p;
	visited[i] = 1;
	printf("%3c", G->vertices[i].vexdata);
	for (p = G->vertices[i].firstarc; p; p = p->nextarc)
	{
		int j = p->adjvex;
		if (!visited[j])
			DFS2(G, j);
	}
}




/*******************************************************************
广度优先搜索遍历
算法描述：
访问初始顶点v;
置顶点v为已访问标记
顶点v入队
while(队不空）
{
	取队首顶点 i;
	依次搜索顶点i的所有邻接点;
	若莫一邻接点j未被访问，则访问该邻接点，并将其入队
}
********************************************************************/
#define MAX_VERTEX_NUM 50
#define MAX_VERTEX_NUM 50
int visited[MAX_VERTEX_NUM];

//对于具有n个顶点和e条边的图，每个顶点均入队一次，所以BF1的外循环次数为n。内循环次数为n，所以时间复杂度为O(n^2)
void BFS1(MGraph* G, int v)
{
	int i;
	int Q[30];									//用来存放图中顶点的序号
	int front = 0, rear = 0;					//置空队列，front和rear分别为队首指针和队尾指针
	printf("%c\t", G->vexs[v]);					//访问初始出发点v
	visited[v] = 1;								//将v标记为已访问过
	rear++;										//
	Q[rear] = v;								//v入队
	while (rear != front)						
	{
		front++;
		i = Q[front];						   //队首顶点i出队
		for (int j = 1; j < G->vexnum; j++)
		{
			if (G->arcs[i][j] == 1 && !visited[j])   //顶点i的未被访问的邻接点j被访问并入队
			{
				printf("%c\t", G->vexs[v]);
				visited[v] = 1;
				rear++;
				Q[rear] = j;
			}
		}
	}
}



//BFS2外循环次数为n，内循环执行的中次数为边接点的总个数2e，故时间复杂度为O(n+e)。由于BFS1和BFS2所用的辅助空间是队列和标志位数组，所以空间复杂度为O(n)
void BFS2(ALGraph* G, int v)
{
	int i;
	ArcNode* p;
	int Q[30];									//用来存放图中顶点的序号
	int front = 0, rear = 0;					//置空队列，front和rear分别为队首指针和队尾指针
	printf("%c\t", G->vertices[v].vexdata);					//访问初始出发点v
	visited[v] = 1;								//将v标记为已访问过
	rear++;										//
	Q[rear] = v;								//v入队
	while (rear != front)
	{
		front++;
		i = Q[front];						   //队首顶点i出队
		for (p = G->vertices[i].firstarc; p;p=p->nextarc)
		{
			int j = p->adjvex;

			if (!visited[j])   //顶点i的未被访问的邻接点j被访问并入队
			{
				printf("%c\t", G->vertices[v].vexdata);
				visited[v] = 1;
				rear++;
				Q[rear] = j;
			}
		}
	}
}


