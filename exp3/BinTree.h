#include "BinNode.h"
#include "D:\DS24\DS24\exp2\Stack.h"
#include <memory>

template <typename T> class BinTree {
protected:
    int _size;BinNodePosi(T) _root;
    virtual int updateHeight ( BinNodePosi(T) x);
    void updateHeightAbove ( BinNodePosi(T) x );
public:
    BinTree(): _size (0), _root( NULL ){    }
    ~BinTree() { if( 0 <_size ) remove (root);}
    int size() const { return _size;}
    bool empty() const { return !_root;}
    BinNodePosi(T) root() const{ return _root;}
    BinNodePosi(T) insertAsRoot (T const& e);
    BinNodePosi(T) insertAsLC ( BinNodePosi(T) x , T const& e);
    BinNodePosi(T) insertAsRC ( BinNodePosi(T) x , T const& e);
    BinNodePosi(T) attachAsLC ( BinNodePosi(T) x , BinTree<T>* &T);
    BinNodePosi(T) attachAsRC ( BinNodePosi(T) x , BinTree<T>* &T);
    int remove ( BinNodePosi(T) x);
    void release(BinTree<T>* &S)；
    BinTree<T>* secede( BinNodePosi(T) x);
    template <typename VST>
    void travLevel (VST& visit ) {if (_root ) _root->travLevel (visit);}
    template <typename VST>
    void travPre ( VST& visit ) { if ( _root ) _root->travPre (visit);}
    template <typename VST>
    void travIn (VST& visit ) { if( _root ) _root->travIn(visit);}
    template <typename VST>
    void travPost (VST& visit ) { if (_root) _root->travPost(visit);}
    bool operator< (BinTree<T> const& t)
    { return _root && t._root && lt (_root,t._root); }
    bool operator> (BinTree<T> const& t)
    { return _root && t._root && rt (_root,t._root);}
    bool operator>= (BinTree<T> const& t)
    { return _root && t._root && _root>=t._root;}
    bool operator<= (BinTree<T> const& t)
    { return _root && t._root && _root<=t._root;}
    bool operator== ( BinTree<T> const& t)
    { return _root && t._root &&(_root == t._root); }
};//BinNode


template <typename T> int BinTree<T>:: updateHeight( BinNodePosi(T) x )
{ return x -> height = 1 + max ( stature( x->lc),stature(x->rc));}

template <typename T> void BinTree<T> :: updateHeightAbove ( BinNodePosi(T) x )
{ while (x) { updateHeight(x);x=x->parent;}}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot (T const& e)
{ _size = 1 ; return _root = new BinNode<T> (e);}

template <typename T> BinNodePosi(T) BinTree<T>:: insertAsLC (BinNodePosi(T) x, T const& e)
{ _size++; x->insertAsLC(e); updateHeightAbove( x ) ; return x->lc;}

template <typename T> BinNodePosi(T) BinTree<T> :: insertAsRC ( BinNodePosi(T) x, T const& e )
{ _size++; x->insertAsRC ( e ); updateHeightAbove ( x );return x->rc;}

