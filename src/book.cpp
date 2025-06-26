#include <iostream>
#include <string>
#include <iomanip>
#include <bits/unique_ptr.h>
using namespace std;

// 前向声明，用于友元函数
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
istream& operator>>(istream& in, Books* book)
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
        book = new ScienceBook(id, name, price, author, publisher, quantity);
        break;
    case 2:
        book = new SocialBook(id, name, price, author, publisher, quantity);
        break;
    case 3:
        {
            cout << "请输入语言: ";
            string language;
            in >> language;
            book = new ForeignBook(id, name, price, author, publisher, quantity, language);
            break;
        }
    default:
        cout << "无效的图书类型!" << endl;
        break;
    }
    return in;
}

// 为 ScienceBook 实现输入操作符重载
istream& operator>>(istream& in, ScienceBook& book) {
    // 从流中读取基本属性
    in >> book.bookID >> book.name >> book.price >> book.author >> book.publisher >> book.quantity;
    return in;
}

// 为 SocialBook 实现输入操作符重载
istream& operator>>(istream& in, SocialBook& book) {
    // 从流中读取基本属性
    in >> book.bookID >> book.name >> book.price >> book.author >> book.publisher >> book.quantity;
    return in;
}

// 为 ForeignBook 实现输入操作符重载
istream& operator>>(istream& in, ForeignBook& book) {
    // 从流中读取基本属性和语言属性
    string language;
    in >> book.bookID >> book.name >> book.price >> book.author >> book.publisher >> book.quantity >> language;
    return in;
}