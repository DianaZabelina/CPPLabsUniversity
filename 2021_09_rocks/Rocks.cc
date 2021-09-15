#include <iostream>
#include <random>

/*
 * Игра "Камни"
 *
 * 2 игрока (пользователь и компьютер) по очереди берут 1, 2 или 3 камня из кучи.
 * В куче N камней (количество выбирается рандомно).
 * Проигрывает тот, кто взял камень последним.
 *
 * 1. Цикл завершается, когда  проигрывает один из игроков.
 * 2. По окончании игры спрашиваем, будут ли играть снова. Если да - повторяем цикл.
 * 3. Проверка ввода значений.
 * 4. Вывод количества камней перед каждый ходом.
 * 5. На ходе компьютера выводим, сколько камней он берёт.
 *
 */

int main() {
	//правила игры
	std::cout
			<< "Игра \"Камни\"\n\n"
					"Правила:\n"
					"1. Имеется куча из N камней.\n"
					"2. 2 игрока (пользователь и компьютер) по очереди берут 1, 2 или 3 камня из этой кучи.\n"
					"3. Проигрывает тот, кто взял камень последним.\n"
			<< std::endl;
game_retry:
	//загадываем количество камней N
	std::default_random_engine rnd;
	std::random_device rdev;
	rnd.seed(rdev());
	std::uniform_int_distribution<> N { 1, 20 };
	int numOfRocks = N(rnd);
	//вывод количества камней
	std::cout << "Количество камней в куче: " << numOfRocks << std::endl;
	do {
		//ход пользователя
		int userTurn;
userTurn_retry:
		std::cout << "Ваш ход: ";
		//проверка типа данных
		if (not (std::cin >> userTurn)) {
			std::cout << "Некорректный ввод. Введите число от 1 до 3."
					<< std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			goto userTurn_retry;
		}
		//проверка условий задачи
		if (userTurn < 1 || userTurn > 3 || userTurn > numOfRocks) {
			std::cout
					<< "Некорректный ввод. Введите число от 1 до 3. Число не должно превышать количество камней в куче."
					<< std::endl;
			std::cin.clear();
			goto userTurn_retry;
		}
		numOfRocks -= userTurn;
		//вывод количества камней
		std::cout << "Количество камней в куче: " << numOfRocks << std::endl;
		if (numOfRocks == 0) {
			std::cout << "Победа компьютера." << std::endl;
			break;
		}
		//загадываем количество камней для хода компьютера
		int n;
		if (numOfRocks < 3)
			n = numOfRocks;
		else
			n = 3;
		std::uniform_int_distribution<> turn { 1, n };
		//ход компьютера
		int computerTurn = turn(rnd);
		std::cout << "Ход компьютера: " << computerTurn << std::endl;
		numOfRocks -= computerTurn;
		//вывод количества камней
		std::cout << "Количество камней в куче: " << numOfRocks << std::endl;
		if (numOfRocks == 0)
			std::cout << "Ваша победа." << std::endl;
	} while (numOfRocks != 0);
	int choice;
choice_retry:
	std::cout << "Сыграть ещё раз? (1/0)" << std::endl;
	//проверка типа данных
	if (not (std::cin >> choice)) {
		std::cout << "Некорректный ввод. Введите 1 (да) либо 0 (нет)."
				<< std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		goto choice_retry;
	}
	if (choice < 0 || choice > 1) {
		std::cout << "Некорректный ввод. Введите 1 (да) либо 0 (нет)."
				<< std::endl;
		std::cin.clear();
		goto choice_retry;
	}
	if (choice == 0)
		std::cout << "Спасибо за игру! Приходите ещё!" << std::endl;
	else
		goto game_retry;
	return 0;
}
