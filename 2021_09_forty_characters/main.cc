#include <iostream>
#include <fstream>
#include <string>

/*
 * ¬ывод содержимого текстового файла input.txt на консоль таким образом,
 * чтобы ширина выводимого текста не превышала 40 символов, но слова разрывать нельз€.
 *
 * —читать, что слов длиннее 40 символов в файле нет, а раздел€ютс€ слова пробелами и переводами строк.
 */

int main() {
	//открытие файла
	std::ifstream file;
	file.open("input.txt");
	//чтение по словам
	std::string s;
	file >> s;
	std::string output = s;
	while (file >> s) {
		if ((output.length() + 1 + s.length()) <= 40) {
			output = output + " " + s;
		}
		else {
			std::cout << output << std::endl;
			output = s;
		}
	}
	//вывод последней строки на случай, если она не вывелась в цикле
	if ((output.length() + 1 + s.length()) <= 40) {
		std::cout << output << std::endl;
	}
	file.close();
	return 0;
}
