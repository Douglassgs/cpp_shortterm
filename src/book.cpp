#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// 前向声明，用于友元函数
class ScienceBook;
class SocialBook;
class ForeignBook;

class Books {
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
        : bookID(id), name(n), price(p), author(a), publisher(pub), quantity(q) {}

    virtual ~Books() {} // 虚析构函数

    // Getter methods
    string getBookID() const { return bookID; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    string getAuthor() const { return author; }
    string getPublisher() const { return publisher; }
    int getQuantity() const { return quantity; }

    // Setter methods (for updating quantity, etc.)
    void setQuantity(int q) { quantity = q; }

    // 纯虚函数
    virtual void ShowMe() = 0;

    // 友元函数重载 >> 操作符
    friend istream& operator>>(istream& is, ScienceBook& book);
    friend istream& operator>>(istream& is, SocialBook& book);
    friend istream& operator>>(istream& is, ForeignBook& book);
};

class ScienceBook : public Books {
public:
    ScienceBook(const string& id = "", const string& n = "", double p = 0.0,
                const string& a = "", const string& pub = "", int q = 0)
        : Books(id, n, p, a, pub, q) {}

    void ShowMe() override {
        cout << "--- 自然科学图书信息 ---" << endl;
        cout << "图书编号: " << bookID << endl;
        cout << "名称: " << name << endl;
        cout << "价格: " << fixed << setprecision(2) << price << endl;
        cout << "作者: " << author << endl;
        cout << "出版社: " << publisher << endl;
        cout << "库存数量: " << quantity << endl;
    }
};

class SocialBook : public Books {
public:
    SocialBook(const string& id = "", const string& n = "", double p = 0.0,
               const string& a = "", const string& pub = "", int q = 0)
        : Books(id, n, p, a, pub, q) {}

    void ShowMe() override {
        cout << "--- 人文社科图书信息 ---" << endl;
        cout << "图书编号: " << bookID << endl;
        cout << "名称: " << name << endl;
        cout << "价格: " << fixed << setprecision(2) << price << endl;
        cout << "作者: " << author << endl;
        cout << "出版社: " << publisher << endl;
        cout << "库存数量: " << quantity << endl;
    }
};

class ForeignBook : public Books {
private:
    string language;
public:
    ForeignBook(const string& id = "", const string& n = "", double p = 0.0,
                const string& a = "", const string& pub = "", int q = 0,
                const string& lang = "")
        : Books(id, n, p, a, pub, q), language(lang) {}

    // Getter for language
    string getLanguage() const { return language; }

    void ShowMe() override {
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