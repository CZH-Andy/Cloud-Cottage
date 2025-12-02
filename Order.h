#ifndef ORDER_H
#define ORDER_H

#include <string>

class Order {
private:
  int orderId;
  std::string username;
  int roomId;
  std::string checkInDate;
  std::string checkOutDate;
  int roomCount;
  int status; // 0=已预订, 1=已完成, 2=已评论
  std::string bookingDate;

public:
  Order();
  Order(int id, const std::string &user, int rId, const std::string &checkIn,
        const std::string &checkOut, int count, int stat,
        const std::string &bookDate);

  // Getters
  int getOrderId() const;
  std::string getUsername() const;
  int getRoomId() const;
  std::string getCheckInDate() const;
  std::string getCheckOutDate() const;
  int getRoomCount() const;
  int getStatus() const;
  std::string getBookingDate() const;

  // Setters
  void setOrderId(int id);
  void setUsername(const std::string &user);
  void setRoomId(int rId);
  void setCheckInDate(const std::string &checkIn);
  void setCheckOutDate(const std::string &checkOut);
  void setRoomCount(int count);
  void setStatus(int stat);
  void setBookingDate(const std::string &bookDate);

  // Utility
  std::string getStatusString() const;
};

#endif
