#include <algorithm>
#include <iostream>
#include "BookManager.h"
#include "Book.h"
#include <vector>
#include <string>
#include <fstream>
#include"User.h"
#define FILENAME "library.txt"
#define FILENAME2 "users.txt"

using namespace std;
void selectOption(vector<Book>& b, vector<User>& u)
{
    int h = 0;
    char choose0;
    do {
        showMenu0();
        cin >> choose0;
        switch (choose0)
        {
        case'1'://��¼
            if (denglu(u))
            {
                h = 1;
                break;
            }
            else
                continue;
        case'2'://ע��
            zhuce(u);
            break;
        case'0':
            cout << "��ӭ�´�ʹ��" << endl;
            return;
        }
        system("pause");
        system("cls");
    } while ((choose0 != '0' && h != 1));
    while (true)
    {
        //չʾ���˵�
        showMenu1();
        char choose;
        cin >> choose;
        switch (choose)
        {
        case'1'://����
        {
            buyBook(b);
            break;
        }
        case'2'://����
        {
            if (quanxian())
                arrangeBook(b);
            else cout << "���������û��Ȩ��" << endl;
            break;
        }
        case '3'://ͳ��
        {
            if (b.empty())
            {
                cout << "��ǰ��ͼ��" << endl;
                break;
            }
            tongji(b);
            break;
        }
        case '4'://����
        {
            save(b);
            break;
        }
        case'0'://�˳�
        {
            cout << "��ӭ�´�ʹ��" << endl;
            return;
        }
        default:
        {
            cout << "ָ���������������" << endl;
        }
        }
        system("pause");
        system("cls");
    }
}

void buyBook(vector<Book>& b) {
    Book mai = findBook(b);
    if (mai.ISBN != -1)
    {
        int number;
        cout << "������Ҫ���������" << endl;
        cin >> number;
        if (number > mai.inStock)//�жϿ�湻����
        {
            cout << "��治�㣬����ʧ��" << endl;
        }
        else
        {
            int huaxiao = number * mai.price;
            for (int i = 0; i < b.size(); ++i) {
                //�����ҵ��Ȿ�飬���������Ŀ��
                if (b[i].ISBN == mai.ISBN)
                {
                    b[i].inStock -= number;
                    break;
                }
            }
            cout << "����ɹ�" << endl;
            cout << "������ " << huaxiao << " Ԫ" << endl;
        }
    }
}

Book findBook(vector<Book>& b)
{
    Book tmp;
    vector<Book>c;//Ϊ��ֹ�鼮������Ϣ�ظ�������Ϣ�ظ��Ĳ��ҽ������c��
    tmp.ISBN = 0;
    showMenu4();
    char choose2;
    cin >> choose2;
    switch (choose2)
    {

    case '1'://����������
    {
        findBookName(b, c);
        break;
    }
    case '2'://ISBN
    {
        findBookIsbn(b, c);
        break;
    }
    case '3'://����
    {
        findBookWriter(b, c);
        break;
    }
    case '4'://������
    {
        findBookPublishingHouse(b, c);
        break;
    }
    case '0'://�˳�
    {
        cout << "��ӭ�´�ʹ��" << endl;
        tmp.ISBN = -1;
        break;
    }
    default: {
        cout << "ָ���������������" << endl;
        break;
    }
    }
    //��ʼ���μ���
    if (tmp.ISBN != -1)
    {
        if (c.empty())
            //�ж���û�ҵ���û�ҵ�vector���ǿյ�
        {
            cout << "���޴���" << endl;
            tmp.ISBN = -1;
        }
        else if (c.size() == 1){
            Book::show(c[0]);
            return c[0];
    }//���vector��ֻ��һ��Ԫ�أ��Ͳ��ٱ����˷�ʱ����
        else
        {
            cout << "��ȷ����Ҫ���ҵ��鼮" << endl;
            int i;
            for (i = 0; i < c.size(); ++i) {//c�ﲻֹһ���飬����cȷ�ϲ��ҵ���
                cout << i + 1 << "��\t";
                Book::show(c[i]);
            }
            cout << "��ѡ����Ҫ���ҵ��鼮���" << endl;
            cin >> i;
            return c[i - 1];
        }
    }
    return tmp;
}
void findBookName(vector<Book>& b, vector<Book>& c) {
    string name;
    cout << "��������Ҫ���ҵ��鼮����" << endl;
    cin >> name;
    for (auto& i : b) {
        if (i.name == name)
        {
            c.push_back(i);
        }
    }
}
void findBookWriter(vector<Book>& b, vector<Book>& c) {
    string writer;
    cout << "��������Ҫ���ҵ��鼮����" << endl;
    cin >> writer;
    for (auto& i : b) {
        if (i.writer == writer)
        {
            c.push_back(i);
        }
    }
}
void findBookPublishingHouse(vector<Book>& b, vector<Book>& c) {
    string chubanshe;
    cout << "��������Ҫ���ҵ��鼮������" << endl;
    cin >> chubanshe;
    for (auto& i : b) {
        if (i.publishingHouse == chubanshe)
        {
            c.push_back(i);
        }
    }
}
void findBookIsbn(vector<Book>& b, vector<Book>& c) {
    cout << "��������Ҫ���ҵ��鼮ISBN" << endl;
    int ISBN;
    cin >> ISBN;
    for (auto& i : b) {
        if (i.ISBN == ISBN)
        {
            c.push_back(i);
        }
    }
}

