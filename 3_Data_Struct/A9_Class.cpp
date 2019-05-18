#include <iostream>
using namespace std;

#include <string>
#include <iostream>

/****************************************************************************
类的定义中，成员属性说明：
1.同一个类内互相都可以访问，public只可以被类实例化对象访问，但是proteced和private不能被对象访问；
2.1（pulic类型继承）继承类可以访问父类的public和protected，但是不能访问父类的private成员， 父类的public和protected在继承类中具有public属性；
2.2（protected类型继承）继承类可以访问父类的public和protected，但是不能访问父类的private成员， 父类的public和protected在继承类中具有protected属性；
2.3（private类型继承）继承类可以访问父类的public和protected，但是不能访问父类的private成员， 父类的public和protected在继承类中具有private属性；

总结：public权限最宽（内部成员，实例化对象，继承类），protected权值中等（内部成员， 继承类）， private权限最严格（内部成员）
https://blog.csdn.net/qq_37828443/article/details/80780768
*****************************************************************************/
class Father
{
public:
	int public_a = 12;
	void public_print();
protected:
	int protected_a = 13;
	void protected_print();

private:
	int private_p = 14;
	void private_print();
};
void Father::public_print()
{
	std::cout << "this is public function print" << std::endl;
}

void Father::protected_print()
{
	std::cout << "this is protected function print" << private_p << std::endl;
}

void Father::private_print()
{
	std::cout << "this is private function print" << std::endl;
}

class Son : protected Father
{
public:
	int public_b = 21;
	void son_public_print();
protected:
	int protected_b = 22;
	void son_protected_print();
private:
	int private_b = 23;
	void son_private_print();
};
void Son::son_public_print()
{
	std::cout << "继承类输出" << std::endl;
	public_print();
	protected_print();
}

void Son::son_protected_print()
{
	std::cout << "继承类输出" << std::endl;
	protected_print();

}

void Son::son_private_print()
{
	std::cout << "继承类输出" << std::endl;
}
/*****************************************************************************************************************/



/************************************************************************************************************
友元的出现：当外部的函数或者类想要访问某一个类的protected或者private的成员时，需要将其以外部的函数或者类以友元的类别写入到想要访问的类的public列表中。
相当于你想来访问我受保护或者私有的成员你得来我这注册一下。外部的类或者函数还是和平常一样声明定义。

*************************************************************************************************************/
class Sales_data {
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend std::ostream &print(std::ostream&, const Sales_data&);
	friend std::istream &read(std::istream&, Sales_data&);
public:
	// constructors
	Sales_data() = default;
	Sales_data(const std::string &s) : bookNo(s) { }
	Sales_data(const std::string &s, unsigned n, double p) :
		bookNo(s), units_sold(n), revenue(p*n) { }
	Sales_data(std::istream &);

	// operations on Sales_data objects
	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
private:
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};


// nonmember Sales_data interface functions
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);


/************************************************************************************


*************************************************************************************/
// used in future chapters
inline
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.isbn() < rhs.isbn();
}




Sales_data::Sales_data(std::istream &is)
{
	// read will read a transaction from is into this object
	read(is, *this);
}

double
Sales_data::avg_price() const {
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}

// add the value of the given Sales_data into this object
Sales_data&
Sales_data::combine(const Sales_data &rhs)
{
	units_sold += rhs.units_sold; // add the members of rhs into 
	revenue += rhs.revenue;       // the members of ``this'' object
	return *this; // return the object on which the function was called
}

Sales_data
add(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;  // copy data members from lhs into sum
	sum.combine(rhs);      // add data members from rhs into sum
	return sum;
}

// transactions contain ISBN, number of copies sold, and sales price
istream&
read(istream &is, Sales_data &item)
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}

ostream&
print(ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.units_sold << " "
		<< item.revenue << " " << item.avg_price();
	return os;
}
/***********************************************************************************/

//int main()
//{
//	int a;
//	Father f_class;
//	Son s_class;
//	f_class.public_print();
//	std::cout << "Son print" << std::endl;
//	s_class.son_public_print();
//	std::cin >> a;
//}
//


//int main()
//{
//	Sales_data total;         // variable to hold the running sum
//	if (read(cin, total))  {  // read the first transaction
//		Sales_data trans;     // variable to hold data for the next transaction
//		while (read(cin, trans)) {      // read the remaining transactions
//			if (total.isbn() == trans.isbn())   // check the isbns
//				total.combine(trans);  // update the running total
//			else {
//				print(cout, total) << endl;  // print the results
//				total = trans;               // process the next book
//			}
//		}
//		print(cout, total) << endl;          // print the last transaction
//	}
//	else {                                 // there was no input
//		cerr << "No data?!" << endl;         // notify the user
//	}
//
//	return 0;
//}
