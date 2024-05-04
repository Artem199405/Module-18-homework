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
	int _count; // ���������� ������������������ ��������� ����
	int iSender; // ����� ��������������� ��������� ���� �� ������� _participants
	vector<Participants> _participants;

	AutoLogin loginSource; // ���������� ������ ��� �������� ����� ������� � ����

public:
	//�����������
	Chat(int size);

	// ����������
	~Chat();

	// �������������� ����
	void restoringChat();

	// ����������� �������� ������ �������� ����
	void registration();

	// ����������� ��������
	void authorization();

	// ���� ���������
	void enteringMessage();

	// ������ ���������
	void readMessages();

	// ����� �� ��������
	void SignOut();

	// ��������� ��������� ����
	void saveChat();

	// ��������� ������������ � ���������� �������
	bool compareLogin(string);

	// ��������� ������������ � ���������� ����
	bool compareName(string);

    // ���������� ������ ��������� ����
	void addParticipant(string, string, string);
	
	// ������ � ���� ������ ������ ��������� ����
	void writeParticipantsFile(string, string, string);

	// ���� � �������
	bool SignIn(string, string);

	// �������� ���������
	void sendMessage(string, string);

	// ������������ ���������� ������
	void findFreeLogin(string);

	// ����������� ��� �� ������
	uint findHash(string);
};