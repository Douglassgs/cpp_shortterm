# 图书馆类基本完成，使用一个自定义的双向链表。读文件部分有赖于重载>>运算符。

## 项目简介

这是一个基于C++的图书馆管理系统，实现了图书的添加、查询、借阅、归还等功能。系统使用自定义的双向链表来存储图书信息和借阅记录，支持三种类型的图书：自然科学类、人文社科类和外文类。

### 图书馆类 (Library)

`Library`类是系统的核心，管理所有图书和借阅记录。

### 借阅类 (Borrow)

`Borrow`类记录图书的借阅信息，包括：
- 图书编号
- 借阅者用户名
- 借出时间
- 归还时间

### 双向链表 (DoubleLinkedList)

自定义的双向链表模板类，用于存储图书和借阅记录。

## 图书馆类主要函数

### 构造与析构函数

```cpp
Library();  // 构造函数，从文件加载图书信息
~Library();  // 析构函数，保存图书信息到文件
```

### 图书管理函数

```cpp
void Add(Books* book);  // 添加新图书，重复图书会增加库存
Books* Search(string bookname);  // 根据书名查找图书
void ShowAllBooks();  // 显示所有图书信息
void CountAllBooks();  // 统计各类图书数量
```

### 借阅管理函数

```cpp
void Lend(const string& bookname);  // 借出图书
void Return(const string& bookname);  // 归还图书
```

## 使用方法

### 1. 创建图书馆实例

```cpp
Library myLibrary;
```

### 2. 添加图书

```cpp
// 添加自然科学类图书
myLibrary.Add(new ScienceBook("S001", "时间简史", 58.0, "史蒂芬·霍金", "湖南科学技术出版社", 5));

// 添加人文社科类图书
myLibrary.Add(new SocialBook("H001", "全球通史", 99.0, "斯塔夫里阿诺斯", "北京大学出版社", 3));

// 添加外文图书
myLibrary.Add(new ForeignBook("F001", "The Little Prince", 35.5, "Antoine de Saint-Exupéry", 
                              "Reynal & Hitchcock", 10, "English"));
```

### 3. 查询图书

```cpp
Books* foundBook = myLibrary.Search("全球通史");
if (foundBook != nullptr) {
    foundBook->ShowMe();  // 显示图书信息
}
```

### 4. 借出与归还图书

```cpp
// 借出图书
myLibrary.Lend("时间简史");  // 会提示输入用户名

// 归还图书
myLibrary.Return("时间简史");
```

### 5. 图书统计

```cpp
// 显示所有图书
myLibrary.ShowAllBooks();

// 统计各类图书数量
myLibrary.CountAllBooks();
```

## 文件存储

图书馆系统会自动从以下文件读取和保存数据：

- `library.txt`: 存储所有图书信息
- `userlist.txt`: 存储借阅记录

## 注意事项

1. 添加重复图书会增加库存而不是创建新条目
2. 借出图书时，库存会相应减少
3. 归还图书时，库存会相应增加
4. 程序退出时会自动保存所有数据
5. 图书ID格式规定：
    - 自然科学类图书：以'S'开头
    - 人文社科类图书：以'H'开头
    - 外文图书：以'F'开头

## 编译要求

项目需要C++14标准支持：

```bash
g++ main.cpp -std=c++14 -o library_system
```

也可使用CMake进行编译：

```bash
mkdir build
cd build
cmake ..
make
```