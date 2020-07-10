#ifndef CORRELATION_ANALYSIS
#define CORRELATION_ANALYSIS

#include "../types.h"
#include "./correlation-analysis.cpp"

std::vector<CorrelRate> correlationAnalysis (std::vector<InputRow> data, std::vector<InputRow> average);

#endif