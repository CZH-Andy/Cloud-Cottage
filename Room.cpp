#include "Room.h"
#include <iomanip>
#include <iostream>


Room::Room()
    : roomId(0), roomName(""), price(0.0), totalQuantity(0), description(""), isActive(true) {}

Room::Room(int id, const std::string &name, double p, int quantity,
           const std::string &desc, bool active)
    : roomId(id), roomName(name), price(p), totalQuantity(quantity),
      description(desc), isActive(active) {}

int Room::getRoomId() const { return roomId; }

std::string Room::getRoomName() const { return roomName; }

double Room::getPrice() const { return price; }

int Room::getTotalQuantity() const { return totalQuantity; }

std::string Room::getDescription() const { return description; }

bool Room::getIsActive() const { return isActive; }

void Room::setRoomId(int id) { roomId = id; }

void Room::setRoomName(const std::string &name) { roomName = name; }

void Room::setPrice(double p) { price = p; }

void Room::setTotalQuantity(int quantity) { totalQuantity = quantity; }

void Room::setDescription(const std::string &desc) { description = desc; }

void Room::setIsActive(bool active) { isActive = active; }

// 显示房型信息
void Room::display() const {
  std::cout << "房型ID: " << roomId << std::endl;
  std::cout << "房型名称: " << roomName << std::endl;
  std::cout << "价格: ¥" << std::fixed << std::setprecision(2) << price << "/晚"
            << std::endl;
  std::cout << "可用数量: " << totalQuantity << std::endl;
  std::cout << "描述: " << description << std::endl;
  std::cout << "状态: " << (isActive ? "有效" : "失效") << std::endl;
}
