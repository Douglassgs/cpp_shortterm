//
// Created by 张励迅 on 25-6-25.
//

#include "../inc/DoubleLinkedList.hpp"
#include "Book.cpp"//todo:在这里引用Boooks类文件
#include "borrow.cpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string bookname;

class Library
{
private:
    DoubleLinkedList<Books*> BookList;
    DoubleLinkedList<Borrow> BorrowList;

    // 查找函数，用于查找图书
    static bool SearchInLibrary(string target, Books* value)
    {
        if (value == nullptr) return false;
        return target == value->getName();
    }

public:
    Library() {
        ifstream file("../library.txt");
        if (!file.is_open()) {
            cout << "图书文件打开失败" << endl;
            return;
        }

        string name, id, author, publisher;
        double price;
        int quantity;

        while (file >> name >> id >> price >> author >> publisher >> quantity) {
            if (id[0] == 'S') {
                BookList.push_back(new ScienceBook(id, name, price, author, publisher, quantity));
            } else if (id[0] == 'H') {
                BookList.push_back(new SocialBook(id, name, price, author, publisher, quantity));
            } else if (id[0] == 'F') {
                string language;
                file >> language; // 外文图书需要额外读取语言
                BookList.push_back(new ForeignBook(id, name, price, author, publisher, quantity, language));
            }
        }
        file.close();
        cout << "图书文件读取成功" << endl;

        // 读取借阅记录
        ifstream userfile("../userlist.txt");
        if (!userfile.is_open()) {
            cout << "用户借阅文件不存在或无法打开，将创建新文件" << endl;
            return;
        }

        string username, bookid;
        time_t borrowTimeT, returnTimeT;

        while (userfile >> username >> bookid >> borrowTimeT >> returnTimeT) {
            auto borrowTime = chrono::system_clock::from_time_t(borrowTimeT);
            auto returnTime = chrono::system_clock::from_time_t(returnTimeT);
            BorrowList.push_back(Borrow(bookid, username,
                                        chrono::high_resolution_clock::time_point(borrowTime),
                                        chrono::high_resolution_clock::time_point(returnTime)));
        }
        userfile.close();
    }
    ~Library() {
        SaveBooksToFile();
        SaveUsersToFile();
    }

    void Add(Books* book) // 添加新图书
    {
        //在链表中查找图书
        Books* findbook = Search(book->getName());
        if (findbook != nullptr)
        {
            cout << "图书《" << book->getName() << "》已存在，库存将增加。" << endl;
            int number = findbook->getQuantity();
            findbook->setQuantity(number + book->getQuantity());
            cout << "《" << book->getName() << "》库存已更新: " << findbook->getQuantity() << endl;
            delete book; // 因为图书已存在，传入的book对象不再需要，删除以防内存泄漏
        }
        else
        {
            cout << "新书《" << book->getName() << "》已入库。" << endl;
            BookList.push_back(book);
        }
        SaveBooksToFile();
    }

    void Lend(const string& bookname,const string& username) // 借出图书
    {
        //在链表中查找图书
        Books* findbook = Search(bookname);
        if (findbook != nullptr)
        {
            int number = findbook->getQuantity();
            if (number > 0)
            {
                findbook->setQuantity(number - 1);
                cout << "《" << bookname << "》借出成功，剩余库存: " << findbook->getQuantity() << endl;
                auto borrowtime=chrono::high_resolution_clock::now();
                BorrowList.push_back(Borrow(findbook->getBookID(), username, borrowtime, chrono::high_resolution_clock::time_point()));
            }
            else
            {
                cout << "《" << bookname << "》库存不足，无法借出。" << endl;
            }
        }
        SaveUsersToFile();
    }

