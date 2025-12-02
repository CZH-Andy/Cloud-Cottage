#ifndef TOURISTMENU_H
#define TOURISTMENU_H

#include "System.h"
#include <string>

class TouristMenu {
private:
  System *system;
  std::string currentUsername;

  void displayMenu();
  void viewRooms();
  void bookRoom();
  void cancelBooking();
  void viewAndDeleteOrders();
  void addComment();

public:
  TouristMenu(System *sys, const std::string &username);
  void run();
};

#endif
