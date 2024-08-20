﻿#include <iostream>
#include <list>
#include "my_list.h"
#include <cassert>
#include <vector>
using namespace std;
const size_t N = 10;

template<typename iter>
typename iterator_traits<iter>::value_type sum(iter start, iter fin) {
	typename iterator_traits<iter>::value_type summ = 0;
	while (start != fin)
		summ += *start++;
	return summ;
}


int main(int argc, char** argv)
{
	setlocale(0,"");

	using elem_type = double;

	//  old-style массив
	elem_type arr[N];
	for (size_t i = 0; i < N; i++)
		arr[i] = elem_type(rand() % 1000) / 100;
	//  Вывод в поток
	copy(arr, arr + N, ostream_iterator<elem_type>(cout, " "));
	cout << endl;
	cout << sum(arr, arr + N) << endl;

	//  std::vector
	vector<elem_type> v{ arr, arr + N };
	copy(v.cbegin(), v.cend(), ostream_iterator<elem_type>(cout, " "));
	cout << endl;
	cout << sum(v.begin(), v.end()) << endl;

	//  std::list
	list<elem_type> lst{ arr, arr + N };
	copy(lst.cbegin(), lst.cend(), ostream_iterator<elem_type>(cout, " "));
	cout << endl;
	cout << sum(lst.begin(), lst.end()) << endl;

	//  MyList
	MyList<elem_type> lst2{ arr, arr + N };
	copy(lst2.cbegin(), lst2.cend(), ostream_iterator<elem_type>(cout, " "));
	cout << endl;	
	cout << sum(lst2.cbegin(), lst2.cend()) << endl;
	cout << endl;
	lst2.push_back(12.2);
	copy(lst2.cbegin(), lst2.cend(), ostream_iterator<elem_type>(cout, " "));
	cout << endl;
	lst2.pop_back();
	copy(lst2.cbegin(), lst2.cend(), ostream_iterator<elem_type>(cout, " "));
	cout << endl;
	cout << *(--lst2.end()) << endl;

	cout << "Кол-во положительных" << endl;
	cout << lst2.countOfPositive() << endl;

}
