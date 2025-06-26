#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
using namespace std;

// 友元函数
class ScienceBook;
class SocialBook;
class ForeignBook;

class Books
{
protected: // 允许派生类访问
    string bookID;
    string name;
    double price;
    string author;
    string publisher;
    int quantity;

public:
    Books(const string& id, const string& n, double p,
          const string& a, const string& pub, int q)
        : bookID(id), name(n), price(p), author(a), publisher(pub), quantity(q)
    {
    }

    virtual ~Books()
    {
    } // 虚析构函数

    // Get方法
    string getBookID() const { return bookID; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    string getAuthor() const { return author; }
    string getPublisher() const { return publisher; }
    int getQuantity() const { return quantity; }

    // Set方法
    void setQuantity(int q) { quantity = q; }

    // 纯虚函数
    virtual void ShowMe() = 0;

    // 友元函数重载 >> 操作符
    friend istream& operator>>(istream& is, ScienceBook& book);
    friend istream& operator>>(istream& is, SocialBook& book);
    friend istream& operator>>(istream& is, ForeignBook& book);
};

class ScienceBook : public Books
{
public:
    ScienceBook(const string& id = "", const string& n = "", double p = 0.0,
                const string& a = "", const string& pub = "", int q = 0)
        : Books(id, n, p, a, pub, q)
    {
    }

    void ShowMe() override
    {
        cout << "--- 自然科学图书信息 ---" << endl;
        cout << "图书编号: " << bookID << endl;
        cout << "名称: " << name << endl;
        cout << "价格: " << fixed << setprecision(2) << price << endl;
        cout << "作者: " << author << endl;
        cout << "出版社: " << publisher << endl;
        cout << "库存数量: " << quantity << endl;
    }
};

class SocialBook : public Books
{
public:
    SocialBook(const string& id = "", const string& n = "", double p = 0.0,
               const string& a = "", const string& pub = "", int q = 0)
        : Books(id, n, p, a, pub, q)
    {
    }

    void ShowMe() override
    {
        cout << "--- 人文社科图书信息 ---" << endl;
        cout << "图书编号: " << bookID << endl;
        cout << "名称: " << name << endl;
        cout << "价格: " << fixed << setprecision(2) << price << endl;
        cout << "作者: " << author << endl;
        cout << "出版社: " << publisher << endl;
        cout << "库存数量: " << quantity << endl;
    }
};

class ForeignBook : public Books
{
private:
    string language;

public:
    ForeignBook(const string& id = "", const string& n = "", double p = 0.0,
                const string& a = "", const string& pub = "", int q = 0,
                const string& lang = "")
        : Books(id, n, p, a, pub, q), language(lang)
    {
    }

    // Getter for language
    string getLanguage() const { return language; }

    void ShowMe() override
    {
        cout << "--- 外文图书信息 ---" << endl;
        cout << "图书编号: " << bookID << endl;
        cout << "名称: " << name << endl;
        cout << "价格: " << fixed << setprecision(2) << price << endl;
        cout << "作者: " << author << endl;
        cout << "出版社: " << publisher << endl;
        cout << "语言: " << language << endl;
        cout << "库存数量: " << quantity << endl;
    }
};

// 重载输入操作符
istream& operator>>(istream& in, Books*& book)
{
    cout << "请输入图书信息" << endl;

    // 图书类型
    cout << "选择图书类型 (1.科学 2.人文社科 3.外文图书): " << endl;
    int type;
    while (!(in >> type) || type < 1 || type > 3)
    {
        in.clear();
        in.ignore(1024, '\n');
        cout << "输入无效! 请重新选择 (1-3): ";
    }

    //输入通用属性
    cout << "请输入图书ID: ";
    string id;
    in >> id;

    cout << "请输入书名: ";
    string name;
    in.ignore();
    getline(in, name);

    cout << "请输入价格: ";
    double price;
    in >> price;

    cout << "输入作者: ";
    string author;
    in.ignore();
    getline(in, author);

    cout << "请输入出版社: ";
    string publisher;
    getline(in, publisher);

    cout << "输入库存数: ";
    int quantity;
    in >> quantity;

    //创建对象
    switch (type)
    {
    case 1:
        book = new ScienceBook('S'+id, name, price, author, publisher, quantity);
        break;
    case 2:
        book = new SocialBook('H'+id, name, price, author, publisher, quantity);
        break;
    case 3:
        {
            cout << "请输入语言: ";
            string language;
            in >> language;
            book = new ForeignBook('F'+id, name, price, author, publisher, quantity, language);
            break;
        }
    default:
        cout << "无效的图书类型!" << endl;
        break;
    }
    return in;
}

class Borrow
{
private:
    string BookId, Username;
    chrono::high_resolution_clock::time_point BorrowTime, ReturnTime;

public:
    string book_id() const
    {
        return BookId;
    }

    string username() const
    {
        return Username;
    }

    chrono::high_resolution_clock::time_point borrow_time() const
    {
        return BorrowTime;
    }

    void set_return_time(const chrono::high_resolution_clock::time_point& return_time)
    {
        ReturnTime = return_time;
    }

