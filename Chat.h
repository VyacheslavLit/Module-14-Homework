#pragma once
#include <vector>
#include <iostream>
#include "Message.h"
#include "Dict.h"

class Dict;

/*
	 ласс Chat - основной класс обеспечивающий общую переписку.

	me_ - переменна€ определ€юща€ пользовател€              -- второстепенные методы - метода LoginMenu --
	users_ - контейнер пользователей					getUsersFile  -  загрузка  пользователей в контейнер из файла
	message_ - контейнер с перепиской					login - вход пользовател€
	currentUser_ - указатель на пользовател€ (мен€)		registration - регистраци€ пользовател€
			из общего контейнера пользователей				setUsersFile (дополнительный метод метода registration) -
																		внесение   зарегистрированного  пользовател€
		--- ќ—Ќќ¬Ќџ≈ ћ≈“ќƒџ ---											в файл
	LoginMenu - вход и регистрацию пользовател€				-- второстепенные методы - метода showChat --
	showChat - переписка								getMessage_File - загрузка переписки из файла
														chat - вывод переписки
	getUserByLogin - указатель провер€ющий логин		addMessage - добавление  сообщени€  в  чат  и  сохранени€ его
		на предмет повторов										в контейнер переписки
	getUserByName - указатель провер€ющий им€				-- вспомогательный метод --
		на предмет повторов								expCin - обработка ошибок при использовании оператора cin
*/
class Chat {
	string me_;
	vector<User> users_;
	vector<Message> message_;
	shared_ptr<User>user_ = nullptr;
	shared_ptr<User>currentUser_ = nullptr;

public:
	shared_ptr<User>getCurrentUser() const { return currentUser_; }
	void loginMenu();
	void showChat();
	void showChatDict(Dict dict);

private:
	void getUsersFile();
	void login();
	void registration();
	void setUsersFile(string, string, string);
	void getMessage_File();
	void chat();
	void addMessage(string txt);
	void expCin();

	shared_ptr<User> getUserByLogin(const string& login)const;
	shared_ptr<User> getUserByName(const string& name)const;
};

