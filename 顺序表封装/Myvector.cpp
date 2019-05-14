#include <stdlib.h>
#include <string.h>
#include<iostream>
using namespace std;
 
//定义一个内置类型int。
typedef int DataType;
 
//写一个动态顺序表：
class Myvector
{
public:
	//形参为空的构造函数
	Myvector()
    
		:_array(new DataType[3])       //直接初始化列表
		,_size(0)
		,_capacity(3)
        {} 

	//已知顺序表的有效长度和每个值进行构造函数。
	Myvector(size_t n, const DataType& data = DataType()) 
		:_array(new DataType[n])
		,_size(n)
		,_capacity(n)
    {
		size_t  i=0;
		for(i=0;i<n;i++)
		{
			_array[i]=data;
		}
} 
 
	//已知顺序表的两个边界的构造函数。
	Myvector(DataType* first, DataType* last)
	{
		size_t m=last-first;
		size_t i=0;
		_array=new DataType[m];
		_size=m;
		_capacity=_size;
		for(i=0;i<m;i++)
		{
			_array[i]=first[i];
		}
	}
 
	//拷贝构造函数：
	Myvector(const Myvector& v) 
		:_array(new DataType[v._size])
		,_size(v._size)
		,_capacity(v._capacity)
{
	
		size_t i=0;
		for(i=0;i<_size;i++)
		{
			_array[i]=v._array[i];
		}
	}
 
	//赋值运算符重载
	Myvector& operator=(const Myvector& v)
	{
		if(this!=&v)
		{
			DataType* t=new DataType[v._size];
			memcpy(t,v._array,v._size);
			delete[] _array;
			_array=t;
			_size=v._size;
			_capacity=v._capacity;
		}
		return *this;
	}
 
	//析构函数
	~Myvector()
	{
		if(_array)
		{
			delete[] _array;
			_size=_capacity=0;
		}
	}
 
	//Acess
	DataType& operator[](size_t index)
	{
		return _array[index];
	}
 
	const DataType& operator[](size_t index)const
	{
		return _array[index];
	}
 
	DataType& front()
	{
		return _array[0];
	}
 
	const DataType& front()const
	{
		return _array[0];
	}
 
	DataType& back()
	{
		return _array[_size-1];
	}
 
	const DataType& back()const
	{
		return _array[_size-1];
	}
 
	//capacity
 
	size_t size()
	{
		return _size;
	}
 
	size_t capacity()
	{
		return _capacity;
	}
 
	//改变顺序表的有效长度。
	void ReSize(size_t newSize, const DataType& data = DataType())
	{
		size_t i=0;
		size_t oldsize=size();
		//若新长度小于旧长度，直接领长度等于新的即可
		if(newSize<=oldsize)                 
		{
			_size=newSize;
		}
		else{
			//否则若不超过最大容量，则直接将data复制过去即可。
			if(newSize<=_capacity)
			{
				for(i=0;i<newSize;i++)
				{
					_array[i]=data;
				}
			}
 
			 //若超过了容量
			else{
 
				//开辟新的空间
			DataType* t=new DataType[newSize];
			//先将旧的值拷贝进来
			for(i=0;i<oldsize;i++)
			{
				t[i]=_array[i];
			}
 
			//再将剩下的赋成data
			while(i<newSize)
			{
				t[i++]=data;
			}
			//销毁旧空间
			delete[] _array;
			_array=t;
			_size=newSize;
			_capacity=_size;
			}
		}
	}
 
	// 为当前顺序表来预留空间，不能改变顺序表中有效元素的个数
	void Reserve(size_t newCapacity)
	{
		size_t i=0;
		size_t old=capacity();
		if(newCapacity>old)
		{
			DataType* t=new DataType[newCapacity];
			for(i=0;i<size();i++)
			{
				t[i]=_array[i];
			}
			delete[] _array;
			_array=t;
			_capacity=newCapacity;
		}
	}
 
 
	//modify
 
 
	//尾插
	void PushBack(DataType& d)
	{
    // 检验是否超过容量。
		if(_capacity==_size)
		{
			Reserve(_capacity*2);
		}
		_array[_size++]=d;
	}
 
	//尾删
	void PopBack()
	{
		_size--;
	}
 
	//任意位置插入
	void Insert(size_t pos, const DataType& data)
	{
		size_t i=0;
		if(_size==_capacity)
		{
			Reserve(2*_capacity);
		}
		for(i=size();i>pos;i--)
		{
			_array[i]=_array[i-1];
		}
		_array[i]=data;
		_size++;
	}
 
	//任意位置进行删除
	void Erase(size_t pos)
	{
		size_t i=pos;
		for(i=pos+1;i<size();i++)
		{
			_array[i-1]=_array[i];
		}
		_size--;
	}
 
	//清空顺序表
	void Clear()
	{
		_size = 0;
	}
 
	//输出运算符重载
	friend ostream& operator<<(ostream& _cout, const Myvector& v)
	{
		for(size_t i = 0; i < v._size; ++i)
			_cout<<v._array[i]<<" ";
 
		return _cout;
	}
private:
	DataType *_array;
	size_t _size;
	size_t _capacity;
};
 
int main()
{
	Myvector v1;
	cout<<v1<<endl;
	cout<<v1.size()<<endl;
	cout<<v1.capacity()<<endl;
	Myvector v2(10,5);
	cout<<v2<<endl;
	cout<<v2.size()<<endl;
	cout<<v2.capacity()<<endl;
	int array[]={0,1,2,3,4,5,6,7,8,9};
	Myvector v3(array,array+sizeof(array)/sizeof(array[0]));
	cout<<v3<<endl;
	cout<<v3.size()<<endl;
	cout<<v3.capacity()<<endl;
 
	v3.Reserve(5);
	cout<<v3<<endl;
	cout<<v3.size()<<endl;
	cout<<v3.capacity()<<endl;
 
	v3.ReSize(5);
	cout<<v3<<endl;
	cout<<v3.size()<<endl;
	cout<<v3.capacity()<<endl;
 
 
	v3.ReSize(30,9);
	cout<<v3<<endl;
	cout<<v3.size()<<endl;
	cout<<v3.capacity()<<endl;
 
	
	return 0;
}
