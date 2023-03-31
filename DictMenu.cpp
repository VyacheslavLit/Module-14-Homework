#include "DictMenu.h"


void dictMenu()
{
	Dict dict;
	bool dictOn{ false };
	int tmp;
	while (true)
	{
		system("cls");
		cout << "       --------- ���� ������ �� �������� ---------\n";
		cout << "1. ���������� ������� �� ����� Dict.txt;\n";
		cout << "2. ���������� ������� �� ����� ����� ��������� messages.txt;\n";
		cout << "3. ���������� ������� �� ����� ���������� �������������;\n";
		cout << "4. �������� �������;\n";
		cout << "5. ����� ���.\n";
		cout << "0. ������� � ���������� ����.\n\n";
		cout << "�������� ������ ������: ";
		cin >> tmp;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "\n������ �����, ��������� �������.\n";
			system("pause");
			continue;
		}
		if (tmp < 0 || tmp>5)
		{
			cout << "\n������ ������ �� ���������, ��������� �������.\n";
			system("pause");
			continue;
		}
		if (tmp == 0) break;
		if (tmp == 1) dictOn = dict.addDictToDict(dictOn);
		if (tmp == 2) dict.addDictToMessages();
		if (tmp == 3) dict.addDictToTxt();
		if (tmp == 4) dict.show();
		if (tmp == 5)
		{
			Chat Chat;
			User user(string, const string&, const string&, const string&);
			Chat.loginMenu();
			if (Chat.getCurrentUser() && dictOn)Chat.showChatDict(dict);
			else if (!dictOn)
			{
				cout << "\n������� ��� �� ��������.\n";
				system("pause");
			}
			else
			{
				cout << "\n������������ ��� �� ������.\n";
				system("pause");
			}
		}
			
	}
}


void expCin()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << "������ �����, ��������� �������.\n";
	system("pause");
};