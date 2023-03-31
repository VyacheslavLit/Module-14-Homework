#include "Dict.h"



Dict::Dict()
{
    root = new DictNode();
}
Dict::~Dict()
{
    destory(root);
}
void Dict::destory(DictNode* root)
{
    if (root == nullptr)
        return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        destory(root->children[i]);
    }
    delete root;
    root = nullptr;
}


// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� ��������� �������� �.�. ����� �����
void Dict::insert(string key)
{
    if (key == "") return;
    DictNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        //������� �� ����� ���������� � �����
        if (key[i] == '.' || key[i] == ',' || key[i] == '?' || key[i] == '!' || key[i] == '-') break;
        // ��������� ������ � ������ ����� �������� ������������� ������ �����
        int index = key[i] + 128;//267
        // ���� ��������� �������, �.�. ����� � ����� ��������� ���
        // ������� ����� ����
        if (!node->children[index])
            node->children[index] = new DictNode();
        node = node->children[index];
    }

    // �������� ��������� ����� ��� ����, �.�. ����� �����
    node->isEndOfWord = true;
}



bool Dict::addDictToDict(bool dictOn)
{
    char tmp;
    string word;
    while (true)
    {
        system("cls");
        ifstream inf("Dict.txt");
        /*
            ���������, �������� �� ����, � ���� �� �� �������� ���� �����������
        ��������� ��������, ����� ���������� �������������� �������� ���� �������������.
        */
        if (!inf)
        {
            while (true)
            {
                cout << "��������� �������� �������, �������� ����� ������ ��� ������� ��� \n0 - ��� ����������� ��� �������� �������.: ";
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
            inf >> word;
            if (!inf) break;
            insert(word);
        }
        inf.close();
        dictOn = { true };
        break;
    }
    return dictOn;
}

void Dict::addDictToMessages()
{
    char tmp;
    string word;
    while (true)
    {
        system("cls");
        ifstream inf("messages.txt");
        /*
            ���������, �������� �� ����, � ���� �� �� �������� ���� �����������
        ��������� ��������, ����� ���������� �������������� �������� ���� �������������.
        */
        if (!inf)
        {
            while (true)
            {
                cout << "��������� �������� �������, �������� ����� ������ ��� ������� ��� \n0 - ��� ����������� ��� �������� �������.: ";
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
            inf >> word;
            if (!inf) break;
            if (word[0]>-33&&word[0]<=-1) insert(word);
        }
        inf.close();
        break;
    }
}

void Dict::addDictToTxt()
{
    char tmp;
    string word;
    while (true)
    {
        system("cls");
        cout << "������� �������� ����� ��� �������� ������� (� ����� ������������ ���� Kramer.txt): ";
        string tmp;
        cin.clear();
        cin.ignore(32767, '\n');
        cin >> tmp;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "\n������ �����, ��������� ���� �����. ";
            system("pause");
            continue;
        }
        ifstream inf(tmp);
        /*
            ���������, �������� �� ����, � ���� �� �� �������� ���� �����������
        ��������� ��������, ����� ���������� �������������� �������� ���� �������������.
        */
        if (!inf)
        {
            while (true)
            {
                cout << "��������� �������� �������, �������� ����� ������ ��� ������� ��� \n0 - ��� ����������� ��� �������� �������.: ";
                cin >> tmp;
                if (cin.fail())
                {
                    expCin();
                    inf.close();
                    continue;
                }
                break;
            }
            if (tmp == "0") break;
            continue;
        }

        while (inf)
        {
            inf >> word;
            if (!inf) break;
            if (word[0] > -33 && word[0] <= -1) insert(word);
        }
        inf.close();
        break;
    }
}


void Dict::show()
{
    class DictNode* node = root;

    string str;
    int ind = 0;
    str += ' ';
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i] != nullptr)
        {
            str[ind] = i - 128;
            show(root->children[i], str, ind + 1);
        }
    }
    system("pause");
}

void Dict::show(DictNode* root)
{
    string str;
    int ind = 0;
    str += ' ';
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i] != nullptr)
        {
            str[ind] = i - 128;
            show(root->children[i], str, ind + 1);
        }
    }
}

void Dict::show(DictNode* root, string str, int ind)
{
    if (root->isEndOfWord)
    {
        cout << str << endl;
        return;
    }
    str += ' ';
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i] != nullptr)
        {
            str[ind] = i - 128;
            show(root->children[i], str, ind + 1);
        }
    }
}

string Dict::messeng()
{
    string mes{};
    string pref;
    while(true)
    {
        pref ="";
        cout << "���� ���������: " << mes << endl;
        cout << "������� ������� ������������ ����� ���: 1 �������� ���������, 0 ��������� ���������.\n";
        cin.clear();
        cin.ignore(32767, '\n');
        cin >> pref;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "\n������ �����, ��������� ���� ���������: ";
            continue;
        }
        if (pref == "1")continue;
        if (pref == "0")break;
        if (pref != "") mes += suf(pref)+' ';

    }
    return mes;
}

string Dict::suf(string txt)
{
    class DictNode* node = root;
    return choosSuffix(search(node, txt), txt);
}

// ���������� ���� �� ������� ���������� ����� 
DictNode* Dict::search(DictNode* node, string key)
{
    for (int i = 0; i < key.length(); i++)
    {
        if (key[i] < '�' || key[i]>'�') nullptr;
        int index = key[i] + 128;
        if (!node->children[index])
            return nullptr;
        node = node->children[index];
    }
    return node;
}

// �������� ��� ������� � ����������� �������� �  ���������� ������ ��������
string Dict::choosSuffix(DictNode* root, string pref)
{
    if (root == nullptr) return pref;
    cout << "�� ����� �������: " << pref << endl;
    cout << "� ������� ���� ��������� ����� � ����� ���������:\n";
    string suffix;
    int ind = 0;
    suf_.clear();

    choosSuf(root, suffix,ind);
    ind = 0;
    for (auto element : suf_)
    {
        ind+=1;
        cout <<ind<<". ("<< pref<<element << ") ";
    }
    cout << "\n����� ����� �� ����� � ���� (�������� �����, ��� " << 0 << " �������� ��� ���������, " << ind + 1 << " �������� ������ �������): ";
    int tmp;
    while (true)
    {
        cin >> tmp;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "\n������ �����, ��������� �����: ";
            continue;
        }
        if (tmp<0 || tmp>ind + 1)
        {
            cout << "��� ��������� ������, ��������� �����: ";
            continue;
        }
        break;
    }
    if (tmp == 0)return (pref);
    if (tmp>0&&tmp<=ind) return (pref+suf_[tmp-1]);
    cout << "\n��������� �����: " << pref;
    while (true)
    {
        cin >> suffix;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "\n������ �����, ��������� ��������� �����: "<<pref;
            continue;
        }
        break;
    }
    return (pref + suffix);
}

void Dict::choosSuf(DictNode* root, string suffix, int ind)
{
    
    if (root!=nullptr) if (root->isEndOfWord) suf_.push_back(suffix);
    string tmp;
    suffix += ' ';
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i])
        {
            suffix[ind] = i - 128;
            choosSuf(root->children[i], suffix, ind+1);
        }
    }

}
