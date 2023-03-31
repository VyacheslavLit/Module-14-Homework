#include "Admin.h"

/*
	  --- �������� ����� ������ �������������� Admin ---
		LoginMenu - ���� ��������������.
		�   ������   ������   ��������������  �����   ���   �����  �������,
	����������� ��� �������� � ����� � ���������� ����.
*/
void Admin::loginMenu()
{
	string tmp;
	while (true)
	{
		system("cls");
		cout << "1. ���� ������.\n2. ����� ������.\n0. ����� � ���������� ����.\n";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp == "1")
		{
			inPassword();
			break;
		}
		if (tmp == "2")
		{
			passChange();
			continue;
		}
		if (tmp == "0")
		{
			break;
		}
		cout << "����� �� ��������. ��������� �������.\n";
		system("pause");
		continue;
	}
}

/*
	  --- �������� ����� ������ �������������� Admin ---
		adminMenu - ���� ��������������.
		�   ������   ������   ������������� ��������  �  �����  �����������
	�������� �� ������ ������.
		1. ��������� (������) ���� � ������������
		2. ����������������� ������ ���� (����������� ������� ���������  ��
	���������� �������)
		3. ������  ���������  �  ��������������  (������� �� ����� PerCor -
	������������ ���������)
*/
void Admin::adminMenu()
{
	string tmp;
	while (true)
	{
		system("cls");
		cout << "----- ��������� ������� ������������������ -----\n";
		cout << "1. ��������� (������) ���� � ������������.\n";
		cout << "2. ����������������� ������ ����.\n";
		cout << "3. ������ ��������� � ��������������\n";
		cout << "------------------------------------------------\n";
		cout << "�������� ����������� ������, 0 - ����� �� �����������������.\n";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp == "0") break;
		if (tmp == "1")
		{
			ban();
			continue;
		}
		if (tmp == "2")
		{
			showChat();
			continue;
		}
		if (tmp == "3")
		{
			PerCor perCor;
			perCor.loginAdminPC();
			perCor.userMenuPC();
			if (perCor.getParty() != "") perCor.showPC();
			continue;
		}
		cout << "\n����� �� ���������.\n��������� �������\n";
		system("pause");
	}
}




/*
	  --- ��������������� ����� ������ loginMenu ---
		loginMenu - ���� ������.
*/
void Admin::inPassword()
{
	string tmp;
	getUsersFile();
	while (!login_)
	{
		system("cls");
		cout << "������� ������, 0 - ����� ��� ����� ������: ";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp == "0") break;
		currentAdmin_ = getAdminByLogin("admin");
		if (tmp != currentAdmin_->getPassword())
		{
			cout << "������ ������ �� �����\n��������� ����.\n";
			system("pause");
			continue;
		}
		login_ = (true);
	}
}

/*
	  --- ��������������� ����� ������ loginMenu ---
		passChange - ����� ������.
*/
void Admin::passChange()
{
	string tmpPass;
	string tmpPassNew1;
	string tmpPassNew2;
	string tmp;
	getUsersFile();
	while (true)
	{
		system("cls");
		cout << "������� ����������� ������, 0 - ��� ������: ";
		cin >> tmpPass;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmpPass == "0")break;
		cout << "������� ����� ������: ";
		cin >> tmpPassNew1;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		cout << "��������� ����� ������: ";
		cin >> tmpPassNew2;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		currentAdmin_ = getAdminByLogin("admin");
		if (tmpPass != currentAdmin_->getPassword())
		{
			cout << "������ ������ �� �����\n��������� ����.\n";
			system("pause");
			continue;
		}
		if (tmpPassNew1 != tmpPassNew2)
		{
			cout << "\n����� ������ �� ���������\n��������� �������.\n";
			system("pause");
			continue;
		}
		tmp = currentAdmin_->getPassword();
		users_[Admin::numAdmin_].setPassword(tmpPassNew1);
		if (setUsersFile())
		{
			cout << "\n���������� ������ ���������.\n��������� �������.\n";
			users_[Admin::numAdmin_].setPassword(tmp);
			system("pause");
		}
		break;
	}
}

/*
	  --- ��������������� ����� ������ loginMenu ---
		setUsersFile - ���������� ������������� � ���� User.txt.
		� ����� ������ �� ��������� ������ �� ������� User, � ���� User.txt.
	��� ����  ����������  �������� �� ������ � ����� � ������ ���� �� ������
	������ �������������.
*/
bool Admin::setUsersFile()
{
	char tmp;
	while (true)
	{
		system("cls");
		ofstream outf("Users.txt", ios::out);
		if (!outf)
		{
			while (true)
			{
				system("cls");
				cout << "��������� ������� ��������� ������, �������� ����� ������ ��� ������� ��� \n0 - ��� ����������� ��� ����������\n";
				cin >> tmp;
				if (cin.fail())
				{
					expCin();
					outf.close();
					continue;
				}
				break;
			}
			if (tmp == '0') return true;
			continue;
		}
		for (auto& user : users_)
		{
			outf << user.getBan() << " " << user.getLogin() << " " << user.getPassword() << " " << user.getName() << " ";
		}
		outf.close();
		return (false);
	}
}

