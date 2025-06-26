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
    Library()// 读入文件
    {
        ifstream file;
        file.open("library.txt");
        if (!file.is_open())
        {
            cout << "文件打开失败" << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string bookname, bookid,author,publisher;
            double price;
            int quantity;
            iss >> bookname >> bookid ; // 假设文件格式是：书名 图书ID 其他信息
            if (bookid[0] == 'S')
            {
                ScienceBook* book = new ScienceBook();
                file >> *book;
                BookList.push_back(book);
            }
            else if (bookid[0] == 'H')
            {
                SocialBook* book = new SocialBook();
                file >> *book;
                BookList.push_back(book);
            }
            else if (bookid[0] == 'F')
            {
                ForeignBook* book = new ForeignBook();
                file >> *book;
                BookList.push_back(book);
            }
        }
        file.close();
        cout << "文件读取成功" << endl;
        ifstream userfile;
        userfile.open("userlist.txt");
        if (!userfile.is_open())
        {
            cout << "文件打开失败" << endl;
            return;
        }
        string userline;
        while (getline(userfile, userline))
        {
            string username, bookid;
            chrono::high_resolution_clock::time_point borrowtime, returntime;
            auto timeFromStream = [](std::istream& is) {
                std::time_t timeT;
                is >> timeT;
                return std::chrono::system_clock::from_time_t(timeT);
            };
            userfile >> username >> bookid;
            borrowtime = timeFromStream(userfile);
            returntime = timeFromStream(userfile);
            BorrowList.push_back(Borrow(bookid, username, borrowtime, returntime));
        }
        userfile.close();
    }
    ~Library()//写入文件
    {
        ofstream file,userlist;
        file.open("../library.txt");
        userlist.open("../userlist.txt");
        auto bookit = BookList.begin();
        auto userit = BorrowList.begin();
        while (true)
        {
            file << bookit->data->getName() << " " << bookit->data->getBookID() << " " << bookit->data->getPrice() << " " << bookit->data->getAuthor() << " " << bookit->data->getPublisher() << " " << bookit->data->getQuantity() << endl;
            auto timeToString = [](const std::chrono::high_resolution_clock::time_point& time) {
                std::time_t timeT = std::chrono::system_clock::to_time_t(std::chrono::system_clock::time_point(time));
                return std::string(std::ctime(&timeT));
            };

            userlist << userit->data.username() << " " << userit->data.book_id() << " "
                     << timeToString(userit->data.borrow_time()) << " "
                     << timeToString(userit->data.return_time()) << endl;
            if (bookit == BookList.end()&&userit==BorrowList.end())
            {
                break;
            }
            bookit++;
            userit++;
        }
        file.close();
        cout << "文件写入成功" << endl;
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
    cout << "\n=============== 图书馆所有图书信息 ===============\n" << endl;
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

};
