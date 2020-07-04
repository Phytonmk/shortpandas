// #include "./cli-prompt/cli-prompt.h"
// #include "./correlation-analysis/correlation-analysis.h"
#include "./csv-reader/csv-reader.h"
// #include "./histograms-render/histograms-render.h"
// #include "./output/output.h"
// #include "./quantitative-computations/quantitative-computations.h"
// #include "./statistical-computations/statistical-computations.h"

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
    std::cout << csvReader ("./input-example.csv")[1];
}