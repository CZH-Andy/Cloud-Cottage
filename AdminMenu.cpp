#include "AdminMenu.h"
#include "Utils.h"
#include <iomanip>
#include <iostream>
#include <limits>

AdminMenu::AdminMenu(System *sys) : system(sys) {}

// 运行管理员菜单
void AdminMenu::run() {
  while (true) {
    Utils::clearScreen();
    displayMenu();

    int choice;
    std::cout << "请选择操作: ";
    std::cin >> choice;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "输入无效，请重新输入！" << std::endl;
      Utils::pause();
      continue;
    }

    std::cin.ignore();

    switch (choice) {
    case 1:
      manageRooms();
      break;
    case 2:
      viewOrdersAndComments();
      break;
    case 3:
      std::cout << "返回上一级..." << std::endl;
      return;
    default:
      std::cout << "无效选择，请重新输入！" << std::endl;
      Utils::pause();
    }
  }
}

// 显示管理员功能菜单
void AdminMenu::displayMenu() {
  Utils::printHeader("经营者管理系统");
  std::cout << "\n";
  std::cout << "  1. 发布及修改房型信息\n";
  std::cout << "  2. 查看订单及评论\n";
  std::cout << "  3. 返回上一级\n";
  std::cout << "\n";
  Utils::printLine();
}

// 管理房型
void AdminMenu::manageRooms() {
  while (true) {
    Utils::clearScreen();
    Utils::printHeader("房型管理");
    std::cout << "\n";
    std::cout << "  1. 添加新房型\n";
    std::cout << "  2. 修改房型信息\n";
    std::cout << "  3. 查看所有房型\n";
    std::cout << "  4. 删除房型\n";
    std::cout << "  5. 返回上一级\n";
    std::cout << "\n";
    Utils::printLine();

    int choice;
    std::cout << "请选择操作: ";
    std::cin >> choice;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "输入无效，请重新输入！" << std::endl;
      Utils::pause();
      continue;
    }

    std::cin.ignore();

    switch (choice) {
    case 1:
      addNewRoom();
      break;
    case 2:
      modifyRoom();
      break;
    case 3:
      Utils::clearScreen();
      Utils::printHeader("查看所有房型");
      std::cout << "\n";
      viewAllRooms();
      std::cout << "\n";
      Utils::pause();
      break;
    case 4:
      deleteRoomMenu();
      break;
    case 5:
      return;
    default:
      std::cout << "无效选择，请重新输入！" << std::endl;
      Utils::pause();
    }
  }
}

// 添加新房型
void AdminMenu::addNewRoom() {
  Utils::clearScreen();
  Utils::printHeader("添加新房型");
  std::cout << "\n";

  std::string name, desc;
  double price;
  int quantity;

  std::cout << "请输入房型名称: ";
  std::getline(std::cin, name);

  std::cout << "请输入价格(元/晚): ";
  std::cin >> price;

  if (std::cin.fail() || price <= 0) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n价格输入无效！" << std::endl;
    Utils::pause();
    return;
  }

  std::cout << "请输入房间数量: ";
  std::cin >> quantity;

  if (std::cin.fail() || quantity <= 0) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n数量输入无效！" << std::endl;
    Utils::pause();
    return;
  }

  std::cin.ignore();

  std::cout << "请输入房型描述: ";
  std::getline(std::cin, desc);

  int newId = system->getNextRoomId();
  Room newRoom(newId, name, price, quantity, desc);
  system->addRoom(newRoom);

  std::cout << "\n房型添加成功！房型ID: " << newId << std::endl;
  Utils::pause();
}

// 修改房型信息
void AdminMenu::modifyRoom() {
  Utils::clearScreen();
  Utils::printHeader("修改房型信息");
  std::cout << "\n";
  std::cout << "当前房型列表：" << std::endl;
  viewAllRooms();

  int roomId;
  std::cout << "\n请输入要修改的房型ID (输入0返回): ";
  std::cin >> roomId;

  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "输入无效！" << std::endl;
    Utils::pause();
    return;
  }

  if (roomId == 0)
    return;

  std::cin.ignore();

  Room *room = system->getRoomById(roomId);
  if (!room) {
    std::cout << "\n房型不存在！" << std::endl;
    Utils::pause();
    return;
  }

  std::cout << "\n当前房型信息：" << std::endl;
  room->display();
  std::cout << "\n";
  Utils::printLine();

  std::string name, desc;
  double price;
  int quantity;

  std::cout << "\n请输入新的房型名称 (直接回车保持不变): ";
  std::getline(std::cin, name);
  if (name.empty())
    name = room->getRoomName();

  std::cout << "请输入新的价格(元/晚) (输入-1保持不变): ";
  std::cin >> price;
  if (price == -1)
    price = room->getPrice();

  std::cout << "请输入新的房间数量 (输入-1保持不变): ";
  std::cin >> quantity;
  if (quantity == -1)
    quantity = room->getTotalQuantity();

  std::cin.ignore();

  std::cout << "请输入新的房型描述 (直接回车保持不变): ";
  std::getline(std::cin, desc);
  if (desc.empty())
    desc = room->getDescription();

  Room updatedRoom(roomId, name, price, quantity, desc);
  system->updateRoom(roomId, updatedRoom);

  std::cout << "\n房型修改成功！" << std::endl;
  Utils::pause();
}

