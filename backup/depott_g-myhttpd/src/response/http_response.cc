//
// Created by silentshad on 18/02/18.
//

#include <cstdlib>
#include <sstream>
#include <cstring>
#include <algorithm>
#include "http_response.hh"
#include <string>
#include <ctime>
#include <sys/stat.h>
#include <experimental/filesystem>
#include <zconf.h>
#include <sys/sendfile.h>
#include <fcntl.h>


#define BUFF_SIZE 255



Http_response::Http_response(int fd, std::string name, std::string dir)
: fd_(fd), name_(name)
{
  error_tab_ = { {200, "ok"}, {404,"Not Found"}
        , {405, "Method Not Allowed"}, {505, " HTTP Version Not Supported"} }; //TODO complete
  ret_code_ =200;
  std::experimental::filesystem::path tmp(dir.c_str());
  dir_ = std::experimental::filesystem::current_path() / tmp;
}

Http_response::~Http_response()
{
}

void upper(std::string& s)
{
  for (auto &&c : s)
  {
      c = std::toupper(c);
  }
}

std::string Http_response::get_err_val(int code)
{
  return error_tab_.at(code);
}

std::vector<std::string> split(const std::string& base, const char* sep )
{
  std::vector<std::string> v;
  std::string tmp;
  for (auto item = base.begin() ; item != base.end(); item++) {
    int i = 0;
    while (*(item + i) == sep[i])
      i++;
    if (sep[i] == '\0') {
      v.push_back(tmp);
      tmp = "";
      item += std::strlen(sep) -1;
    }
    else
      tmp += *item;

  }
  v.push_back(tmp);
  return v;
}

void Http_response::msg_recieve()
{

  char *buff_ = (char*) malloc(BUFF_SIZE);
  buff_size_t = 0;
  while (!recv(fd_, buff_ + buff_size_t , BUFF_SIZE, 0)) // TODO check retrun value
  {
    buff_ = (char*)realloc(buff_, buff_size_t + BUFF_SIZE);
    buff_size_t += BUFF_SIZE;
  }
  std::string s(buff_);
  request_ = split(s, "\r\n");
  parse_request_head();
  parse_request_option();
}

long file_size(std::string filename)
{
  struct stat stat_buf;
  int rc = stat(filename.c_str(), &stat_buf);
  return rc == 0 ? stat_buf.st_size : -1;
}

long Http_response::valid_path()
{
  std::experimental::filesystem::path path(options_.at(FILER).c_str());
  dir_ /=  path;
  long len = file_size(std::string(dir_));
  if (len == -1)
    ret_code_ = 404;
  return len;
}

void Http_response::append_resp_header(std::string& response)
{
  response.append(options_.at(VERSION));
  response.append(" ");
  response.append(std::to_string(ret_code_));
  response.append(" ");
  response.append(get_err_val(ret_code_));
  response.append("\r\n");
}

std::string now()
{
  std::time_t now= std::time(0);
  std::tm* now_tm= std::gmtime(&now);
  char buf[42];
  std::strftime(buf, 42, "%a, %d %b %Y %X GMT", now_tm);
  return buf;
}


void Http_response::msg_respond()
{
  long file_len;
  std::string response;
  if (ret_code_ == 200)
    file_len = valid_path();
  append_resp_header(response);
  response.append("date: ");
  response.append(now());
  response.append("\r\n");
  if (ret_code_ == 200 ) {
    response.append("content-length: ");
    response.append(std::to_string(file_len));
    response.append("\r\n");
    response.append("\r\n");

    int fd = open(dir_.c_str(), 'r');
    sendfile(fd_, fd, nullptr, static_cast<size_t >(file_len));
  }
  else {
    response.append("\r\n");
    send(fd_, response.c_str(), response.size(), 0);
  }
}

enum option get_enum(std::string s)
{
  upper(s);
  if (s == "ACCEPT:")
    return  ACCEPT;
  if (s == "CONNECTION:")
    return ALIVE;
  else //(s == "HOST:")
    return HOST;
}

void Http_response::parse_request_head()
{
  auto phrase = split(*request_.begin(), " ");
  auto word = begin(phrase);
  upper(*word);
  if (*word == "GET" || *word == "POST")
        options_.insert(std::make_pair(METHOD,*word));
  else {
    options_.insert(std::make_pair(METHOD,"missing"));
    ret_code_ = 405;
  }
  word++;
  options_.insert(std::make_pair(FILER,*word));
  word++;
  if (*word == "HTTP/1.1" || *word == "HTTP/1.0")
    options_.insert(std::make_pair(VERSION,*word));
  else
  {
    options_.insert(std::make_pair(VERSION,"missing"));
    ret_code_ = 505 ;
  }
}

void Http_response::parse_request_option()
{
  auto additionals = request_;
  additionals.erase(begin(additionals));
  for (auto &&line : additionals) {
    if (line == "\n")
      break;
    auto line_op = split(line, " ");
    if (line_op.size() >= 2)
      options_.insert(std::make_pair(get_enum(line_op.at(0)), line_op.at(1)));
  }
}

std::string Http_response::get_meth()
{
  return options_.at(METHOD);
}

std::string Http_response::get_ver()
{
  return options_.at(VERSION);
}

std::string Http_response::get_resrc()
{
  return options_.at(FILER);
}