/*
	  --- ��������������� ����� ������ adminMenu ---
		ban - � ������ ������ ��������� ����������� ��������  � ����� ��� ��
	������������.

*/
void Admin::ban()
{
	int numTMP;
	string tmpBan;
	unsigned tmpUser;
	while (true)
	{
		system("cls");
		cout << "----- �������� ������������� -----\n";
		numTMP = -1;
		for (auto& user : users_)
		{
			if (numTMP <= 0)
			{
				numTMP++;
				continue;
			}
			cout << numTMP << ".\t" << user.getLogin() << "\t" << user.getName();
			if (users_[numTMP + 1].getBan() == "true") cout << "\t(�������).";
			cout << endl;
			numTMP++;
		}
		cout << "----------------------------------\n";
		cout << "1. �������� ���.\n2. ����� ���.\n-------------\n�������� ����������� ������, 0 - ����� � ���������� ����.\n";
		cin >> tmpBan;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmpBan == "0")
		{
			setUsersFile();
			break;
		}
		cout << "�������� ������������ �� 1 �� " << users_.size() - 2 << ", 0 - ����� � ���������� ����: ";
		cin >> tmpUser;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmpUser == 0)
		{
			setUsersFile();
			break;
		}
		if (tmpUser > users_.size() - 2)
		{
			cout << "����� �� ��������� ������. ��������� ����.\n";
			system("pause");
			continue;
		}
		if (tmpBan == "1")
		{
			if (users_[tmpUser + 1].getBan() == "false")
			{
				users_[tmpUser + 1].setBan(0);
			}
			else
			{
				cout << "�� ������������ ��� ������� ���.\n��������� �������.\n";
				system("pause");

			}
			continue;
		}
		if (tmpBan == "2")
		{
			if (users_[tmpUser + 1].getBan() == "true")
			{
				users_[tmpUser + 1].setBan(1);
			}
			else
			{
				cout << "�� ������������ ��� ����.\n��������� �������.\n";
				system("pause");

			}
			continue;
		}
		cout << "\n����� �� ���������.\n��������� �������\n";
		system("pause");
	}
}

/*
	  --- �������������� ����� ������ adminMenu ---
		showChat  -  �����  ��  �����  ��������� � ������������ �����������
	��������� � �������� ��������� �������������.
		�  ������  ������  ������������  ����������� ����, �������  �������
	���������   �  ����  �����������  ��������  �����  ���������,  ��������
	���������, ����� ��������� ����� ���������, � �����  �������  ���������
	�� ���������� �������� ������.
*/
void Admin::showChat()//const
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
		cout << "������� ��������� ���: 1 - �������� ���������, 2 - ������� ���������,\n\t\t\t 3 ����� �������� � ���������, 0 ����� �� ���������.\n";
		getline(cin, txt);
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (txt == "0")break;
		if (txt == "1")continue;
		if (txt == "2")
		{
			delMess();
			continue;
		}
		if (txt == "3")
		{
			upDelMess();
			continue;
		}
		if (txt != "") addMessage(txt);
	}
}

/*
	  --- �������������� ����� ������ showChat ---
		chat  -  �����  �� ����� ��������� � ���� ������� ������ �� �������
	message_ � ��� �����������.
*/
void Admin::chat()
{
	system("cls");
	string from;
	int tmp = 1;
	getMessage_File();
	cout << "����� ���: " << "\n-----------------------------------------------------------------------\n";
	for (auto& mess : message_)
	{
		if (mess.getDelete() == "")continue;
		cout << tmp << "\t";
		if (mess.getDelete() == "true") cout << "(�������)\t";
		cout << mess.getTime() << "\t" << mess.getFrom() << "\t" << mess.getText() << endl;
		tmp++;
	}
	cout << "-----------------------------------------------------------------------" << endl;
}

/*
	  --- �������������� ����� ������ showChat ---
		getMessagePC_File  -  ����������  ��������� �� ����� messages.txt �
	��������   ��   �  ������  message_,  ���  ����  ��������������  ������
	�������� �����.
*/
void Admin::getMessage_File()
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
	  --- �������������� ����� ������ showChat ---
		delMess  - �����������  ��������  ���������  ��������� ������������
	������������ �������� ����.
