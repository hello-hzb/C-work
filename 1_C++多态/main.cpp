#include <iostream> 
#include <stdlib.h>
using namespace std;

class Father
{
public:
	void Face()
	{
		cout << "Father's face" << endl;
	}

	virtual void Say()
	{
		cout << "Father say hello" << endl;
	}

	void Father_unique()
	{
		cout << "Father's unique func" << endl;
	}
};


class Son :public Father
{
public:
	void Face()
	{
		cout << "Son's face" << endl;
	}

	void Say()
	{
		cout << "Son say hello" << endl;
	}

	void Son_unique()
	{
		cout << "Son's unique func" << endl;
	}


};

class Grandson :public Son
{
public:
	void Face()
	{
		cout << "Grandson's face" << endl;
	}

	void Say()
	{
		cout << "Grandson say hello" << endl;
	}

	void Grandson_unique()
	{
		cout << "Grandson's unique func" << endl;;
	}
};


//总结起来：常规的类继承中是可以定义相同函数名的函数，多态就是在在父类中将在子类中将要重复定义的函数定义virtual类型后，在对子类进行隐式类型转换成父类
//后仍然可以调用子类中相同名字的函数功能。


void main()
{
	Father fa;
	Son so;
	Grandson gr;

	//case1: 对象调用成员函数变量名即使一样，只会调用自己的成员函数，就算是继承的也不会调用父类中去(和有没有virtual情况都是一样的）
	fa.Face();
	fa.Say();
	so.Face();
	so.Say();

	//case2: 做了隐式类型转换后（将子类隐式转换成父类）
	Father *pFather = &so; // 隐式类型转换
	pFather->Face();       //未加virtual重写  调用的是隐式转换后的类（即父类）中定义的功能  "Father's face"
	pFather->Say();        //加virtual重写    调用的是隐式转换前的类（即子类）中定义的功能  "Son say hello"


	//case2: 做了隐式类型转换后（将子类隐式转换成父类）
	Father *pFather2 = &gr; // 隐式类型转换
	pFather2->Face();       //未加virtual重写  调用的是隐式转换前的类中定义的功能  "Father's face"
	pFather2->Say();        //加virtual重写    调用的是隐式转换前的类中定义的功能  "Grandson say hello" 


	system("pause");
}
