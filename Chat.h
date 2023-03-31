#pragma once
#include <vector>
#include <iostream>
#include "Message.h"
#include "Dict.h"

class Dict;

/*
	����� Chat - �������� ����� �������������� ����� ���������.

	me_ - ���������� ������������ ������������              -- �������������� ������ - ������ LoginMenu --
	users_ - ��������� �������������					getUsersFile  -  ��������  ������������� � ��������� �� �����
	message_ - ��������� � ����������					login - ���� ������������
	currentUser_ - ��������� �� ������������ (����)		registration - ����������� ������������
			�� ������ ���������� �������������				setUsersFile (�������������� ����� ������ registration) -
																		��������   �������������������  ������������
		--- �������� ������ ---											� ����
	LoginMenu - ���� � ����������� ������������				-- �������������� ������ - ������ showChat --
	showChat - ���������								getMessage_File - �������� ��������� �� �����
														chat - ����� ���������
	getUserByLogin - ��������� ����������� �����		addMessage - ����������  ���������  �  ���  �  ���������� ���
		�� ������� ��������										� ��������� ���������
	getUserByName - ��������� ����������� ���				-- ��������������� ����� --
		�� ������� ��������								expCin - ��������� ������ ��� ������������� ��������� cin
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

