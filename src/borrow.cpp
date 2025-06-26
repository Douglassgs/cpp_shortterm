//
// Created by 张励迅 on 25-6-26.
//
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

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
        if (ReturnTime == chrono::high_resolution_clock::now())
        {
            cout << "归还时间: 未归还" << endl;
        }
        else
        {
            PrintTimeVector(ReturnTime, "归还时间");
        }
    }
};
