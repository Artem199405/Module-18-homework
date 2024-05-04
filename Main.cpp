#include <iostream>
#include "Chat.h"

using namespace std;

int main()
{
    cout << "Welcome to the chat!" << endl;

    const int iParticipants = 1;
    Chat chat(iParticipants);

    // Восстановление чата
    chat.restoringChat();

    int action1;
    do
    {
        cout << "Select an action (1 - register an account; 2 - log in to your account; 3 - exit the application): ";
        cin >> action1;

        if (action1 == 1)
        {
            // Регистрация аккаунтов
            chat.registration();
        }
        else if (action1 == 2)
        {
            // Вход в аккаунт
            chat.authorization();

            int action2;
            do
            {
                cout << "Select an action (1 - write a message; 2 - read the sent messages; 3 - log out of your account): ";
                cin >> action2;

                if (action2 == 1)
                {
                    // Ввод сообщения
                    chat.enteringMessage();
                }
                else if (action2 == 2)
                {
                    // Чтение присланных сообщений
                    chat.readMessages();
                }
                else if (action2 == 3)
                {
                    // Выход из аккаунта
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
            // Сохранить состояние чата
            chat.saveChat();
        }
        else
        {
            cout << "Invalid operator, repeat the input" << endl;
        }
    } while (action1 != 3);

    return 0;
}