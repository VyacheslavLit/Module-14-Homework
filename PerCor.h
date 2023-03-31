#pragma once
#include <vector>
//#include <exception>
//#include <memory>
#include <iostream>
#include "MessagePC.h"


//��������� ���������� �� ������ ������
struct ExpLogin :public exception
{
	const char* what() const noexcept override
	{
		return "� ��������� ������ ����� �����, �������� �����.\n";
	}
};

//��������� ���������� �� ������ �����
struct ExpName :public exception
{
	const char* what() const noexcept override
	{
		return "� ��������� ������ ��� ������, �������� ���.\n";
	}
};



/*
	����� PerCor - �������� ����� �������������� ����� ���������.

	me_ - ���������� ������������ ������������              -- �������������� ������ - ������ LoginMenu --
	party_ - ���������� ������������ �����������       getUsersFile - �������� ������������� � ��������� �� �����
	users_ - ��������� �������������                   login - ���� ������������
	perCorParty_ - ��������� �������������             registration - ����������� ������������
			� �������� ������� ���������				  setUsersFile (�������������� ����� ������ registration) -
	messagePC_ - ��������� � ������ ����������							�������� ������������������� ������������ � ����
	currentUser_ - ��������� �� ������������ (����)			-- �������������� ������ - ������ UserMenu --
			�� ������ ���������� �������������         getMessagePC_File - �������� ������ ��������� �� �����
			--- �������� ������ ---					   perCorParty - ���������� ���������� ������������� � �������� ������� ������ ���������
	LoginMenu - ���� � ����������� ������������	  	   setParty - ����� �������� �����������
	UserMenu - ����� �����������					   addParty - ���������� � ����� ������ �����������
	showPC - ��������� 								   expParty (�������������� ����� ������ addParty) -
	loginAdminPC() - ���� ������					   �������� ���������� ������������ �� ������
															-- �������������� ������ - ������ showPC --
	getUserByLogin - ��������� ����������� �����	   chat - ����� ������ ��������� � ��������� ������������
		�� �������� ��������						   addMessage - ���������� ��������� � ��� � ���������� ��� � ��������� ���������
	getUserByName - ��������� ����������� ���				-- ��������������� ����� --
		�� �������� ��������						   expCin - ��������� ������ ��� ������������� ��������� cin
*/
class PerCor {
	string me_;
	string party_;
	vector<User> users_;
	vector<string> perCorParty_;
	vector<MessagePC> messagePC_;
	shared_ptr<User>currentUser_ = nullptr;
	shared_ptr<User>_party = nullptr;

public:
	shared_ptr<User>getCurrentUser() const { return currentUser_; }
	void loginMenuPC();
	void userMenuPC();
	void showPC();
	void loginAdminPC();
	auto getParty() { return party_; }

private:
	void getUsersFile();
	void login();
	void registration();
	void setUsersFile(string, string, string);
	void getMessagePC_File();
	void perCorParty();
	void setParty(string party) { party_ = party; }
	void addParty();
	bool expParty(string name);
	void chat();
	void addMessage(string txt);
	void expCin();

	shared_ptr<User> getUserByLogin(const string& login) const;
	shared_ptr<User> getUserByName(const string& name)const;
};