    chrono::high_resolution_clock::time_point return_time() const
    {
        return ReturnTime;
    }


    Borrow() : BookId(""), Username(""),
               BorrowTime(chrono::high_resolution_clock::now()),
               ReturnTime(chrono::high_resolution_clock::now())
    {
    }

    Borrow(string BookId, string Username, chrono::high_resolution_clock::time_point BorrowTime,
           chrono::high_resolution_clock::time_point ReturnTime): BookId(BookId), Username(Username),
                                                                  BorrowTime(BorrowTime), ReturnTime(ReturnTime)
    {
    }

    void PrintTimeVector(const chrono::high_resolution_clock::time_point& time, const string& label)
    {
        cout << label << ": ";
        time_t timeT = chrono::system_clock::to_time_t(chrono::system_clock::time_point(time));
        cout << std::ctime(&timeT) << " ";
        cout << endl;
    }

    void ShowMe()
    {
        cout << "图书编号: " << BookId << endl;
        cout << "用户名: " << Username << endl;
        PrintTimeVector(BorrowTime, "借阅时间");
        if (ReturnTime == chrono::high_resolution_clock::time_point())
        {
            cout << "归还时间: 未归还" << endl;
        }
        else
        {
            PrintTimeVector(ReturnTime, "归还时间");
        }
    }
};

class Library
{
private:
    list<Books*> BookList;
    list<Borrow> BorrowList;
    // 查找函数，用于查找图书
    static bool SearchInLibrary(string target, Books* value)
    {
        if (value == nullptr) return false;
        return target == value->getName();
    }

public:
    Library()
    {
        ifstream file("library.txt");
        if (!file.is_open())
        {
            cout << "图书文件打开失败" << endl;
            return;
        }
        string line1, name, id, author, publisher;
        double price;
        int quantity;

        while (getline(file, line1))
        {
            if (line1.empty()) continue;

            istringstream iss(line1);
            iss >> name >> id >> price >> author >> publisher >> quantity;

            if (id[0] == 'S')
            {
                BookList.push_back(new ScienceBook(id, name, price, author, publisher, quantity));
            }
            else if (id[0] == 'H')
            {
                BookList.push_back(new SocialBook(id, name, price, author, publisher, quantity));
            }
            else if (id[0] == 'F')
            {
                string language;
                iss >> language;
                BookList.push_back(new ForeignBook(id, name, price, author, publisher, quantity, language));
            }
        }
        file.close();
        cout << "图书文件读取成功" << endl;
        // 读取借阅记录
        ifstream userfile("userlist.txt");
        if (!userfile.is_open())
        {
            cout << "用户借阅文件不存在或无法打开，将创建新文件" << endl;
            return;
        }

        // 清除文件流状态和缓存
        userfile.clear();

        string line2, username, bookid;
        time_t borrowTimeT, returnTimeT;

        while (getline(userfile, line2))
        {
            if (line2.empty()) continue;

            istringstream iss(line2);
            if (iss >> username >> bookid >> borrowTimeT >> returnTimeT)
            {
                auto borrowTime = chrono::system_clock::from_time_t(borrowTimeT);
                auto returnTime = chrono::system_clock::from_time_t(returnTimeT);
                BorrowList.push_back(Borrow(bookid, username,
                                    chrono::high_resolution_clock::time_point(borrowTime),
                                    chrono::high_resolution_clock::time_point(returnTime)));
            }
            else
            {
                cout << "警告: 跳过格式不正确的行: " << line2 << endl;
            }
        }

        // 清除文件流状态
        userfile.clear();
        userfile.close();
        cout << "用户借阅数据读取成功" << endl;
    }

    ~Library()
    {
        SaveBooksToFile();
        SaveUsersToFile();
    }

    void Add(Books* book) // 添加新图书
    {
        Books* findbook = Search(book->getName());
        if (findbook != nullptr)
        {
            cout << "图书《" << book->getName() << "》已存在，库存将增加。" << endl;
            int number = findbook->getQuantity();
            findbook->setQuantity(number + book->getQuantity());
            cout << "《" << book->getName() << "》库存已更新: " << findbook->getQuantity() << endl;
            delete book;
        }
        else
        {
            cout << "新书《" << book->getName() << "》已入库。" << endl;
            BookList.push_back(book);
        }
        SaveBooksToFile();
    }

    void Lend(const string& bookname, const string& username, int count)
    {
        Books* findbook = Search(bookname);
        if (findbook != nullptr)
        {
            int number = findbook->getQuantity();
            if (number >= count)
            {
                findbook->setQuantity(number - count);
                cout << "《" << bookname << "》借出成功，借出本数: " << count << "，剩余库存: " << findbook->getQuantity() << endl;
                auto borrowtime = chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    BorrowList.push_back(Borrow(findbook->getBookID(), username, borrowtime,
                                                chrono::high_resolution_clock::time_point()));
                }
            }
            else
            {
                cout << "《" << bookname << "》库存不足，无法借出。当前库存: " << number << endl;
            }
        }
        SaveUsersToFile();
    }

