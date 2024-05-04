#include "Chat.h"

Chat::Chat(int size) : _count(0)
{
    vector<Participants> _participants(size - 1);

    loginSource.insert("Log1"); loginSource.insert("Log2"); loginSource.insert("Log3");
    loginSource.insert("Login1"); loginSource.insert("Login2"); loginSource.insert("Login3");
    loginSource.insert("log1"); loginSource.insert("log2"); loginSource.insert("log3");
    loginSource.insert("login1"); loginSource.insert("login2"); loginSource.insert("login3");
}

Chat::~Chat()
{
}

void Chat::restoringChat()
{
    fstream participant_file = fstream("Participants.txt", ios::in | ios::out);

    if (participant_file)
    {
        participant_file.seekp(0, ios_base::beg);
        while (!participant_file.eof())
        {
            string login, password, name;

            participant_file >> login;
            participant_file >> password;
            participant_file >> name;
            if (login != "" && password != "" && name != "")
                addParticipant(login, password, name);
        }
    }

    fstream messages_file = fstream("Messages.txt", ios::in | ios::out);

    if (messages_file)
    {
        messages_file.seekp(0, ios_base::beg);
        while (!messages_file.eof())
        {
            string receiver, sender, text;

            messages_file >> receiver;
            messages_file >> sender;
            messages_file >> text;
            if (receiver != "" && sender != "" && text != "")
            {
                for (int i = 0; i < _count; i++)
                {
                    if (receiver == _participants[i].getName())
                    {
                        _participants[i].recordMessage(sender, text);
                    }
                }
            }
        }

        messages_file = fstream("Messages.txt", ios::in | ios::out | ios::trunc);
    }
}

void Chat::registration()
{
    string login, password, name;
    bool key = true;

    do
    {
        int answer;

        cout << "Suggest free logins? (1 - yes; 2 - no): ";
        cin >> answer;
        if (answer == 1)
        {
            string keyword;
            cout << "Enter the keyword: ";
            cin >> keyword;
            findFreeLogin(keyword);
        }
        cout << "Enter your login: ";
        cin >> login;
        key = compareLogin(login);
        if (key == true)
            cout << "A user with this login already exists. Come up with a new login." << endl;
    } while (key == true);

    cout << "Enter the password: ";
    cin >> password;

    do
    {
        cout << "Enter your username: ";
        cin >> name;
        key = compareName(name);
        if (key == true)
            cout << "A user with this username already exists. Come up with a new username." << endl;
    } while (key == true);

    addParticipant(login, password, name);
    writeParticipantsFile(login, password, name);
}

void Chat::authorization()
{
    string login, password;
    bool key = true;

    do
    {
        cout << "Enter your login: ";
        cin >> login;
        cout << "Enter the password: ";
        cin >> password;
        key = SignIn(login, password);
        if (key == false)
            cout << "You have entered an incorrect login or password. Try again." << endl;
    } while (key == false);

    cout << "You are logged in to your account." << endl;
}

void Chat::enteringMessage()
{
    string name, text;
    bool key = true;

    do
    {
        cout << "Enter the name of the user to send the message to, or 'all' - all chat participants: ";
        cin >> name;
        key = compareName(name);
        if (key == false)
            cout << "A user with that name was not found. Try again." << endl;
    } while (key == false);

    cout << "Enter the text of the message: ";
    cin >> text;

    sendMessage(name, text);
}

void Chat::readMessages()
{
    _participants[iSender].showMessages();
}

void Chat::SignOut()
{
    iSender = -1;
}

void Chat::saveChat()
{
    for (int i = 0; i < _count; i++)
    {
        _participants[i].writeMessagesFile(_participants[i].getName());
    }
}

bool Chat::compareLogin(string login)
{
    for (int i = 0; i < _count; i++)
    {
        if (login == _participants[i].getLogin())
            return true;
    }

    return false;
}

bool Chat::compareName(string name)
{
    if (name == "all")
        return true;
    
    for (int i = 0; i < _count; i++)
    {
        if (name == _participants[i].getName())
            return true;
    }

    return false;
}

void Chat::addParticipant(string login, string password, string name)
{
    Participants participant;
    
    participant.setLogin(login);
    participant.setPassword(password);
    participant.setName(name);
    participant.setPasswordHash(password);

    vector<Participants>::iterator it = _participants.begin() + _count;
    vector<Participants>::iterator newIt = _participants.insert(it, participant);

    _count++;
}

void Chat::writeParticipantsFile(string login, string password, string name)
{
    fstream participant_file = fstream("Participants.txt", ios::in | ios::out);

    filesystem::permissions("Participants.txt",
        filesystem::perms::group_all | filesystem::perms::others_all,
        filesystem::perm_options::remove);

    if (!participant_file)
        participant_file = fstream("Participants.txt", ios::in | ios::out | ios::trunc);

    if (participant_file)
    {
        participant_file.seekp(0, std::ios_base::end);
        participant_file << login << ' ' << password << ' ' << name << endl;
    }
    else
    {
        cout << "Could not open file Participants.txt !" << endl;
    }
}

bool Chat::SignIn(string login, string password)
{
    uint hash = findHash(password);
    
    for (int i = 0; i < _count; i++)
    {
        if (login == _participants[i].getLogin())
        {
            // Первый вариант
            /*if (password == _participants[i].getPassword())
            {
                iSender = i;
                return true;
            }
            else
            {
                return false;
            }*/

            // Второй вариант
            if (hash == _participants[i].getPasswordHash())
            {
                iSender = i;
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}

void Chat::sendMessage(string name, string text)
{
    if (name == "all")
    {
        for (int i = 0; i < _count; i++)
        {
            if (i != iSender)
            {
                _participants[i].recordMessage(_participants[iSender].getName(), text);
            }
        }
    }
    else
    {
        for (int i = 0; i < _count; i++)
        {
            if (name == _participants[i].getName())
            {
                _participants[i].recordMessage(_participants[iSender].getName(), text);
                break;
            }
        }
    }
}

void Chat::findFreeLogin(string keyword)
{
    string res;
    
    loginSource.findPrefixWords(keyword, &res);

    if (res.at(0) == ' ')
    {
        cout << "No words with matching keyword found " << endl;
    }
    else
    {
        string newLogin;

        cout << "Words with keyword: " << endl;
        
        for (size_t i = 0; i < res.length(); i++)
        {
            
            if (res.at(i) == ' ')
            {
                bool key = compareLogin(newLogin);
                if (!key)
                    cout << newLogin + ' ';

                newLogin.clear();
            }
            else
                newLogin += res.at(i);
        }
    }

    cout << endl;
}

uint Chat::findHash(string password)
{
    const char* charPassword = password.c_str();
    int length = strlen(charPassword);

    uint* hash = sha1(charPassword, (uint)length);

    return *hash;
}