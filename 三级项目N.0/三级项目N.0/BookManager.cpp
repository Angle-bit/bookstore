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
        case'1'://登录
            if (denglu(u))
            {
                h = 1;
                break;
            }
            else
                continue;
        case'2'://注册
            zhuce(u);
            break;
        case'0':
            cout << "欢迎下次使用" << endl;
            return;
        }
        system("pause");
        system("cls");
    } while ((choose0 != '0' && h != 1));
    while (true)
    {
        //展示主菜单
        showMenu1();
        char choose;
        cin >> choose;
        switch (choose)
        {
        case'1'://购买
        {
            buyBook(b);
            break;
        }
        case'2'://整理
        {
            if (quanxian())
                arrangeBook(b);
            else cout << "密码错误，您没有权限" << endl;
            break;
        }
        case '3'://统计
        {
            if (b.empty())
            {
                cout << "当前无图书" << endl;
                break;
            }
            tongji(b);
            break;
        }
        case '4'://保存
        {
            save(b);
            break;
        }
        case'0'://退出
        {
            cout << "欢迎下次使用" << endl;
            return;
        }
        default:
        {
            cout << "指令错误，请重新输入" << endl;
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
        cout << "请输入要购买的数量" << endl;
        cin >> number;
        if (number > mai.inStock)//判断库存够不够
        {
            cout << "库存不足，购买失败" << endl;
        }
        else
        {
            int huaxiao = number * mai.price;
            for (int i = 0; i < b.size(); ++i) {
                //遍历找到这本书，并调整他的库存
                if (b[i].ISBN == mai.ISBN)
                {
                    b[i].inStock -= number;
                    break;
                }
            }
            cout << "购买成功" << endl;
            cout << "共花费 " << huaxiao << " 元" << endl;
        }
    }
}

Book findBook(vector<Book>& b)
{
    Book tmp;
    vector<Book>c;//为防止书籍其他信息重复，讲信息重复的查找结果存在c中
    tmp.ISBN = 0;
    showMenu4();
    char choose2;
    cin >> choose2;
    switch (choose2)
    {

    case '1'://按书名查找
    {
        findBookName(b, c);
        break;
    }
    case '2'://ISBN
    {
        findBookIsbn(b, c);
        break;
    }
    case '3'://作者
    {
        findBookWriter(b, c);
        break;
    }
    case '4'://出版社
    {
        findBookPublishingHouse(b, c);
        break;
    }
    case '0'://退出
    {
        cout << "欢迎下次使用" << endl;
        tmp.ISBN = -1;
        break;
    }
    default: {
        cout << "指令错误，请重新输入" << endl;
        break;
    }
    }
    //开始二次检索
    if (tmp.ISBN != -1)
    {
        if (c.empty())
            //判断找没找到，没找到vector就是空的
        {
            cout << "查无此书" << endl;
            tmp.ISBN = -1;
        }
        else if (c.size() == 1){
            Book::show(c[0]);
            return c[0];
    }//如果vector内只有一个元素，就不再遍历浪费时间啦
        else
        {
            cout << "请确认您要查找的书籍" << endl;
            int i;
            for (i = 0; i < c.size(); ++i) {//c里不止一本书，遍历c确认查找的书
                cout << i + 1 << "、\t";
                Book::show(c[i]);
            }
            cout << "请选择您要查找的书籍序号" << endl;
            cin >> i;
            return c[i - 1];
        }
    }
    return tmp;
}
void findBookName(vector<Book>& b, vector<Book>& c) {
    string name;
    cout << "请输入您要查找的书籍名称" << endl;
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
    cout << "请输入您要查找的书籍作者" << endl;
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
    cout << "请输入您要查找的书籍出版社" << endl;
    cin >> chubanshe;
    for (auto& i : b) {
        if (i.publishingHouse == chubanshe)
        {
            c.push_back(i);
        }
    }
}
void findBookIsbn(vector<Book>& b, vector<Book>& c) {
    cout << "请输入您要查找的书籍ISBN" << endl;
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
    case '0'://退出
    {
        cout << "退出统计系统" << endl;
        return;
    }
    case '1'://isbn
    {
        sort(b.begin(), b.end(), isbnCmp);//排序
        for (const auto& i : b)
        {
            Book::show(i);//显示排完序后的书库
        }
        break;
    }
    case '2'://库存
    {
        sort(b.begin(), b.end(), inStockCmp);
        for (const auto& i : b)
        {
            Book::show(i);
        }
        break;
    }
    case '3'://价格
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
    //价格相等的时候按ISBN排序
    return a.price > b.price;
}
bool inStockCmp(const Book& a, const Book& b)
{
    if (a.inStock == b.inStock)return a.ISBN > b.ISBN;
    //库存相等的时候按ISBN排序
    return a.inStock > b.inStock;
}

void showMenu0() {
    cout << "*************************************" << endl;
    cout << "********  书是人类进步的阶梯  *********" << endl;
    cout << "********    登录帐号请按1    *********" << endl;
    cout << "********    注册账号请按2    *********" << endl;
    cout << "********  退出图书系统请按0  *********" << endl;
    cout << "*************************************" << endl;
}
void showMenu1()
{
    cout << "*************************************" << endl;
    cout << "********  书是人类进步的阶梯  *********" << endl;
    cout << "********    购买书籍请按1    *********" << endl;
    cout << "********    整理书籍请按2    *********" << endl;
    cout << "********  显示书籍信息请按3  *********" << endl;
    cout << "********  保存图书信息请按4  *********" << endl;
    cout << "********  退出图书系统请按0  *********" << endl;
    cout << "*************************************" << endl;
}
void showMenu2()
{
    cout << "*************************************" << endl;
    cout << "********   添加书籍信息请按1      *****" << endl;
    cout << "********   修改书籍信息请按2      *****" << endl;
    cout << "********   退出整理系统请按0      *****" << endl;
    cout << "*************************************" << endl;
}
void showMenu3()
{
    cout << "*************************************" << endl;
    cout << "********   修改该书籍请按1   *****" << endl;
    cout << "********   删除该书籍请按2   *****" << endl;
    cout << "********      退出请按0     *****" << endl;
    cout << "*************************************" << endl;
}
void showMenu4()
{
    cout << "*************************************" << endl;
    cout << "***   请选择您检索书籍的方式   *******" << endl;
    cout << "***   通过书名查找请按1        ******" << endl;
    cout << "***   通过IBSN号查找请按2      ******" << endl;
    cout << "***   通过作者查找请按3        ******" << endl;
    cout << "***   通过出版社查找请按4       ******" << endl;
    cout << "***   退出查找请按0           *******" << endl;
    cout << "***********************************" << endl;
}
void showMenu5()
{
    cout << "*************************************" << endl;
    cout << "*****   您想要修改该书哪种信息   ******" << endl;
    cout << "*******    修改书名请按1      *******" << endl;
    cout << "*******    修改ISBN请按2      *******" << endl;
    cout << "*******    修改作者请按3      *******" << endl;
    cout << "*******   修改出版社请按4     *******" << endl;
    cout << "*******    修改价格请按5      *******" << endl;
    cout << "*******    修改库存请按6      *******" << endl;
    cout << "*******    退出修改请按0      *******" << endl;
    cout << "***********************************" << endl;
}
void showMenu6() {
    cout << "*********************************************" << endl;
    cout << "******    选择你要统计图书信息的排序方式    ******" << endl;
    cout << "*******        按ISBN统计请按1         *******" << endl;
    cout << "*******        按库存统计请按2          *******" << endl;
    cout << "*******        按价格统计请按3          *******" << endl;
    cout << "*******          退出请按0             *******" << endl;
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
        case'0'://退出
        {
            cout << "退出整理系统" << endl;
            return;
        }
        case '1'://添加
        {
            addBook(b);
            break;
        }
        case '2'://修改
        {
            Book gai = findBook(b);
            if (gai.ISBN != -1)
            {
                modifyBook(b, gai);
            }
            break;
        }
        }
        system("pause");//按任意键继续
        system("cls");//清屏
    }
}

