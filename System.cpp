#include "System.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <sstream>

System::System() : adminPassword("Admin123") { loadAllData(); }

// 分割字符串
std::vector<std::string> System::split(const std::string &str, char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;

  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }

  return tokens;
}

// 加载所有数据
void System::loadAllData() {
  loadAdmin();
  loadUsers();
  loadRooms();
  loadOrders();
  loadComments();
}

// 保存所有数据
void System::saveAllData() {
  saveAdmin();
  saveUsers();
  saveRooms();
  saveOrders();
  saveComments();
}

// 加载用户数据
void System::loadUsers() {
  users.clear();
  std::ifstream file(USERS_FILE);

  if (!file.is_open()) {
    return; // 文件不存在，返回空列表
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    std::vector<std::string> tokens = split(line, '|');
    if (tokens.size() >= 2) {
      User user(tokens[0], tokens[1]);
      users.push_back(user);
    }
  }

  file.close();
}

// 保存用户数据
void System::saveUsers() {
  std::ofstream file(USERS_FILE);

  if (!file.is_open()) {
    std::cerr << "无法保存用户数据！" << std::endl;
    return;
  }

  for (const auto &user : users) {
    file << user.getUsername() << "|" << user.getPassword() << std::endl;
  }

  file.close();
}

// 加载房型数据
void System::loadRooms() {
  rooms.clear();
  std::ifstream file(ROOMS_FILE);

  if (!file.is_open()) {
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    std::vector<std::string> tokens = split(line, '|');
    if (tokens.size() >= 5) {
      int id = std::stoi(tokens[0]);
      std::string name = tokens[1];
      double price = std::stod(tokens[2]);
      int quantity = std::stoi(tokens[3]);
      std::string desc = tokens[4];

      Room room(id, name, price, quantity, desc);
      rooms.push_back(room);
    }
  }

  file.close();
}

// 保存房型数据
void System::saveRooms() {
  std::ofstream file(ROOMS_FILE);

  if (!file.is_open()) {
    std::cerr << "无法保存房型数据！" << std::endl;
    return;
  }

  for (const auto &room : rooms) {
    file << room.getRoomId() << "|" << room.getRoomName() << "|"
         << room.getPrice() << "|" << room.getTotalQuantity() << "|"
         << room.getDescription() << std::endl;
  }

  file.close();
}

// 加载订单数据
void System::loadOrders() {
  orders.clear();
  std::ifstream file(ORDERS_FILE);

  if (!file.is_open()) {
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    std::vector<std::string> tokens = split(line, '|');
    if (tokens.size() >= 8) {
      int id = std::stoi(tokens[0]);
      std::string username = tokens[1];
      int roomId = std::stoi(tokens[2]);
      std::string checkIn = tokens[3];
      std::string checkOut = tokens[4];
      int roomCount = std::stoi(tokens[5]);
      int status = std::stoi(tokens[6]);
      std::string bookDate = tokens[7];

      Order order(id, username, roomId, checkIn, checkOut, roomCount, status,
                  bookDate);
      orders.push_back(order);
    }
  }

  file.close();
}

// 保存订单数据
void System::saveOrders() {
  std::ofstream file(ORDERS_FILE);

  if (!file.is_open()) {
    std::cerr << "无法保存订单数据！" << std::endl;
    return;
  }

  for (const auto &order : orders) {
    file << order.getOrderId() << "|" << order.getUsername() << "|"
         << order.getRoomId() << "|" << order.getCheckInDate() << "|"
         << order.getCheckOutDate() << "|" << order.getRoomCount() << "|"
         << order.getStatus() << "|" << order.getBookingDate() << std::endl;
  }

  file.close();
}

// 加载评论数据
void System::loadComments() {
  comments.clear();
  std::ifstream file(COMMENTS_FILE);

  if (!file.is_open()) {
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    std::vector<std::string> tokens = split(line, '|');
    if (tokens.size() >= 6) {
      int orderId = std::stoi(tokens[0]);
      std::string username = tokens[1];
      int roomId = std::stoi(tokens[2]);
      int rating = std::stoi(tokens[3]);
      std::string content = tokens[4];
      std::string date = tokens[5];

      Comment comment(orderId, username, roomId, rating, content, date);
      comments.push_back(comment);
    }
  }

  file.close();
}

// 保存评论数据
void System::saveComments() {
  std::ofstream file(COMMENTS_FILE);

  if (!file.is_open()) {
    std::cerr << "无法保存评论数据！" << std::endl;
    return;
  }

  for (const auto &comment : comments) {
    file << comment.getOrderId() << "|" << comment.getUsername() << "|"
         << comment.getRoomId() << "|" << comment.getRating() << "|"
         << comment.getContent() << "|" << comment.getCommentDate()
         << std::endl;
  }

  file.close();
}

// 加载管理员数据
void System::loadAdmin() {
  std::ifstream file(ADMIN_FILE);

  if (!file.is_open()) {
    // 如果文件不存在，使用默认密码
    adminPassword = "Admin123";
    saveAdmin();
    return;
  }

  std::string line;
  if (std::getline(file, line)) {
    std::vector<std::string> tokens = split(line, '|');
    if (tokens.size() >= 2) {
      adminPassword = tokens[1];
    }
  }

  file.close();
}

// 保存管理员数据
void System::saveAdmin() {
  std::ofstream file(ADMIN_FILE);

  if (!file.is_open()) {
    std::cerr << "无法保存管理员数据！" << std::endl;
    return;
  }

  file << "admin|" << adminPassword << std::endl;
  file.close();
}

