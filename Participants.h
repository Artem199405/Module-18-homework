#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include "Messages.h"
#include "Sha1.h"

using namespace std;

class Participants
{
private:
	int _count; // Количество присланных сообщений
	string _login, _password, _name;
	uint* _password_hash;
	vector<Messages> _messages;

public:
	//Конструктор
	Participants();

	// Деструктор
	~Participants();

	// Добавление нового сообщения
	void recordMessage(string, string);

	// Чтение присланных сообщений
	void showMessages();

	// Запись в файл присланных (непрочитанных) сообщений
	void writeMessagesFile(string);

	// Сеттеры
	void setLogin(string);

	void setPassword(string);

	void setName(string);

	void setPasswordHash(string);

	// Геттеры
	string getLogin();

	string getPassword();

	string getName();

	uint getPasswordHash();
};