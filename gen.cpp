/*
 * autor:   lis
 * created: Nov 13 2020
 * changed: Nov 20 03:35:10 2020
 */

/*
 * Программа принимает три аргумента
 * (целых числа):
 * 1.Количество элементов, которые нужно
 *   сгенерировать
 * 2.Минимальное значение элементов
 * 3.Максимальное значение элементов
 *
 * На выходе программа выдаёт случайную
 * последовательность строк:
 *
 * + KEY_1
 * ...
 * + KEY_N
 * - KEY_X
 * ...
 * - KEY_Z
 *
 * где KEY — случайное значение в
 * отрезке [min, max]. Строки, содержащие
 * '-' в начале, содержат все те же ключи
 * KEY_1 — KEY_N, но в случайном порядке
 *
 * Ключи могут повторяться.
 */

#include <algorithm>
#include <iostream>
#include <vector>

#include <lis/comarg.hpp>
#include <lis/rand.hpp>


using namespace lis;
using namespace std;





// functions
template<typename T, class Alloc>
vector<T, Alloc> &operator<<(std::vector<T, Alloc> &vec, T &&t)
{
	vec.push_back(move(t));
	return vec;
}

template<typename T, class Alloc>
vector<T, Alloc> &operator<<(std::vector<T, Alloc> &vec, T const &t)
{
	vec.push_back(t);
	return vec;
}





// main
int main( int argc, char *argv[] )
{
	int count = arg(argc, argv, 1, 50);
	int min   = arg(argc, argv, 2, 0);
	int max   = arg(argc, argv, 3, 100);

	vector<int> values;

	dre_type dre(time(0));
	disI dis(min, max);
	int val;
	for(int i = 0; i < count; ++i)
	{
		val = dis(dre);
		values << val;
		cout << "+ " << val << '\n';
	}

	shuffle( values.begin(), values.end(), dre );
	for(auto b = values.begin(), e = values.end(); b != e; ++b)
		printf("- %i\n", *b);

	return 0;
}





// end