int isExist(int isbn, vector<Book>& b)
{
    for (auto& i : b) { 
        //遍历这个Book类vector，判断ISBN是否唯一
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
    Book newbook;//声明一个Book类变量
    addBookName(b, newbook);
    addBookIsbn(b, newbook);
    addBookWriter(b, newbook);
    addBookPublishingHouse(b, newbook);
    addBookInStock(b, newbook);
    addBookPrice(b, newbook);
    //将信息读取到newbook变量中
    b.push_back(newbook);
    //再将newbook添加到Book类vector中
    cout << "添加成功" << endl;
}
void addBookIsbn(vector<Book>& b, Book& c) {
    int isbn;
    cout << "请输入ISBN号" << endl;
    while (true)
    {
        cin >> isbn;
        if (isExist(isbn, b) == -1)cout << "ISBN号重复，请重新输入" << endl;
        else break;
    }
    c.ISBN = isbn;
}
void addBookName(vector<Book>& b, Book& c) {
    string name;
    cout << "请输入书名" << endl;
    cin >> name;
    c.name = name;
}
void addBookWriter(vector<Book>& b, Book& c) {
    string writer;
    cout << "请输入作者" << endl;
    cin >> writer;
    c.writer = writer;
}
void addBookPublishingHouse(vector<Book>& b, Book& c) {
    string chubanshe;
    cout << "请输入出版社" << endl;
    cin >> chubanshe;
    c.publishingHouse = chubanshe;
}
void addBookInStock(vector<Book>& b, Book& c) {
    int kucun;
    cout << "请输入库存" << endl;
    cin >> kucun;
    c.inStock = kucun;
}
void addBookPrice(vector<Book>& b, Book& c) {
    int jiage;
    cout << "请输入价格" << endl;
    cin >> jiage;
    c.price = jiage;
}

void modifyBook(vector<Book>& b, Book& c) {
    showMenu3();
    char choose4;
    cin >> choose4;
    switch (choose4)
    {
    case '0'://退出
    {
        cout << "退出修改系统" << endl;
        break;
    }
    case '1'://修改
    {
        modifyBookInformation(b, c);

        break;
    }
    case '2'://删除
    {
        Book::deleteBook(b, c);
        break;
    }
    default:
    {
        cout << "指令错误，修改失败" << endl;
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
            cout << "退出修改系统" << endl;
            return;
        }
        default:
        {
            cout << "指令错误，请重新输入" << endl;
            break;
        }
        }

    }
}
void modifyBookName(vector<Book>& b, Book& c)
{
    string name;
    cout << "请输入修改后书名" << endl;
    cin >> name;
    int i = 0;
    for (; i < b.size(); ++i) {
        if (b[i].ISBN == c.ISBN)break;
    }
    b[i].name = name;
    cout << "修改成功" << endl;
}
void modifyBookIsbn(vector<Book>& b, Book& c)
{
    int isbn;
    cout << "请输入修改后ISBN号" << endl;
    cin >> isbn;
    if (isExist(isbn, b) == -1)//判断ISBN是否重复
    {
        cout << "ISBN重复，修改失败" << endl;
    }
    else {
        int i = 0;
        for (; i < b.size(); ++i) {
            if (b[i].ISBN == c.ISBN)break;
        }
        b[i].ISBN = isbn;
        cout << "修改成功" << endl;
    }
}
void modifyBookChubanshe(vector<Book>& b, Book& c)
{
    string chubanshe;
    cout << "请输入修改后出版社" << endl;
    cin >> chubanshe;
    int i = 0;
    for (; i < b.size(); ++i) {
        if (b[i].ISBN == c.ISBN)break;
    }
    b[i].publishingHouse = chubanshe;
    cout << "修改成功" << endl;
}
void modifyBookWriter(vector<Book>& b, Book& c)
{
    string zuozhe;
    cout << "请输入修改后作者" << endl;
    cin >> zuozhe;
    int i = 0;
    for (; i < b.size(); ++i) {
        if (b[i].ISBN == c.ISBN)break;
    }
    b[i].writer = zuozhe;
    cout << "修改成功" << endl;
}
void modifyBookKucun(vector<Book>& b, Book& c)
{
    int kucun;
    cout << "请输入修改后库存" << endl;
    cin >> kucun;
    int i = 0;
    for (; i < b.size(); ++i) {
        if (b[i].ISBN == c.ISBN)break;
    }
    b[i].inStock = kucun;
    cout << "修改成功" << endl;
}
void modifyBookJiage(vector<Book>& b, Book& c)
{
    int jiage;
    cout << "请输入修改后价格" << endl;
    cin >> jiage;
    int i = 0;
    for (; i < b.size(); ++i) {
        if (b[i].ISBN == c.ISBN)break;
    }
    b[i].price = jiage;
    cout << "修改成功" << endl;
}

