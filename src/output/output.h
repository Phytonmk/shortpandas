#ifndef OUTPUT
#define OUTPUT

#include "../types.h"
#include "./output.cpp"
#include "string"
#include "vector"

void output (std::vector<InputRow> table, std::string filename, std::string tableHeader);
void output (std::vector<CorrelRate> table, std::string filename, std::string tableHeader);

#endif