#include <csignal>

#include "host/host.hh"
#include "response/http_response.hh"
#include "parser/parser.hh"

static bool loop = true;


void sigint_handler(int signal)
{
    if (signal == SIGINT)
    {
      loop = false;
    }
    else
        std::cout << "Unhandled signal" << std::endl;
}

int main (int argc, char* argv[])
{
  /* Setting the signal handler */
  std::signal(SIGINT, sigint_handler);

  /* Check arguments */
  if (argc < 2 || (argc == 3 && std::strcmp(argv[1], "--dry-run")) || argc > 3)
   exit(2);

  char* filename;
  if (argc == 2)
    filename = argv[1];
  /* If --dry-run */
  else
    filename = argv[2];

  /* Parsing the configuration file and creating the servers */
  auto v = new std::vector<Server*>();
  conf_parse(filename, v);

  /* Creating the mutex and giving it to the servers */

  (*v->begin())->set_up_server();
  (*v->begin())->set_up_epoll();
  /* Waiting loop */
  while (loop)
  {
    try {
      (*v->begin())->wait();
    }
    catch (...) {
      loop = false;
    }
  }

  return 0;
}
