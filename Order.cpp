#include "Order.h"

Order::Order()
    : orderId(0), username(""), roomId(0), checkInDate(""), checkOutDate(""),
      roomCount(0), status(0), bookingDate("") {}

Order::Order(int id, const std::string &user, int rId,
             const std::string &checkIn, const std::string &checkOut, int count,
             int stat, const std::string &bookDate)
    : orderId(id), username(user), roomId(rId), checkInDate(checkIn),
      checkOutDate(checkOut), roomCount(count), status(stat),
      bookingDate(bookDate) {}

int Order::getOrderId() const { return orderId; }

std::string Order::getUsername() const { return username; }

int Order::getRoomId() const { return roomId; }

std::string Order::getCheckInDate() const { return checkInDate; }

std::string Order::getCheckOutDate() const { return checkOutDate; }

int Order::getRoomCount() const { return roomCount; }

int Order::getStatus() const { return status; }

std::string Order::getBookingDate() const { return bookingDate; }

void Order::setOrderId(int id) { orderId = id; }

void Order::setUsername(const std::string &user) { username = user; }

void Order::setRoomId(int rId) { roomId = rId; }

void Order::setCheckInDate(const std::string &checkIn) {
  checkInDate = checkIn;
}

void Order::setCheckOutDate(const std::string &checkOut) {
  checkOutDate = checkOut;
}

void Order::setRoomCount(int count) { roomCount = count; }

void Order::setStatus(int stat) { status = stat; }

void Order::setBookingDate(const std::string &bookDate) {
  bookingDate = bookDate;
}

std::string Order::getStatusString() const {
  switch (status) {
  case 0:
    return "已预订";
  case 1:
    return "已完成";
  case 2:
    return "已评论";
  default:
    return "未知";
  }
}
