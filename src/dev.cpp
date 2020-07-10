#include "./cli-prompt/cli-prompt.h"
#include "./correlation-analysis/correlation-analysis.h"
#include "./csv-reader/csv-reader.h"
#include "./differences/differences.h"
// #include "./histograms-render/histograms-render.h"
// #include "./output/output.h"
// #include "./quantitative-computations/quantitative-computations.h"
#include "./statistical-computations/statistical-computations.h"

#include "iostream"

/*
    Специальный файл для разработки отдельных функций. Сборка и
    мгновенный запуск файла может выполняться командой
    `make dev`.

    Предполагается что в этом файле мы будем подключать нужные
    функции по необходимости и запускать их прямо здесь
*/
int main ()
{
    std::cout << "Dev mode\n";
    // std::string inputFileName = cliPrompt ();
    // std::vector<InputRow> data = csvReader (inputFileName);
    std::vector<InputRow> data = csvReader ("./input-example.csv");
    std::vector<InputRow> min;
    std::vector<InputRow> max;
    std::vector<InputRow> average;
    std::vector<InputRow> median;
    std::vector<InputRow> quartile_25;
    std::vector<InputRow> quartile_75;
    std::vector<InputRow> square_deviation;
    statisticalComputations (data, min, max, average, median, quartile_25, quartile_75, square_deviation);

    std::vector<InputRow> diff_data = differences (data);
    std::vector<InputRow> diff_min;
    std::vector<InputRow> diff_max;
    std::vector<InputRow> diff_average;
    std::vector<InputRow> diff_median;
    std::vector<InputRow> diff_quartile_25;
    std::vector<InputRow> diff_quartile_75;
    std::vector<InputRow> diff_square_deviation;
    statisticalComputations (data, diff_min, diff_max, diff_average, diff_median, diff_quartile_25,
                             diff_quartile_75, diff_square_deviation);

    correlationAnalysis (data, average);
    // std::cout << cliPrompt ();
    // std::cout << csvReader ("./input-example.csv")[1];
}