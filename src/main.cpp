#include "./cli-prompt/cli-prompt.h"
#include "./correlation-analysis/correlation-analysis.h"
#include "./csv-reader/csv-reader.h"
#include "./histograms-render/histograms-render.h"
#include "./output/output.h"
#include "./quantitative-computations/quantitative-computations.h"
#include "./statistical-computations/statistical-computations.h"

/*
    Временный комментарий на период разработки

    Сейчас все выполняемые из main() функции делают ничего кроме
    возвращения 0 (int). Последовательно нужно наполнить их
    функционалом, добавить аргументы и описать возвращаемые
    структуры.

    Для разработки отдельных функций стоит использовать
    src/dev.cpp и команду `make dev`
*/

int main ()
{
    cliPrompt ();
    csvReader ();

    quantitativeComputations ();
    statisticalComputations ();
    correlationAnalysis ();

    histogramRender ();
    output ();

    return 0;
}