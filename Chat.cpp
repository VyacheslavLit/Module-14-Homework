#include <iostream>
#include <ctime>
#include <fstream>
#include "Chat.h"
#include "PerCor.h"
#include "Windows.h"

/*
	  --- ОСНОВНОЙ МЕТОД класса переписки Chat ---
		LoginMenu - вход и регистрацию пользователя.
		В данном методе предоставлется выбор и реализация Входа в переписку
	под  своим  логином  и  паролем, регистрация нвого пользователя и выход
	в предыдущее меню.
		Определяется    значение    указателя    currentUser_   (корректный
	пользователь)   текущий   пользователь,  от  лица  которого  происходит
	общение.
		База   пользователей   загружается   из   файла   User.txt,   новые
	пользователи добавляются в данный файл.
*/
void Chat::loginMenu()
{
	currentUser_ = nullptr;
	string operation;
	getUsersFile();
	while (true)
	{
		system("cls");
		cout << "1. Вход.\n2. Регистрация.\n0. Выход в предыдущее меню.\n";
		cin >> operation;
		cin.clear();
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (operation == "1")
		{
			login();
			break;
		}
		//При регистрации отрабатываются исключения на повтор имён и логинов.
		if (operation == "2")
		{
			try
			{
				registration();
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
				system("pause");
			}
			continue;
		}
		if (operation == "0")
		{
			break;
		}
		cout << "Выбор не пределен. Повторите попытку.\n";
		system("pause");
		continue;
	}
}

/*
	  --- ОСНОВНОЙ МЕТОД класса переписки Chat ---
		showChat  -  вывод  на  экран  переписки с возможностью продолжения
	переписки.
		В  данном  методе  предоставлен  бесконечный цикл, который  выводит
	переписку   и  дает  возможность  написать  новое  сообщение,  обновить
	переписку, чтобы проверить новые сообщения.
*/
void Chat::showChat()//const
{
	string txt;
	system("cls");
	getMessage_File();
	/*
	Применение бесконечного цикла обеспечивает непрерывнсть работы
	и возможность обновлять переписку.
	*/
	while (true)
	{
		chat();
		cout << "Введите сообщение или: 1 обновить переписку, 0 выйти из переписки.\n";
		getline(cin, txt);
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (txt == "1")continue;
		if (txt == "0")break;
		if (txt != "") addMessage(txt);
	}
}

/*
	  --- ОСНОВНОЙ МЕТОД класса переписки Chat ---
		showChatDict  -  вывод  на  экран  переписки с возможностью продолжения
	переписки с использованием словаря.
		В  данном  методе  предоставлен  бесконечный цикл, который  выводит
	переписку   и  дает  возможность  написать  новое  сообщение (возможно с 
	использованием словаря),  обновить 	переписку, чтобы проверить новые сообщения.
*/

void Chat::showChatDict(Dict dict)//const
{
	string mes;
	char tmp;
	system("cls");
	getMessage_File();
	/*
	Применение бесконечного цикла обеспечивает непрерывнсть работы
	и возможность обновлять переписку.
	*/
	while (true)
	{
		system("cls");
		chat();
		mes=dict.messeng();
		if (mes != "") addMessage(mes);
		cout << "Продолжить переписку любая буква, 0 выйти из переписки.\n";
		cin>> tmp;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
		}
		if (tmp == '0')break;
	}
}




/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода LoginMenu ---
		getUsersFile - загрузка пользователей из файла User.txt.
		В  даном  методе  мы  заполняем  вектор  User,  данными  считанными
	из  файла  User.txt.  При  этом  происходит  проверка на доступ к файлу
	в случае если он открыт другим пользователем.
