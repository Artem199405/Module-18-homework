#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdio>
#include "Participants.h"
#include "AutoLogin.h"

using namespace std;

class Chat
{
private:
	int _count; // Количество зарегистрированных учатников чата
	int iSender; // Номер авторизованного участника чата из массива _participants
	vector<Participants> _participants;

	AutoLogin loginSource; // Префиксное дерево для создания новых логинов в чате

public:
	//Конструктор
	Chat(int size);

	// Деструктор
	~Chat();

	// Восстановление чата
	void restoringChat();

	// Регистрация аккаунта нового частника чата
	void registration();

	// Авторизация аккаунта
	void authorization();

	// Ввод сообщения
	void enteringMessage();

	// Чтение сообщения
	void readMessages();

	// Выход из аккаунта
	void SignOut();

	// Сохранить состояние чата
	void saveChat();

	// Сравнение существующих и введенного логинов
	bool compareLogin(string);

	// Сравнение существующих и введенного имен
	bool compareName(string);

    // Добавление нового участника чата
	void addParticipant(string, string, string);
	
	// Запись в файл данных нового участника чата
	void writeParticipantsFile(string, string, string);

	// Вход в аккаунт
	bool SignIn(string, string);

	// Отправка сообщения
	void sendMessage(string, string);

	// Автодопление введенного логина
	void findFreeLogin(string);

	// Определение хеш от пароля
	uint findHash(string);
};