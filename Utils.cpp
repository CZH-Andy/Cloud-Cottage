#define _CRT_SECURE_NO_WARNINGS
#include "Utils.h"
#include <cctype>
#include <conio.h>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <windows.h>

// 清屏函数
void Utils::clearScreen() { system("cls"); }

// 暂停函数（按任意键继续）
void Utils::pause() {
  std::cout << "\n按任意键继续..." << std::flush;
  _getch();
  std::cout << std::endl;
}

// 打印标题头部
void Utils::printHeader(const std::string &title) {
  printDoubleLine();
  centerText(title);
  printDoubleLine();
}

// 打印单层分隔线
void Utils::printLine(int length) {
  for (int i = 0; i < length; i++) {
    std::cout << "-";
  }
  std::cout << std::endl;
}

// 打印双层分隔线
void Utils::printDoubleLine(int length) {
  for (int i = 0; i < length; i++) {
    std::cout << "=";
  }
  std::cout << std::endl;
}

// 打印框式文本
void Utils::printBox(const std::string &content) {
  int contentLength = content.length();
  int boxWidth = contentLength + 4;

  // 上边框
  std::cout << "+";
  for (int i = 0; i < boxWidth - 2; i++) {
    std::cout << "-";
  }
  std::cout << "+" << std::endl;

  // 内容
  std::cout << "| " << content << " |" << std::endl;

  // 下边框
  std::cout << "+";
  for (int i = 0; i < boxWidth - 2; i++) {
    std::cout << "-";
  }
  std::cout << "+" << std::endl;
}

// 验证用户名是否符合要求：只能包含英文字母
bool Utils::isValidUsername(const std::string &username) {
  if (username.empty()) {
    return false;
  }

  for (char c : username) {
    if (!isalpha(c)) {
      return false;
    }
  }
  return true;
}

// 验证密码是否符合要求：一大写一小写一数字且长度至少8位
bool Utils::isValidPassword(const std::string &password) {
  if (password.length() < 8) {
    return false;
  }

  bool hasUpper = false;
  bool hasLower = false;
  bool hasDigit = false;

  for (char c : password) {
    if (isupper(c))
      hasUpper = true;
    if (islower(c))
      hasLower = true;
    if (isdigit(c))
      hasDigit = true;
  }

  return hasUpper && hasLower && hasDigit;
}

bool Utils::isValidDate(const std::string &date) {
  // 验证日期格式是否为YYYY-MM-DD
  if (date.length() != 10) {
    return false;
  }
  if (date[4] != '-' || date[7] != '-') {
    return false;
  }
  for (int i = 0; i < 10; i++) {
    if (i == 4 || i == 7)
      continue;
    if (!isdigit(date[i])) {
      return false;
    }
  }

  int year = std::stoi(date.substr(0, 4));
  int month = std::stoi(date.substr(5, 2));
  int day = std::stoi(date.substr(8, 2));

  // 验证年份是否在2025-2030之间
  if (year < 2025 || year > 2030)
    return false;
  // 验证月份是否在1-12之间
  if (month < 1 || month > 12)
    return false;
  // 验证日期是否在1-31之间
  if (day < 1 || day > 31)
    return false;

  // 简单的日期合法性检查
  if (month == 2) {
    bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (day > (isLeap ? 29 : 28))
      return false;
  } else if (month == 4 || month == 6 || month == 9 || month == 11) {
    if (day > 30)
      return false;
  }

  return true;
}

// 验证评分是否在1-5之间
bool Utils::isValidRating(int rating) { return rating >= 1 && rating <= 5; }

// 获取当前日期
std::string Utils::getCurrentDate() {
  time_t now = time(0);
  tm *ltm = localtime(&now);

  std::ostringstream oss;
  oss << (1900 + ltm->tm_year) << "-" << std::setfill('0') << std::setw(2)
      << (1 + ltm->tm_mon) << "-" << std::setfill('0') << std::setw(2)
      << ltm->tm_mday;

  return oss.str();
}

// 判断日期是否在另一个日期之后
bool Utils::isDateAfter(const std::string &date1, const std::string &date2) {
  return compareDates(date1, date2) > 0;
}

int Utils::compareDates(const std::string &date1, const std::string &date2) {
  // 比较两个日期：date1 > date2 返回正数，date1 < date2 返回负数，相等返回0
  if (date1 == date2)
    return 0;
  return (date1 > date2) ? 1 : -1;
}

// 去除字符串两端的空格
std::string Utils::trim(const std::string &str) {
  size_t first = str.find_first_not_of(' ');
  if (std::string::npos == first) {
    return str;
  }
  size_t last = str.find_last_not_of(' ');
  return str.substr(first, (last - first + 1));
}

// 居中显示文本
void Utils::centerText(const std::string &text, int width) {
  int textLen = text.length();
  int padding = (width - textLen) / 2;

  for (int i = 0; i < padding; i++) {
    std::cout << " ";
  }
  std::cout << text << std::endl;
}