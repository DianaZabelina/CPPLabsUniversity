#include <iostream>
#include <iomanip>
#include <fstream>

/*
 * --- Массивы
 * >>> Структуры
 * --- Объединения
 */

/*
 * Задача
 *
 * Есть список сотрудников.
 * У сотрудника есть ФИО, должность, ЗП.
 * Вывести список сотрудников в виде таблицы.
 */

struct Employee {
	char name[21];
	char job[16];
	int salary;
};

constexpr int EMPL_COUNT = 3;
Employee empl_list[] {
		{ "Ivanov I.I.", "SysAdmin", 3'000 },
		{ "Petrov P.P.", "Manager", 9'000 },
		{ "Sidorov S.S", "Janitor", 12'000 },
};

int main() {
	std::cout <<
			"       Employee      |       Job       | Salary \n"
			"---------------------+-----------------+--------\n";
	for (unsigned i = 0; i < EMPL_COUNT; i++) {
		std::cout <<
				std::setw(20) <<
				std::left <<
				empl_list[i].name <<
				" | " <<
				std::setw(15) <<
				std::left <<
				empl_list[i].job <<
				" | " <<
				std::setw(7) <<
				std::right <<
				empl_list[i].salary <<
				std::endl;
	}

	return 0;
}

