#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // For std::fixed and std::setprecision

// 前向声明，用于友元函数
class ScienceBook;
class SocialBook;
class ForeignBook;

class Books {
protected: // 允许派生类访问
    std::string bookID;
    std::string name;
    double price;
    std::string author;
    std::string publisher;
    int quantity;

public:
    Books(const std::string& id, const std::string& n, double p,
          const std::string& a, const std::string& pub, int q)
        : bookID(id), name(n), price(p), author(a), publisher(pub), quantity(q) {}

    virtual ~Books() {} // 虚析构函数

    // Getter methods
    std::string getBookID() const { return bookID; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    std::string getAuthor() const { return author; }
    std::string getPublisher() const { return publisher; }
    int getQuantity() const { return quantity; }

    // Setter methods (for updating quantity, etc.)
    void setQuantity(int q) { quantity = q; }

    // 纯虚函数
    virtual void ShowMe() = 0;

    // 友元函数重载 >> 操作符
    friend std::istream& operator>>(std::istream& is, ScienceBook& book);
    friend std::istream& operator>>(std::istream& is, SocialBook& book);
    friend std::istream& operator>>(std::istream& is, ForeignBook& book);
};

class ScienceBook : public Books {
public:
    ScienceBook(const std::string& id = "", const std::string& n = "", double p = 0.0,
                const std::string& a = "", const std::string& pub = "", int q = 0)
        : Books(id, n, p, a, pub, q) {}

    void ShowMe() override {
        std::cout << "--- 自然科学图书信息 ---" << std::endl;
        std::cout << "图书编号: " << bookID << std::endl;
        std::cout << "名称: " << name << std::endl;
        std::cout << "价格: " << std::fixed << std::setprecision(2) << price << std::endl;
        std::cout << "作者: " << author << std::endl;
        std::cout << "出版社: " << publisher << std::endl;
        std::cout << "库存数量: " << quantity << std::endl;
    }
};

class SocialBook : public Books {
public:
    SocialBook(const std::string& id = "", const std::string& n = "", double p = 0.0,
               const std::string& a = "", const std::string& pub = "", int q = 0)
        : Books(id, n, p, a, pub, q) {}

    void ShowMe() override {
        std::cout << "--- 人文社科图书信息 ---" << std::endl;
        std::cout << "图书编号: " << bookID << std::endl;
        std::cout << "名称: " << name << std::endl;
        std::cout << "价格: " << std::fixed << std::setprecision(2) << price << std::endl;
        std::cout << "作者: " << author << std::endl;
        std::cout << "出版社: " << publisher << std::endl;
        std::cout << "库存数量: " << quantity << std::endl;
    }
};

class ForeignBook : public Books {
private:
    std::string language;
public:
    ForeignBook(const std::string& id = "", const std::string& n = "", double p = 0.0,
                const std::string& a = "", const std::string& pub = "", int q = 0,
                const std::string& lang = "")
        : Books(id, n, p, a, pub, q), language(lang) {}

    // Getter for language
    std::string getLanguage() const { return language; }

    void ShowMe() override {
        std::cout << "--- 外文图书信息 ---" << std::endl;
        std::cout << "图书编号: " << bookID << std::endl;
        std::cout << "名称: " << name << std::endl;
        std::cout << "价格: " << std::fixed << std::setprecision(2) << price << std::endl;
        std::cout << "作者: " << author << std::endl;
        std::cout << "出版社: " << publisher << std::endl;
        std::cout << "语言: " << language << std::endl;
        std::cout << "库存数量: " << quantity << std::endl;
    }
};