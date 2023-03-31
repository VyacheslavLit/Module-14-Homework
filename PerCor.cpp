#include <iostream>
#include <ctime>
#include <fstream>
#include "PerCor.h"
#include <Windows.h>

/*
	  --- �������� ����� ������ ������ ��������� PerCop ---
		LoginMenu - ���� � ����������� ������������.
		� ������ ������ �������������� ����� � ���������� ����� � ���������
	���  �����  �������  �  �������, ����������� ����� ������������ � �����
	� ���������� ����.
		������������    ��������    ���������    currentUser_   (����������
	������������)   �������   ������������,  ��  ����  ��������  ����������
	�������.
		����   �������������   �����������   ��   �����   User.txt,   �����
	������������ ����������� � ������ ����.
*/
void PerCor::loginMenuPC()
{
	currentUser_ = nullptr;
	string operation;
	getUsersFile();
	while (true)
	{
		system("cls");
		cout << "1. ����.\n2. �����������.\n0. ����� � ���������� ����.\n";
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
		//��� ����������� �������������� ���������� �� ������ ��� � �������.
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
		cout << "����� �� ��������. ��������� �������.\n";
		system("pause");
		continue;
	}
}

/*
	  --- �������� ����� ������ ������ ��������� PerCop ---
		userMenuPC - ����� �������� �� ���������.
		�����  �����  ����  ����������  �� ��� ������� ��������� ��� ������
	����� ���������.

*/
void PerCor::userMenuPC()
{
	system("cls");
	/*
	����� ��������� �������� ������ ��������� �� ����� messagesPC.txt,
	����� ���������� ����� ��������� ��� �������.
	*/
	getMessagePC_File();
	//	perCorParty_ = {};
		/*
		����� � ������� ������ perCorParty, ����������� ������ perCorParty_(������ �������������, � �������� ������� ���������),
		����� � ��������� ������� ������������� �� ����� ������� � ��� ��������� ��� �������.
		*/
	perCorParty();
	getUsersFile();
	cout << "������, " << currentUser_->getName() << ".\n� ��� ������� ��������� � " << perCorParty_.size() - 1 << " ��������(��, ��, ���).\n";
	unsigned int tmp = 0;
	for (auto name : perCorParty_)
	{
		_party = getUserByName(name);
		if (tmp > 0) cout << tmp << ". " << name;
		if (_party != nullptr) if (_party->getBan() == "true")cout << " (�������)";
		cout << endl;
		tmp++;
	}
	while (true)
	{
		cout << "�������� � ��� ���������� ���������, " << (perCorParty_.size()) << " ��� ���������� ������ ���������, 0 - �����\n";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		/*
		� ������� ������ eraseParty �� ���������� ������� �������� ���� �� ��� ��� ������,
		��� ������������� ������ ������.

//		eraseParty();*/
		if (tmp > (perCorParty_.size()))
		{
			cout << "������ �����.\n������� �� 0 �� " << (perCorParty_.size()) << endl;
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
	  --- �������� ����� ������ ������ ��������� PerCop ---
		showPC   -   �����   ��  �����  ���������  �  ���������  ����������
	� ������������ ����������� ���������.
		�  ������  ������  ������������  ����������� ����, �������  �������
	���������  �  ����������  �  ���� ����������� �������� ����� ���������,
	�������� ���������,	����� ��������� ����� ��������� �� ���������.
*/
void PerCor::showPC()//const
{
	string txt;
	/*
	���������� ������������ ����� ������������ ������������ ������
	� ����������� ��������� ���������.
	*/
	while (true)
	{
		chat();
		cout << "������� ��������� ���: 1 �������� ���������, 0 ����� �� ���������.\n";
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
	  --- �������� ����� ������ ������ ��������� PerCop ---
		loginAdminPC - ���� � ������ ��������� ������ �� ������ Admin.
		�  ������  ������  ������������ �������� ��������� currentUser_ ���
	admin, �� ���� �������� ���������� �������.
		����   �������������   �����������   ��   �����   User.txt.
*/
void PerCor::loginAdminPC()
{
	string login = "admin";
	getUsersFile();
	currentUser_ = getUserByLogin(login);
	me_ = currentUser_->getName();
}




/*
	  --- ��������������� ����� ������ loginMenuPC ---
		getUsersFile - �������� ������������� �� ����� User.txt.
		�  �����  ������  ��  ���������  ������  User,  �������  ����������
	��  �����  User.txt.  ���  ����  ����������  �������� �� ������ � �����
	� ������ ���� �� ������ ������ �������������.
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
			���������, �������� �� ����, � ���� �� �� �������� ���� �����������
		��������� ��������, ����� ���������� �������������� �������� ���� �������������.
		*/
		if (!inf)
		{
			while (true)
			{
				cout << "��������� �������� ���� �������������, �������� ����� ������ ��� ������� ��� \n0 - ��� ����������� ��� �������� ���� �������������.: ";
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
	  --- ��������������� ����� ������ loginMenuPC ---
		login - ���� � �������� �� ������ � ������.
		�  �����  ������  ������������ ������ ����������� ������ ���� �����
	� ������. ������������ �� ��������, ��� ������� ����� ���������� � ����
	�������������     ����������    �������    ������������    currentUser_
	�  �������������  ����������  me_  ��� ������� ������������. ���� �����
	�����   ����������   ���  ������  ��  �������������  ���������  ������,
	��������� ������, � ����������� �������� ����.
*/
void PerCor::login() {
	string login, password;
	do
	{
		system("cls");
		cout << "��� ����� ������� ����� � ������, ��� 0 ��� ������:\n";
		cout << "�����: ";
		cin >> login;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		cout << "������: ";
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
			cout << "����� ��� ������ ������� �� �����\n��������� ����.\n";
			system("pause");
			continue;
		}
		if (currentUser_->getBan() == "true")
		{
			currentUser_ = nullptr;
			cout << "������ ������������ �������\n���������� ������� ������������.\n";
			system("pause");
			continue;
		}
		me_ = currentUser_->getName();
	} while (!currentUser_);
}

/*
	  --- ��������������� ����� ������ loginMenuPC ---
		registration - ���������� ������������������ � ���� �������������.
		�  �����  ������  ������������  ������  �����������  �������� �����
	������� ������, ����� �������� ����� ������, ������ � �����.
		������������  ��������  ������ � ����� �� ������������, ��� �������
	��������  �  ����  �������������,  ������  �����������  ���������  ����
	�������������� ������.
		��  ����������� ����� ���������� �������������� ����� setUsersFile,
	���   ����������  ������  ������������  �  ����  �  ����������  �������
	� ���������� ����.
*/
void PerCor::registration()
{
	string login, password, name;
	while (true)
	{
		system("cls");
		cout << "��� ����������� ������ ������������ ������� �����, ������ � ��� ������������.\n";
		cout << "�����: ";
		cin >> login;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (getUserByLogin(login) || login == "Admin" || login == "0")throw ExpLogin();
		cout << "\n������: ";
		cin >> password;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		cout << "\n���: ";
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
	  --- ��������������� ����� ������ registration ---
		setUsersFile  - ���������� ������������������ � ���� �������������.
		�  ����� ������ ������ ������������ ��������� � ������ registration
	�������� � ���� Users.txt � ����������� ����� ������ � ������ User. ���
	����  �����������,  ���  ����  ������  ���  ������.  ��� ������� ������
	��������  �����,  ������������  ������  �����������  ���������  �������
	���������� ���� ������..
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
				cout << "��������� ������� ��������� ������, �������� ����� ������ ��� ������� ��� \n0 - ��� ����������� ��� �������� ���� �������������.: ";
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
	  --- ��������������� ����� ������ userMenuPC ---
		getMessagePC_File  - ���������� ��������� �� ����� messagesPC.txt �
	��������  ��  �  ������  messagePC_,  ���  ����  ��������������  ������
	�������� �����.
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
				cout << "��������� �������� ���� ������ ���������, �������� ����� ������ ��� �������. ";
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
	  --- ��������������� ����� ������ userMenuPC ---
		perCorParty    -   �����������   �������   perCorParty_   (��������
	�������������  �  ��������  ���  ������  ���������),  �� ������ �������
	messagePC_ (������������ ���������).
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
	  --- ��������������� ����� ������ userMenuPC ---
		addParty - ���������� � ������ perCorParty_ (�������� �������������
	���������   ���   ������   ���������),   ������   ���������.  ���  ����
	�����������, ������� ��� ���, ��������� � ������ ����������.
*/
void PerCor::addParty()
{
	unsigned int tmp;
	while (true)
	{
		tmp = 0;
		getUsersFile();
		cout << "������� ��������� ���������:\n";
		for (auto& user : users_)
		{
			cout << ++tmp << ". " << user.getName();
			if (user.getBan() == "true")cout << " (�������)";
			for (auto& name : perCorParty_)
			{
				if (name == user.getName())
				{
					cout << " (��������� �������)";
					break;
				}
			}
			if (user.getName() == currentUser_->getName())
			{
				cout << " (�)";
			}
			cout << endl;
		}
		cout << "� ��� ������ ���������? �������� �� 1 �� " << (users_.size()) << ", 0 - �����.\n";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp > users_.size())
		{
			cout << "������������ ����, ��������� �������.\n";
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
	  --- ��������������� ����� ������ addParty ---
		expParty - �������� �� ������� �� ��������� � ��������� ��������� �
	�� ���������� �� ������������ �������� ��� � �����.
*/
bool PerCor::expParty(string name)
{
	for (auto names : perCorParty_)
	{
		if (name == names)
		{
			cout << "� ���� ������������� ��������� ��� �������.\n��������� �����\n";
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
			cout << "��� �� ����������� �������� ��� � �����?\n";
			system("pause");
			return false;
		case 1:
			cout << "���� �� �������� � ��������, ���������� � ����������\n";
			system("pause");
			return false;
		case 2:
			cout << "� ����� ����� ��������� �� ��������\n";
			system("pause");
			return false;
		default:
			cout << "������ �����, ��������� �������\n";
			system("pause");
			return false;
		}
	}
	return true;
}

/*
	  --- ��������������� ����� ������ showPC ---
		chat  -  �����  �� ����� ��������� � ��������� ������������� � ����
	�������	������ �� ������� messagePC_.
*/
void PerCor::chat()
{
	system("cls");
	string from, to;
	getMessagePC_File();
	cout << "��������� � " << party_ << "\n-----------------------------------------------------------------------\n";
	for (auto& mess : messagePC_)
	{
		/*
		���������� ������� ���������, ��� ����������� ������ ��� ���������,
		������� ��������� � ������ ��������� (������������ � ����������)
		*/
		if ((me_ == mess.getFrom() && party_ == mess.getTo()) || (me_ == mess.getTo() && party_ == mess.getFrom()))
		{
			if (me_ == mess.getFrom())
			{
				from = "(�)";
				to = mess.getTo();
				//				if (party_.getBan()=="true")
			}
			else
			{
				from = mess.getFrom();
				to = "(���)";
			}
			mess.getDelete() == "false" ? cout << mess.getTime() << "\t" << from << " -> " << to << "\t" << mess.getText() << endl :
				cout << mess.getTime() << "\t" << from << " -> " << to << "\t" << "��������� ������� �����������" << endl;
		}
	}
	cout << "-----------------------------------------------------------------------" << endl;
}

/*
	  --- ��������������� ����� ������ showPC ---
		addMessage - ���������� ������ ��������� � ���������, � �����������
	������� ��������� � ���� messagesPC.txt � � ��������� messagePC_.
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
				cout << "��������� ������� ��������� ���������, �������� ����� ������ ��� ������� ��� \n0 - ��� ����������� ��� �������� ���������.: ";
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
	  --- ��������������� ����� ---
		expCin - ����� ��������� ������ ��� ������������ ��������� cin.
		�  �����  ������  ������������  ������� ������ �����, �������������
	������ � ��������� ��������� ������������ ��������� �� ������.
*/
void PerCor::expCin()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << "������ �����, ��������� �������.\n";
	system("pause");
};


//�������� ������ �� �������
shared_ptr<User> PerCor::getUserByLogin(const string& login)const
{
	for (auto& user : users_)
	{
		if (login == user.getLogin())return make_shared<User>(user);
	}
	return nullptr;
}

//�������� ����� �� �������.
shared_ptr<User> PerCor::getUserByName(const string& name)const
{
	for (auto& user : users_)
	{
		if (name == user.getName()) return make_shared<User>(user);
	}
	return nullptr;
}
