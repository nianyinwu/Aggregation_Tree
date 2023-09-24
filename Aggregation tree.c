#include<stdio.h>
#include <limits.h>
#include<stdlib.h>
#include<string.h>
#define MAX INT_MAX
long long int Cost( long long int weight, int size ); // 計算cost
void Prim( int id, int size, int node[][id+1], long long int weight[] ); // 建樹

int main(){
    int id, link, size, end1, end2, tmp;
    printf("Input:\n");
    printf("#Nodes  #Links  Packet_Size\n");
    scanf("%d%d%d", &id, &link, &size);
    printf("Graph:\n");
    int node [id][id+1];
    memset(node, -1 , sizeof(node)); //陣列初始為-1
    long long int weight[id] ; // 存放每
    memset( weight, -1, sizeof(weight)); // 初始為-1
    for( int i = 0; i < id + link ; i++){
        //讀入input
        if( i < id ){
            scanf("%d%lld", &tmp, &weight[i]); // tmp:Node_ID
        } // if
        else if ( i >= id && i < id+link ){ // 開始存入link
            scanf("%d%d%d", &end1, &end1, &end2); // 讀入Link_ID、Link_End1、Link_End2
            node[end1][end2] = weight[end2] ;
            node[end2][end1] = weight[end2] ;
        } // else if
    } // for

    Prim( id, size, node, weight ); // 生成樹


}

long long int Cost( long long int weight, int size ){  // 計算cost
    if( weight/size == 0 && weight != 0) return 1;
    //weight為0或是不足packet_size
    else if( weight/size != 0 && weight%size != 0 ) return (weight/size) + 1;
    // weight不能被packet_size整除
    else return weight/size;
    // weight剛好可以被packet_size整除
} // Cost()

void Prim( int id, int size, int node[][id+1], long long int weight[] ){
    int now = 0;//目前的node(一開始 root = 0)
    long long int cost = 0; // 存放total cost
    int dist[id], visit[id], parent[id]; // dist : weight ; visit : 看此點是否拜訪過
    memset( visit, 0, sizeof(visit)); // 初始為0 (false)
    for( int i = 0; i < id; i++ ) dist[i] = MAX; // 初始每點間的權重(weight)為MAX
    dist[now] = 0; // 以0為樹根
    parent[now] = 0;  // 0的parent也是0


    for( int i = 0; i < id; i++ ){ //跑每個node

        int a = -1, b = -1, min = MAX;
        for( int j = 0; j < id; j++){
        // 找不在樹上且離樹最近(最小的)的weight
            if( visit[j] == 0 && dist[j] < min ){
                a = j; // 紀錄最小值的node_id
                min = dist[j]; // 將其設為最小值
            }
        } // for


        if( a == -1 ) break; // 若 a = -1 表沒有可連通的點
        visit[a] = 1; // 將前面所找到的點的visit變為1(true)表示已拜訪過

        for( b = 0; b < id ; b++ ){
        // 從前面所找的離樹最近且不在樹上的點之連接的點中(a)找出離樹最近的點
            if( visit[b] == 0 && node[a][b] < dist[b] && node[a][b] != -1){
                dist[b] = node[a][b];
                parent[b] = a; // 將此點parent設為前面所找的點
            } // if

        } // for

    }

    int height[id], max = 0;
    memset(height, 0, sizeof(height) ); //初始為0

    for( int i = id-1; i > 0 ; i-- ){
        int c =0, tmp = i;
        do{ // 當其parent不為0，計算每個節點的高度(樹根為0)
            c = parent[tmp];
            height[i]++;
            tmp = c;
        } while( c != 0);
        if( height[i] > max ){ // 找最高點並將其設為max
            max = height[i];
        } // if
    } // for


    for( int i = max ; i > 0; i--){ // 將每個樹枝的weight一層一層的由下往上加
        for( int j = 0; j < id; j++ ){
            if( height[j] == i ){
                cost += Cost(weight[j], size );//計算weight的cost
                weight[parent[j]] += weight[j];
            } // if
        }
    } // for
    printf("\nOutput:\n");
    printf("#Nodes: %d   Total Cost: %lld\n", id, cost); // 印出結果
    printf("node_ID   parent_ID\n");
    for(int i = 0; i< id; i++){
        printf("%d\t  %d\n", i, parent[i]);
    }

} // Prim()
