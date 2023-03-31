#include <iostream>
#include <ctime>
#include <fstream>
#include "Chat.h"
#include "PerCor.h"
#include "Windows.h"

/*
	  --- �������� ����� ������ ��������� Chat ---
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
void Chat::loginMenu()
{
	currentUser_ = nullptr;
	string operation;
	getUsersFile();
	while (true)
	{
		system("cls");
		cout << "1. ����.\n2. �����������.\n0. ����� � ���������� ����.\n";
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
	  --- �������� ����� ������ ��������� Chat ---
		showChat  -  �����  ��  �����  ��������� � ������������ �����������
	���������.
		�  ������  ������  ������������  ����������� ����, �������  �������
	���������   �  ����  �����������  ��������  �����  ���������,  ��������
	���������, ����� ��������� ����� ���������.
*/
void Chat::showChat()//const
{
	string txt;
	system("cls");
	getMessage_File();
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
	  --- �������� ����� ������ ��������� Chat ---
		showChatDict  -  �����  ��  �����  ��������� � ������������ �����������
	��������� � �������������� �������.
		�  ������  ������  ������������  ����������� ����, �������  �������
	���������   �  ����  �����������  ��������  �����  ��������� (�������� � 
	�������������� �������),  �������� 	���������, ����� ��������� ����� ���������.
*/

void Chat::showChatDict(Dict dict)//const
{
	string mes;
	char tmp;
	system("cls");
	getMessage_File();
	/*
	���������� ������������ ����� ������������ ������������ ������
	� ����������� ��������� ���������.
	*/
	while (true)
	{
		system("cls");
		chat();
		mes=dict.messeng();
		if (mes != "") addMessage(mes);
		cout << "���������� ��������� ����� �����, 0 ����� �� ���������.\n";
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
	  --- ��������������� ����� ������ LoginMenu ---
		getUsersFile - �������� ������������� �� ����� User.txt.
		�  �����  ������  ��  ���������  ������  User,  �������  ����������
	��  �����  User.txt.  ���  ����  ����������  �������� �� ������ � �����
	� ������ ���� �� ������ ������ �������������.
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
	  --- ��������������� ����� ������ LoginMenu ---
		login - ���� � �������� �� ������ � ������.
		�  �����  ������  ������������ ������ ����������� ������ ���� �����
	� ������. ������������ �� ��������, ��� ������� ����� ���������� � ����
	�������������     ����������    �������    ������������    currentUser_
	�  �������������  ����������  me_  ��� ������� ������������. ���� �����
	�����   ����������   ���  ������  ��  �������������  ���������  ������,
	��������� ������, � ����������� �������� ����.
*/
void Chat::login() {
	string login, password;
	//	char operation;
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
			cout << "������������ �������\n���������� ������� ������������.\n";
			system("pause");
			continue;
		}
		me_ = currentUser_->getName();
	} while (!currentUser_);
}

/*
	  --- ��������������� ����� ������ LoginMenu ---
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
void Chat::registration()
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
	  --- ��������������� ����� ������ showChat ---
		getMessagePC_File  -  ����������  ��������� �� ����� messages.txt �
	��������   ��   �  ������  message_,  ���  ����  ��������������  ������
	�������� �����.
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
				cout << "��������� �������� ���� ������ ���������, �������� ����� ������ ��� �������";
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
	  --- ��������������� ����� ������ showChat ---
		chat  -  �����  �� ����� ��������� � ���� ������� ������ �� �������
	message_ � ��� �����������.
*/
void Chat::chat()
{
	getUsersFile();
	string from;
	getMessage_File();
	cout << "����� ���: " << "\n-----------------------------------------------------------------------\n";
	for (auto& mess : message_)
	{
		user_ = getUserByName(mess.getFrom());
		me_ == mess.getFrom() ? from = "(�)" : from = mess.getFrom();
		if (user_ != nullptr) if (user_->getBan() == "true")from += " (�������)";
		if (mess.getTime() != "") mess.getDelete() == "false" ? cout << mess.getTime() << "\t" << from << "\t" << mess.getText() << endl :
			cout << mess.getTime() << "\t" << from << "\t" << "��������� ������� �����������" << endl;
	}
	cout << "-----------------------------------------------------------------------" << endl;
}

/*
	  --- ��������������� ����� ������ showChat ---
		addMessage - ���������� ������ ��������� � ���������, � �����������
	������� ��������� � ���� messages.txt � � ��������� message_.
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
		outf << "false\n" << time() << "\n" << me_ << "\n" << txt << "\n";
		outf.close();
		Message message = Message("false", time(), me_, txt);
		message_.push_back(message);
		break;
	}
}



/*
	  --- ��������������� ����� ---
		expCin - ����� ��������� ������ ��� ������������ ��������� cin.
		�  �����  ������  ������������  ������� ������ �����, �������������
	������ � ��������� ��������� ������������ ��������� �� ������.
*/
void Chat::expCin()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << "������ �����, ��������� �������.\n";
	system("pause");
};

//�������� ������ �� �������
shared_ptr<User> Chat::getUserByLogin(const string& login)const
{
	for (auto& user : users_)
	{
		if (login == user.getLogin())return make_shared<User>(user);
	}
	return nullptr;
}

//�������� ����� �� �������.
shared_ptr<User> Chat::getUserByName(const string& name)const
{
	for (auto& user : users_)
	{
		if (name == user.getName()) return make_shared<User>(user);
	}
	return nullptr;
}