bool quanxian()
{
    cout << "请输入密码来证明您的权限" << endl;
    string c;
    cin >> c;
    return c == "73748156";
}

bool denglu(vector<User> u)
{
    string name, password;
    cout << "请输入用户名" << endl;
    cin >> name;
    int a = isUserExist(name, u);
    if (a == -1) {
        cout << "用户名不存在，登录失败" << endl;
        return false;
    }
    else
    {
        cout << "请输入密码" << endl;
        cin >> password;
        if (u[a].password == password) {
            cout << "登录成功" << endl;
            return true;
        }
        else
        {
            cout << "密码错误，登录失败" << endl;
            return false;
        }
    }
}

void zhuce(vector<User>& u)
{
    string password;
    User tmp;
    string name;
    cout << "请输入用户名" << endl;
    cin >> name;
    int a = isUserExist(name, u);
    if (a == -1)
    {
        tmp.userName = name;
        cout << "请输入密码" << endl;
        cin >> password;
        tmp.password = password;
        u.push_back(tmp);
        ofstream ofs;
        ofs.open(FILENAME2, ios::out);
        for (auto& i : u) {//录入用户信息
            ofs  << i.userName << " "<< i.password << endl;
        }
        cout << "保存成功" << endl;
        ofs.close();//关闭文件
    }
    else cout << "该用户名已被使用，注册失败" << endl;
}

