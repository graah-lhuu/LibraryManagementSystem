#include <iostream>
#include <string>
#include <vector>
#include <limits>  // 添加这个头文件用于输入清理

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

class Book {
public:
	string title;
	string author;
	int publishYear;

	Book(string t, string a, int y) : title(t), author(a), publishYear(y) {}

	void display() const {//const表示这是一个只读操作，不会造成修改
		cout << "《" << title << "》 作者：" << author << " (" << publishYear << "年)" << endl;
	}
};

class Library {
private:
	vector<Book> books;

public:
	void initializeLibrary() {
		books.emplace_back("C++ Primer", "Stanley B. Lippman", 2012);
		/*直接在 books这个vector的末尾，
		利用给定的参数（书名、作者、年份）构造一本新的 Book对象。
		这是一种高效且现代的添加元素的方法。*/
		books.emplace_back("深入理解计算机系统", "Randal E. Bryant", 2016);
		books.emplace_back("算法导论", "Thomas H. Cormen", 2006);
		cout << "图书馆初始化完成，已添加3本默认书籍！" << endl;
	}

	void addBook(const string& title, const string& author, int year) {
		books.emplace_back(title, author, year);
		cout << "添加成功！" << endl;
	}

	// 修复后的查询函数 - 添加输入清理
	void findBook() {
		string title;
		cout << "请输入要查询的书名：";
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 清理输入缓冲区
		std::getline(cin, title);  // 使用getline支持空格

		for (const auto& book : books) {
			if (book.title == title) {
							//范围for循环（range-based for loop），一种非常方便的遍历容器方法
							//book用于遍历books
				cout << "找到书籍：";
				book.display();
				return;
			}
		}
		cout << "未找到书籍《" << title << "》" << endl;
	}

	void listAllBooks() {
		if (books.empty()) {
			cout << "图书馆目前是空的。" << endl;
			return;
		}
		cout << "\n--- 馆藏图书列表 ---" << endl;
		for (const auto& book : books) {
			book.display();
		}//展示每一本书
		cout << "-------------------" << endl;
	}

	// 修复后的删除函数 - 安全的迭代器用法
	bool removeBook() {
		string title;
		cout << "请输入要删除的书名：";
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		/*std::numeric_limits<std::streamsize>::max()：
			一个非常大的数字，表示要忽略的字符数量上限，基本能涵盖所有情况
		'\n'：指定的分隔符。函数会持续丢弃字符，直到遇到换行符（即回车键输入）或达到最大字符数*/

		std::getline(cin, title);
		/*这行代码的作用是安全地读取一行可能包含空格的文本。*/

		for (auto it = books.begin(); it != books.end(); ) {//auto根据初始化表达式自动推断变量的类型
			if (it->title == title) {
				/*
				it是一个迭代器，可以理解为一种“智能指针”，
				指向容器（booksvector）中的某个元素（一本 Book对象）。
				->是成员访问运算符。因为 it是一个指向 Book对象的迭代器（类似指针），
				所以使用 it->title来访问当前迭代器所指 Book对象的 title成员变量。
				*/
				it = books.erase(it);  // 正确用法：接收erase返回的新迭代器
				cout << "删除成功！" << endl;
				return true;
			} else {
				++it;  // 只有不删除时才递增迭代器
			}
		}
		cout << "删除失败，未找到该书。" << endl;
		return false;
	}
};

int main() {
	Library myLib;
	myLib.initializeLibrary();

	int choice = 0;

	while (choice != 5) {
		cout << "\n===== 简易图书管理系统 =====" << endl;
		cout << "1. 添加图书" << endl;
		cout << "2. 查询图书" << endl;
		cout << "3. 显示所有图书" << endl;
		cout << "4. 删除图书" << endl;
		cout << "5. 退出" << endl;
		cout << "请选择操作：";

		// 添加输入验证防止死循环
		if (!(cin >> choice)) {
			cin.clear();  // 清除错误状态
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "输入错误，请输入数字！" << endl;
			continue;
		}

		string title, author;
		int year;
		switch (choice) {
		case 1:
			cout << "请输入书名：";
			cin.ignore();
			std::getline(cin, title);
			cout << "请输入作者：";
			std::getline(cin, author);
			cout << "请输入出版年份：";
			cin >> year;
			myLib.addBook(title, author, year);
			break;
		case 2:
			myLib.findBook();  // 修改为无参数版本
			break;
		case 3:
			myLib.listAllBooks();
			break;
		case 4:
			myLib.removeBook();  // 修改为无参数版本
			break;
		case 5:
			cout << "感谢使用，再见！" << endl;
			break;
		default:
			cout << "无效的选择，请重新输入。" << endl;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	return 0;
}