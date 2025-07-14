#include "imovel.h"

int Imovel::nextId = 1;

Imovel::Imovel() : id(nextId++) {}