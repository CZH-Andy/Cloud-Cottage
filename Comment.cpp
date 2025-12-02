#include "Comment.h"
#include <iostream>

Comment::Comment()
    : orderId(0), username(""), roomId(0), rating(0), content(""),
      commentDate("") {}

Comment::Comment(int oId, const std::string &user, int rId, int rate,
                 const std::string &cont, const std::string &date)
    : orderId(oId), username(user), roomId(rId), rating(rate), content(cont),
      commentDate(date) {}

int Comment::getOrderId() const { return orderId; }

std::string Comment::getUsername() const { return username; }

int Comment::getRoomId() const { return roomId; }

int Comment::getRating() const { return rating; }

std::string Comment::getContent() const { return content; }

std::string Comment::getCommentDate() const { return commentDate; }

void Comment::setOrderId(int oId) { orderId = oId; }

void Comment::setUsername(const std::string &user) { username = user; }

void Comment::setRoomId(int rId) { roomId = rId; }

void Comment::setRating(int rate) { rating = rate; }

void Comment::setContent(const std::string &cont) { content = cont; }

void Comment::setCommentDate(const std::string &date) { commentDate = date; }

// 显示评论信息
void Comment::display() const {
  std::cout << "订单ID: " << orderId << std::endl;
  std::cout << "用户: " << username << std::endl;
  std::cout << "评分: ";
  for (int i = 0; i < rating; i++) {
    std::cout << "★";
  }
  for (int i = rating; i < 5; i++) {
    std::cout << "☆";
  }
  std::cout << " (" << rating << "/5)" << std::endl;
  std::cout << "评论内容: " << content << std::endl;
  std::cout << "评论日期: " << commentDate << std::endl;
}
