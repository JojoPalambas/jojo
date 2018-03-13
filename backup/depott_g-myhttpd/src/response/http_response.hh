#pragma once

#include <string>
#include <map>
#include "../server/server.hh"
#include <experimental/filesystem>

enum option
{
  METHOD,
  VERSION,
  FILER,
  ALIVE,
  HOST,
  ACCEPT,
};

class Http_response
{
public:
  Http_response(int fd, std::string name, std::string dir);
  ~Http_response();

  void msg_recieve();
  void msg_respond();

  std::string get_meth();
  std::string get_ver();
  std::string get_resrc();
private:
  int fd_;
  std::vector<std::string> request_;
  size_t buff_size_t;
  std::string name_;
  std::experimental::filesystem::path dir_;
  int ret_code_;
  std::map<enum option, std::string> options_;

  void parse_request_head();
  void parse_request_option();
  void append_resp_header(std::string& response);
  long valid_path();

  std::map<int, std::string> error_tab_;
  std::string get_err_val(int code);
};

