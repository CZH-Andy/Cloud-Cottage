#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
  std::string username;
  std::string password;

public:
  User();
  User(const std::string &uname, const std::string &pwd);

  // Getters
  std::string getUsername() const;
  std::string getPassword() const;

  // Setters
  void setUsername(const std::string &uname);
  void setPassword(const std::string &pwd);
};

#endif
