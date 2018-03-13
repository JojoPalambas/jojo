#include <cassert>

#include "parser.hh"
#include "../exception/missing-parameter-exception.hh"

/*
 ** Parse the conf file
 ** Return a vector of Server
*/
void conf_parse(char* filename, std::vector<Server*>* v)
{
  std::ifstream file(filename);
  assert(file.good());
  try {

    /*Parse the conf file */
    const auto data = toml::parse(file);

    /* Get optional parameter log_file or set it to "" by default */
    auto search = data.find("log_file");
    std::string log_file = "";
    if (search != data.end())
      log_file = toml::get<std::string>(data.at("log_file"));

    /* Get a map of servers */
    const auto aot =
      toml::get<std::vector<toml::Table>>(data.at("server"));

    /* Get informations about each server */
    for (auto serv : aot)
    {
      /* Mandatory parameters */
      search = serv.find("server_name");
      std::string server_name;
      if (search != serv.end())
        server_name = toml::get<std::string>(serv.at("server_name"));
      else
       throw MissingParameterException(3,
                                       "server_name is missing in conf file");
      search = serv.find("port");
      std::string port;
      if (search != serv.end())
        port = toml::get<std::string>(serv.at("port"));
      else
        throw MissingParameterException(3,
                                      "port is missing in conf file");

      search = serv.find("ip");
      std::string ip;
      if (search != serv.end())
        ip = toml::get<std::string>(serv.at("ip"));
      else
        throw MissingParameterException(3,
                                        "ip is missing in conf file");

      search = serv.find("root_dir");
      std::string root_dir;
      if (search != serv.end())
        root_dir = toml::get<std::string>(serv.at("root_dir"));
      else
        throw MissingParameterException(3,
                                        "root_dir is missing in conf file");
      /*
       ** Optional parameter
       ** If log_file is empty, set it to false by default
       ** Else if this parameter is not given set it to true by default
      */
      bool log = false;
      if (log_file != "")
      {
        search = serv.find("log");
        log = true;
        if (search != serv.end())
        {
          log = toml::get<bool>(serv.at("log"));
        }
      }

      /* Create a server */
      auto s = new Server(server_name, port, ip, root_dir, log, log_file);

      /* Add the curren server in vector v */
      v->push_back(s);
    }
  } catch (toml::type_error &e) {
      std::cerr << e.what() << std::endl;
      exit(2);
  } catch (std::runtime_error &e) {
      std::cerr << e.what() << std::endl;
      exit(2);
  } catch (toml::syntax_error &e) {
      std::cerr << e.what() << std::endl;
      exit(2);
  } catch (MissingParameterException &e) {
      std::cerr << e.what() << std::endl;
      exit(2);
  }
}
