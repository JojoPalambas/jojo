#include <cstring>
#include <fstream>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>

#include "../server/server.hh"
#include "../toml/toml.hpp"

void conf_parse(char* filename, std::vector<Server*>* v);
