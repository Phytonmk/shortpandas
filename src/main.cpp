#include "./cli-prompt/cli-prompt.h"
#include "./correlation-analysis/correlation-analysis.h"
#include "./csv-reader/csv-reader.h"
#include "./differences/differences.h"
#include "./histograms-render/histograms-render.h"
#include "./output/output.h"
#include "./quantitative-computations/quantitative-computations.h"
#include "./statistical-computations/statistical-computations.h"
#include "./types.h"
#include <chrono>

#include "iostream"

int main ()
{
    std::string inputFileName = cliPrompt ();

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now ();

    std::vector<InputRow> data = csvReader (inputFileName);
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

    Quantitatives quantitatives = quantitativeComputations (data);
    std::string quantitativesOutput = "all,unique,empty\n" + std::to_string (quantitatives.all) +
                                      "," + std::to_string (quantitatives.unique) + "," +
                                      std::to_string (quantitatives.empty) + "\n";

    std::vector<CorrelRate> correlRate = correlationAnalysis (data, average);

    output (data, "output/input.csv");

    output (min, "output/statistical/min.csv");
    output (max, "output/statistical/max.csv");
    output (average, "output/statistical/average.csv");
    output (median, "output/statistical/median.csv");
    output (quartile_25, "output/statistical/quartile_25.csv");
    output (quartile_75, "output/statistical/quartile_75.csv");
    output (square_deviation, "output/statistical/square_deviation.csv");

    output (diff_data, "output/statistical/diff.csv");
    output (diff_min, "output/diff_statistical/min.csv");
    output (diff_max, "output/diff_statistical/max.csv");
    output (diff_average, "output/diff_statistical/average.csv");
    output (diff_median, "output/diff_statistical/median.csv");
    output (diff_quartile_25, "output/diff_statistical/quartile_25.csv");
    output (diff_quartile_75, "output/diff_statistical/quartile_75.csv");
    output (diff_square_deviation, "output/diff_statistical/square_deviation.csv");

    output (correlRate, "output/correlation.csv", "contry,rate");

    outputString (quantitativesOutput, "output/quantitatives.csv");

    std::vector<std::vector<InputRow>> toRender = {
        min,
        max,
        average,
        median,
        quartile_25,
        quartile_75,
        square_deviation,
        diff_min,
        diff_max,
        diff_average,
        diff_median,
        diff_quartile_25,
        diff_quartile_75,
        diff_square_deviation,
    };
    std::vector<std::string> toRenderNames = {

        "min",
        "max",
        "average",
        "median",
        "quartile_25",
        "quartile_75",
        "square_deviation",
        "diff_min",
        "diff_max",
        "diff_average",
        "diff_median",
        "diff_quartile_25",
        "diff_quartile_75",
        "diff_square_deviation",
    };

    histogramRender (toRender, toRenderNames, "output/barCharts");

    std::chrono::high_resolution_clock::time_point finish = std::chrono::high_resolution_clock::now ();
    long long durationMs = std::chrono::duration_cast<std::chrono::milliseconds> (finish - start).count ();
    int durationS = durationMs / 1000;
    int durationAfterPoint = durationMs % 1000;

    std::cout << "Done in " << durationS << "." << durationAfterPoint << "s.\n";

    return 0;
}