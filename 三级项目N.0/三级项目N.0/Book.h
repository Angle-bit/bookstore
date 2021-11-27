//
// Created by DELL on 2020/5/1.
//
#ifndef INC_3_2_BOOK_H
#define INC_3_2_BOOK_H
#include<iostream>
#include<string>
#include <vector>
#include <fstream>
#define FILENAME "library.txt"
using namespace std;
class Book
{
public:
    Book();
    ~Book();
    string name;
    int ISBN;
    int price;
    string writer;
    string publishingHouse;
    int inStock;
    static void show(Book b);
    static void deleteBook(vector<Book>& b, Book c);
};

#endif //INC_3_2_BOOK_H
