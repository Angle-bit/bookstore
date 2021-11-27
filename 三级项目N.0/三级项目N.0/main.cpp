#include <iostream>
#include <string>
#include <vector>
#include"Book.h"
#include "BookManager.h"
#include <fstream>
#define FILENAME "library.txt"
#include"User.h"
using namespace std;


int main() {
    system("color 9F");
    vector<Book>lib;
    vector<User>users;
    fetchUser(users);
    fetchBook(lib);
    selectOption(lib, users);
    return 0;
}
