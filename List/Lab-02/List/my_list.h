#include <initializer_list>
#include <memory>
#include <iterator>
#include <cassert>
#include <list>
#include "unordered_map"
#include <stdexcept>
#include <algorithm>

template<typename T>
class MyList
{
private:


	struct mynode {
		T data;
		mynode* next;
		mynode* prev;
		mynode(T d, mynode* p, mynode* n) : data(d), prev(p), next(n) {}
		mynode(T&& d) : data(std::move(d)), prev(nullptr), next(nullptr) {}
	};

	mynode* _dummy_node;
	size_t _size;
public:
	using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	template<typename Pointer, typename Reference>
	class BaseIterator : public std::iterator<std::bidirectional_iterator_tag, value_type, difference_type, Pointer, Reference>
	{
	public:
		BaseIterator(mynode* ptr) {
			this->ptr = ptr;
		}
		bool operator==(const BaseIterator& other) const {
			return ptr == other.ptr;
		}

		bool operator!=(const BaseIterator& other) {
			return !(*this == other);
		}

		Pointer operator->() {
			return ptr;
		}

		BaseIterator& operator--() {
			
			ptr = ptr->prev;
			return *this;
		}

		BaseIterator operator--(int) {
			BaseIterator temp(*this);
			ptr = ptr->prev;
			return temp;
		}

		BaseIterator& operator++() {
			ptr = ptr->next;
			return *this;
		}

		BaseIterator operator++(int) {
			BaseIterator temp(*this);
			++(*this);
			return temp;
		}

		Reference operator*() {	
				return ptr->data;
		}

		mynode* getNode() const {
			return ptr;
		}

	private:
		mynode* ptr;
	};

	using iterator = BaseIterator<pointer, reference>;
	using const_iterator = BaseIterator<const_pointer, const_reference>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;



	MyList() : _size(0) {
		void* place = operator new(sizeof(mynode));
		_dummy_node = static_cast<mynode*>(place);
		_dummy_node->next = _dummy_node;
		_dummy_node->prev = _dummy_node;
	};
	MyList(const MyList& other):MyList() {
		std::for_each(other.begin(), other.end(), [this](const T& value) {
			this->push_back(value);
			});
			
	}
	MyList(MyList&& other) :MyList() {
		std::for_each(other.begin(), other.end(), [this](const T& value) {
			this->push_back(value);
			});
		other._dummy_node = nullptr;
	
		other._size = 0;
	};
	MyList(std::initializer_list<T> init) : MyList() {
		for (auto x : init)
			push_back(x);
	}
	template<typename iter>
	MyList(iter start, iter fin) : MyList() {
		while (start != fin)
			push_back(*start++);
	}
	~MyList() {
		clear();
		operator delete (_dummy_node, sizeof(mynode));
	}


	MyList& operator=(const MyList& other) {
		if (*this != other) {
			clear();

			_size = other._size;
			_dummy_node = other._dummy_node;
			std::copy(other.begin(), other.end(), begin());
		}
		return *this;
	}
	MyList& operator=(MyList&& other) noexcept {
		if (this != &other) {
			clear();
			_dummy_node = other._dummy_node;

			other._dummy_node = nullptr;

			other._size = 0;
		}
		return *this;
	}
	MyList& operator=(std::initializer_list<T> ilist) {

		clear();
		_size = ilist.size();
		_dummy_node = ilist._dummy_node;
		std::copy(ilist.begin(), ilist.end(), begin());

	}

	reference front() {
		return _dummy_node->next->data;
	}
	const_reference front() const {
		return _dummy_node->next->data;
	}
	reference back() {
		return _dummy_node->prev->data;
	}
	const_reference back() const {
		return _dummy_node->prev->data;
	}

	iterator begin() {
		return iterator(_dummy_node->next);
	}
	const_iterator begin() const {
		return const_iterator(_dummy_node->next);
	}
	const_iterator cbegin() {
		return const_iterator(_dummy_node->next);
	}

	const_iterator cbegin() const noexcept {
		return const_iterator(_dummy_node->next);
	}


	iterator end() noexcept {
		return iterator(_dummy_node);
	};
	const_iterator cend() const noexcept {
		return const_iterator(_dummy_node);
	}


	const_iterator cend() {
		return const_iterator(_dummy_node);
	};


	reverse_iterator rbegin() noexcept {
		return reverse_iterator(_dummy_node);
	};
	reverse_iterator rend() noexcept {
		return reverse_iterator(_dummy_node->next);
	}

