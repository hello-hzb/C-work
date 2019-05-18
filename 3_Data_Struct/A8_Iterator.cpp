#include <iostream>
using namespace std;


/*****************************************************************************
P292   C++ PPRIMER
所有的顺序容器都提供了快速顺序访问元素的能力，但是这些容器在以下方面都有不同的性能折中。
1.vector：			可变数组大小。支持快速随机访问。在尾部之外的位置插入或者删除元素可能很慢。
2.deque：			双端队列。支持快速随机访问。在头尾位置插入删除速度很快
3.list：				双向链表。只支持双向顺序访问。在list中任何位置插入和删除操作速度都很快。
4.forward_list：		单向链表。只支持单向顺序访问。在链表任何位置进行插入和删除操作速度很快
5.array：			固定数组大小。支持快速随机访问，不能添加或删除元素。
6.string：			与vector相似的容器，但专门用于保存字符。随机访问速度快，在尾部插入删除元素速度快





******************************************************************************/
#include <stack>
using std::stack;

void stack_operate()
{
	stack<int> intStack;  // empty stack

	// fill up the stack
	for (size_t ix = 0; ix != 10; ++ix)
		intStack.push(ix);   // intStack holds 0 . . . 9 inclusive

	// while there are still values in intStack
	while (!intStack.empty()) {
		int value = intStack.top();
		// code that uses value
		cout << value << endl;
		intStack.pop(); // pop the top element, and repeat
	}
}


#include <vector>
using std::vector;
void vector_operate()
{
	vector<int> ivec;
	// size should be zero; capacity is implementation defined
	cout << "ivec: size: " << ivec.size()
		<< " capacity: " << ivec.capacity() << endl;

	// give ivec 24 elements
	for (vector<int>::size_type ix = 0; ix != 24; ++ix)
		ivec.push_back(ix);

	// size should be 24; capacity will be >= 24 and is implementation defined
	cout << "ivec: size: " << ivec.size()
		<< " capacity: " << ivec.capacity() << endl;
	ivec.reserve(50); // sets capacity to at least 50; might be more
	// size should be 24; capacity will be >= 50 and is implementation defined
	cout << "ivec: size: " << ivec.size()
		<< " capacity: " << ivec.capacity() << endl;

	// add elements to use up the excess capacity
	while (ivec.size() != ivec.capacity())
		ivec.push_back(0);

	// capacity should be unchanged and size and capacity are now equal
	cout << "ivec: size: " << ivec.size()
		<< " capacity: " << ivec.capacity() << endl;
	ivec.push_back(42); // add one more element

	// size should be 51; capacity will be >= 51 and is implementation defined  添加一个元素后， capacity会自动增大
	cout << "ivec: size: " << ivec.size()
		<< " capacity: " << ivec.capacity() << endl;

	ivec.shrink_to_fit();  // ask for the memory to be returned         //将多余的空间释放

	// size should be unchanged; capacity is implementation defined
	cout << "ivec: size: " << ivec.size()
		<< " capacity: " << ivec.capacity() << endl;

}


#include <algorithm>
using std::find;

#include <string>
using std::string;

#include <list>
using std::list;

#include <vector>
using std::vector;

void list_operate()
{
	list<string> slist;
	string s;
	while (cin >> s)
		slist.push_back(s);  // read the contents into slist

	/* we'll explain find in chapter 10
	* find looks in the sequence denoted by its first two
	* iterator arguments for the value of its third argument
	* returns an iterator to the first element with that value
	* if that element exists in the input sequence
	* otherwise returns the end iterator
	*/
	auto iter = find(slist.begin(), slist.end(), "Quasimodo");
	if (iter != slist.end())
		slist.erase(iter);

	auto orig = slist; // keep a copy before we destroy the contents
	slist.clear();     // delete all the elements within the container
	cout << "after clear, size is: " << slist.size() << endl;

	slist = orig; // restore the data
	slist.erase(slist.begin(), slist.end()); // equivalent
	cout << "after erase begin to end, size is: " << slist.size() << endl;

	slist = orig; // restore the data
	auto elem1 = slist.begin(), elem2 = slist.end();
	// delete the range of elements between two iterators
	// returns an iterator to the element just after the last removed element
	elem1 = slist.erase(elem1, elem2); // after the call elem1 == elem2
	cout << "after erase elem1 to elem2 size is: " << slist.size() << endl;

	if (elem1 != elem2)
		cout << "somethings wrong" << endl;
	else
		cout << "okay, they're equal " << endl;

}


#include <algorithm>
using std::find;

#include <string>
using std::string;

#include <list>
using std::list;

#include <forward_list>
using std::forward_list;

#include <vector>
using std::vector;

#include <iostream>
using std::cout; using std::endl;

void erase_operate()
{
	// lst has ten elements 0 ... 9 in value   双向链表
	list<int> lst = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// print the initial values in lst
	cout << "initial list: ";
	for (auto it : lst)
		cout << it << " ";
	cout << endl;

	// erase the odd elements in lst
	auto it = lst.begin();
	while (it != lst.end())
		if (*it % 2)             // if the element is odd
			it = lst.erase(it);  // erase this element
		else
			++it;

	// print the current contents of lst
	cout << "after erasing odd elements from lst: ";
	for (auto it : lst)
		cout << it << " ";
	cout << endl;

	// repeat the same actions but on a forward_list    单向链表
	forward_list<int> flst = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// print the initial values in flst
	cout << "initial list: ";
	for (auto it : flst)
		cout << it << " ";
	cout << endl;

	// erase the odd elements in flst
	auto prev = flst.before_begin(); // element "off the start" of flst
	auto curr = flst.begin();     // denotes the first element in flst
	while (curr != flst.end()) {  // while there are still elements 
		if (*curr % 2)                     // if the element is odd
			curr = flst.erase_after(prev); // erase it and move curr 
		else {
			prev = curr; // move the iterators to denote the next
			++curr;      // element and one before the next element
		}
	}

	// print the current contents of lst
	cout << "after erasing elements from flst: ";
	for (auto it : flst)
		cout << it << " ";
	cout << endl;

}


