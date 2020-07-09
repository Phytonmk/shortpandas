#ifndef STATISTICAL_COMPUTATIONS
#define STATISTICAL_COMPUTATIONS

#include "./statistical-computations.cpp"

int statisticalComputations (std::vector<InputRow> data,
                             std::vector<InputRow>& min,
                             std::vector<InputRow>& max,
                             std::vector<InputRow>& average,
                             std::vector<InputRow>& median,
                             std::vector<InputRow>& quartile_25,
                             std::vector<InputRow>& quartile_75,
                             std::vector<InputRow>& square_deviation);


#endif