void fetchUser(vector<User>& u)
{
    ifstream ifs;
    ifs.open(FILENAME2, ios::in);//读文件
    if (!ifs.is_open())//判断是否存在
    {
        cout << "用户文件不存在" << endl;
        ifs.close();
        return;
    }

    User temp;
    while (ifs >> temp.userName && ifs >> temp.password)//信息读取到temp中
    {
        u.push_back(temp);//将temp存在u中
    }
    ifs.close();
    if (u.empty())
    {
        cout << "用户文件为空" << endl;
    }
    else
        cout << "当前用户数目为" << u.size() << "位" << endl;
}

void save(vector<Book>& b)
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for (auto& i : b) {//录入每本书信息
        ofs << i.name << " " << i.ISBN << " " << i.writer << " "
            << i.publishingHouse << " " << i.inStock << " " << i.price << endl;
        //将所有信息存储，信息之间以空格分隔，书之间以换行符分隔
    }
    cout << "保存成功" << endl;
    ofs.close();//关闭文件

}

void fetchBook(vector<Book>& b)
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//读文件
    if (!ifs.is_open())//判断是否存在
    {
        cout << "图书文件不存在" << endl;
        ifs.close();
        return;
    }

    Book temp;
    while (ifs >> temp.name && ifs >> temp.ISBN && ifs >> temp.writer && ifs >> temp.publishingHouse &&
        ifs >> temp.inStock && ifs >> temp.price)//信息读取到temp中
    {
        b.push_back(temp);//将temp存在b中
    }
    ifs.close();
    if (b.empty())
    {
        cout << "图书文件为空" << endl;
    }
    else
        cout << "当前图书种类数目为" << b.size() << "本" << endl;
}

//
// Created by DELL on 2020/5/1.
//

