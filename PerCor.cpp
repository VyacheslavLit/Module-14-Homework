#include <iostream>
#include <ctime>
#include <fstream>
#include "PerCor.h"
#include <Windows.h>

/*
	  --- ОСНОВНОЙ МЕТОД класса личной переписки PerCop ---
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
void PerCor::loginMenuPC()
{
	currentUser_ = nullptr;
	string operation;
	getUsersFile();
	while (true)
	{
		system("cls");
		cout << "1. Вход.\n2. Регистрация.\n0. Выход в предыдущее меню.\n";
		cin >> operation;
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
	  --- ОСНОВНОЙ МЕТОД класса личной переписки PerCop ---
		userMenuPC - выбор опонента по переписке.
		Выбор  может  быть  произведен  из уже начатых переписок или начата
	новая переписка.

*/
void PerCor::userMenuPC()
{
	system("cls");
	/*
	Далее происходт загрузка личных переписок из фойла messagesPC.txt,
	чтобы определить какие переписки уже открыты.
	*/
	getMessagePC_File();
	//	perCorParty_ = {};
		/*
		далее с помощью метода perCorParty, заполняется вектор perCorParty_(список пользователей, с которыми открыта переписка),
		чтобы в выводимой таблице пользователей мы могли указать с кем переписка уже ведется.
		*/
	perCorParty();
	getUsersFile();
	cout << "Привет, " << currentUser_->getName() << ".\nУ вас имеется переписка с " << perCorParty_.size() - 1 << " участник(ов, ом, ами).\n";
	unsigned int tmp = 0;
	for (auto name : perCorParty_)
	{
		_party = getUserByName(name);
		if (tmp > 0) cout << tmp << ". " << name;
		if (_party != nullptr) if (_party->getBan() == "true")cout << " (Забанен)";
		cout << endl;
		tmp++;
	}
	while (true)
	{
		cout << "Выберите с кем продолжить переписку, " << (perCorParty_.size()) << " для добавления нового участника, 0 - выход\n";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		/*
		с помощью метода eraseParty мы производим очистку опонента если он уже был выбран,
		что предотвратить утечку памяти.

//		eraseParty();*/
		if (tmp > (perCorParty_.size()))
		{
			cout << "Ошибка ввода.\nВведите от 0 до " << (perCorParty_.size()) << endl;
			system("pause");
			continue;
		}
		if (tmp == 0) break;
		if (perCorParty_.size() > 1) if (tmp < perCorParty_.size()) {
			setParty(perCorParty_[tmp]);
			break;
		}
		if (tmp == (perCorParty_.size()))
		{
			addParty();
			break;
		}
	}

}

/*
	  --- ОСНОВНОЙ МЕТОД класса личной переписки PerCop ---
		showPC   -   вывод   на  экран  переписки  с  выбранным  оппонентом
	с возможностью продолжения переписки.
		В  данном  методе  предоставлен  бесконечный цикл, который  выводит
	переписку  с  оппонентом  и  дает возможность написать новое сообщение,
	обновить переписку,	чтобы проверить новые сообщения от оппонента.
*/
void PerCor::showPC()//const
{
	string txt;
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
	  --- ОСНОВНОЙ МЕТОД класса личной переписки PerCop ---
		loginAdminPC - вход в личную переписку админа из класса Admin.
		В  данном  методе  определяется значение указателя currentUser_ как
	admin, от лица которого происходит общение.
		База   пользователей   загружается   из   файла   User.txt.
*/
void PerCor::loginAdminPC()
{
	string login = "admin";
	getUsersFile();
	currentUser_ = getUserByLogin(login);
	me_ = currentUser_->getName();
}




/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода loginMenuPC ---
		getUsersFile - загрузка пользователей из файла User.txt.
		В  даном  методе  мы  заполняем  вектор  User,  данными  считанными
	из  файла  User.txt.  При  этом  происходит  проверка на доступ к файлу
	в случае если он открыт другим пользователем.
*/
void PerCor::getUsersFile()
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
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода loginMenuPC ---
		login - вход в прорамму по логину и паролю.
		В  даном  методе  пользователю дается возможность ввести свой логин
	и пароль. Производится их проверка, при наличии такой комбинации в базе
	пользователей     выбирается    текущий    пользователь    currentUser_
	и  присваивается  переменной  me_  имя текущео пользователя. если такой
	логин   отсутсвует   или  пароль  не  соответствует  введеному  логину,
	выводится ошибка, и предложение повториь ввод.
*/
void PerCor::login() {
	string login, password;
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
			cout << "Данный пользователь забанен\nПопробуйте другова пользователя.\n";
			system("pause");
			continue;
		}
		me_ = currentUser_->getName();
	} while (!currentUser_);
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода loginMenuPC ---
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
void PerCor::registration()
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
void PerCor::setUsersFile(string login, string password, string name)
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
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода userMenuPC ---
		getMessagePC_File  - считывание сообщений из файла messagesPC.txt и
	внесение  их  в  вектор  messagePC_,  при  этом  обрабатывается  ошибка
	открытия файла.