void tongji(vector<Book>& b)
{
    showMenu6();
    char choose6;
    cin >> choose6;
    switch (choose6)
    {
    case '0'://�˳�
    {
        cout << "�˳�ͳ��ϵͳ" << endl;
        return;
    }
    case '1'://isbn
    {
        sort(b.begin(), b.end(), isbnCmp);//����
        for (const auto& i : b)
        {
            Book::show(i);//��ʾ�����������
        }
        break;
    }
    case '2'://���
    {
        sort(b.begin(), b.end(), inStockCmp);
        for (const auto& i : b)
        {
            Book::show(i);
        }
        break;
    }
    case '3'://�۸�
    {
        sort(b.begin(), b.end(), priceCmp);
        for (const auto& i : b)
        {
            Book::show(i);
        }
        break;
    }
    }
}

bool isbnCmp(const Book& a, const Book& b)
{
    return a.ISBN > b.ISBN;
}
bool priceCmp(const Book& a, const Book& b)
{
    if (a.price == b.price)return a.ISBN > b.ISBN;
    //�۸���ȵ�ʱ��ISBN����
    return a.price > b.price;
}
bool inStockCmp(const Book& a, const Book& b)
{
    if (a.inStock == b.inStock)return a.ISBN > b.ISBN;
    //�����ȵ�ʱ��ISBN����
    return a.inStock > b.inStock;
}

