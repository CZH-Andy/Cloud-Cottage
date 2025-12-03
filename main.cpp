#include "AdminMenu.h"
#include "System.h"
#include "TouristMenu.h"
#include "Utils.h"
#include <iostream>
#include <limits>
#include <windows.h>

using namespace std;

// 角色选择
int selectRole();

// 经营者菜单
void adminInterface(System &system);

// 游客菜单
void touristInterface(System &system);

// 注册功能
bool registerTourist(System &system);

// 登录功能
bool loginTourist(System &system, string &username);

int main()
{
  SetConsoleCP(CP_UTF8);       // 输入UTF-8编码
  SetConsoleOutputCP(CP_UTF8); // 输出UTF-8编码
  ios::sync_with_stdio(false); // 同步输入输出流

  System system;

  while (true)
  {
    Utils::clearScreen();
    Utils::printHeader("Cloud Cottage 民宿预订系统");
    cout << "\n";
    Utils::centerText("欢迎使用 Cloud Cottage 民宿预订系统");
    cout << "\n";

    int role = selectRole();

    if (role == 1)
    {
      // 经营者
      adminInterface(system);
    }
    else if (role == 2)
    {
      // 游客
      touristInterface(system);
    }
    else if (role == 3)
    {
      // 退出程序
      Utils::clearScreen();
      Utils::printHeader("感谢使用");
      cout << "\n";
      Utils::centerText("欢迎下次光临 Cloud Cottage！");
      cout << "\n";
      Utils::printLine();
      break;
    }
  }

  return 0;
}

int selectRole()
{
  cout << "  请选择您的角色：\n";
  cout << "\n";
  cout << "    1. 经营者\n";
  cout << "    2. 游客\n";
  cout << "    3. 退出程序\n";
  cout << "\n";
  Utils::printLine();

  int choice;
  cout << "请输入选项: ";
  cin >> choice;

  if (cin.fail())
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "输入无效，请重新选择！" << endl;
    Utils::pause();
    return 0;
  }

  cin.ignore();

  if (choice < 1 || choice > 3)
  {
    cout << "无效选择，请重新输入！" << endl;
    Utils::pause();
    return 0;
  }

  return choice;
}

void adminInterface(System &system)
{
  while (true)
  {
    Utils::clearScreen();
    Utils::printHeader("经营者登录");
    cout << "\n";
    cout << "  1. 登录\n";
    cout << "  2. 退出程序\n";
    cout << "\n";
    Utils::printLine();

    int choice;
    cout << "请选择操作: ";
    cin >> choice;

    if (cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "输入无效！" << endl;
      Utils::pause();
      continue;
    }

    cin.ignore();

    if (choice == 2)
    {
      Utils::clearScreen();
      Utils::printHeader("感谢使用");
      cout << "\n";
      Utils::centerText("欢迎下次光临 Cloud Cottage！");
      cout << "\n";
      Utils::printLine();
      exit(0);
    }
    else if (choice == 1)
    {
      string username, password;
      cout << "\n请输入用户名: ";
      getline(cin, username);

      // 验证用户名是否为admin
      if (username != "admin")
      {
        cout << "\n管理员用户名错误！" << endl;
        Utils::pause();
        continue;
      }

      cout << "请输入密码: ";
      getline(cin, password);

      if (system.loginAdmin(password))
      {
        cout << "\n登录成功！" << endl;
        Utils::pause();

        AdminMenu adminMenu(&system);
        adminMenu.run();

        return; // 返回角色选择界面
      }
      else
      {
        cout << "\n密码错误！" << endl;
        Utils::pause();
      }
    }
    else
    {
      cout << "无效选择！" << endl;
      Utils::pause();
    }
  }
}

void touristInterface(System &system)
{
  while (true)
  {
    Utils::clearScreen();
    Utils::printHeader("游客登录");
    cout << "\n";
    cout << "  1. 注册\n";
    cout << "  2. 登录\n";
    cout << "  3. 退出程序\n";
    cout << "\n";
    Utils::printLine();

    int choice;
    cout << "请选择操作: ";
    cin >> choice;

    if (cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "输入无效！" << endl;
      Utils::pause();
      continue;
    }

    cin.ignore();

    if (choice == 3)
    {
      Utils::clearScreen();
      Utils::printHeader("感谢使用");
      cout << "\n";
      Utils::centerText("欢迎下次光临 Cloud Cottage！");
      cout << "\n";
      Utils::printLine();
      exit(0);
    }
    else if (choice == 1)
    {
      if (registerTourist(system))
      {
        cout << "\n注册成功！请登录。" << endl;
        Utils::pause();
      }
    }
    else if (choice == 2)
    {
      string username;
      if (loginTourist(system, username))
      {
        cout << "\n登录成功！欢迎您，" << username << "！" << endl;
        Utils::pause();

        TouristMenu touristMenu(&system, username);
        touristMenu.run();

        return; // 返回角色选择界面
      }
    }
    else
    {
      cout << "无效选择！" << endl;
      Utils::pause();
    }
  }
}

bool registerTourist(System &system)
{
  Utils::clearScreen();
  Utils::printHeader("游客注册");
  cout << "\n";

  string username, password, confirmPassword;

  cout << "请输入用户名 (只能包含英文字母): ";
  getline(cin, username);

  // 验证用户名合法性
  if (!Utils::isValidUsername(username))
  {
    cout << "\n用户名不合法！用户名只能由英文字母组成。" << endl;
    Utils::pause();
    return false;
  }

  // 验证用户名唯一性
  if (system.isUsernameExists(username))
  {
    cout << "\n该用户名已被注册，请更换用户名！" << endl;
    Utils::pause();
    return false;
  }

  cout << "请输入密码 (至少8位，包含大小写字母和数字): ";
  getline(cin, password);

  // 验证密码合法性
  if (!Utils::isValidPassword(password))
  {
    cout << "\n密码不合法！密码必须至少8位，且包含大小写字母和数字。" << endl;
    Utils::pause();
    return false;
  }

  cout << "请再次输入密码: ";
  getline(cin, confirmPassword);

  // 验证两次密码是否一致
  if (password != confirmPassword)
  {
    cout << "\n两次输入的密码不一致！" << endl;
    Utils::pause();
    return false;
  }

  // 注册用户
  if (system.registerUser(username, password))
  {
    return true;
  }
  else
  {
    cout << "\n注册失败！" << endl;
    Utils::pause();
    return false;
  }
}

bool loginTourist(System &system, string &username)
{
  Utils::clearScreen();
  Utils::printHeader("游客登录");
  cout << "\n";

  string password;
  int attempts = 0;
  const int MAX_ATTEMPTS = 3;

  cout << "请输入用户名: ";
  getline(cin, username);

  // 检查用户名是否存在
  if (!system.isUsernameExists(username))
  {
    cout << "\n该用户名未注册！请先注册。" << endl;
    Utils::pause();
    return false;
  }

  // 密码输入（最多3次机会）
  while (attempts < MAX_ATTEMPTS)
  {
    cout << "请输入密码: ";
    getline(cin, password);

    if (system.loginUser(username, password))
    {
      return true;
    }
    else
    {
      attempts++;
      if (attempts < MAX_ATTEMPTS)
      {
        cout << "\n密码错误！这是第 " << attempts << " 次错误，您还有 "
             << (MAX_ATTEMPTS - attempts) << " 次机会。" << endl;
      }
      else
      {
        cout << "\n密码错误次数超过限制！程序即将退出。" << endl;
        Utils::pause();
        exit(0);
      }
    }
  }

  return false;
}
