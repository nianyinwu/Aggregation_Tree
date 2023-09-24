#include<stdio.h>
#include <limits.h>
#include<stdlib.h>
#include<string.h>
#define MAX INT_MAX
long long int Cost( long long int weight, int size ); // �p��cost
void Prim( int id, int size, int node[][id+1], long long int weight[] ); // �ؾ�

int main(){
    int id, link, size, end1, end2, tmp;
    printf("Input:\n");
    printf("#Nodes  #Links  Packet_Size\n");
    scanf("%d%d%d", &id, &link, &size);
    printf("Graph:\n");
    int node [id][id+1];
    memset(node, -1 , sizeof(node)); //�}�C��l��-1
    long long int weight[id] ; // �s��C
    memset( weight, -1, sizeof(weight)); // ��l��-1
    for( int i = 0; i < id + link ; i++){
        //Ū�Jinput
        if( i < id ){
            scanf("%d%lld", &tmp, &weight[i]); // tmp:Node_ID
        } // if
        else if ( i >= id && i < id+link ){ // �}�l�s�Jlink
            scanf("%d%d%d", &end1, &end1, &end2); // Ū�JLink_ID�BLink_End1�BLink_End2
            node[end1][end2] = weight[end2] ;
            node[end2][end1] = weight[end2] ;
        } // else if
    } // for

    Prim( id, size, node, weight ); // �ͦ���


}

long long int Cost( long long int weight, int size ){  // �p��cost
    if( weight/size == 0 && weight != 0) return 1;
    //weight��0�άO����packet_size
    else if( weight/size != 0 && weight%size != 0 ) return (weight/size) + 1;
    // weight����Qpacket_size�㰣
    else return weight/size;
    // weight��n�i�H�Qpacket_size�㰣
} // Cost()

void Prim( int id, int size, int node[][id+1], long long int weight[] ){
    int now = 0;//�ثe��node(�@�}�l root = 0)
    long long int cost = 0; // �s��total cost
    int dist[id], visit[id], parent[id]; // dist : weight ; visit : �ݦ��I�O�_���X�L
    memset( visit, 0, sizeof(visit)); // ��l��0 (false)
    for( int i = 0; i < id; i++ ) dist[i] = MAX; // ��l�C�I�����v��(weight)��MAX
    dist[now] = 0; // �H0�����
    parent[now] = 0;  // 0��parent�]�O0


    for( int i = 0; i < id; i++ ){ //�]�C��node

        int a = -1, b = -1, min = MAX;
        for( int j = 0; j < id; j++){
        // �䤣�b��W�B����̪�(�̤p��)��weight
            if( visit[j] == 0 && dist[j] < min ){
                a = j; // �����̤p�Ȫ�node_id
                min = dist[j]; // �N��]���̤p��
            }
        } // for


        if( a == -1 ) break; // �Y a = -1 ��S���i�s�q���I
        visit[a] = 1; // �N�e���ҧ�쪺�I��visit�ܬ�1(true)��ܤw���X�L

        for( b = 0; b < id ; b++ ){
        // �q�e���ҧ䪺����̪�B���b��W���I���s�����I��(a)��X����̪��I
            if( visit[b] == 0 && node[a][b] < dist[b] && node[a][b] != -1){
                dist[b] = node[a][b];
                parent[b] = a; // �N���Iparent�]���e���ҧ䪺�I
            } // if

        } // for

    }

    int height[id], max = 0;
    memset(height, 0, sizeof(height) ); //��l��0

    for( int i = id-1; i > 0 ; i-- ){
        int c =0, tmp = i;
        do{ // ���parent����0�A�p��C�Ӹ`�I������(��ڬ�0)
            c = parent[tmp];
            height[i]++;
            tmp = c;
        } while( c != 0);
        if( height[i] > max ){ // ��̰��I�ñN��]��max
            max = height[i];
        } // if
    } // for


    for( int i = max ; i > 0; i--){ // �N�C�Ӿ�K��weight�@�h�@�h���ѤU���W�[
        for( int j = 0; j < id; j++ ){
            if( height[j] == i ){
                cost += Cost(weight[j], size );//�p��weight��cost
                weight[parent[j]] += weight[j];
            } // if
        }
    } // for
    printf("\nOutput:\n");
    printf("#Nodes: %d   Total Cost: %lld\n", id, cost); // �L�X���G
    printf("node_ID   parent_ID\n");
    for(int i = 0; i< id; i++){
        printf("%d\t  %d\n", i, parent[i]);
    }

} // Prim()
