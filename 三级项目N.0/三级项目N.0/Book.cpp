//
// Created by DELL on 2020/5/1.
//
#include<iostream>
#include<fstream>

#include<string>
#include <vector>
#include"Book.h"
#include"BookManager.h"
using namespace std;
Book::Book() {}
Book::~Book() {}
void Book::show(Book b) {
    cout << "������" << b.name << "\tISBN��" << b.ISBN << "\t���ߣ�"
        << b.writer << "\t�����磺" << b.publishingHouse << "\t�۸�" << b.price << "\t��棺" << b.inStock << endl;
}
void Book::deleteBook(vector<Book>& b, Book c)
{
    int i;
    for (i = 0; i < b.size(); i++) {//ͨ��ISBN�����Ȿ��
        if (b[i].ISBN == c.ISBN) {
            b.erase(b.begin() + i);//ɾ���Ȿ��
        }
    }
    cout << "ɾ���ɹ�" << endl;
}
