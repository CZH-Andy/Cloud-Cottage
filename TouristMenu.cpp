#include "TouristMenu.h"
#include "Utils.h"
#include <iomanip>
#include <iostream>
#include <limits>

TouristMenu::TouristMenu(System *sys, const std::string &username)
    : system(sys), currentUsername(username) {}

// 运行游客菜单
void TouristMenu::run() {
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
      viewRooms();
      break;
    case 2:
      bookRoom();
      break;
    case 3:
      cancelBooking();
      break;
    case 4:
      viewAndDeleteOrders();
      break;
    case 5:
      addComment();
      break;
    case 6:
      std::cout << "返回上一级..." << std::endl;
      return;
    default:
      std::cout << "无效选择，请重新输入！" << std::endl;
      Utils::pause();
    }
  }
}

// 显示游客功能菜单
void TouristMenu::displayMenu() {
  Utils::printHeader("游客功能菜单");
  std::cout << "\n";
  std::cout << "  欢迎您，" << currentUsername << "！\n";
  std::cout << "\n";
  std::cout << "  1. 查看房型\n";
  std::cout << "  2. 预订房间\n";
  std::cout << "  3. 取消预订\n";
  std::cout << "  4. 查看及删除订单\n";
  std::cout << "  5. 发表评论\n";
  std::cout << "  6. 返回上一级\n";
  std::cout << "\n";
  Utils::printLine();
}

// 查看房型
void TouristMenu::viewRooms() {
  Utils::clearScreen();
  Utils::printHeader("查看房型");
  std::cout << "\n";

  std::vector<Room> rooms = system->getActiveRooms();

  if (rooms.empty()) {
    std::cout << "暂无可用房型。" << std::endl;
    Utils::pause();
    return;
  }

  for (const auto &room : rooms) {
    Utils::printLine();
    std::cout << "【房型ID: " << room.getRoomId() << "】" << std::endl;
    std::cout << "  房型名称: " << room.getRoomName() << std::endl;
    std::cout << "  价格: ¥" << std::fixed << std::setprecision(2)
              << room.getPrice() << "/晚" << std::endl;
    std::cout << "  可用数量: " << room.getTotalQuantity() << " 间"
              << std::endl;
    std::cout << "  描述: " << room.getDescription() << std::endl;

    // 显示评分
    std::vector<Comment> comments =
        system->getCommentsByRoomId(room.getRoomId());
    if (!comments.empty()) {
      double totalRating = 0;
      for (const auto &comment : comments) {
        totalRating += comment.getRating();
      }
      double avgRating = totalRating / comments.size();
      std::cout << "  平均评分: " << std::fixed << std::setprecision(1)
                << avgRating << "/5.0 (" << comments.size() << "条评论)"
                << std::endl;
    }
  }
  Utils::printLine();

  std::cout << "\n";
  Utils::pause();
}

// 预订房间
void TouristMenu::bookRoom() {
  Utils::clearScreen();
  Utils::printHeader("预订房间");
  std::cout << "\n";

  std::vector<Room> rooms = system->getActiveRooms();

  if (rooms.empty()) {
    std::cout << "暂无可用房型。" << std::endl;
    Utils::pause();
    return;
  }

  // 显示房型列表
  std::cout << "可用房型：" << std::endl;
  for (const auto &room : rooms) {
    std::cout << "  [" << room.getRoomId() << "] " << room.getRoomName()
              << " - ¥" << std::fixed << std::setprecision(2) << room.getPrice()
              << "/晚 (可用: " << room.getTotalQuantity() << "间)" << std::endl;
  }

  int roomId;
  std::cout << "\n请输入要预订的房型ID (输入0返回): ";
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

  if (!room->getIsActive()) {
    std::cout << "\n该房型已失效，无法预订！" << std::endl;
    Utils::pause();
    return;
  }

  std::string checkIn, checkOut;
  int roomCount;

  std::cout << "请输入入住日期 (格式: YYYY-MM-DD): ";
  std::getline(std::cin, checkIn);

  if (!Utils::isValidDate(checkIn)) {
    std::cout << "\n入住日期格式不正确！" << std::endl;
    Utils::pause();
    return;
  }

  std::cout << "请输入退房日期 (格式: YYYY-MM-DD): ";
  std::getline(std::cin, checkOut);

  if (!Utils::isValidDate(checkOut)) {
    std::cout << "\n退房日期格式不正确！" << std::endl;
    Utils::pause();
    return;
  }

  if (Utils::compareDates(checkOut, checkIn) <= 0) {
    std::cout << "\n退房日期必须晚于入住日期！" << std::endl;
    Utils::pause();
    return;
  }

  std::cout << "请输入预订房间数量: ";
  std::cin >> roomCount;

  if (std::cin.fail() || roomCount <= 0) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n房间数量无效！" << std::endl;
    Utils::pause();
    return;
  }

  // 检查房间可用性
  int available = system->getAvailableRoomCount(roomId, checkIn, checkOut);
  if (available < roomCount) {
    std::cout << "\n抱歉，该时间段只有 " << available
              << " 间房可用，无法满足您的需求！" << std::endl;
    Utils::pause();
    return;
  }

  // 创建订单
  int orderId = system->getNextOrderId();
  std::string bookDate = Utils::getCurrentDate();
  Order newOrder(orderId, currentUsername, roomId, checkIn, checkOut, roomCount,
                 0, bookDate);
  system->addOrder(newOrder);

  std::cout << "\n预订成功！" << std::endl;
  std::cout << "订单ID: " << orderId << std::endl;
  std::cout << "房型: " << room->getRoomName() << std::endl;
  std::cout << "入住日期: " << checkIn << std::endl;
  std::cout << "退房日期: " << checkOut << std::endl;
  std::cout << "房间数量: " << roomCount << std::endl;

  Utils::pause();
}

