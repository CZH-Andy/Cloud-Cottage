#ifndef COMMENT_H
#define COMMENT_H

#include <string>

class Comment {
private:
  int orderId;
  std::string username;
  int roomId;
  int rating; // 1-5星
  std::string content;
  std::string commentDate;

public:
  Comment();
  Comment(int oId, const std::string &user, int rId, int rate,
          const std::string &cont, const std::string &date);

  // Getters
  int getOrderId() const;
  std::string getUsername() const;
  int getRoomId() const;
  int getRating() const;
  std::string getContent() const;
  std::string getCommentDate() const;

  // Setters
  void setOrderId(int oId);
  void setUsername(const std::string &user);
  void setRoomId(int rId);
  void setRating(int rate);
  void setContent(const std::string &cont);
  void setCommentDate(const std::string &date);

  // Display
  void display() const;
};

#endif
