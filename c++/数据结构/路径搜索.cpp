#include <iostream.h>
#include <fstream.h>

const int MAX_N = 100;              // ���Ľڵ���Ŀ
const char* INPUT_FILE = "Graph.txt";


struct Graph {
    int NodeCount;                  // �ڵ����Ŀ
    int AdjMatrix[MAX_N][MAX_N];    // �ڽӾ���,���ͼ��i,j������G[i][j]>0������G[i][j]=0
};

typedef int Path[MAX_N];            // �����洢·��
    
typedef bool Mark[MAX_N];          // ��Ƿ��ʹ��Ľڵ�


void PrintPath(Path& path, int length) {        // ��ӡ·��
    for (int i = 0; i < length; i++) {
        cout << path[i] << " ";
    }
    cout << endl;
}

// �����������
// G �����ͼ��
// path������¼·��
// visited ��������������Ľڵ㣬��ʼ��ȫ��Ϊfalse
// v ��ǰ�Ľڵ�
// T Ŀ�Ľڵ�
// length Ŀǰ�Ѿ��õ���·���ĳ���
void SearchAllPath(const Graph& G, Path& path, Mark& visited, int v, int des, int length) {
    if (visited[v]) return;
    path[length-1] = v;
    if (v == des) {
        PrintPath(path, length);
    } else {
        visited[v] = true;
        for (int i = 0; i < G.NodeCount; i++) 
            if (G.AdjMatrix[v][i] != 0 && !visited[i]) {                
                SearchAllPath(G, path, visited, i, des, length+1);
            }
        visited[v] = false;
    }
}


void ReadData(Graph& G, int& src, int& des)  //��������
{
    ifstream fin(INPUT_FILE);
    fin >> G.NodeCount >> src >> des;      // ����ڵ���Ŀ������յ㣬�ڵ��0��ʼ���
    for (int i = 0; i < G.NodeCount; i++) 
        for (int j = 0; j < G.NodeCount; j++) {
            fin >> G.AdjMatrix[i][j];
        }
}

int main()
{
    
    Graph G;
    int src, des;          // �����յ�    
    Path path;              // �洢·��
    Mark visited;          // ���ʱ��
    ReadData(G, src, des);  //��������

    for (int i = 0; i < G.NodeCount; i++) visited[i] = false;  // ��ʼ��
    SearchAllPath(G, path, visited, src, des, 1);  
    
    return 0;
}