// 取消预订
void TouristMenu::cancelBooking() {
  Utils::clearScreen();
  Utils::printHeader("取消预订");
  std::cout << "\n";

  std::vector<Order> myOrders = system->getOrdersByUsername(currentUsername);

  // 筛选可取消的订单（状态为已预订，且入住日期在未来）
  std::vector<Order> cancelableOrders;
  std::string today = Utils::getCurrentDate();

  for (const auto &order : myOrders) {
    if (order.getStatus() == 0 &&
        Utils::compareDates(order.getCheckInDate(), today) > 0) {
      cancelableOrders.push_back(order);
    }
  }

  if (cancelableOrders.empty()) {
    std::cout << "您没有可取消的订单。" << std::endl;
    std::cout << "(只能取消入住日期在未来的已预订订单)" << std::endl;
    Utils::pause();
    return;
  }

  std::cout << "可取消的订单：" << std::endl;
  Utils::printLine();

  for (const auto &order : cancelableOrders) {
    Room *room = system->getRoomById(order.getRoomId());
    std::string roomName = room ? room->getRoomName() : "未知";

    std::cout << "订单ID: " << order.getOrderId() << std::endl;
    std::cout << "  房型: " << roomName << std::endl;
    std::cout << "  入住日期: " << order.getCheckInDate() << std::endl;
    std::cout << "  退房日期: " << order.getCheckOutDate() << std::endl;
    std::cout << "  房间数量: " << order.getRoomCount() << std::endl;
    std::cout << "  预订日期: " << order.getBookingDate() << std::endl;
    Utils::printLine();
  }

  int orderId;
  std::cout << "\n请输入要取消的订单ID (输入0返回): ";
  std::cin >> orderId;

  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "输入无效！" << std::endl;
    Utils::pause();
    return;
  }

  if (orderId == 0)
    return;

  std::cin.ignore();

  // 验证订单是否可取消
  bool found = false;
  for (const auto &order : cancelableOrders) {
    if (order.getOrderId() == orderId) {
      found = true;
      break;
    }
  }

  if (!found) {
    std::cout << "\n无效的订单ID或该订单不可取消！" << std::endl;
    Utils::pause();
    return;
  }

  std::cout << "\n确认要取消该订单吗？(y/n): ";
  char confirm;
  std::cin >> confirm;

  if (confirm == 'y' || confirm == 'Y') {
    system->deleteOrder(orderId);
    std::cout << "\n订单取消成功！" << std::endl;
  } else {
    std::cout << "\n已取消操作。" << std::endl;
  }

  Utils::pause();
}

