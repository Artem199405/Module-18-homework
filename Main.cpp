#include <iostream>
#include "Chat.h"

using namespace std;

int main()
{
    cout << "Welcome to the chat!" << endl;

    const int iParticipants = 1;
    Chat chat(iParticipants);

    // �������������� ����
    chat.restoringChat();

    int action1;
    do
    {
        cout << "Select an action (1 - register an account; 2 - log in to your account; 3 - exit the application): ";
        cin >> action1;

        if (action1 == 1)
        {
            // ����������� ���������
            chat.registration();
        }
        else if (action1 == 2)
        {
            // ���� � �������
            chat.authorization();

            int action2;
            do
            {
                cout << "Select an action (1 - write a message; 2 - read the sent messages; 3 - log out of your account): ";
                cin >> action2;

                if (action2 == 1)
                {
                    // ���� ���������
                    chat.enteringMessage();
                }
                else if (action2 == 2)
                {
                    // ������ ���������� ���������
                    chat.readMessages();
                }
                else if (action2 == 3)
                {
                    // ����� �� ��������
                    chat.SignOut();
                }
                else
                {
                    cout << "Invalid operator, repeat the input" << endl;
                }
            } while (action2 != 3);
        }
        else if (action1 == 3)
        {
            // ��������� ��������� ����
            chat.saveChat();
        }
        else
        {
            cout << "Invalid operator, repeat the input" << endl;
        }
    } while (action1 != 3);

    return 0;
}