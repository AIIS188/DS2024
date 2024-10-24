#include<iostream>
#include<math.h>
#include<random>
#include<ctime>
using namespace std;

typedef int Rank;
#define DEFAULT_CAPACITY 3
template <typename T> class Vector{
    private:
        Rank _size;int _capacity; T* _elem;
    protected:
        void copyFrom(T* const A,Rank lo,Rank hi);
        void expand();//空间不足时候扩容
        void shrink();//装填因子过小时压缩
        bool bubble(Rank lo ,Rank hi);//扫描交换算法
        void bubbleSort(Rank lo , Rank hi);
        void merge(Rank lo , Rank mi,Rank hi );
        void mergeSort(Rank lo ,Rank hi);
        Rank partition(Rank lo,Rank hi );
        void quickSort(Rank lo ,Rank hi );
        void heapSort(Rank lo ,Rank hi);
    public:
        Vector(int c =DEFAULT_CAPACITY){_elem = new T[_capacity = c ];_size=0;}//默认
        Vector(T* A,Rank lo ,Rank hi){copyFrom(A,lo,hi);}//数组区间复制
        Vector(T* A, Rank n ){copyFrom(A, 0,n);}//数组整体复制
        Vector(Vector<T> const& V,Rank lo,Rank hi){copyFrom(V._elem,lo,hi);}
        Vector(Vector<T> const& V){copyFrom(V._elem,0,V._size);}
        ~Vector(){delete [] _elem; }
        Rank size() const{return _size;}
        bool empty() const {return _size <=0;}//判空
        int disordered() const;//判断向量是否已经排序
        Rank find(T const& e) const { return find(e,0,(Rank)_size);}//无序向量整体查找
        Rank find(T const& e,Rank lo ,Rank hi )const;//无序向量区间查找
        Rank search(T const& e)const //有序向量整体查找
        { return (0 >= _size)? -1:search(e,(Rank)0,(Rank)_size);}
        Rank search(T const& e,Rank lo ,Rank hi )const;//有序向量区间查找
        T& operator[](Rank r ) const;
        Vector<T> & operator=(Vector<T> const& V);
        T remove(Rank r);
        int remove(Rank lo,Rank hi );
        Rank insert(Rank r , T const& e);
        Rank insert(T const& e){ return insert(_size,e);}
        void sort(Rank lo , Rank hi);
        void sort(){sort(0,_size);};
        void msort(Rank lo ,Rank hi);
        void msort(){msort(0,_size);};
        void qsort(Rank lo, Rank hi );
        void qsort(){qsort(0,_size);};
        void unsort(Rank lo ,Rank hi);
        void unsort(){ unsort(0,_size);}
        void resort(Rank lo,Rank hi );//逆序排列
        void resort(){resort(0,_size);};
        int deduplicate();//无序去重
        int uniquify();//有序去重
        void setsize(int n){ _size=n;};
        Vector<T> findmodel(double m1,double m2,Rank lo,Rank hi);
        Vector<T> findmodel(double m1,double m2){Vector<T> A=findmodel(m1,m2,0,_size);return A;};

//遍历
        void traverse(void(*)(T&));//遍历（使用函数指针，只读或局部修改）
        template<typename VST> void traverse(VST&);//遍历（使用函数对象，可全局性修改）
};//Vector





////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#######保护变量定义###

//复制
template<typename T>
void Vector<T>::copyFrom(T* const A,Rank lo,Rank hi){
    _elem = new T[(_capacity = 2*(hi-lo))];_size=0;
    while(lo<hi){
        _elem[_size++] = A[lo++];
    }
}


//空间不足时候扩容
template<typename T>
void Vector<T>::expand(){
    if(_size < _capacity) return;
    if(_capacity < DEFAULT_CAPACITY) _capacity =DEFAULT_CAPACITY;
    T*oldElem = _elem;
    _elem = new T[_capacity<<=1];
    for(int i = 0 ; i < _size ; i++) _elem[i]=oldElem[i];
    delete [] oldElem;
}


