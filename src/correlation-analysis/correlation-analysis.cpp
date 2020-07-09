#include "../csv-reader/csv-reader.h"
#include "../statistical-computations/statistical-computations.h"
#include "cmath"
#include <iostream>
#include <string>
#include <vector>


struct correlRate
{
    std::string country;
    long double rate;
};

/**
 * Функция для выполнения корреляционного анализа (расчет коэффициента Пирсона)
 */
std::vector<correlRate> correlationAnalysis (std::vector<InputRow> data, std::vector<InputRow> average)
{
    long double x_average, y_average;
    std::string current_country;
    std::vector<correlRate> correlation_analysis;
    struct correlRate current_rate;
    std::vector<long double> x;
    std::vector<long double> y;
    std::vector<long double> x_diff;
    std::vector<long double> y_diff;
    std::vector<long double> x_diffSq;
    std::vector<long double> y_diffSq;
    int i = 0;
    int key = 0;
    int data_size = data.size ();
    while (i < data_size)
    {
        do //считываем нужные выборки по текущей стране
        {
            x.push_back (data.at (i).percapita);
            y.push_back (data.at (i).population);
            i++;
            if (i == data_size) key = 1;
        } while ((key == 0) && (data.at (i).country == data.at (i - 1).country));
        current_country = data.at (i - 1).country;
        for (int j = 0; j < average.size (); j++) //считываем выборочные средние по текущей стране
        {
            if (current_country == average.at (j).country)
            {
                x_average = average.at (j).percapita;
                y_average = average.at (j).population;
                break;
            }
            break;
        }
        for (int j = 0; j < x.size (); j++) //считаем разности для формулы
        {
            if ((x[j] != (-1)) && (y[j] != (-1)))
            {
                x_diff.push_back (x[j] - x_average);
                y_diff.push_back (y[j] - y_average);
            }
        }
        if ((x_diff.size () != 0) && y_diff.size () != 0) //проверка на возможность посчитать коэффициент Пирсона
        {
            for (int j = 0; j < x_diff.size (); j++) //вычисление квадратов разностей
            {
                x_diffSq.push_back ((x_diff[j] * x_diff[j]));
                y_diffSq.push_back ((y_diff[j] * y_diff[j]));
            }
            long double currMulti = 0, currSum = 0;
            for (int j = 0; j < x_diff.size (); j++) //подсчет числителя (сумма произведений разностей)
            {
                currMulti = x_diff[j] * y_diff[j];
                currSum = currSum + currMulti;
            }
            long double sumSq_x = 0, sumSq_y = 0;
            for (int j = 0; j < x_diffSq.size (); j++) //подсчет суммы квадратов разностей выборки Х
            {
                sumSq_x = sumSq_x + x_diffSq[j];
            }
            for (int j = 0; j < y_diffSq.size (); j++) //подсчет суммы квадратов разностей выборки Y
            {
                sumSq_y = sumSq_y + y_diffSq[j];
            }
            current_rate.country = current_country;
            current_rate.rate = currSum / (sqrt (sumSq_x * sumSq_y));
            correlation_analysis.push_back (current_rate);
        }
        else
        {
            current_rate.country = current_country;
            current_rate.rate = -11; //-11 означает, что коэффициент не удалось посчитать
            correlation_analysis.push_back (current_rate);
        }
        x.clear ();
        y.clear ();
        x_diff.clear ();
        y_diff.clear ();
        x_diffSq.clear ();
        y_diffSq.clear ();
    }
    return correlation_analysis;
}