// 查看及删除订单
void TouristMenu::viewAndDeleteOrders() {
  Utils::clearScreen();
  Utils::printHeader("查看及删除订单");
  std::cout << "\n";

  std::vector<Order> myOrders = system->getOrdersByUsername(currentUsername);

  if (myOrders.empty()) {
    std::cout << "您还没有任何订单。" << std::endl;
    Utils::pause();
    return;
  }

  std::cout << "您的订单列表：" << std::endl;
  Utils::printLine();

  for (const auto &order : myOrders) {
    Room *room = system->getRoomById(order.getRoomId());
    std::string roomName = room ? room->getRoomName() : "未知";

    std::cout << "订单ID: " << order.getOrderId() << std::endl;
    std::cout << "  房型: " << roomName << std::endl;
    std::cout << "  入住日期: " << order.getCheckInDate() << std::endl;
    std::cout << "  退房日期: " << order.getCheckOutDate() << std::endl;
    std::cout << "  房间数量: " << order.getRoomCount() << std::endl;
    std::cout << "  订单状态: " << order.getStatusString() << std::endl;
    std::cout << "  预订日期: " << order.getBookingDate() << std::endl;
    Utils::printLine();
  }

  std::cout << "\n是否要删除订单？(y/n): ";
  char choice;
  std::cin >> choice;

  if (choice != 'y' && choice != 'Y') {
    return;
  }

  std::cin.ignore();

  int orderId;
  std::cout << "请输入要删除的订单ID (输入0返回): ";
  std::cin >> orderId;

  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "输入无效！" << std::endl;
    Utils::pause();
    return;
  }

  if (orderId == 0)
    return;

  std::cin.ignore();

  Order *order = system->getOrderById(orderId);
  if (!order || order->getUsername() != currentUsername) {
    std::cout << "\n订单不存在或不属于您！" << std::endl;
    Utils::pause();
    return;
  }

  if (order->getStatus() == 0) {
    std::cout << "\n无法删除进行中的订单！请先取消预订。" << std::endl;
    Utils::pause();
    return;
  }

  std::cout << "\n确认要删除该订单吗？(y/n): ";
  char confirm;
  std::cin >> confirm;

  if (confirm == 'y' || confirm == 'Y') {
    system->deleteOrder(orderId);
    std::cout << "\n订单删除成功！" << std::endl;
  } else {
    std::cout << "\n已取消删除。" << std::endl;
  }

  Utils::pause();
}

// 发表评论
void TouristMenu::addComment() {
  Utils::clearScreen();
  Utils::printHeader("发表评论");
  std::cout << "\n";

  std::vector<Order> myOrders = system->getOrdersByUsername(currentUsername);

  // 筛选可评论的订单（状态为已完成）
  std::vector<Order> commentableOrders;

  for (const auto &order : myOrders) {
    if (order.getStatus() == 1) {
      commentableOrders.push_back(order);
    }
  }

  if (commentableOrders.empty()) {
    std::cout << "您没有可评论的订单。" << std::endl;
    std::cout << "(只能对已完成且未评论的订单进行评价)" << std::endl;
    Utils::pause();
    return;
  }

  std::cout << "可评论的订单：" << std::endl;
  Utils::printLine();

  for (const auto &order : commentableOrders) {
    Room *room = system->getRoomById(order.getRoomId());
    std::string roomName = room ? room->getRoomName() : "未知";

    std::cout << "订单ID: " << order.getOrderId() << std::endl;
    std::cout << "  房型: " << roomName << std::endl;
    std::cout << "  入住日期: " << order.getCheckInDate() << std::endl;
    std::cout << "  退房日期: " << order.getCheckOutDate() << std::endl;
    Utils::printLine();
  }

  int orderId;
  std::cout << "\n请输入要评论的订单ID (输入0返回): ";
  std::cin >> orderId;

  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "输入无效！" << std::endl;
    Utils::pause();
    return;
  }

  if (orderId == 0)
    return;

  std::cin.ignore();

  // 验证订单是否可评论
  Order *order = nullptr;
  for (auto &o : commentableOrders) {
    if (o.getOrderId() == orderId) {
      order = system->getOrderById(orderId);
      break;
    }
  }

  if (!order) {
    std::cout << "\n无效的订单ID或该订单不可评论！" << std::endl;
    Utils::pause();
    return;
  }

  int rating;
  std::string content;

  std::cout << "\n请输入评分 (1-5星): ";
  std::cin >> rating;

  if (std::cin.fail() || !Utils::isValidRating(rating)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n评分无效！请输入1-5之间的数字。" << std::endl;
    Utils::pause();
    return;
  }

  std::cin.ignore();

  std::cout << "请输入评论内容: ";
  std::getline(std::cin, content);

  if (content.empty()) {
    std::cout << "\n评论内容不能为空！" << std::endl;
    Utils::pause();
    return;
  }

  // 创建评论
  std::string commentDate = Utils::getCurrentDate();
  Comment newComment(orderId, currentUsername, order->getRoomId(), rating,
                     content, commentDate);
  system->addComment(newComment);

  // 更新订单状态为已评论
  order->setStatus(2);
  system->updateOrder(orderId, *order);

  std::cout << "\n评论发表成功！感谢您的反馈。" << std::endl;
  Utils::pause();
}