// 查看所有房型
void AdminMenu::viewAllRooms() {
  std::vector<Room> &rooms = system->getAllRooms();

  if (rooms.empty()) {
    std::cout << "暂无房型信息。" << std::endl;
    return;
  }

  Utils::printLine();
  
  for (const auto &room : rooms) {
    std::cout << "【房型 ID: " << room.getRoomId() << "】" << std::endl;
    std::cout << "  房型名称: " << room.getRoomName() << std::endl;
    std::cout << "  价格: ¥" << std::fixed << std::setprecision(2) 
              << room.getPrice() << "/晚" << std::endl;
    std::cout << "  可用数量: " << room.getTotalQuantity() << " 间" << std::endl;
    std::cout << "  描述: " << room.getDescription() << std::endl;
    Utils::printLine();
  }
}

// 删除房型菜单
void AdminMenu::deleteRoomMenu() {
  Utils::clearScreen();
  Utils::printHeader("删除房型");
  std::cout << "\n";
  std::cout << "当前房型列表：" << std::endl;
  viewAllRooms();

  int roomId;
  std::cout << "\n请输入要删除的房型ID (输入0返回): ";
  std::cin >> roomId;

  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "输入无效！" << std::endl;
    Utils::pause();
    return;
  }

  if (roomId == 0)
    return;

  std::cin.ignore();

  Room *room = system->getRoomById(roomId);
  if (!room) {
    std::cout << "\n房型不存在！" << std::endl;
    Utils::pause();
    return;
  }

  std::cout << "\n确认要删除房型 \"" << room->getRoomName() << "\" 吗？(y/n): ";
  char confirm;
  std::cin >> confirm;

  if (confirm == 'y' || confirm == 'Y') {
    system->deleteRoom(roomId);
    std::cout << "\n房型删除成功！" << std::endl;
  } else {
    std::cout << "\n已取消删除。" << std::endl;
  }

  Utils::pause();
}

// 查看订单及评论
void AdminMenu::viewOrdersAndComments() {
  Utils::clearScreen();
  Utils::printHeader("查看订单及评论");
  std::cout << "\n";

  std::vector<Room> &rooms = system->getAllRooms();

  if (rooms.empty()) {
    std::cout << "暂无房型信息。" << std::endl;
    Utils::pause();
    return;
  }

  // 显示所有房型
  std::cout << "可用房型：" << std::endl;
  for (const auto &room : rooms) {
    std::cout << "  [" << room.getRoomId() << "] " << room.getRoomName()
              << std::endl;
  }

  int roomId;
  std::cout << "\n请输入要查看的房型ID (输入0查看所有): ";
  std::cin >> roomId;

  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "输入无效！" << std::endl;
    Utils::pause();
    return;
  }

  std::cin.ignore();

  Utils::clearScreen();
  Utils::printHeader("订单及评论详情");
  std::cout << "\n";

  std::vector<Order> orders;
  if (roomId == 0) {
    orders = system->getAllOrders();
  } else {
    orders = system->getOrdersByRoomId(roomId);
  }

  if (orders.empty()) {
    std::cout << "暂无订单信息。" << std::endl;
    Utils::pause();
    return;
  }

  int orderCount = 0;
  int commentCount = 0;

  for (const auto &order : orders) {
    orderCount++;
    Room *room = system->getRoomById(order.getRoomId());
    std::string roomName = room ? room->getRoomName() : "未知";

    Utils::printLine();
    std::cout << "订单 #" << order.getOrderId() << std::endl;
    std::cout << "  用户名: " << order.getUsername() << std::endl;
    std::cout << "  房型: " << roomName << " (ID: " << order.getRoomId() << ")"
              << std::endl;
    std::cout << "  入住日期: " << order.getCheckInDate() << std::endl;
    std::cout << "  退房日期: " << order.getCheckOutDate() << std::endl;
    std::cout << "  房间数量: " << order.getRoomCount() << std::endl;
    std::cout << "  订单状态: " << order.getStatusString() << std::endl;
    std::cout << "  预订日期: " << order.getBookingDate() << std::endl;

    // 查找评论
    Comment *comment = system->getCommentByOrderId(order.getOrderId());
    if (comment) {
      commentCount++;
      std::cout << "\n  【评论】" << std::endl;
      std::cout << "    评分: ";
      for (int i = 0; i < comment->getRating(); i++) {
        std::cout << "★";
      }
      for (int i = comment->getRating(); i < 5; i++) {
        std::cout << "☆";
      }
      std::cout << " (" << comment->getRating() << "/5)" << std::endl;
      std::cout << "    内容: " << comment->getContent() << std::endl;
      std::cout << "    评论日期: " << comment->getCommentDate() << std::endl;
    }
    std::cout << std::endl;
  }

  Utils::printDoubleLine();
  std::cout << "统计信息：" << std::endl;
  std::cout << "  总订单数: " << orderCount << std::endl;
  std::cout << "  评论数: " << commentCount << std::endl;
  Utils::printDoubleLine();

  Utils::pause();
}