	void push_back(const T& value) {
		insert(cend(), value);

	}
	void push_back(T&& value) {
		insert(cend(), std::move(value));

	}
	void pop_back() {
		erase(iterator(_dummy_node->prev));
	}

	iterator insert(const_iterator pos, const T& value) {
		mynode* pos_node = pos.getNode();
		mynode* new_node = new mynode(value, pos_node->prev, pos_node);
		pos_node->prev->next = new_node;
		pos_node->prev = new_node;
		_size++;
		return iterator(new_node);
	}



	iterator insert(const_iterator pos, T&& value) {
		mynode* prevNode = pos.getNode()->prev;
		mynode* nextNode = pos.getNode();
		mynode* newNode = new mynode(std::move(value));
		newNode->next = nextNode;
		newNode->prev = prevNode;
		prevNode->next = newNode;
		nextNode->prev = newNode;
		_size++;
		return iterator(newNode);
	}

	iterator erase(iterator pos) {
		mynode* current = pos.getNode();
		if (current == _dummy_node) {
			throw std::out_of_range("Iterator is pointing to nullptr");
		};
		mynode* prevNode = current->prev;
		mynode* nextNode = current->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode; 
		delete current;
		--_size;
		return iterator(prevNode);
	}


	iterator erase(const_iterator pos) {
		mynode* current = pos.getNode();
		if (current == _dummy_node) {
			throw std::out_of_range("Iterator is pointing to nullptr");
		};


		mynode* prevNode = current->prev;
		mynode* nextNode = current->next;
		if (prevNode) {
			prevNode->next = nextNode;
		}
		else {
			_dummy_node->next = nextNode;
		}

		if (nextNode) {
			nextNode->prev = prevNode;
		}

		delete current;
		--_size;

		return iterator(nextNode);
	}

	iterator erase(iterator first, iterator last) {
		if (first.getNode == nullptr || last.getNode() == nullptr) {
			throw std::out_of_range("Iterator is pointing to nullptr");
		}

		while (first != last) {
			first = erase(first);
		}

		return last;

	}
	iterator erase(const_iterator first, const_iterator last) {
		if (first.getNode() == nullptr || last.getNode() == nullptr) {
			throw std::out_of_range("Iterator is pointing to nullptr");
		}

		while (first != last) {
			first = erase(first);
		}

		return last;
	}


	void push_front(const T& item) {
		insert(cbegin(), item);
		_size++;
	}
	void push_front(T&& value) 
	{
		insert(cbegin(), std::move(value));
		//_size++;
	}
	void pop_front() {
		erase(cbegin());
		_size--;
	}

	void swap(MyList& other) noexcept {
		std::swap(*this->_dummy_node->next, other._dummy_node->prev);
		std::swap(*this->_dummy_node->prev, other._dummy_node->next);
	}


	bool empty() const noexcept {
		return _size == 0;
	}
	size_t size() const noexcept {
		return _size;
	}

	void clear() noexcept {
		while (!empty()) {
			pop_back();
		}
	};



	int countOfPositive() {
		int c = 0;
		for (auto it = begin(); it != end(); it++) {
			if (*it > 0) {
				c++;
			}
		}
		return c;

	};

	//std::pair<value_type, int> maxElementAndCount() {
	//	if (empty()) {
	//		throw std::out_of_range("List is empty");
	//	}
	//	int maxCount = 0;
	//	double maxelem = DBL_MIN;
	//	value_type maxElement;
	//	std::unordered_map<value_type, int> countMap;
	//	for (auto it = begin(); it != end(); ++it) {

	//		if (maxelem <= *it)
	//		{
	//			if (*it == maxelem)
	//				maxCount++;
	//			maxelem = *it;

	//		}
	//	}
	//	return std::make_pair(maxelem, maxCount);
	//}
	std::pair<MyList, MyList> splitBySign() {
		MyList positiveList;
		MyList negativeList;
		for (auto it = begin(); it != end(); ++it) {
			if (*it >= 0) {
				positiveList.push_back(*it);
			}
			else {
				negativeList.push_back(*it);
			}
		}
		return std::make_pair(positiveList, negativeList);
	}

	//void reverse()
	//{
	//	MyList<T> lst2;
	//	for (auto i = this->rend; i != this->rbegin; i++)
	//		lst2.push_back(*i);
	//	this->clear()
	//	this = lst2;
	//}

};

