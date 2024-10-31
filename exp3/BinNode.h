
#include <iostream>
#define BinNodePosi(T) BinNode<T>*  //节点位置

#define stature(p) ((p) ? (p)->height ; -1) //节点高度（与'空树高度为-1'的约定相统一）
typedef enum{RB_RED,RB_BLACK} RBColor;


template<typename T> struct BinNode {
    //成员
    T data;
    BinNodePosi(T) parent; BinNodePosi(T) lc ; BinNodePosi(T) rc;//父亲节点和左右孩子节点
    int height;
    int npl;
    RBColor color;

    //构造函数
    BinNode():
        parent(NULL),lc(NULL),rc(NULL),height(0),npl(1),color(RB_RED){ }
    BinNode(T e , BinNodePosi(T) p = NULL,BinNodePosi(T) lc = NULL ,BinNodePosi(T) rc = NULL, 
            int h = 0 ,int l = 1 , RBColor c = RB_RED ):
            data(e),parent(p),lc(lc),rc(rc),height(h),npl(l),color(c){ }
    //操作接口
    int size();
    BinNodePosi(T) insertAsLC(T const& );//作为当前节点的左孩子插入新节点
    BinNodePosi(T) insertAsRC(T const& );
    BinNodePosi(T) succ();
    template<typename VST> void travLevel(VST&);
    template<typename VST> void travPre(VST&);
    template<typename VST> void travIn(VST&);
    template<typename VST> void travPost(VST&);
    //比较器，判等器
    bool operator<(BinNode const& bn){return data < bn.data;}
    bool operator>(BinNode const& bn){return data>bn.data;}
    bool operator>=(BinNode const& bn){return data>=bn.data;}
    bool operator<=(BinNode const& bn){return data<=bn.data;}
    bool operator==(BinNode const& bn){return data == bn.data;}
};

/*
*BinNode状态与性质的判断
 */
#define IsRoot(x) (!((X).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x)==(x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x)==(x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (! HasChild(x))
/*
*与BinNode具有特定关系的节点及指针
*/

#define sibling(p)/*兄弟*/\
    (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(x)/*叔叔*/\
    (IsLChild(*((x)->parent))? (x)->parent-parent->lc : (x)->parent->parent->rc)
#define FromParentTo(x)/*来自父亲的引用*/\
    (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc:(x).parent->rc))

template<typename T> BinNodePosi(T) BinNode<T>:: insertAsLC(T const& e)
{ return lc = new BinNode ( e,this ); }

template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const& e )
{ return rc = new BinNode (e,this); }

template <typename T> BinNodePosi(T) BinNode<T>::succ() {
    BinNodePosi(T) s = this;
    if(rc){
        s=rc;
        while (HasLChild( *s)) s = s->lc;
    }else{
        while(IsRChild(*s)) s = s->parent;
        s=s->parent;
    }
    return s;
}

template<typename T> template <typename VST>
void BinNode<T>::travIn(VST& visit ){
    switch( rand() % 5 ){
        case 1: travIn_I1( this, visit );break;
        case 2: travIn_I2( this, visit );break;
        case 3: travIn_I3( this, visit );break;
        case 4: travIn_I4( this, visit );break;
        default: travIn_R( this, visit );break;
    }
}

template<typename T> template <typename VST>
void BinNode<T>::travLevel(VST& visit ) {
    
    Queue<BinNodePosi(T)> Q;
    Q.enqueue ( this );
    while ( !Q.empty() ) {
        BinNodePosi(T) x = Q.dequeue(); visit ( x->data );
        if ( HasLChild ( *x ) ) Q.enqueue ( x->lc );
        if ( HasRChild ( *x ) ) Q.enqueue ( x->rc );
    }
    
}