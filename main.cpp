#include <iostream>
#include "src/library.cpp"

int main() {
    std::cout << "================ 图书馆管理系统测试 ================\n" << std::endl;

    // 1. 创建图书馆实例
    Library myLibrary;
    std::cout << "图书馆已初始化。\n" << std::endl;

    // 2. 创建并添加不同类型的图书
    std::cout << "--- 开始添加图书 ---" << std::endl;
    // 添加自然科学类图书
    myLibrary.Add(new ScienceBook("S001", "时间简史", 58.0, "史蒂芬·霍金", "湖南科学技术出版社", 5));
    myLibrary.Add(new ScienceBook("S002", "宇宙的起源", 45.5, "卡尔·萨根", "中国科学出版社", 3));

    // 添加人文社科类图书
    myLibrary.Add(new SocialBook("H001", "全球通史", 99.0, "斯塔夫里阿诺斯", "北京大学出版社", 3));
    myLibrary.Add(new SocialBook("H002", "人类简史", 68.0, "尤瓦尔·赫拉利", "中信出版社", 4));

    // 添加外文图书
    myLibrary.Add(new ForeignBook("F001", "The Little Prince", 35.5, "Antoine de Saint-Exupéry", "Reynal & Hitchcock", 10, "English"));
    myLibrary.Add(new ForeignBook("F002", "1984", 42.0, "George Orwell", "Secker & Warburg", 6, "English"));
    std::cout << "--- 图书添加完毕 ---\n" << std::endl;

    // 3. 显示所有图书
    myLibrary.ShowAllBooks();

    // 4. 按类型统计图书
    myLibrary.CountAllBooks();

    // 5. 测试添加重复图书（增加库存）
    std::cout << "--- 测试添加重复图书 ---" << std::endl;
    myLibrary.Add(new ScienceBook("S001", "时间简史", 58.0, "史蒂芬·霍金", "湖南科学技术出版社", 3));
    std::cout << "--- 重复图书添加测试完毕 ---\n" << std::endl;

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

    // 7. 测试借出图书
    std::cout << "\n--- 测试借出图书 ---" << std::endl;
    myLibrary.Lend("时间简史"); // 第一次借出
    myLibrary.Lend("人类简史"); // 借出另一本书
    myLibrary.Lend("The Little Prince"); // 借出外文书
    std::cout << "--- 借出测试完毕 ---\n" << std::endl;

    // 8. 查看库存变化
    std::cout << "\n--- 查看借出后库存 ---" << std::endl;
    myLibrary.ShowAllBooks();
    std::cout << "--- 库存查看完毕 ---\n" << std::endl;

    // 9. 测试归还图书
    std::cout << "\n--- 测试归还图书 ---" << std::endl;
    myLibrary.Return("时间简史");
    myLibrary.Return("The Little Prince");
    std::cout << "--- 归还测试完毕 ---\n" << std::endl;

    // 10. 再次查看库存变化
    std::cout << "\n--- 查看归还后库存 ---" << std::endl;
    myLibrary.ShowAllBooks();
    std::cout << "--- 库存查看完毕 ---\n" << std::endl;

    // 11. 测试借出库存不足的图书
    std::cout << "\n--- 测试借出库存不足的图书 ---" << std::endl;
    // 先将库存全部借出
    std::cout << "将宇宙的起源全部借出：" << std::endl;
    myLibrary.Lend("宇宙的起源"); // 库存 3
    myLibrary.Lend("宇宙的起源"); // 库存 2
    myLibrary.Lend("宇宙的起源"); // 库存 1
    myLibrary.Lend("宇宙的起源"); // 库存 0，此次应该失败
    std::cout << "--- 库存不足测试完毕 ---\n" << std::endl;

    // 12. 测试归还不存在的图书
    std::cout << "\n--- 测试归还不存在的图书 ---" << std::endl;
    myLibrary.Return("不存在的书");
    std::cout << "--- 归还不存在图书测试完毕 ---\n" << std::endl;

    // 13. 最终统计
    std::cout << "\n--- 最终图书统计 ---" << std::endl;
    myLibrary.CountAllBooks();
    std::cout << "--- 统计完毕 ---\n" << std::endl;

    // 14. 程序结束
    std::cout << "\n================ 测试完成 ================\n" << std::endl;
    std::cout << "程序即将退出..." << std::endl;

    // Library 析构函数会在程序结束时自动调用，释放所有图书内存并保存数据
    return 0;
}