// 注册用户
bool System::registerUser(const std::string &username,
                          const std::string &password) {
  if (isUsernameExists(username)) {
    return false;
  }

  User newUser(username, password);
  users.push_back(newUser);
  saveUsers();

  return true;
}

// 登录用户
bool System::loginUser(const std::string &username,
                       const std::string &password) {
  for (const auto &user : users) {
    if (user.getUsername() == username && user.getPassword() == password) {
      return true;
    }
  }
  return false;
}

// 检查用户名是否存在
bool System::isUsernameExists(const std::string &username) {
  for (const auto &user : users) {
    if (user.getUsername() == username) {
      return true;
    }
  }
  return false;
}

// 登录管理员
bool System::loginAdmin(const std::string &password) {
  return password == adminPassword;
}

// 设置管理员密码
void System::setAdminPassword(const std::string &password) {
  adminPassword = password;
  saveAdmin();
}

// 添加房型
void System::addRoom(const Room &room) {
  rooms.push_back(room);
  saveRooms();
}

// 更新房型
void System::updateRoom(int roomId, const Room &room) {
  for (auto &r : rooms) {
    if (r.getRoomId() == roomId) {
      r = room;
      saveRooms();
      return;
    }
  }
}

// 根据房型ID获取房型
Room *System::getRoomById(int roomId) {
  for (auto &room : rooms) {
    if (room.getRoomId() == roomId) {
      return &room;
    }
  }
  return nullptr;
}

// 获取所有房型
std::vector<Room> &System::getAllRooms() { return rooms; }

// 获取下一个房型ID
int System::getNextRoomId() {
  int maxId = 0;
  for (const auto &room : rooms) {
    if (room.getRoomId() > maxId) {
      maxId = room.getRoomId();
    }
  }
  return maxId + 1;
}

// 删除房型
bool System::deleteRoom(int roomId) {
  for (auto it = rooms.begin(); it != rooms.end(); ++it) {
    if (it->getRoomId() == roomId) {
      rooms.erase(it);
      saveRooms();
      return true;
    }
  }
  return false;
}

// 添加订单
void System::addOrder(const Order &order) {
  orders.push_back(order);
  saveOrders();
}

// 更新订单
void System::updateOrder(int orderId, const Order &order) {
  for (auto &o : orders) {
    if (o.getOrderId() == orderId) {
      o = order;
      saveOrders();
      return;
    }
  }
}

// 删除订单
bool System::deleteOrder(int orderId) {
  for (auto it = orders.begin(); it != orders.end(); ++it) {
    if (it->getOrderId() == orderId) {
      orders.erase(it);
      saveOrders();
      return true;
    }
  }
  return false;
}

// 根据订单ID获取订单
Order *System::getOrderById(int orderId) {
  for (auto &order : orders) {
    if (order.getOrderId() == orderId) {
      return &order;
    }
  }
  return nullptr;
}

// 根据用户名获取订单
std::vector<Order> System::getOrdersByUsername(const std::string &username) {
  std::vector<Order> userOrders;
  for (const auto &order : orders) {
    if (order.getUsername() == username) {
      userOrders.push_back(order);
    }
  }
  return userOrders;
}

// 根据房型ID获取订单
std::vector<Order> System::getOrdersByRoomId(int roomId) {
  std::vector<Order> roomOrders;
  for (const auto &order : orders) {
    if (order.getRoomId() == roomId) {
      roomOrders.push_back(order);
    }
  }
  return roomOrders;
}

// 获取所有订单
std::vector<Order> &System::getAllOrders() { return orders; }

// 获取下一个订单ID
int System::getNextOrderId() {
  int maxId = 0;
  for (const auto &order : orders) {
    if (order.getOrderId() > maxId) {
      maxId = order.getOrderId();
    }
  }
  return maxId + 1;
}

// 添加评论
void System::addComment(const Comment &comment) {
  comments.push_back(comment);
  saveComments();
}

// 根据订单ID获取评论
Comment *System::getCommentByOrderId(int orderId) {
  for (auto &comment : comments) {
    if (comment.getOrderId() == orderId) {
      return &comment;
    }
  }
  return nullptr;
}

// 根据房型ID获取评论
std::vector<Comment> System::getCommentsByRoomId(int roomId) {
  std::vector<Comment> roomComments;
  for (const auto &comment : comments) {
    if (comment.getRoomId() == roomId) {
      roomComments.push_back(comment);
    }
  }
  return roomComments;
}

// 获取所有评论
std::vector<Comment> &System::getAllComments() { return comments; }

// 获取可用房间数量
int System::getAvailableRoomCount(int roomId, const std::string &checkIn,
                                  const std::string &checkOut) {
  Room *room = getRoomById(roomId);
  if (!room)
    return 0;

  int totalCount = room->getTotalQuantity();
  int bookedCount = 0;

  // 检查与该日期范围重叠的订单
  for (const auto &order : orders) {
    if (order.getRoomId() == roomId && order.getStatus() == 0) {
      // 检查日期是否重叠
      if (!(Utils::compareDates(checkOut, order.getCheckInDate()) <= 0 ||
            Utils::compareDates(checkIn, order.getCheckOutDate()) >= 0)) {
        bookedCount += order.getRoomCount();
      }
    }
  }

  return totalCount - bookedCount;
}
