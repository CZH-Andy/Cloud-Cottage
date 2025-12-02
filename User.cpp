#include "User.h"

User::User() : username(""), password("") {}

User::User(const std::string &uname, const std::string &pwd)
    : username(uname), password(pwd) {}

std::string User::getUsername() const { return username; }

std::string User::getPassword() const { return password; }

void User::setUsername(const std::string &uname) { username = uname; }

void User::setPassword(const std::string &pwd) { password = pwd; }