*/
void Chat::getUsersFile()
{
	char tmp;
	string banTMP;
	string loginTMP;
	string passwordTMP;
	string nameTMP;
	while (true)
	{
		system("cls");
		ifstream inf("Users.txt");
		/*
			Проверяем, считался ли файл, и если он не считался даем возможность
		повторить операцию, чтобы обеспечить обязательность загрузки базы пользователей.
		*/

		if (!inf)
		{
			while (true)
			{
				cout << "Неудачная загрузка базы пользователей, наберите любой символ для повтора или \n0 - для продолжения без загрузки базы пользователей.: ";
				cin >> tmp;
				if (cin.fail())
				{
					expCin();
					inf.close();
					continue;
				}
				break;
			}
			if (tmp == '0') break;
			continue;
		}

		while (inf)
		{
			inf >> banTMP;
			if (!inf) break;
			inf >> loginTMP;
			if (!inf) break;
			inf >> passwordTMP;
			if (!inf) break;
			inf >> nameTMP;
			if (getUserByLogin(loginTMP) || getUserByName(nameTMP)) continue;
			User user = User(banTMP, loginTMP, passwordTMP, nameTMP);
			users_.push_back(user);
		}
		inf.close();
		break;
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода LoginMenu ---
		login - вход в прорамму по логину и паролю.
		В  даном  методе  пользователю дается возможность ввести свой логин
	и пароль. Производится их проверка, при наличии такой комбинации в базе
	пользователей     выбирается    текущий    пользователь    currentUser_
	и  присваивается  переменной  me_  имя текущео пользователя. если такой
	логин   отсутсвует   или  пароль  не  соответствует  введеному  логину,
	выводится ошибка, и предложение повториь ввод.
*/
void Chat::login() {
	string login, password;
	//	char operation;
	do
	{
		system("cls");
		cout << "Для входя введите логин и пароль, или 0 для выхода:\n";
		cout << "Логин: ";
		cin >> login;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		cout << "Пароль: ";
		cin >> password;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (login == "0" || password == "0") break;
		currentUser_ = getUserByLogin(login);
		if (currentUser_ == nullptr || password != currentUser_->getPassword())
		{
			currentUser_ = nullptr;

			cout << "Логин или пароль введены не верно\nПовторите ввод.\n";
			system("pause");
			continue;
		}
		if (currentUser_->getBan() == "true")
		{
			currentUser_ = nullptr;
			cout << "Пользователь забанен\nПопробуйте другово пользователя.\n";
			system("pause");
			continue;
		}
		me_ = currentUser_->getName();
	} while (!currentUser_);
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода LoginMenu ---
		registration - добавление новогопользователя в базу пользователей.
		В  даном  методе  пользователю  дается  возможность  добавить новую
	учетную запись, путем введения своих логина, пароля и имени.
		Производится  проверка  логина и имени на уникальность, при наличии
	повторов  в  базе  пользователей,  дается  возможность  повторить  ввод
	скорректировав повтор.
		По  результатам ввода вызывается дополнительный метод setUsersFile,
	для   добавления  нового  пользователя  в  базу  и  происходит  возврат
	в предыдущее меню.
*/
void Chat::registration()
{
	string login, password, name;
	while (true)
	{
		system("cls");
		cout << "Для регистрации нового пользователя введите логин, пароль и имя пользователя.\n";
		cout << "Логин: ";
		cin >> login;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (getUserByLogin(login) || login == "Admin" || login == "0")throw ExpLogin();
		cout << "\nПароль: ";
		cin >> password;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		cout << "\nИмя: ";
		cin >> name;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (getUserByName(name) || name == "0") throw ExpName();
		cout << endl;
		break;
	}
	setUsersFile(login, password, name);
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода registration ---
		setUsersFile  - добавление новогопользователя в базу пользователей.
		В  даном методе данные пользователя введенные в методе registration
	вносятся в файл Users.txt и добавляется новая запись в вектор User. При
	этом  проверяется,  что  файл  открыт  без  ошибок.  При наличии ошибки
	открытия  файла,  пользователю  дается  возможность  повторить  попытку
	сохранения свои данных..
*/
void Chat::setUsersFile(string login, string password, string name)
{
	char tmp;
	while (true)
	{
		system("cls");
		ofstream outf("Users.txt", ios::app);
		if (!outf)
		{
			while (true)
			{
				system("cls");
				cout << "Неудачная попытка сохранить данные, наберите любой символ для повтора или \n0 - для продолжения без загрузки базы пользователей.: ";
				cin >> tmp;
				if (cin.fail())
				{
					expCin();
					outf.close();
					continue;
				}
				break;
			}
			if (tmp == '0') break;
			continue;
		}
		outf << "false " << login << " " << password << " " << name << " ";
		outf.close();
		User user = User("false", login, password, name);
		users_.push_back(user);
		break;
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода showChat ---
		getMessagePC_File  -  считывание  сообщений из файла messages.txt и
	внесение   их   в  вектор  message_,  при  этом  обрабатывается  ошибка
	открытия файла.
*/
void Chat::getMessage_File()
{
	char tmp;
	message_.resize(1);
	string delTMP;
	string timeTMP;
	string fromTMP;
	string txtTMP;
	while (true)
	{
		system("cls");
		ifstream inf("messages.txt");
		if (!inf)
		{
			while (true)
			{
				cout << "Неудачная загрузка базы личных сообщений, наберите любой символ для повтора";
				cin >> tmp;
				if (cin.fail())
				{
					expCin();
					inf.close();
					continue;
				}
				break;
			}
			continue;
		}
		while (inf)
		{
			getline(inf, delTMP);
			if (!inf) break;
			getline(inf, timeTMP);
			if (!inf) break;
			getline(inf, fromTMP);
			if (!inf) break;
			getline(inf, txtTMP);
			Message message = Message(delTMP, timeTMP, fromTMP, txtTMP);
			message_.push_back(message);
		}
		inf.close();
		break;
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода showChat ---
		chat  -  вывод  на экран переписки в виде таблицы изходя из вектора
	message_ с его обновлением.
*/
void Chat::chat()
{
	getUsersFile();
	string from;
	getMessage_File();
	cout << "Общий чат: " << "\n-----------------------------------------------------------------------\n";
	for (auto& mess : message_)
	{
		user_ = getUserByName(mess.getFrom());
		me_ == mess.getFrom() ? from = "(Я)" : from = mess.getFrom();
		if (user_ != nullptr) if (user_->getBan() == "true")from += " (Забанен)";
		if (mess.getTime() != "") mess.getDelete() == "false" ? cout << mess.getTime() << "\t" << from << "\t" << mess.getText() << endl :
			cout << mess.getTime() << "\t" << from << "\t" << "Сообщение удалено модератором" << endl;
	}
	cout << "-----------------------------------------------------------------------" << endl;
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода showChat ---
		addMessage - добавление нового сообщения в переписку, с добавлением
	данного сообщения в файл messages.txt и в контейнер message_.
*/
void Chat::addMessage(string txt)
{
	char tmp;
	while (true)
	{
		system("cls");
		ofstream outf("messages.txt", ios::app);
		if (!outf)
		{
			while (true)
			{
				system("cls");
				cout << "Неудачная попытка сохранить сообщение, наберите любой символ для повтора или \n0 - для продолжения без отправки сообщения.: ";
				cin >> tmp;
				if (cin.fail())
				{
					expCin();
					outf.close();
					continue;
				}
				break;
			}
			if (tmp == '0') break;
			continue;
		}
		outf << "false\n" << time() << "\n" << me_ << "\n" << txt << "\n";
		outf.close();
		Message message = Message("false", time(), me_, txt);
		message_.push_back(message);
		break;
	}
}



/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД ---
		expCin - метод отработки ошибки при испльзовании оператора cin.
		В  даном  методе  производится  очистка буфера ввода, игнорирование
	ошибок и выводится сообщение пользователю сообщения об ошибке.
*/
void Chat::expCin()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << "Ошибка ввода, повторите попытку.\n";
	system("pause");
};

//проверка логина на повторы
shared_ptr<User> Chat::getUserByLogin(const string& login)const
{
	for (auto& user : users_)
	{
		if (login == user.getLogin())return make_shared<User>(user);
	}
	return nullptr;
}

//проверка имени на повторы.
shared_ptr<User> Chat::getUserByName(const string& name)const
{
	for (auto& user : users_)
	{
		if (name == user.getName()) return make_shared<User>(user);
	}
	return nullptr;
}
