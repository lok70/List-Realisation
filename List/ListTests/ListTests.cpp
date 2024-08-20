#include <list>
#include <vector>
#include "CppUnitTest.h"
#include "my_list.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ListTests
{
	class Elem {
		int data;
		uint32_t watch;
		static size_t elem_counter;
		void check() const { Assert::IsTrue(watch == 0xDEADBEEF, L"Повреждение памяти!! (Обращение к неинициализированному экземпляру класса Elem)"); }
	public:
		

		Elem(const Elem&) = delete;
		Elem& operator=(const Elem&) = delete;
		explicit Elem(int value) : data(value), watch(0xDEADBEEF) { ++elem_counter; }
		Elem(Elem&& e) noexcept { e.check(); data = e.data; watch = e.watch; ++elem_counter; }
		Elem& operator=(Elem&& e) noexcept { check(); e.check(); data = e.data; watch = e.watch; }
		bool operator==(const Elem& e) const { check(); e.check(); return data == e.data; }
		~Elem() { check(); watch = 0; --elem_counter; }
		static size_t count() { return elem_counter; }
	};
	size_t Elem::elem_counter = 0;

	//  Для того, чтобы выполнить тестирование одного из указанных контейнеров (std::list или MyList),
	//  должна быть раскомментирована одна из следующих строк:
	//template<typename T> using ContainerTemplate = std::list<T>;
	template<typename T> using ContainerTemplate = MyList<T>;

	TEST_CLASS(ComplexTypeTests)
	{

	public:

		TEST_METHOD(IteratorTests)
		{
			ContainerTemplate<int> list{ 3, 4, 8, 5, 2, 13, 20 };
			list.push_back(10);
			Assert::IsTrue(list.end() == ++--list.end(), L"++--list.end() должен возвращать list.end()");
			Assert::AreEqual(10, *(--list.end()), L"--list.end() должен возвращать последний элемент");
		}

		TEST_METHOD(StringTests)
		{
			ContainerTemplate<std::string> list{ "123", "AAAAAAAA", "abc", "cde" };
			std::vector<std::string> expected1{ "123", "AAAAAAAA", "abc", "cde" };

			Assert::AreEqual(4ull, list.size(), L"Неправильно считается количество строковых элементов");
			Assert::IsTrue(std::equal(list.begin(), list.end(), expected1.begin(), expected1.end()), L"Неправильный порядок строковых элементов");
			Assert::IsTrue(std::equal(list.rbegin(), list.rend(), expected1.rbegin(), expected1.rend()), L"Неправильный порядок строковых элементов");

			for (const auto& str : expected1)
				list.erase(std::find(list.begin(), list.end(), str));

			Assert::AreEqual(0ull, list.size(), L"Список не пуст после удаления всех элементов");
			for (const auto& elem : list)
				Assert::Fail(L"Что-то лежит в списке после удаления всех элементов");

			list.push_back("test-1");
			list.push_back("test-2");
			list.push_back("test-4");
			std::vector<std::string> expected2{ "test-1", "test-2", "test-4" };
			Assert::IsTrue(std::equal(list.begin(), list.end(), expected2.begin(), expected2.end()), L"Неправильный порядок строковых элементов");
			Assert::IsTrue(std::equal(list.rbegin(), list.rend(), expected2.rbegin(), expected2.rend()), L"Неправильный порядок строковых элементов");
		}

	TEST_METHOD(ElemTests)
		{
			size_t init_count = Elem::count();
			{
				ContainerTemplate<Elem> list;
				Assert::AreEqual(0ull, Elem::count() - init_count, L"Создан лишний экземпляр класса Elem");

				for (const auto& elem : list)
					Assert::Fail(L"Что-то лежит в пустом списке");

				list.push_back(Elem(40));
				list.push_back(Elem(75));
				list.push_front(Elem(50));
				list.push_back(Elem(23));
				list.push_back(Elem(87));
				Assert::IsTrue(Elem::count() - init_count == 5, L"Создан лишний экземпляр класса Elem");
				list.erase(std::find(list.begin(), list.end(), Elem(75)));
				Assert::IsTrue(Elem::count() - init_count == 4, L"Неправильно работает удаление элементов списка");
			}
			Assert::IsTrue(Elem::count() - init_count == 0, L"Утечка памяти!!");
		}
	TEST_METHOD(PushBackTest)
	{
		// Тестирование метода push_back
		MyList<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);

		Assert::AreEqual(static_cast<size_t>(3), list.size(), L"Неправильный размер списка после добавления элементов");
		Assert::AreEqual(1, list.front(), L"Неправильное значение первого элемента после добавления");
		Assert::AreEqual(3, list.back(), L"Неправильное значение последнего элемента после добавления");
	}

	TEST_METHOD(PopBackTest)
	{
		// Тестирование метода pop_back
		MyList<int> list{ 1, 2, 3 };
		list.pop_back();

		Assert::AreEqual(static_cast<size_t>(2), list.size(), L"Неправильный размер списка после удаления элемента с конца");
		Assert::AreEqual(1, list.front(), L"Неправильное значение первого элемента после удаления");
		Assert::AreEqual(2, list.back(), L"Неправильное значение последнего элемента после удаления");
	}
	TEST_METHOD(MaxElementAndCountTest)
	{
		MyList<int> list{ 1, 3, 5, 3, 2, 5, 5 };
		auto result = list.maxElementAndCount();

		Assert::AreEqual(5, result.first, L"Неправильный максимальный элемент");
		Assert::AreEqual(static_cast<size_t>(3), static_cast<size_t>(result.second), L"Неправильное количество вхождений максимального элемента");
	}

	TEST_METHOD(CountOfPositiveTest)
	{
		MyList<int> list{ 1, -3, 5, -3, 2, 5, -5 };
		int count = list.countOfPositive();

		Assert::AreEqual(4, count, L"Неправильное количество положительных элементов");
	}

	TEST_METHOD(SplitBySignTest)
	{
		MyList<int> list{ -1, 2, -3, 4, 5, -6 };
		auto result = list.splitBySign();

		Assert::AreEqual(static_cast<size_t>(3), result.first.size(), L"Неправильное количество элементов в списке положительных чисел");
		Assert::AreEqual(static_cast<size_t>(3), result.second.size(), L"Неправильное количество элементов в списке отрицательных чисел");

		Assert::AreEqual(2, result.first.front(), L"Неправильное значение первого элемента в списке положительных чисел");
		Assert::AreEqual(5, result.first.back(), L"Неправильное значение последнего элемента в списке положительных чисел");

		Assert::AreEqual(-1, result.second.front(), L"Неправильное значение первого элемента в списке отрицательных чисел");
		Assert::AreEqual(-6, result.second.back(), L"Неправильное значение последнего элемента в списке отрицательных чисел");
	}

	TEST_METHOD(ReverseTest)
	{
		MyList<int> list{ 1, 2, 3, 4, 5 };
		list.reverse();

		Assert::AreEqual(static_cast<size_t>(5), list.size(), L"Неправильный размер списка после разворота");

		auto it = list.begin();
		Assert::AreEqual(5, *it++, L"Неправильное значение первого элемента после разворота");
		Assert::AreEqual(4, *it++, L"Неправильное значение второго элемента после разворота");
		Assert::AreEqual(3, *it++, L"Неправильное значение третьего элемента после разворота");
		Assert::AreEqual(2, *it++, L"Неправильное значение четвертого элемента после разворота");
		Assert::AreEqual(1, *it++, L"Неправильное значение пятого элемента после разворота");
	}

	};

}
