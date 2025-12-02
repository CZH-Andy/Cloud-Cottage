#ifndef ROOM_H
#define ROOM_H

#include <string>

class Room {
private:
  int roomId;
  std::string roomName;
  double price;
  int totalQuantity;
  std::string description;

public:
  Room();
  Room(int id, const std::string &name, double p, int quantity,
       const std::string &desc);

  // Getters
  int getRoomId() const;
  std::string getRoomName() const;
  double getPrice() const;
  int getTotalQuantity() const;
  std::string getDescription() const;

  // Setters
  void setRoomId(int id);
  void setRoomName(const std::string &name);
  void setPrice(double p);
  void setTotalQuantity(int quantity);
  void setDescription(const std::string &desc);

  // Display
  void display() const;
};

#endif
