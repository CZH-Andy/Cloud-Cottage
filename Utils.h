#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils {
public:
    // 清屏函数
    static void clearScreen();
    
    // 暂停函数（按任意键继续）
    static void pause();
    
    // 界面美化函数
    static void printHeader(const std::string& title);
    static void printLine(int length = 80);
    static void printDoubleLine(int length = 80);
    static void printBox(const std::string& content);
    
    // 输入验证函数
    static bool isValidUsername(const std::string& username);
    static bool isValidPassword(const std::string& password);
    static bool isValidDate(const std::string& date);
    static bool isValidRating(int rating);
    
    // 日期处理函数
    static std::string getCurrentDate();
    static bool isDateAfter(const std::string& date1, const std::string& date2);
    static int compareDates(const std::string& date1, const std::string& date2);
    
    // 字符串处理
    static std::string trim(const std::string& str);
    static void centerText(const std::string& text, int width = 80);
};

#endif