//装填因子过小时压缩
template<typename T>
void Vector<T>::shrink(){
    if(_capacity < DEFAULT_CAPACITY << 1) return;
    if(_size<<2 > _capacity) return;
    T* oldElem=_elem; _elem = new T[_capacity>>=1];
    for(int i = 0 ; i< _size;i++) _elem[i]=oldElem[i];
    delete [] oldElem;
}


//扫描交换算法
template<typename T>
bool Vector<T>::bubble(Rank lo ,Rank hi){
    return _elem[lo]>_elem[hi]? true:false;
}


//冒泡排序
template<typename T>
void Vector<T>::bubbleSort(Rank lo , Rank hi ){
    bool sorted=false;

    while(!sorted){
        sorted=true;
        for(int le = lo ; le <hi-1;le++){
            if(bubble(le,le+1)){
            swap(_elem[le],_elem[le+1]);
            sorted=false;
            }
        }
        hi--;
    }
}


//归并算法 
template<typename T>
void Vector<T>::merge(Rank lo , Rank mi , Rank hi ){
    Vector A(_elem,_size);
    int i=lo,j=mi;
    while(i<mi && j<hi){
        if(A[i]<A[j]){
            _elem[lo++]=A[i++];
        }
        else{_elem[lo++]=A[j++];}
        }
    while(i<mi){
        _elem[lo++]=A[i++];
    }
    while(j<hi){
        _elem[lo++]=A[j++];
    }
    
}


//归并排序算法
template<typename T>
void Vector<T>::mergeSort(Rank lo ,Rank hi){
    Rank mi;
    mi=lo+(hi-lo)/2;
    if(lo==mi) return;
    else{ mergeSort(lo,mi);mergeSort(mi,hi);merge(lo,mi,hi);};

    
}


//轴点构造算法
template<typename T>
Rank Vector<T> ::partition(Rank lo,Rank hi ){
    T m=_elem[lo];
    Vector<T> A(_elem,_size);
    int i=lo,j=hi-1;
    for(int k=lo+1;k<hi;k++){
        if(A[k]<m) _elem[lo++]=A[k];
        else _elem[hi--]=A[k];
    }
    _elem[lo]=m;
    return lo;
}

//快速排序
template<typename T>
void Vector<T>::quickSort(Rank lo ,Rank hi ){
    if(lo<hi){
        Rank p=partition(lo,hi);
        quickSort(lo,p);
        quickSort(p,hi);
    }
    else return;
}


