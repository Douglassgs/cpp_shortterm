#include <iostream>
#include "src/library.cpp"
using namespace std;


int main()
{
    Library lib;
    int choice;
    while (true)
    {
        cout << "\n=============== 图书管理系统 ===============\n" << endl;
        cout << "1. 添加图书" << endl;
        cout << "2. 借出图书" << endl;
        cout << "3. 归还图书" << endl;
        cout << "4. 查找图书" << endl;
        cout << "5. 显示各类图书数量" << endl;
        cout << "6. 显示所有图书" << endl;
        cout << "0. 退出系统" << endl;
        cout << "请输入以选择功能: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            {
                Books* book = nullptr;
                cin>>book;
                lib.Add(book);
                break;
            }
        case 2:
            {
                string username, bookname;
                cout << "请输入用户名: ";
                cin >> username;
                cout << "请输入要借出的图书名称: ";
                cin >> bookname;
                lib.Lend(bookname, username);
                break;
            }
        case 3:
            {
                string username, bookname;
                cout << "请输入用户名: ";
                cin >> username;
                cout << "请输入要归还的图书名称: ";
                cin >> bookname;
                lib.Return(bookname, username);
                break;
            }
        case 4:
            {
                string bookname;
                cout << "请输入要查找的图书名称: ";
                cin >> bookname;
                Books* book = lib.Search(bookname);
                if (book != nullptr)
                {
                    cout << "找到图书: " << endl;
                    book->ShowMe();
                }
                else
                {
                    cout << "未找到图书: " << bookname << endl;
                }
                break;
            }
        case 5:
            {
                lib.CountAllBooks();
                break;
            }
        case 6:
            {
                lib.ShowAllBooks();
                break;
            }
        default:
            {
                cout << "退出系统" << endl;
                return 0;
            }
        }
    }
}
