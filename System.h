#ifndef SYSTEM_H
#define SYSTEM_H

#include "Comment.h"
#include "Order.h"
#include "Room.h"
#include "User.h"
#include <string>
#include <vector>


class System {
private:
  std::vector<User> users;
  std::vector<Room> rooms;
  std::vector<Order> orders;
  std::vector<Comment> comments;
  std::string adminPassword;

  // 数据文件路径
  const std::string USERS_FILE = "users.txt";
  const std::string ROOMS_FILE = "rooms.txt";
  const std::string ORDERS_FILE = "orders.txt";
  const std::string COMMENTS_FILE = "comments.txt";
  const std::string ADMIN_FILE = "admin.txt";

  // 辅助函数
  std::vector<std::string> split(const std::string &str, char delimiter);

public:
  System();

  // 数据加载和保存
  void loadAllData();
  void saveAllData();
  void loadUsers();
  void saveUsers();
  void loadRooms();
  void saveRooms();
  void loadOrders();
  void saveOrders();
  void loadComments();
  void saveComments();
  void loadAdmin();
  void saveAdmin();

  // 用户管理
  bool registerUser(const std::string &username, const std::string &password);
  bool loginUser(const std::string &username, const std::string &password);
  bool isUsernameExists(const std::string &username);

  // 管理员管理
  bool loginAdmin(const std::string &password);
  void setAdminPassword(const std::string &password);

  // 房型管理
  void addRoom(const Room &room);
  void updateRoom(int roomId, const Room &room);
  Room *getRoomById(int roomId);
  std::vector<Room> &getAllRooms();
  std::vector<Room> getActiveRooms();
  int getNextRoomId();
  bool setRoomStatus(int roomId, bool active);

  // 订单管理
  void addOrder(const Order &order);
  void updateOrder(int orderId, const Order &order);
  bool deleteOrder(int orderId);
  Order *getOrderById(int orderId);
  std::vector<Order> getOrdersByUsername(const std::string &username);
  std::vector<Order> getOrdersByRoomId(int roomId);
  std::vector<Order> &getAllOrders();
  int getNextOrderId();

  // 评论管理
  void addComment(const Comment &comment);
  Comment *getCommentByOrderId(int orderId);
  std::vector<Comment> getCommentsByRoomId(int roomId);
  std::vector<Comment> &getAllComments();

  // 统计功能
  int getAvailableRoomCount(int roomId, const std::string &checkIn,
                            const std::string &checkOut);
};

#endif
