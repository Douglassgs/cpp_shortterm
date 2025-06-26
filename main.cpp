#include <iostream>
#include "src/library.cpp"

int main() {
    // 1. 创建图书馆实例
    Library myLibrary;
    std::cout << "图书馆已创建。\n" << std::endl;

    // 2. 创建并添加不同类型的图书
    std::cout << "--- 开始添加图书 ---" << std::endl;
    myLibrary.Add(new ScienceBook("S001", "时间简史", 58.0, "史蒂芬·霍金", "湖南科学技术出版社", 5));
    myLibrary.Add(new SocialBook("H001", "全球通史", 99.0, "斯塔夫里阿诺斯", "北京大学出版社", 3));
    myLibrary.Add(new SocialBook("H001", "全球dd通史", 99.0, "斯塔夫里阿诺斯", "北京大学出版社", 3));
    myLibrary.Add(new ForeignBook("F001", "The Little Prince", 35.5, "Antoine de Saint-Exupéry", "Reynal & Hitchcock", 10, "English"));
    std::cout << "--- 图书添加完毕 ---\n" << std::endl;

    // 3. 显示所有图书
    myLibrary.ShowAllBooks();

    // 4. 测试添加重复图书（增加库存）
    std::cout << "--- 测试添加重复图书 ---" << std::endl;
    myLibrary.Add(new ScienceBook("S001", "时间简史", 58.0, "史蒂芬·霍金", "湖南科学技术出版社", 3));
    std::cout << "--- 重复图书添加测试完毕 ---\n" << std::endl;

    // 5. 再次显示所有图书，检查库存
    myLibrary.ShowAllBooks();

    // 6. 查找图书
    std::cout << "\n--- 测试查找图书 ---" << std::endl;
    std::cout << "查找 '全球通史'..." << std::endl;
    Books* foundBook = myLibrary.Search("全球通史");
    if (foundBook != nullptr) {
        std::cout << "查找成功！图书信息：" << std::endl;
        foundBook->ShowMe();
    }

    std::cout << "\n查找 '不存在的书'..." << std::endl;
    foundBook = myLibrary.Search("不存在的书");
    if (foundBook == nullptr) {
        std::cout << "查找失败，未找到该图书。" << std::endl;
    }
    std::cout << "--- 查找测试完毕 ---\n" << std::endl;

    // 7. 借出图书
    std::cout << "\n--- 测试借出图书 ---" << std::endl;
    myLibrary.Lend("时间简史");
    myLibrary.Lend("时间简史");
    std::cout << "--- 借出测试完毕 ---\n" << std::endl;

    // 8. 归还图书
    std::cout << "\n--- 测试归还图书 ---" << std::endl;
    myLibrary.Return("时间简史");
    std::cout << "--- 归还测试完毕 ---\n" << std::endl;

    // 9. 再次显示所有图书，检查最终库存
    myLibrary.ShowAllBooks();

    // 10. 测试借出库存不足的图书
    std::cout << "\n--- 测试借出库存不足的图书 ---" << std::endl;
    myLibrary.Lend("全球通史"); // 库存 3
    myLibrary.Lend("全球通史"); // 库存 2
    myLibrary.Lend("全球通史"); // 库存 1
    myLibrary.Lend("全球通史"); // 库存 0, 此次应失败
    std::cout << "--- 库存不足测试完毕 ---\n" << std::endl;

    // 11. 最终显示
    myLibrary.CountAllBooks();

    // 12. main函数结束时，myLibrary的析构函数会自动调用，释放所有内存
    std::cout << "\n程序即将退出..." << std::endl;
    return 0;
}