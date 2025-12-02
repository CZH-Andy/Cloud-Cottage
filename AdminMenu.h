#ifndef ADMINMENU_H
#define ADMINMENU_H

#include "System.h"

class AdminMenu {
private:
  System *system;

  void displayMenu();
  void manageRooms();
  void viewOrdersAndComments();

  // 房型管理子功能
  void addNewRoom();
  void modifyRoom();
  void viewAllRooms();
  void deleteRoomMenu();

public:
  AdminMenu(System *sys);
  void run();
};

#endif