void string_operate()
{
	string numbers("0123456789"), name("r2d2");
	// returns 1, i.e., the index of the first digit in name
	auto pos = name.find_first_of(numbers);
	if (pos != string::npos)
		cout << "found number at index: " << pos
		<< " element is " << name[pos] << endl;
	else
		cout << "no number in: " << name << endl;

	pos = 0;
	// each iteration finds the next number in name
	while ((pos = name.find_first_of(numbers, pos))
		!= string::npos) {
		cout << "found number at index: " << pos
			<< " element is " << name[pos] << endl;

		++pos; // move to the next character
	}

	string river("Mississippi");

	auto first_pos = river.find("is");  // returns 1
	auto last_pos = river.rfind("is");  // returns 4
	cout << "find returned: " << first_pos
		<< " rfind returned: " << last_pos << endl;

	string dept("03714p3");
	// returns 5, which is the index to the character 'p'
	pos = dept.find_first_not_of(numbers);
	cout << "first_not returned: " << pos << endl;

}



void printVec(const vector<int> &vi)
{
	// print the vector's elements
	auto iter = vi.begin();
	while (iter != vi.end())
		cout << *iter++ << endl;
}

void vector_interator()
{

	// silly loop to remove even-valued elements 
	// and insert a duplicate of odd-valued elements
	vector<int> vi = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	printVec(vi);

	// we call begin, not cbegin because we're changing vi
	auto iter = vi.begin();
	while (iter != vi.end()) {
		if (*iter % 2) {    // if the element is odd
			iter = vi.insert(iter, *iter);  // duplicate  it
			iter += 2; // advance past this element and the new one 
		}
		else
			iter = vi.erase(iter);          // remove even elements
		// don't advance the iterator; 
		// iter denotes the element after the one we erased
	}
	printVec(vi);
}



void assign_ops()
{
	string s = "some string", s2 = "some other string";
	// equivalent ways to insert all the characters from s2 at beginning of s
	// insert iterator range before s.begin()
	s.insert(s.begin(), s2.begin(), s2.end());
	cout << "insert iterators version:        " << s << endl;

	s = "some string";
	s.insert(0, s2); // insert a copy of s2 before position 0 in s
	cout << "insert string at given position: " << s << endl;

	s = "some string";
	// insert s2.size() characters from s2 starting at s2[0] before s[0]
	s.insert(0, s2, 0, s2.size());
	cout << "insert positional version:       " << s << endl;


	s = "";  // s is now empty
	vector<char> c_vec(1, 'a');
	// insert characters from c_vec into s
	s.insert(s.begin(), c_vec.begin(), c_vec.end());
	s.insert(s.size(), 5, '!'); // add five exclamation points at the end of s
	cout << s << endl;

	s.erase(s.size() - 5, 5);   // erase the last five characters from s
	cout << s << endl;

	s = "";  // s is now empty
	const char *cp = "Stately, plump Buck";
	s.assign(cp, 7);            // s == "Stately"
	cout << s << endl;
	s.insert(s.size(), cp + 7); // s == "Stately, plump Buck"
	cout << s << endl;

	s = "C++ Primer";  // reset s and s2
	s2 = s;            // to "C++ Primer"
	s.insert(s.size(), " 4th Ed."); // s == "C++ Primer 4th Ed."
	s2.append(" 4th Ed."); // equivalent: appends " 4th Ed." to s2; 
	cout << s << " " << s2 << endl;

	// two ways to replace "4th" by "5th"
	// 1. insert and erase
	s.erase(11, 3);                 // s == "C++ Primer Ed."
	s.insert(11, "5th");            // s == "C++ Primer 5th Ed."

	// 2. use replace
	// erase three characters starting at position 11
	//  and then insert "5th"
	s2.replace(11, 3, "5th"); // equivalent: s == s2

	cout << s << " " << s2 << endl;

	// two ways to replace "5th" by "Fifth"
	// 1. use replace if we know where the string we want to replace is
	s.replace(11, 3, "Fifth"); // s == "C++ Primer Fifth Ed."

	// 2. call find first to get position from which to replace
	auto pos = s2.find("5th");
	if (pos != string::npos)
		s2.replace(pos, 3, "Fifth");
	else
		cout << "something's wrong, s2 is: " << s2 << endl;
	cout << s << " " << s2 << endl;
}


#include <stdexcept>
using std::out_of_range;
void Sub_String_Operate()
{
	try {
		string s("hello world");
		cout << s.substr(0, 5) << endl;  // prints hello
		cout << s.substr(6) << endl;     // prints world
		cout << s.substr(6, 11) << endl; // prints world
		cout << s.substr(12) << endl;    // throws out_of_range 
	}
	catch (out_of_range) { cout << "caught out_of_range" << endl; }
}


using std::to_string; using std::stod;
#include <iostream>
using std::cout; using std::endl;

void use_Convs()
{
	int i = 42;
	// converts the int i to its character representation
	string s = to_string(i);

	double d = stod(s);   // converts the string s to floating-point
	cout << "i = " << i << " s = " << s << " d is: " << d << endl;

	// convert the first substring in s that starts with a digit,  d = 3.14
	string s2 = "pi = 3.14";
	d = stod(s2.substr(s2.find_first_of("+-.0123456789")));

	cout << "d = " << d << " s = " << s << " s2 is: " << s2 << endl;
}



//int main()
//{
//	//stack_operate();
//	//vector_operate();
//	use_Convs();
//}