void showMenu0() {
    cout << "*************************************" << endl;
    cout << "********  ������������Ľ���  *********" << endl;
    cout << "********    ��¼�ʺ��밴1    *********" << endl;
    cout << "********    ע���˺��밴2    *********" << endl;
    cout << "********  �˳�ͼ��ϵͳ�밴0  *********" << endl;
    cout << "*************************************" << endl;
}
void showMenu1()
{
    cout << "*************************************" << endl;
    cout << "********  ������������Ľ���  *********" << endl;
    cout << "********    �����鼮�밴1    *********" << endl;
    cout << "********    �����鼮�밴2    *********" << endl;
    cout << "********  ��ʾ�鼮��Ϣ�밴3  *********" << endl;
    cout << "********  ����ͼ����Ϣ�밴4  *********" << endl;
    cout << "********  �˳�ͼ��ϵͳ�밴0  *********" << endl;
    cout << "*************************************" << endl;
}
void showMenu2()
{
    cout << "*************************************" << endl;
    cout << "********   ����鼮��Ϣ�밴1      *****" << endl;
    cout << "********   �޸��鼮��Ϣ�밴2      *****" << endl;
    cout << "********   �˳�����ϵͳ�밴0      *****" << endl;
    cout << "*************************************" << endl;
}
void showMenu3()
{
    cout << "*************************************" << endl;
    cout << "********   �޸ĸ��鼮�밴1   *****" << endl;
    cout << "********   ɾ�����鼮�밴2   *****" << endl;
    cout << "********      �˳��밴0     *****" << endl;
    cout << "*************************************" << endl;
}
void showMenu4()
{
    cout << "*************************************" << endl;
    cout << "***   ��ѡ���������鼮�ķ�ʽ   *******" << endl;
    cout << "***   ͨ�����������밴1        ******" << endl;
    cout << "***   ͨ��IBSN�Ų����밴2      ******" << endl;
    cout << "***   ͨ�����߲����밴3        ******" << endl;
    cout << "***   ͨ������������밴4       ******" << endl;
    cout << "***   �˳������밴0           *******" << endl;
    cout << "***********************************" << endl;
}
void showMenu5()
{
    cout << "*************************************" << endl;
    cout << "*****   ����Ҫ�޸ĸ���������Ϣ   ******" << endl;
    cout << "*******    �޸������밴1      *******" << endl;
    cout << "*******    �޸�ISBN�밴2      *******" << endl;
    cout << "*******    �޸������밴3      *******" << endl;
    cout << "*******   �޸ĳ������밴4     *******" << endl;
    cout << "*******    �޸ļ۸��밴5      *******" << endl;
    cout << "*******    �޸Ŀ���밴6      *******" << endl;
    cout << "*******    �˳��޸��밴0      *******" << endl;
    cout << "***********************************" << endl;
}
void showMenu6() {
    cout << "*********************************************" << endl;
    cout << "******    ѡ����Ҫͳ��ͼ����Ϣ������ʽ    ******" << endl;
    cout << "*******        ��ISBNͳ���밴1         *******" << endl;
    cout << "*******        �����ͳ���밴2          *******" << endl;
    cout << "*******        ���۸�ͳ���밴3          *******" << endl;
    cout << "*******          �˳��밴0             *******" << endl;
    cout << "*********************************************" << endl;
}

void arrangeBook(vector<Book>& b) {
    while (true)
    {
        showMenu2();
        char choose3;
        cin >> choose3;
        switch (choose3)
        {
        case'0'://�˳�
        {
            cout << "�˳�����ϵͳ" << endl;
            return;
        }
        case '1'://���
        {
            addBook(b);
            break;
        }
        case '2'://�޸�
        {
            Book gai = findBook(b);
            if (gai.ISBN != -1)
            {
                modifyBook(b, gai);
            }
            break;
        }
        }
        system("pause");//�����������
        system("cls");//����
    }
}

int isExist(int isbn, vector<Book>& b)
{
    for (auto& i : b) { 
        //�������Book��vector���ж�ISBN�Ƿ�Ψһ
        if (i.ISBN == isbn)return -1;
    }
    return 0;
}
int isUserExist(string name, vector<User>u) {
    for (int i = 0; i < u.size(); ++i) {
        if (u[i].userName == name) return i;
    }
    return -1;
}

void addBook(vector<Book>& b) {
    Book newbook;//����һ��Book�����
    addBookName(b, newbook);
    addBookIsbn(b, newbook);
    addBookWriter(b, newbook);
    addBookPublishingHouse(b, newbook);
    addBookInStock(b, newbook);
    addBookPrice(b, newbook);
    //����Ϣ��ȡ��newbook������
    b.push_back(newbook);
    //�ٽ�newbook��ӵ�Book��vector��
    cout << "��ӳɹ�" << endl;
}
void addBookIsbn(vector<Book>& b, Book& c) {
    int isbn;
    cout << "������ISBN��" << endl;
    while (true)
    {
        cin >> isbn;
        if (isExist(isbn, b) == -1)cout << "ISBN���ظ�������������" << endl;
        else break;
    }
    c.ISBN = isbn;
}
void addBookName(vector<Book>& b, Book& c) {
    string name;
    cout << "����������" << endl;
    cin >> name;
    c.name = name;
}
void addBookWriter(vector<Book>& b, Book& c) {
    string writer;
    cout << "����������" << endl;
    cin >> writer;
    c.writer = writer;
}
void addBookPublishingHouse(vector<Book>& b, Book& c) {
    string chubanshe;
    cout << "�����������" << endl;
    cin >> chubanshe;
    c.publishingHouse = chubanshe;
}
void addBookInStock(vector<Book>& b, Book& c) {
    int kucun;
    cout << "��������" << endl;
    cin >> kucun;
    c.inStock = kucun;
}
void addBookPrice(vector<Book>& b, Book& c) {
    int jiage;
    cout << "������۸�" << endl;
    cin >> jiage;
    c.price = jiage;
}