*/
void Admin::delMess()
{
	string tmpTrue{ "true" };
	string tmpFalse{ "false" };
	int tmp;
	while (true)
	{
		cout << "\n� ��������� ��� ��������, �� 1 �� " << message_.size() - 1 << ", 0 - ����� �� ������������: ";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp == 0) break;
		if (tmp<1 || tmp>message_.size() - 1)
		{
			cout << "\n�������� ����� ��� ���������.\n��������� ����.\n";
			system("pause");
			continue;
		}
		if (message_[tmp].getDelete() == "true")
		{
			cout << "\n��������� ��� �������.\n";
			system("pause");
			break;
		}
		getMessage_File();
		message_[tmp].setDelete(tmpTrue);
		if (setMessage_File()) message_[tmp].setDelete(tmpFalse);
		break;
	}
}

/*
	  --- �������������� ����� ������ showChat ---
		upDelMess  - ������ ������� ������� � ��������� ������������.
*/
void Admin::upDelMess()
{
	string tmpTrue{ "true" };
	string tmpFalse{ "false" };
	int tmp;
	while (true)
	{
		cout << "\n� ��������� ��� ��������������, �� 1 �� " << message_.size() - 1 << ", 0 - ����� �� ������������: ";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp == 0) break;
		if (tmp<1 || tmp>message_.size() - 1)
		{
			cout << "\n�������� ����� ��� ���������.\n��������� ����.\n";
			system("pause");
			continue;
		}
		if (message_[tmp].getDelete() == "false")
		{
			cout << "\n��������� �� �������.\n";
			system("pause");
			break;
		}
		getMessage_File();
		message_[tmp].setDelete(tmpFalse);
		if (setMessage_File()) message_[tmp].setDelete(tmpTrue);
		break;
	}
}

/*
	  --- �������������� ����� ������ showChat ---
		setMessage_File  -  ������  ��������� � ���� messages.txt �� �������
	message_,  ���  ����   ��������������   ������   ��������   �����,   ���
	�� ����������� ��������� ������������ �������� false,  ��� �������������
	��������� ���������.
*/
bool Admin::setMessage_File()
{
	char tmp;
	while (true)
	{
		system("cls");
		ofstream outf("messages.txt", ios::out);
		if (!outf)
		{
			while (true)
			{
				system("cls");
				cout << "��������� ������� ��������� ������, �������� ����� ������ ��� ������� ��� \n0 - ��� ����������� ��� ����������\n";
				cin >> tmp;
				if (cin.fail())
				{
					expCin();
					outf.close();
					continue;
				}
				break;
			}
			if (tmp == '0') return true;
			continue;
		}
		for (auto& mess : message_)
		{
			if (mess.getDelete() == "")continue;
			outf << mess.getDelete() << "\n" << mess.getTime() << "\n" << mess.getFrom() << "\n" << mess.getText() << "\n";
		}
		outf.close();
		return (false);
	}

}

/*
	  --- �������������� ����� ������ showChat ---
		addMessage - ���������� ������ ��������� � ���������, � �����������
	������� ��������� � ���� messages.txt � � ��������� message_.
*/
void Admin::addMessage(string txt)
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
		outf << "false\n" << time() << "\n" << "admin" << "\n" << txt << "\n";
		outf.close();
		Message message = Message("false", time(), "admin", txt);
		message_.push_back(message);
		break;
	}
}

/*
	  --- ��������������� ����� ������ �������������� Admin ---
		expCin - ��������� ������ ����� � ����������.
*/
void Admin::expCin()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << "������ �����, ��������� �������.\n";
	system("pause");
};

/*
	  --- ��������������� ����� ---
		getUsersFile - �������� ������������� �� ����� User.txt.
		�  �����  ������  ��  ���������  ������  User,  �������  ����������
	��  �����  User.txt.  ���  ����  ����������  �������� �� ������ � �����
	� ������ ���� �� ������ ������ �������������.
*/
void Admin::getUsersFile()
{
	char tmp;
	string banTMP;
	string loginTMP;
	string passwordTMP;
	string nameTMP;
	while (true)
	{
		system("cls");
		users_.resize(1);
		ifstream inf("Users.txt");
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
			if (getAdminByLogin(loginTMP) || getAdminByName(nameTMP)) continue;
			User user = User(banTMP, loginTMP, passwordTMP, nameTMP);
			users_.push_back(user);
		}
		inf.close();
		break;
	}
}




//�������� ������ �� �������
shared_ptr<User> Admin::getAdminByLogin(const string& login)//const
{
	int num = 0;
	for (auto& user : users_)
	{
		if (login == user.getLogin())
		{
			setNumAdmin(num);
			return make_shared<User>(user);
		}
		num++;
	}
	return nullptr;
}

//�������� ����� �� �������.
shared_ptr<User> Admin::getAdminByName(const string& name)const
{
	for (auto& user : users_)
	{
		if (name == user.getName()) return make_shared<User>(user);
	}
	return nullptr;
}