template <typename T>
BinNodePosi(T) BinTree<T> ::attachAsLC ( BinNodePosi(T) x, BinTree<T>* &S ){
    if( x->lc = S->_root ) x->lc->parent = x;
    _size +=S->_size; updateHeightAbove ( x ) ;
    S->_root = NULL; S->_size = 0;release( S ); S = NULL ; return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC ( BinNodePosi(T) x , BinTree<T>* &S ){
    if( x->rc = S->_root ) x->rc->parent = x;
    _size+=S->_size; updateHeightAbove ( x );
    S->_root = NULL ; S->_size = 0;release( S ); S = NULL ; return x;
}

template <typename T>
int BinTree<T>::remove ( BinNodePosi(T) x ) {
    FromParentTo ( *x ) = NULL;
    updateHeightAbove ( x->parent );
    int n = removeAt ( x );_size -=n;return n;
}

template <typename T>
static int removeAt ( BinNodePosi(T) x ) {
    if (!x) return 0;
    int n = 1 + removeAt ( x->lc ) + removeAt ( x->rc );
    release ( x->data ) ; release ( x ); return n ;
}

template <typename T,typename VST>
void travPre_R ( BinNodePosi(T) x,VST& visit ) {
    if ( !x ) return;
    visit ( x->data );
    travPre_R ( x->lc, visit );
    travPre_R ( x->rc, visit );
}//前序遍历（递归版）

template <typename T, typename VST>
void travPost_R ( BinNodePosi(T) x , VST& visit ) {
    if ( !x ) return;
    travPost_R ( x->lc, visit );
    travPost_R ( x->rc, visit );
    visit ( x->data );
}//后序遍历（递归版）

template <typename T, typename VST>
void travIn_R ( BinNodePosi(T) x ,VST& visit ) {
    if ( !x ) return;
    travIn_R ( x->lc , visit );
    visit ( data );
    travIn_R ( x->rc , visit );
}//中序遍历（递归版）

//从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
template <typename T,typename VST>
static void visitAlongLeftBranch ( BinNodePosi(T) x , VST& visit, Stack<BinNodePosi(T)>& S) {
    while ( x ) {
        visit ( x->data );
        S.push ( x->rc );
        x = x->lc;
    }
}

template <typename T,typename VST>
void travPre_I2 ( BinNodePosi(T) x ,VST& visit ) {
    Stack<BinNodePosi(T)> S;
    while ( true ) {
        visitAlongLeftBranch ( x, visit , S );
        if ( S.empty()) break;
        x = S.pop();
    }
} //先序遍历（迭代版1）

template <typename T>
static void goAlongLeftBranch ( BinNodePosi(T) x , Stack<BinNodePosi(T)>& S ) {
    while( x ) { S.push ( x ) ; x = x->lc;}
}

template <typename T,typename VST>
void travIn_I1 ( BinNodePosi(T) x , VST& visit ) {
    Stack<BinNodePosi(T)> S;
    while ( true ) {
        goAlongLeftBranch ( x , S ) ;
        if ( S.empty()) break;
        x = S.pop(); visit ( x->data );
        x = x->rc;
    }
}//中序遍历（迭代版1）

template <typename T ,typename VST>
void travIn_I2 ( BinNodePosi(T) x , VST& visit ) {
    Stack<BinNodePosi(T)> S;
    while ( true )
        if( x ) {
            S.push ( x );
            x = x->lc;
        }else if ( !S.empty()) {
            x = S.pop();
            visit ( x->data );
            x = x->rc;
        }else
        break;
}//中序遍历（迭代版2）

template<typename T, typename VST>
void travIn_I3 ( BinNodePosi(T) x ,VST& visit ) {
    bool backtrack =  false;
    while ( true )
        if ( !backtrack && HasLChild( *x ))
            x= x->lc;
        else {
            visit ( x->data );
            if ( HasRChild ( *x )) {
                x = x->rc;
                backtrack = false;
            } else {
                if ( ! ( x = x->succ())) break;
                backtrack = true ;
            }
        }
}//中序遍历（迭代版3）

template <typename T>
static void gotoHLVFL ( Stack<BinNodePosi(T)>& S ) {
    while ( BinNodePosi(T) x = S.top())
        if ( HasLChild ( *x )) {
            if( HasRChild (*x)) S.push ( x-> rc );
            S.push ( x->lc );
        } else
        S.push ( x->rc );
    S.pop();
}

template <typename T,typename VST>
void travPost_I ( BinNodePosi(T) x , VST& visit ) {
    Stack<BinNodePosi(T)> S;
    if ( x ) S.push ( x );
    while ( !S.empty() ) {
        if ( S.top() != x->parent )
            gotoHLVFL ( S );
        x = S.pop();
        visit ( x->data );
    }
}//后序遍历（迭代版）



                  