void modifyBook(vector<Book>& b, Book& c) {
    showMenu3();
    char choose4;
    cin >> choose4;
    switch (choose4)
    {
    case '0'://�˳�
    {
        cout << "�˳��޸�ϵͳ" << endl;
        break;
    }
    case '1'://�޸�
    {
        modifyBookInformation(b, c);

        break;
    }
    case '2'://ɾ��
    {
        Book::deleteBook(b, c);
        break;
    }
    default:
    {
        cout << "ָ������޸�ʧ��" << endl;
        break;
    }
    }
}
void modifyBookInformation(vector<Book>& b, Book& c)
{
    while (true)
    {
        showMenu5();
        char choose5;
        cin >> choose5;
        switch (choose5) {
        case '1':
        {
            modifyBookName(b, c);
            break;
        }
        case '2': {
            modifyBookIsbn(b, c);
            break;
        }
        case '3': {
            modifyBookWriter(b, c);
            break;
        }
        case '4': {
            modifyBookChubanshe(b, c);
            break;
        }
        case '5': {
            modifyBookJiage(b, c);
            break;
        }
        case '6':
        {
            modifyBookKucun(b, c);
            break;
        }
        case '0':
        {
            cout << "�˳��޸�ϵͳ" << endl;
            return;
        }
        default:
        {
            cout << "ָ���������������" << endl;
            break;
        }
        }

    }
}
void modifyBookName(vector<Book>& b, Book& c)
{
    string name;
    cout << "�������޸ĺ�����" << endl;
    cin >> name;
    int i = 0;
    for (; i < b.size(); ++i) {
        if (b[i].ISBN == c.ISBN)break;
    }
    b[i].name = name;
    cout << "�޸ĳɹ�" << endl;
}
void modifyBookIsbn(vector<Book>& b, Book& c)
{
    int isbn;
    cout << "�������޸ĺ�ISBN��" << endl;
    cin >> isbn;
    if (isExist(isbn, b) == -1)//�ж�ISBN�Ƿ��ظ�
    {
        cout << "ISBN�ظ����޸�ʧ��" << endl;
    }
    else {
        int i = 0;
        for (; i < b.size(); ++i) {
            if (b[i].ISBN == c.ISBN)break;
        }
        b[i].ISBN = isbn;
        cout << "�޸ĳɹ�" << endl;
    }
}
void modifyBookChubanshe(vector<Book>& b, Book& c)
{
    string chubanshe;
    cout << "�������޸ĺ������" << endl;
    cin >> chubanshe;
    int i = 0;
    for (; i < b.size(); ++i) {
        if (b[i].ISBN == c.ISBN)break;
    }
    b[i].publishingHouse = chubanshe;
    cout << "�޸ĳɹ�" << endl;
}
void modifyBookWriter(vector<Book>& b, Book& c)
{
    string zuozhe;
    cout << "�������޸ĺ�����" << endl;
    cin >> zuozhe;
    int i = 0;
    for (; i < b.size(); ++i) {
        if (b[i].ISBN == c.ISBN)break;
    }
    b[i].writer = zuozhe;
    cout << "�޸ĳɹ�" << endl;
}
void modifyBookKucun(vector<Book>& b, Book& c)
{
    int kucun;
    cout << "�������޸ĺ���" << endl;
    cin >> kucun;
    int i = 0;
    for (; i < b.size(); ++i) {
        if (b[i].ISBN == c.ISBN)break;
    }
    b[i].inStock = kucun;
    cout << "�޸ĳɹ�" << endl;
}
void modifyBookJiage(vector<Book>& b, Book& c)
{
    int jiage;
    cout << "�������޸ĺ�۸�" << endl;
    cin >> jiage;
    int i = 0;
    for (; i < b.size(); ++i) {
        if (b[i].ISBN == c.ISBN)break;
    }
    b[i].price = jiage;
    cout << "�޸ĳɹ�" << endl;
}

