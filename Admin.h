#pragma once
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include "PerCor.h"
#include "Message.h"



/*
	 ласс Admin - основной класс обеспечивающий администрирование.

	login_ - переменна€ индикатор входа							-- вспомогательные методы - метода LoginMenu --
	numAdmin_ - пор€дковый є в векторе			       inPassword - ввод парол€
	users_ - контейнер пользователей                   passChange - смена парол€
	message_ - контейнер с перепиской			       registration - регистраци€ пользовател€
	currentAdmin_ - указатель на админа				   setUsersFile (дополнительный метод метода LoginMenu) -
				из общего контейнера рользователе					внесение зарегистриррованного пользовател€ в файл
																-- второстепенные методы - метода adminMenu --
													   ban - наложение, сн€тие бана
			--- ќ—Ќќ¬Ќџ≈ ћ≈“ќƒџ ---					   showChat - вывод чата на экран
	LoginMenu - вход администратора					   getMessage_File - заполнение вектора сообщений из файла
	adminMenu - основное мен€ дл€ работы			   delMess - пометка сообщени€ как удаленного
				администатора						   upDelMess - сн€тие отметки об удалении с сообщени€
													   setMessage_File - выгрузка сообщений из вектора в файл.
													   addMessage - добавление сообщени€ в чат и сохранени€ его в контейнер переписки
	getAdminByLogin - указатель провер€ющий логин				-- вспомогательные методы --
		на предмеет повторов						   expCin - обработка ошибок при использовании оператора cin
	getAdminByName - указатель провер€ющий им€		   getUsersFile - загрузкапользователей из файла
		на предмеет повторов						   setNumAdmin - присвоение значени€ numAdmin_
*/
class Admin
{
	bool login_{ false };
	int numAdmin_;
	vector<User> users_;
	vector<Message> message_;
	shared_ptr<User>currentAdmin_ = nullptr;

public:
	void loginMenu();
	void adminMenu();

	bool getLogin() { return login_; }
private:
	void inPassword();
	void passChange();
	bool setUsersFile();
	void ban();
	void showChat();
	void chat();
	void getMessage_File();
	void delMess();
	void upDelMess();
	bool setMessage_File();
	void addMessage(string txt);
	void expCin();
	void getUsersFile();
	void setNumAdmin(int numAdmin) { numAdmin_ = numAdmin; }


	shared_ptr<User> getAdminByLogin(const string& login);// const;
	shared_ptr<User> getAdminByName(const string& name)const;
}; 
