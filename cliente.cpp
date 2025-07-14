#include "cliente.h"

int Cliente::nextId = 1;

Cliente::Cliente() : id(nextId++) {}