bool quanxian()
{
    cout << "������������֤������Ȩ��" << endl;
    string c;
    cin >> c;
    return c == "73748156";
}

bool denglu(vector<User> u)
{
    string name, password;
    cout << "�������û���" << endl;
    cin >> name;
    int a = isUserExist(name, u);
    if (a == -1) {
        cout << "�û��������ڣ���¼ʧ��" << endl;
        return false;
    }
    else
    {
        cout << "����������" << endl;
        cin >> password;
        if (u[a].password == password) {
            cout << "��¼�ɹ�" << endl;
            return true;
        }
        else
        {
            cout << "������󣬵�¼ʧ��" << endl;
            return false;
        }
    }
}

void zhuce(vector<User>& u)
{
    string password;
    User tmp;
    string name;
    cout << "�������û���" << endl;
    cin >> name;
    int a = isUserExist(name, u);
    if (a == -1)
    {
        tmp.userName = name;
        cout << "����������" << endl;
        cin >> password;
        tmp.password = password;
        u.push_back(tmp);
        ofstream ofs;
        ofs.open(FILENAME2, ios::out);
        for (auto& i : u) {//¼���û���Ϣ
            ofs  << i.userName << " "<< i.password << endl;
        }
        cout << "����ɹ�" << endl;
        ofs.close();//�ر��ļ�
    }
    else cout << "���û����ѱ�ʹ�ã�ע��ʧ��" << endl;
}

void fetchUser(vector<User>& u)
{
    ifstream ifs;
    ifs.open(FILENAME2, ios::in);//���ļ�
    if (!ifs.is_open())//�ж��Ƿ����
    {
        cout << "�û��ļ�������" << endl;
        ifs.close();
        return;
    }

    User temp;
    while (ifs >> temp.userName && ifs >> temp.password)//��Ϣ��ȡ��temp��
    {
        u.push_back(temp);//��temp����u��
    }
    ifs.close();
    if (u.empty())
    {
        cout << "�û��ļ�Ϊ��" << endl;
    }
    else
        cout << "��ǰ�û���ĿΪ" << u.size() << "λ" << endl;
}

void save(vector<Book>& b)
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for (auto& i : b) {//¼��ÿ������Ϣ
        ofs << i.name << " " << i.ISBN << " " << i.writer << " "
            << i.publishingHouse << " " << i.inStock << " " << i.price << endl;
        //��������Ϣ�洢����Ϣ֮���Կո�ָ�����֮���Ի��з��ָ�
    }
    cout << "����ɹ�" << endl;
    ofs.close();//�ر��ļ�

}

void fetchBook(vector<Book>& b)
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//���ļ�
    if (!ifs.is_open())//�ж��Ƿ����
    {
        cout << "ͼ���ļ�������" << endl;
        ifs.close();
        return;
    }

    Book temp;
    while (ifs >> temp.name && ifs >> temp.ISBN && ifs >> temp.writer && ifs >> temp.publishingHouse &&
        ifs >> temp.inStock && ifs >> temp.price)//��Ϣ��ȡ��temp��
    {
        b.push_back(temp);//��temp����b��
    }
    ifs.close();
    if (b.empty())
    {
        cout << "ͼ���ļ�Ϊ��" << endl;
    }
    else
        cout << "��ǰͼ��������ĿΪ" << b.size() << "��" << endl;
}

//
// Created by DELL on 2020/5/1.
//

