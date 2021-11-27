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
    cout << "书名：" << b.name << "\tISBN：" << b.ISBN << "\t作者："
        << b.writer << "\t出版社：" << b.publishingHouse << "\t价格：" << b.price << "\t库存：" << b.inStock << endl;
}
void Book::deleteBook(vector<Book>& b, Book c)
{
    int i;
    for (i = 0; i < b.size(); i++) {//通过ISBN查找这本书
        if (b[i].ISBN == c.ISBN) {
            b.erase(b.begin() + i);//删除这本书
        }
    }
    cout << "删除成功" << endl;
}
