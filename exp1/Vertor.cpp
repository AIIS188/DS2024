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
        Vector(T* A,Rank lo ,Rank hi){copyFrom(A,lo,hi)}//数组区间复制
        Vector(T* A, Rank n ){copyFrom(A, 0,n)}//数组整体复制
        Vector(Vector<T> const& V,Rank lo,Rank hi){copyFrom(V._elem,lo,hi)}
        Vector(Vector<T> const& V){copyFrom(V._elem,V._size)}
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
        Vector<T> &a operator=(Vector<T> const&);
        T remove(Rank r);
        int remove(Rank lo,Rank hi );
        Rank insert(Rank r , T const& e);
        Rank insert(T const& e){ return insert(_size,e);}
        void sort(Rank lo , Rank hi);
        void sort(){sort(0,_size)};
        void unsort(Rank lo ,Rank hi);
        void unsort(){ unsort(0,_size);}
        int deduplicate();//无序去重
        int uniquify();//有序去重
//遍历
        void traverse(void(*)(T&));//遍历（使用函数指针，只读或局部修改）
        template<typename VST> void traverse(VST&);//遍历（使用函数对象，可全局性修改）
};//Vector



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
    T* ex=new T(_capacity = _size+10);
    ex.copyFrom(_elem,0 ,_size);
    _elem=ex;
}


//装填因子过小时压缩
template<typename T>
void Vector<T>::shrink(){
    T* sh=new T(_capacity = _size+10);
    sh.copyFrom(_elem,0 ,_size);
    _elem=sh;
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
        int le=lo;
        sorted=true;
        while(le<hi){
            if(bubble(le,le+1)){
                _elem[le]=_elem[++le];
                sorted=false;
            }
        hi--;
        }
        
    }
}


//归并算法
template<typename T>
void Vector<T>::merge(Rank lo , Rank mi , Rank hi ){
    Vector A(*this,_size);
    int i=lo,j=mi,k=hi,l=lo;
    while(i<mi && j<k){
        if(A[i]<A[j]){
            _elem[l++]=A[i++];
        }
        else{_elem[l++]=A[j++];}
        }
    while(i<mi){
        _elem[l++]=A[i++];
    }
    while(j<hi){
        _elme=[l++]=A[j++];
    }
    
}


//归并排序算法
template<typename T>
void Vector<T>::mergeSort(Rank lo ,Rank hi){
    int mi;
    if(lo<hi){
        mi=(hi-lo)/2
        mergeSort(lo,mi);
        mergeSort(mi,hi);
        merge(lo,mi,hi);
    }
}


//轴点构造算法
template<typename T>
Rank Vector<T> ::partition(Rank lo,Rank hi ){
    Rank m=_elem[lo];
    Vector<T> A(*this,_size);
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
        p=partition(lo,hi);
        quickSort(lo,p);
        quickSort(p,hi);
    }
}


//堆排序
template<typename T>
void Vector<T>::heapSort(Rank lo,Rank hi ){
    ...
}



//判断是否排序
template<typename T>
int Vector<T>::disordered() const{
    
}