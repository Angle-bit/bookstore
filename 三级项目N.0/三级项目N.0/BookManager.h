//
// Created by DELL on 2020/5/1.
//
#ifndef INC_3_2_BOOKMANAGER_H
#define INC_3_2_BOOKMANAGER_H
#include"Book.h"
#include<vector>
#include <iostream>
#include <string>
#include"User.h"
#include <fstream>
#define FILENAME "library.txt"
using namespace std;


void selectOption(vector<Book>& b, vector<User>& u);

void buyBook(vector<Book>& b);

void tongji(vector<Book>& b);

bool isbnCmp(const Book& a, const Book& b);
bool priceCmp(const Book& a, const Book& b);
bool inStockCmp(const Book& a, const Book& b);

void showMenu0();
void showMenu1();
void showMenu2();
void showMenu3();
void showMenu4();
void showMenu5();
void showMenu6();

Book findBook(vector<Book>& b);
void findBookName(vector<Book>& b, vector<Book>& c);
void findBookWriter(vector<Book>& b, vector<Book>& c);
void findBookPublishingHouse(vector<Book>& b, vector<Book>& c);
void findBookIsbn(vector<Book>& b, vector<Book>& c);

void addBook(vector<Book>& b);
void addBookIsbn(vector<Book>& b, Book& c);
void addBookName(vector<Book>& b, Book& c);
void addBookWriter(vector<Book>& b, Book& c);
void addBookPublishingHouse(vector<Book>& b, Book& c);
void addBookInStock(vector<Book>& b, Book& c);
void addBookPrice(vector<Book>& b, Book& c);

int isExist(int isbn, vector<Book>& b);
int isUserExist(string name, vector<User>u);

void save(vector<Book>& b);
void fetchBook(vector<Book>& b);

void userDengLu();

void arrangeBook(vector<Book>& b);

bool quanxian();

bool denglu(vector<User>u);

void zhuce(vector<User>& u);

void fetchUser(vector<User>& u);

void modifyBookInformation(vector<Book>& b, Book& c);
void modifyBook(vector<Book>& b, Book& c);
void modifyBookName(vector<Book>& b, Book& c);
void modifyBookIsbn(vector<Book>& b, Book& c);
void modifyBookChubanshe(vector<Book>& b, Book& c);
void modifyBookWriter(vector<Book>& b, Book& c);
void modifyBookKucun(vector<Book>& b, Book& c);
void modifyBookJiage(vector<Book>& b, Book& c);
#endif //INC_3_2_BOOKMANAGER_H
