#define N_CHAR ( 0x80 - 0x20 )//仅以可打印字符为例
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

#