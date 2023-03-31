//#ifndef DICT_H
//#define DICT_H
#pragma once
#include<iostream>
#include <vector>
#include "DictMenu.h"
const int ALPHABET_SIZE = 256;
using namespace std;


//����� ����� �������
class DictNode {
public:
    int isEndOfWord; // ������, ��������������� ���� ��������
    DictNode* children[ALPHABET_SIZE];

    DictNode()
    {
        isEndOfWord = 0;
        memset(children, NULL, sizeof(DictNode*) * ALPHABET_SIZE);
    }

};

//����� ������� - ������ Trie
class Dict {
private:
    vector<string>suf_;

public:
    DictNode* root;
    Dict();
    ~Dict();
    void destory(DictNode* root);
    // ��������� ����� str
    void insert(string str);
    //���������� ������� �� ����� Dict.txt
    bool addDictToDict(bool dictOn);
    //���������� ������� �� ����� messanges.txt
    void addDictToMessages();
    //���������� ������� �� ��������� ����� txt
    void addDictToTxt();

    //����� ���� ��������� ������� � ���������� ����
    void show();
    void show(DictNode*);
    void show(DictNode*, string, int);

    //����� ����� ������ ��������� � ������� ���������
    string messeng();
    //��������������� ����� ������ messeng()
    string suf(string);
    // ���������, ��������� �� ������ str, � ���������� ��� ������� 
    DictNode* search(DictNode*, string);
    // �������� ��� ������� � ����������� �������� �  ���������� ������ ��������
    string choosSuffix(DictNode*, string);
    void choosSuf(DictNode*, string,int );

};





//#endif