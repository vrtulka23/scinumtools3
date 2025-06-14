#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <iomanip>
#include <exception>

#include "puq/quantity.h"
#include "puq/nostd/nostd.h"
#include "puq/systems/systems.h"
#include "puq/calc/calc.h"

void display_info(std::string expr);
void display_lists(std::deque<std::string>& convert);
  
#endif // MAIN_H
