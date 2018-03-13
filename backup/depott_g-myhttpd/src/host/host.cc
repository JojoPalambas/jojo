//
// Created by silentshad on 14/02/18.
//

#include <cstdlib>
#include "host.hh"

Host::Host()
{
  server_list = std::vector<Server>();
}

Host::~Host()
{
}


void Host::add_serv(Server serv)
{
  server_list.push_back(serv);
}