*/
void PerCor::getMessagePC_File()
{
	char tmp;
	messagePC_.resize(1);
	string delTMP;
	string timeTMP;
	string fromTMP;
	string toTMP;
	string txtTMP;
	while (true)
	{
		system("cls");
		ifstream inf("messagesPC.txt");
		if (!inf)
		{
			while (true)
			{
				cout << "Неудачная загрузка базы личных сообщений, наберите любой символ для повтора. ";
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
			getline(inf, toTMP);
			if (!inf) break;
			getline(inf, txtTMP);
			MessagePC messagePC = MessagePC(delTMP, timeTMP, fromTMP, toTMP, txtTMP);
			messagePC_.push_back(messagePC);
		}
		inf.close();
		break;
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода userMenuPC ---
		perCorParty    -   составление   вектора   perCorParty_   (перечень
	пользователей  с  которыми  уже  начата  переписка),  на основе вектора
	messagePC_ (персональная переписка).
*/
void PerCor::perCorParty()
{
	string tmp_name;
	bool tmp;
	for (auto& MessagesPC : messagePC_)
	{


		tmp = false;
		if (MessagesPC.getFrom() == me_)tmp_name = MessagesPC.getTo();
		if (MessagesPC.getTo() == me_) tmp_name = MessagesPC.getFrom();
		for (auto& name : perCorParty_)
		{
			if (name == tmp_name)
			{
				tmp = true;
				break;
			}
		}
		if (tmp == false) perCorParty_.push_back(tmp_name);
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода userMenuPC ---
		addParty - добавление в вектор perCorParty_ (перечень пользователей
	скоторыми   уже   начата   переписка),   нового   оппонента.  При  этом
	проверяется, открыта или нет, переписка с данным оппонентом.
*/
void PerCor::addParty()
{
	unsigned int tmp;
	while (true)
	{
		tmp = 0;
		getUsersFile();
		cout << "Имеются следующие участники:\n";
		for (auto& user : users_)
		{
			cout << ++tmp << ". " << user.getName();
			if (user.getBan() == "true")cout << " (Забанен)";
			for (auto& name : perCorParty_)
			{
				if (name == user.getName())
				{
					cout << " (переписка открыта)";
					break;
				}
			}
			if (user.getName() == currentUser_->getName())
			{
				cout << " (я)";
			}
			cout << endl;
		}
		cout << "С кем начать переписку? Выберите от 1 до " << (users_.size()) << ", 0 - выход.\n";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp > users_.size())
		{
			cout << "Некорректный ввод, повторите попытку.\n";
			system("pause");
			continue;
		}
		if (tmp == 0)break;
		if (PerCor::expParty(users_[tmp - 1].getName()))
		{
			party_ = users_[tmp - 1].getName();
			break;
		}
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода addParty ---
		expParty - проверка не открыта ли переписка с выбранным опонентом и
	не собирается ли пользователь говорить сам с собой.
*/
bool PerCor::expParty(string name)
{
	for (auto names : perCorParty_)
	{
		if (name == names)
		{
			cout << "С этим пользователем переписка уже открыта.\nПовторите выбор\n";
			system("pause");
			return false;
		}
	}
	if (name == currentUser_->getName())
	{
		srand(static_cast<unsigned int>(time(0)));
		int tmp = (rand() % 3);
		switch (tmp)
		{
		case 0:
			cout << "Как ты собираешься говорить сам с собой?\n";
			system("pause");
			return false;
		case 1:
			cout << "Если вы говорите с зеркалом, обратитесь к психиатору\n";
			system("pause");
			return false;
		case 2:
			cout << "С самим собой переписка не доступна\n";
			system("pause");
			return false;
		default:
			cout << "Ошибка ввода, повторите попытку\n";
			system("pause");
			return false;
		}
	}
	return true;
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода showPC ---
		chat  -  вывод  на экран переписки с выбранным пользователем в виде
	таблицы	изходя из вектора messagePC_.
*/
void PerCor::chat()
{
	system("cls");
	string from, to;
	getMessagePC_File();
	cout << "Переписка с " << party_ << "\n-----------------------------------------------------------------------\n";
	for (auto& mess : messagePC_)
	{
		/*
		Происходит выборка сообщений, для отображения только тех сообщений,
		которые относятся к данной переписке (пользователя с оппонентом)
		*/
		if ((me_ == mess.getFrom() && party_ == mess.getTo()) || (me_ == mess.getTo() && party_ == mess.getFrom()))
		{
			if (me_ == mess.getFrom())
			{
				from = "(Я)";
				to = mess.getTo();
				//				if (party_.getBan()=="true")
			}
			else
			{
				from = mess.getFrom();
				to = "(Мне)";
			}
			mess.getDelete() == "false" ? cout << mess.getTime() << "\t" << from << " -> " << to << "\t" << mess.getText() << endl :
				cout << mess.getTime() << "\t" << from << " -> " << to << "\t" << "Сообщение удалено модератором" << endl;
		}
	}
	cout << "-----------------------------------------------------------------------" << endl;
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода showPC ---
		addMessage - добавление нового сообщения в переписку, с добавлением
	данного сообщения в файл messagesPC.txt и в контейнер messagePC_.
*/
void PerCor::addMessage(string txt)
{
	char tmp;
	while (true)
	{
		system("cls");
		ofstream outf("messagesPC.txt", ios::app);
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
		outf << "false\n" << time() << "\n" << me_ << "\n" << party_ << "\n" << txt << "\n";
		outf.close();
		MessagePC messagePC = MessagePC("false", time(), me_, party_, txt);
		messagePC_.push_back(messagePC);
		break;
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД ---
		expCin - метод отработки ошибки при испльзовании оператора cin.
		В  даном  методе  производится  очистка буфера ввода, игнорирование
	ошибок и выводится сообщение пользователю сообщения об ошибке.
*/
void PerCor::expCin()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << "Ошибка ввода, повторите попытку.\n";
	system("pause");
};


//проверка логина на повторы
shared_ptr<User> PerCor::getUserByLogin(const string& login)const
{
	for (auto& user : users_)
	{
		if (login == user.getLogin())return make_shared<User>(user);
	}
	return nullptr;
}

//проверка имени на повторы.
shared_ptr<User> PerCor::getUserByName(const string& name)const
{
	for (auto& user : users_)
	{
		if (name == user.getName()) return make_shared<User>(user);
	}
	return nullptr;
}
