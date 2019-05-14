/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-14 15:22:14
 * Filename      : seqlist.c
 * Description   : 使用类进行顺序表的封装 
 * *******************************************************/
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
using namespace std;

typedef int Datatype;
class seqlist {
public:
    // 创建(使用构造函数)
    seqlist(size_t capacity = 10) {
        _array =(Datatype*)malloc(sizeof(Datatype)*capacity);
        _capacity = capacity;
        _size = 0;
    }


	//已知顺序表的有效长度和每个值进行构造函数。
	seqlist(size_t n, const DataType& data = DataType())
		:_array(new DataType[n])
		,_size(n)
		,_capacity(n)
	{
		size_t i=0;
		for(i=0;i<n;i++)
		{
			_array[i]=data;
		}
	}

    // 扩容
    void CheckCapacity() {
        if(_size >= _capacity) {
            size_t newCapacity = _capacity * 2;
            Datatype* newArray = (Datatype*)malloc(sizeof(Datatype)*newCapacity);
            

            // 搬家
            for(int i = 0; i < _size; i++) {
                newArray[i] = _array[i];
            }

            // 释放老空间绑定新空间
            free(_array);
            _array = newArray;
            _capacity = newCapacity;
        }
    }

    // 销毁 (使用析构函数)
    ~seqlist() {
        if(_array) {
            free(_array);
            _capacity = 0;
            _size = 0;
        }
        
    }
    // 头插
    void PushFront(Datatype val) {
        assert(_array != NULL);
        assert(_size > 0);
        CheckCapacity();


        for(int i = _size; i > 0; i--) {
            _array[i] = _array[i-1];

        }

        _array[0] = val;
        _size++ ;
    }
    // 尾插
    void PushBack(Datatype val) {
        CheckCapacity();
        _array[_size++] = val;

    }
    // 头删
    void PopFront () {
        assert(_array != NULL);
        assert(_size > 0);
        for(int i = 0; i < _size; i++) {
            _array[i] = _array[i+1];
        }

        _size-- ;



    }
    // 尾删
    void PopBack() {
        assert(_array != NULL);
        assert(_size > 0);

        _size-- ;
        

    }
    // 查找
    int Search(Datatype val) {
        if(_array == NULL || _size <= 0) {
            return -1;
        }

        for(int i = 0; i < _size; i++) {
            if(_array[i] == val) {
                return i;
            }
        }

        return -1;

    }
    // 修改
    void Modify(int pos, Datatype val) {
        assert(pos > 0 && _size >= 0);

        _array[pos] = val;
        
    }

private:
    Datatype* _array;
    size_t _capacity;
    size_t _size;


};

void Test() {
    int array[]={0,1,2,3,4,5,6,7,8,9};
	seqlist v3(array,array+sizeof(array)/sizeof(array[0]));
	cout<<v3<<endl;
	cout<<v3.size()<<endl;
	cout<<v3.capacity()<<endl;

    
    
}

int main() {

    Test();
    return 0;
}
