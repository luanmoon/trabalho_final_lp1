#include "corretor.h"

int Corretor::nextId = 1;

Corretor::Corretor() : id(nextId++) {}