    void Return(const string& bookname,const string& username) // 归还图书
    {
        //在链表中查找图书
        Books* findbook = Search(bookname);
        if (findbook != nullptr)
        {
            int number = findbook->getQuantity();
            findbook->setQuantity(number + 1);
            cout << "《" << bookname << "》归还成功，当前库存: " << findbook->getQuantity() << endl;
            //在借阅记录中添加还书时间
            auto it = BorrowList.begin();
            while (true)
            {
                if ((it->data.book_id() == findbook->getBookID())&&(it->data.username()==username))
                {
                    auto time=chrono::high_resolution_clock::now();
                    it->data.set_return_time(time);
                    break;
                }
                if (it == BorrowList.end())
                {
                    break;
                }
                it++;
            }
        }
        else
        {
            // 图书记录不存在
            cout << "归还失败，图书馆无此图书记录: 《" << bookname << "》" << endl;
        }
        SaveUsersToFile();
    }

    Books* Search(string bookname) // 查找图书
    {
        auto it = BookList.search(bookname, SearchInLibrary);

        if (it != nullptr)
        {
            return it->data;
        }
        return nullptr;
    }

    void ShowAllBooks()// 显示所有图书
    {
    if (BookList.getLen() == -1)
    {
        cout << "图书馆中没有图书。" << endl;
        return;
    }
    auto it = BookList.begin();
    while (true)
    {
        it->data->ShowMe();
        cout << "--------------------------------------------------" << endl;
        if (it == BookList.end())
        {
            break;
        }
        it++;
    }
    cout << "==================== 显示完毕 ====================\n" << endl;
    }

    void CountAllBooks()//显示各类图书数量
    {
        int ScienceBookNum = 0, SocialBookNum = 0, ForeignBookNum = 0;
        if (BookList.getLen() == -1)
        {
            cout << "图书馆中没有图书。" << endl;
            return;
        }
        cout << "\n=============== 图书馆各类图书数量 ===============\n" << endl;
        auto iter = BookList.begin();
        //动态类型转换操作,判断图书类型
        while (iter!=nullptr)
        {
            if (dynamic_cast<ScienceBook*>(iter->data) != nullptr)
                ScienceBookNum++;
            else if (dynamic_cast<SocialBook*>(iter->data)!= nullptr)
                SocialBookNum++;
            else if (dynamic_cast<ForeignBook*>(iter->data)!= nullptr)
                ForeignBookNum++;

            if (iter == BookList.end())
            {
                break;
            }
            iter++;
        }
        cout << "自然科学图书数量: " << ScienceBookNum << endl;
        cout << "人文社科图书数量: " << SocialBookNum << endl;
        cout << "外文图书数量: " << ForeignBookNum << endl;
        cout << "==================== 显示完毕 ====================\n" << endl;
    }

    void SaveBooksToFile()
    {
        ofstream file("../library.txt");  // 移除 ../前缀
        if (!file.is_open()) {
            cout << "无法打开图书文件进行写入" << endl;
            return;
        }

        auto bookit = BookList.begin();
        while (bookit != BookList.end()) {
            file << bookit->data->getName() << " "
                 << bookit->data->getBookID() << " "
                 << bookit->data->getPrice() << " "
                 << bookit->data->getAuthor() << " "
                 << bookit->data->getPublisher() << " "
                 << bookit->data->getQuantity();

            // 为外文图书额外写入语言信息
            auto foreignBook = dynamic_cast<ForeignBook*>(bookit->data);
            if (foreignBook) {
                file << " " << foreignBook->getLanguage();
            }

            file << endl;
            bookit++;
        }
        file.close();
        cout << "图书数据已保存到文件" << endl;
    }

    void SaveUsersToFile()
    {
        ofstream userlist("../userlist.txt");  // 移除 ../前缀
        if (!userlist.is_open()) {
            cout << "无法打开用户文件进行写入" << endl;
            return;
        }

        auto userit = BorrowList.begin();
        while (userit != BorrowList.end()) {
            // 转换时间点为时间戳
            time_t borrowTimeT = chrono::system_clock::to_time_t(
                chrono::system_clock::time_point(userit->data.borrow_time()));
            time_t returnTimeT = chrono::system_clock::to_time_t(
                chrono::system_clock::time_point(userit->data.return_time()));

            userlist << userit->data.username() << " "
                    << userit->data.book_id() << " "
                    << borrowTimeT << " "
                    << returnTimeT << endl;
            userit++;
        }
        userlist.close();
        cout << "用户借阅数据已保存到文件" << endl;
    }

};
