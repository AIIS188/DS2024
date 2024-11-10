#define N_CHAR ( 0x80 - 0x20 )//仅以可打印字符为例
#include "D:\DS24\DS24\exp3\BinTree.h"
struct HuffChar {
    char ch ; int weight;
    HuffChar ( char c = '^',int w = 0 ) : ch ( c ), weight ( w ) {};
    bool operator< ( HuffChar const& hc ) { return weight > hc.weight ; }
    bool operator> (HuffChar const& hc ) { return weight < hc.weight; }
    bool operator>= ( HuffChar const& hc ) { return weight >= hc.weight; }
    bool operator<= ( HuffChar const& hc ) { return weight <= hc.weight; }
    bool operator== ( HuffChar const& hc ) { return weight == hc.weight; }
};//Huffman(超)字符

#define HuffTree BinTree<HuffChar> //Huffman数,由BinTree派生,节点类型为HuffChar
#include "List.h"
typedef List<HuffTree*> HuffForest;


#include "Bitmap.h"  // 包含 Bitmap 类的定义
typedef Bitmap HuffCode;

int* statistics ( char* sample_text_file ) {
    int* freq = new int[N_CHAR];
    memset ( freq, 0, sizeof ( int ) * N_CHAR );
    FILE* fp = fopen ( sample_text_file, "r");
    for ( char ch; 0 < fscanf ( fp, "%c", &ch ); )
        if (ch >= 0x20 ) freq[ch - 0x20]++;
    fclose (fp); return freq;
}

HuffForest* initForest ( int* freq ) {
    HuffForest* forest = new HuffForest;
    for ( int i = 0; i < N_CHAR; i++ ) {
        forest->insertAsLast( new HuffTree );
        forest->last()->data->insertAsRoot ( HuffChar ( 0x20 + i, freq[i] ) );
    }
    return forest;
}

HuffTree* minHChar ( HuffForest* forest ) { 
    ListNodePosi ( HuffTree* ) p = forest->first();
    ListNodePosi ( HuffTree* ) minChar = p ;

    int minWeight = p->data->root()->data.weight;
    while( forest->valid ( p = p->succ ) )
        if ( minWeight > p->data->root()->data.weight )
        { minWeight = p->data->root()->data.weight;minChar = p; }
    return forest->remove ( minChar );

}

HuffTree* generateTree ( HuffForest* forest ) {
    while ( 1 < forest->size() ) {
        HuffTree* T1 = minHChar ( forest ); HuffTree* T2 = minHChar ( forest );
        HuffTree* S = new HuffTree();
        S->insertAsRoot ( HuffChar ( '^', T1->root()->data.weight+ T2 ->root()->data.weight));
        S->attachAsLC ( S->root(), T1 ); S->attachAsRC ( S->root(),T2 );
        forest->insertAsLast( S );

    }
    return forest->first()->data;

}

//解码
void decode ( HuffTree* tree, Bitmap* code,int n ){
    BinNodePosi( HuffChar ) x = tree->root();
    for ( int i = 0; i<n; i++ ) {
        x = code->test ( i ) ? x->rc : x->lc;
        if ( IsLeaf ( *x )){ printf("%c",x->data.ch ) ; x =tree->root(); }
    }
}

