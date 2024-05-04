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
	int _count; // ���������� ���������� ���������
	string _login, _password, _name;
	uint* _password_hash;
	vector<Messages> _messages;

public:
	//�����������
	Participants();

	// ����������
	~Participants();

	// ���������� ������ ���������
	void recordMessage(string, string);

	// ������ ���������� ���������
	void showMessages();

	// ������ � ���� ���������� (�������������) ���������
	void writeMessagesFile(string);

	// �������
	void setLogin(string);

	void setPassword(string);

	void setName(string);

	void setPasswordHash(string);

	// �������
	string getLogin();

	string getPassword();

	string getName();

	uint getPasswordHash();
};