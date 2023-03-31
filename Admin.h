#pragma once
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include "PerCor.h"
#include "Message.h"



/*
	����� Admin - �������� ����� �������������� �����������������.

	login_ - ���������� ��������� �����							-- ��������������� ������ - ������ LoginMenu --
	numAdmin_ - ���������� � � �������			       inPassword - ���� ������
	users_ - ��������� �������������                   passChange - ����� ������
	message_ - ��������� � ����������			       registration - ����������� ������������
	currentAdmin_ - ��������� �� ������				   setUsersFile (�������������� ����� ������ LoginMenu) -
				�� ������ ���������� ������������					�������� �������������������� ������������ � ����
																-- �������������� ������ - ������ adminMenu --
													   ban - ���������, ������ ����
			--- �������� ������ ---					   showChat - ����� ���� �� �����
	LoginMenu - ���� ��������������					   getMessage_File - ���������� ������� ��������� �� �����
	adminMenu - �������� ���� ��� ������			   delMess - ������� ��������� ��� ����������
				�������������						   upDelMess - ������ ������� �� �������� � ���������
													   setMessage_File - �������� ��������� �� ������� � ����.
													   addMessage - ���������� ��������� � ��� � ���������� ��� � ��������� ���������
	getAdminByLogin - ��������� ����������� �����				-- ��������������� ������ --
		�� �������� ��������						   expCin - ��������� ������ ��� ������������� ��������� cin
	getAdminByName - ��������� ����������� ���		   getUsersFile - ��������������������� �� �����
		�� �������� ��������						   setNumAdmin - ���������� �������� numAdmin_
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