    void Return(const string& bookname, const string& username) // 归还图书
    {
        Books* findbook = Search(bookname);
        if (findbook != nullptr)
        {
            int number = findbook->getQuantity();
            findbook->setQuantity(number + 1);
            cout << "《" << bookname << "》归还成功，当前库存: " << findbook->getQuantity() << endl;
            for (auto it = BorrowList.begin(); it != BorrowList.end(); ++it)
            {
                if ((it->book_id() == findbook->getBookID()) && (it->username() == username))
                {
                    auto time = chrono::high_resolution_clock::now();
                    it->set_return_time(time);
                    break;
                }
            }
        }
        else
        {
            cout << "归还失败，图书馆无此图书记录: 《" << bookname << "》" << endl;
        }
        SaveUsersToFile();
    }

    Books* Search(string bookname) // 查找图书
    {
        for (auto it = BookList.begin(); it != BookList.end(); ++it)
        {
            if (SearchInLibrary(bookname, *it))
            {
                return *it;
            }
        }
        return nullptr;
    }

    void ShowAllBooks() // 显示所有图书
    {
        if (BookList.empty())
        {
            cout << "图书馆中没有图书。" << endl;
            return;
        }
        for (auto it = BookList.begin(); it != BookList.end(); ++it)
        {
            (*it)->ShowMe();
            cout << "--------------------------------------------------" << endl;
        }
        cout << "==================== 显示完毕 ====================\n" << endl;
    }

    void CountAllBooks() //显示各类图书数量
    {
        int ScienceBookNum = 0, SocialBookNum = 0, ForeignBookNum = 0;
        if (BookList.empty())
        {
            cout << "图书馆中没有图书。" << endl;
            return;
        }
        cout << "\n=============== 图书馆各类图书数量 ===============\n" << endl;
        for (auto iter = BookList.begin(); iter != BookList.end(); ++iter)
        {
            if (dynamic_cast<ScienceBook*>(*iter) != nullptr)
                ScienceBookNum++;
            else if (dynamic_cast<SocialBook*>(*iter) != nullptr)
                SocialBookNum++;
            else if (dynamic_cast<ForeignBook*>(*iter) != nullptr)
                ForeignBookNum++;
        }
        cout << "自然科学图书数量: " << ScienceBookNum << endl;
        cout << "人文社科图书数量: " << SocialBookNum << endl;
        cout << "外文图书数量: " << ForeignBookNum << endl;
        cout << "==================== 显示完毕 ====================\n" << endl;
    }

    void SaveBooksToFile()
    {
        ofstream file("library.txt");
        if (!file.is_open())
        {
            cout << "无法打开图书文件进行写入" << endl;
            return;
        }
        for (auto bookit = BookList.begin(); bookit != BookList.end(); ++bookit)
        {
            file << (*bookit)->getName() << " "
                << (*bookit)->getBookID() << " "
                << (*bookit)->getPrice() << " "
                << (*bookit)->getAuthor() << " "
                << (*bookit)->getPublisher() << " "
                << (*bookit)->getQuantity();
            auto foreignBook = dynamic_cast<ForeignBook*>(*bookit);
            if (foreignBook)
            {
                file << " " << foreignBook->getLanguage();
            }
            file << endl;
        }
        file.close();
        cout << "图书数据已保存到文件" << endl;
    }

    void SaveUsersToFile()
    {
        ofstream userlist("userlist.txt");
        if (!userlist.is_open())
        {
            cout << "无法打开用户文件进行写入" << endl;
            return;
        }
        for (auto userit = BorrowList.begin(); userit != BorrowList.end(); ++userit)
        {
            time_t borrowTimeT = chrono::system_clock::to_time_t(
                chrono::system_clock::time_point(userit->borrow_time()));
            time_t returnTimeT = chrono::system_clock::to_time_t(
                chrono::system_clock::time_point(userit->return_time()));
            userlist << userit->username() << " "
                << userit->book_id() << " "
                << borrowTimeT << " "
                << returnTimeT << endl;
        }
        userlist.close();
        cout << "用户借阅数据已保存到文件" << endl;
    }

    void ShowAllBorrows() // 显示所有借阅记录
    {
        if (BorrowList.empty())
        {
            cout << "没有借阅记录。" << endl;
            return;
        }
        cout << "\n=============== 所有借阅记录 ===============\n" << endl;
        for (auto it = BorrowList.begin(); it != BorrowList.end(); ++it)
        {
            it->ShowMe();
            cout << "--------------------------------------------------" << endl;
        }
        cout << "==================== 显示完毕 ====================\n" << endl;
    }
};


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
        cout << "7. 显示所有借阅记录" << endl;
        cout << "0. 退出系统" << endl;
        cout << "请输入以选择功能: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入缓冲区
        switch (choice)
        {
        case 1:
            {
                Books* book = nullptr;
                cin >> book;
                lib.Add(book);
                break;
            }
        case 2:
            {
                string username, bookname;
                int count;
                cout << "请输入用户名: ";
                cin >> username;
                cout << "请输入要借出的图书名称: ";
                cin >> bookname;
                cout << "请输入借出数量: ";
                cin >> count;
                lib.Lend(bookname, username,count);
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
        case 7:
            {
                lib.ShowAllBorrows();
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
