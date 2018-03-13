#pragma once

#include <vector>
#include <mutex>
#include "../server/server.hh"
#include "../socket/socket.hh"

class Host
{// FIXME implement to handle multiple serv
public:
  Host();
  ~Host();
  void add_serv(Server serv);
private:
  std::vector<Server> server_list;


public:
  // add log to the log file if present beware no newline or spaces are added! TODO move it to cc file
  static void addLog(std::string file, std::string name
    , const std::string& version
    , const  std::string& request,const std::string& resrc
    , std::mutex* mut)
  {
    std::unique_lock<std::mutex> lock(*mut);

    std::ofstream fd(file);
    if (file.empty()) {
      throw *new std::exception();
    }

    fd << "[" << name << "] " <<  version << " "
            << request << " " << resrc << std::endl;
    fd.close();
  }

};