//堆排序
template<typename T>
void Vector<T>::heapSort(Rank lo,Rank hi ){
    //...
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//###############公有变量定义###

//判断是否排序
template<typename T>
int Vector<T>::disordered() const{
    int sorted = 1;
    for(int i = 0 ; i < _size-1 ; i++){
        if(_elem[i]>_elem[i+1]){
            sorted = -1 ;
            return sorted;
        }
    }
    return sorted;
}


//无序向量区间查找
template<typename T>
Rank Vector<T>::find(T const& e,Rank lo ,Rank hi)const{
    Rank i=lo;
    bool finded=false;
    while(i<hi && !finded){
        if(e==_elem[i++]){
            finded = true;
            return i-1;
        }
    }
    return -1;

}


//有序向量区间查找

template<typename T>
Rank Vector<T>:: search(T const& e,Rank lo ,Rank hi )const{
    Rank i=lo;
    bool finded=false;
    while(i<hi && !finded){
        if(e==_elem[i]){
            finded = true;
            return i-1;
        }
        else{
            if(e<_elem[i]){
                return -1;
            }
            else i++;
        }
    }
}


//向量模板类下标的重载
template<typename T>
T& Vector<T>::operator[](Rank r ) const{
    return _elem[r];
    
}

//向量模板类赋值符的重载
template<typename T>
Vector<T>& Vector<T>:: operator=(Vector<T> const& V){
    if(_elem) delete [] _elem;
    copyFrom(V._elem,0,V.size());
    return *this;

}

template<typename T>
T Vector<T>:: remove(Rank r){
    T e = _elem[r];
    remove(r,r+1);
    return e;
}

template<typename T>
int Vector<T>::remove(Rank lo ,Rank hi){
    if(lo==hi) return 0;
    while(hi<_size) _elem[lo++]=_elem[hi++];
    _size=lo;shrink();
    return hi-lo;
}


template<typename T>
Rank Vector<T>::insert(Rank r , T const& e){
    expand();
    for(int i  = _size ;  i > r ; i-- )_elem[i]=_elem[i-1];
    _elem[r] = e ; 
    _size++;
    return r ;
}


template<typename T>
void  Vector<T>::sort(Rank lo , Rank hi){
    bubbleSort(lo,hi);
}


template<typename T>
void Vector<T>::msort(Rank lo,Rank hi){
    mergeSort(lo,hi);
}


template<typename T>
void Vector<T>::resort(Rank lo ,Rank hi){
    sort(lo,hi);
    Rank i =lo,j=hi-1;
    while(i!=j){
        swap(_elem[i++],_elem[j--]);
    }
}

template<typename T>
void Vector<T>::qsort(Rank lo , Rank hi ){
    quickSort(lo,hi);
}

template<typename T>
void Vector<T>::unsort(Rank lo ,Rank hi){
    T*V = _elem +lo;
    for(Rank i = hi -lo;i>0;i--){
        swap(V[i-1],V[rand()%i]);
    }
}

//无序去重
template<typename T>int Vector<T>::deduplicate(){
    int oldSize = _size;
    Rank i = 0;
    while(i+1<_size) (0>find(_elem[i],i+1,oldSize))?
    i++:remove(i);shrink();
    return oldSize-_size;
}

//有序去重

template<typename T> int Vector<T>::uniquify(){
    Rank i = 0, j = 0;
    _elem[i]=_elem[0];
    while(j++<_size){
        if(_elem[i]!=_elem[j]) 
         _elem[++i]=_elem[j];
    }_size=i;shrink();
    return j-i-1;  
}
//交换
template<typename T>
void swap(T*p1,T*p2){
    T temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

//遍历
template<typename T>
void Vector<T>::traverse(void(*visit)(T&)){
    for(int i = 0;i<_size;i++){
        visit(_elem[i]);
    }
}
template<typename T>
template<typename VST>
void Vector<T>::traverse(VST &visit){
    for(int i = 0;i<_size;i++){
        visit(_elem[i]);
    }
};



class Complex{
private:
    double _real;
    double _image;
    double _model;
public:
    Complex(double r=0 ,double i=0){_real=r;_image=i;_model=sqrt(_real*_real+_image*_image);};
    Complex(Complex const& A){_real=A._real;_image=A._image;_model=A._model;};
    void print(){cout<<_real<<"+"<<_image<<"i";};
    void reset(double r , double i ){_real = r ; _image = i;_model=sqrt(_real*_real+_image*_image);};
    bool operator !=(const Complex& other) const{ return (_real != other._real) || (_image != other._image);};
    bool operator ==(const Complex& other) const{ return (_real == other._real) && (_image == other._image);};
    bool operator <(const Complex& other) const{ if(_real*_real+_image*_image==other._real*other._real+other._image*other._image) return _real<other._real;
        else return _real*_real+_image*_image<other._real*other._real+other._image*other._image;};
    bool operator >(const Complex& other) const{if(_real*_real+_image*_image==other._real*other._real+other._image*other._image) return _real>other._real;
        else return _real*_real+_image*_image>other._real*other._real+other._image*other._image;};
    double model(){return _model;};
};//Complex

class ComplexVector: public Vector<Complex>{

};//复数向量的继承，重载一下特殊的查找函数



void set1(Complex a){
    a.reset(1,2);
}
void allprint1(Complex a){
    // cout<<a<<" ";
    a.print();
    cout<<" ";
}
template<typename T>
Vector<T> Vector<T>::findmodel(double m1,double m2,Rank lo,Rank hi){
    T* B = new T[(hi-lo)*2];
    Rank i=lo,j=0;
    for(int i = 0 ; i < hi ; i++){
        cout<<_elem[i].model()<<"   ";
        if(_elem[i].model()>=m1 && _elem[i].model()<m2){ B[j++]=_elem[i];
        }
    }
    Vector<T> A(B,j);
    A.traverse(allprint1);
    return A;
}

