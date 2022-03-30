#include <iostream>
#include <limits>
#include <iomanip>
#include <fstream>
#include <vector>

const char *DB_FILE_NAME = "empl_roster.db";

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
 *
 */

struct Employee {
	char name[21];
	char job[16];
	int salary;
};

void print_table_header() {
	std::cout <<
			"    |       Employee      |       Job       | Salary \n"
			"----+---------------------+-----------------+--------\n";
}

void print_table_row(const Employee &empl, int row) {
	std::cout <<
			std::setw(3) << std::right << row << " | " <<
			std::setw(20) << std::left << empl.name << " | " <<
			std::setw(15) << std::left << empl.job << " | " <<
			std::setw(7) << std::right << empl.salary <<
			std::endl;
}

/*
 * | char[]     | char[]     |i|
 * | Employee                  |
 * -------------------------------
 * | char[]                    |
 * ^
 * empl
 *
 * &empl - Employee *
 *         char *
 * */

void read_file(const char *filename, std::vector<Employee> &list) {
	list.clear();

	std::ifstream data_file { filename, std::ios::binary };
	if (not data_file)
		return;

	Employee empl;
	while (data_file.read(
				/*массив char-ов*/reinterpret_cast<char*>(&empl),
				/*размер*/sizeof(empl)))
		list.push_back(empl);

	data_file.close();
}

void write_file(const char *filename, std::vector<Employee> &list) {
	std::ofstream data_file { filename, std::ios::binary };

	for (auto &&e : list)
		data_file.write(reinterpret_cast<char*>(&e), sizeof(e));

	data_file.close();
}

void input_employee(std::vector<Employee> &list){
	Employee empl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Введите имя сотрудника: ";
	std::cin.getline(empl.name, sizeof(empl.name));

	std::cout << "Введите должность     : ";
	std::cin.getline(empl.job, sizeof(empl.job));

	std::cout << "Введите зарплату      : ";
	std::cin >> empl.salary;

	list.push_back(empl);
}

void change_employee(std::vector<Employee> &list){
	std::cout << "Введите номер записи: ";
	//size_type - беззнаковое целое число, поэтому нужно исключить отрицательное значение int
	unsigned int n;
	std::cin >> n;
	if (n >= list.size()) {
		std::cout << "Записи под таким номером нет." << std::endl;
	}
	else {
		list.erase(list.begin() + n);

		Employee empl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Введите имя сотрудника: ";
		std::cin.getline(empl.name, sizeof(empl.name));

		std::cout << "Введите должность     : ";
		std::cin.getline(empl.job, sizeof(empl.job));

		std::cout << "Введите зарплату      : ";
		std::cin >> empl.salary;

		list.emplace(list.begin()+n, empl);
	}
}

void delete_employee(std::vector<Employee> &list){
	//list.erase(list.begin() + num)
}

int main() {
	std::vector<Employee> empl_roster;

	read_file(DB_FILE_NAME, empl_roster);

	int choice;
	do {
		menu:
			std::cout <<
					" Действия над списком:\n"
					" ---------------------\n"
					" 1. Вывести список\n"
					" 2. Добавить сотрудника\n"
					" 3. Изменить запись\n"
					" 4. Удалить запись\n"
					"\n"
					" 0. Выход\n"
					"---> ";
			if(not(std::cin >> choice)){
				if(std::cin.eof()){
					std::cerr << "Ошибка ввода-вывода" << std::endl;
					return 1;
				}
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				goto menu;
			}

			int i=0;

			switch(choice){
			case 0:
				std::cout << "До свидания!" << std::endl;
				break;
			case 1:
				print_table_header();
				for (auto &&e : empl_roster)
					print_table_row(e, i++);
				std::cout << std::endl;
				break;
			case 2:
				input_employee(empl_roster);
				break;
			case 3:
				change_employee(empl_roster);
				break;
			case 4:
				delete_employee(empl_roster);
				break;
			default:
				std::cout << "Нет такого варианта." << std::endl;
			}
	} while (choice!=0);

	write_file(DB_FILE_NAME, empl_roster);

	return 0;
}

