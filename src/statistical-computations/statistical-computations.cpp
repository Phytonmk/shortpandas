/**
 * Функция для вычисления статистических характеристик
  
 */
#include "../csv-reader/csv-reader.h"
#include <math.h>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>


struct Columns
{
    std::string country;
    int year;
    long double crop_land;
    long double grazing_land;
    long double forest_land;
    long double fishing_ground;
    long double built_up_land;
    long double carbon;
    long double total;
    long double percapita;
    long double population;

};

struct Account // структура для хранения количетва строк на страну
{
    std::string country;
    int point_beg;
    int point_end;
};




void Simple_calculation(std:: vector <long double> array, int beg, int end, long double& min,  long double& max, long double& median, long double& quartile_25, long double& quartile_75)
{
    int quantity = end-beg+1;
    long double num_quart = 0;
    min=array.at(0);
    max=array.at(quantity-1);
    if (quantity % 2 != 0)
        {
            median = array.at((quantity+1)/2-1);
        }
    else median = (array.at(quantity/2-1)+array.at((quantity/2+1)/2-1));
    num_quart = (quantity+1)*(0.25);
    if (num_quart == round(num_quart))
    {
        quartile_25=array.at(num_quart);
    }
    else {
        quartile_25=(array.at(floor(num_quart)-1)+array.at(ceil(num_quart)-1))/2;
    }

    num_quart = (quantity+1)*(0.75);
    if (num_quart == round(num_quart))
    {
        quartile_75=array.at(num_quart);
    }
    else {
        quartile_75=(array.at(floor(num_quart)-1)+array.at(ceil(num_quart)-1))/2;
    }

}

void Square_dev_calculation(std:: vector <long double> array, int beg, int end, long double sum, long double& square_deviation, long double& average)
{
    int quantity = end-beg+1;
    average=sum/quantity;
    sum=0;
    for (int i = 0; i < array.size(); i++)
    {
        sum += pow((array.at(i) - average),2);
    }
    square_deviation = sqrt(sum/(quantity-1));
}

int statisticalComputations (std::vector <InputRow> data)
{
    // перечисление векторов, в которых будут хранится значения вычисляемых параметров
    std:: vector <Columns> min;
    std:: vector <Columns> max;
    std:: vector <Columns> average;
    std:: vector <Columns> median;
    std:: vector <Columns> quartile_25;
    std:: vector <Columns> quartile_75;
    std:: vector <Columns>  square_deviation;
    std:: vector <Account> counter;
    std:: vector <long double> array;
    int num_countr = 0;
    for (int i = 0; i < data.size(); i++) // ошибка где-то тут data.size()
    {
        int m=data.size();
        array.clear();
         // для подсчета суммы
        Columns sum = { "unknown", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        Account nulln = {"unknown", 0, 0};
        counter.push_back(nulln);
        min.push_back(sum);
        max.push_back(sum);
        average.push_back(sum);
        median.push_back(sum);
        quartile_25.push_back(sum);
        quartile_75.push_back(sum);
        square_deviation.push_back(sum);
        counter.at(num_countr).point_beg = i;
            do {
                if (num_countr!=0 && data.at(i-1).country != data.at(i-2).country)
                {
                    i--;
                    counter.at(num_countr).point_beg = i;
                }
                array.push_back(data.at(i).crop_land);
                sum.crop_land+=data.at(i).crop_land;
                i++;
            } while (data.at(i).country == data.at(i-1).country && i != data.size()-1);
            counter.at(num_countr).point_end = i-1;
            counter.at(num_countr).country=data.at(i-1).country;
            if (i == data.size()-1)
            {
                array.push_back(data.at(i).crop_land);
                sum.crop_land+=data.at(i).crop_land;
                counter.at(num_countr).point_end = i;
                i++;
            }
            
            /* */ sort(array.begin(), array.end());
            Simple_calculation(array,counter.at(num_countr).point_beg, counter.at(num_countr).point_end, min.at(num_countr).crop_land, max.at(num_countr).crop_land, median.at(num_countr).crop_land, quartile_25.at(num_countr).crop_land, quartile_75.at(num_countr).crop_land);
            Square_dev_calculation(array, counter.at(num_countr).point_beg, counter.at(num_countr).point_end, sum.crop_land, square_deviation.at(num_countr).crop_land, average.at(num_countr).crop_land);

            array.clear();
            for (int j = counter.at(num_countr).point_beg; j <= counter.at(num_countr).point_end; j++)
            {
                array.push_back(data.at(j).grazing_land);
                sum.grazing_land+=data.at(j).grazing_land;
            }
            sort(array.begin(), array.end());
            Simple_calculation(array,counter.at(num_countr).point_beg, counter.at(num_countr).point_end, min.at(num_countr).grazing_land, max.at(num_countr).grazing_land, median.at(num_countr).grazing_land, quartile_25.at(num_countr).grazing_land, quartile_75.at(num_countr).grazing_land);
            Square_dev_calculation(array, counter.at(num_countr).point_beg, counter.at(num_countr).point_end, sum.grazing_land, square_deviation.at(num_countr).grazing_land, average.at(num_countr).grazing_land);
        
            array.clear();
            for (int j = counter.at(num_countr).point_beg; j <= counter.at(num_countr).point_end; j++)
            {
                array.push_back(data.at(j).forest_land);
                sum.forest_land+=data.at(j).forest_land;
            }
            sort(array.begin(), array.end());
            Simple_calculation(array,counter.at(num_countr).point_beg, counter.at(num_countr).point_end, min.at(num_countr).forest_land, max.at(num_countr).forest_land, median.at(num_countr).forest_land, quartile_25.at(num_countr).forest_land, quartile_75.at(num_countr).forest_land);
            Square_dev_calculation(array, counter.at(num_countr).point_beg, counter.at(num_countr).point_end, sum.forest_land, square_deviation.at(num_countr).forest_land, average.at(num_countr).forest_land);

            array.clear();
            for (int j = counter.at(num_countr).point_beg; j <= counter.at(num_countr).point_end; j++)
            {
                array.push_back(data.at(j).fishing_ground);
                sum.forest_land+=data.at(j).fishing_ground;
            }
            sort(array.begin(), array.end());
            Simple_calculation(array,counter.at(num_countr).point_beg, counter.at(num_countr).point_end, min.at(num_countr).fishing_ground, max.at(num_countr).fishing_ground, median.at(num_countr).fishing_ground, quartile_25.at(num_countr).fishing_ground, quartile_75.at(num_countr).fishing_ground);
            Square_dev_calculation(array, counter.at(num_countr).point_beg, counter.at(num_countr).point_end, sum.fishing_ground, square_deviation.at(num_countr).fishing_ground, average.at(num_countr).fishing_ground);

            array.clear();
            for (int j = counter.at(num_countr).point_beg; j <= counter.at(num_countr).point_end; j++)
            {
                array.push_back(data.at(j).built_up_land);
                sum.forest_land+=data.at(j).built_up_land;
            }
            sort(array.begin(), array.end());
            Simple_calculation(array,counter.at(num_countr).point_beg, counter.at(num_countr).point_end, min.at(num_countr).built_up_land, max.at(num_countr).built_up_land, median.at(num_countr).built_up_land, quartile_25.at(num_countr).built_up_land, quartile_75.at(num_countr).built_up_land);
            Square_dev_calculation(array, counter.at(num_countr).point_beg, counter.at(num_countr).point_end, sum.built_up_land, square_deviation.at(num_countr).built_up_land, average.at(num_countr).built_up_land);

            array.clear();
            for (int j = counter.at(num_countr).point_beg; j<=counter.at(num_countr).point_end; j++)
            {
                array.push_back(data.at(j).carbon);
                sum.forest_land+=data.at(j).carbon;
            }
            sort(array.begin(), array.end());
            Simple_calculation(array,counter.at(num_countr).point_beg, counter.at(num_countr).point_end, min.at(num_countr).carbon, max.at(num_countr).carbon, median.at(num_countr).carbon, quartile_25.at(num_countr).carbon, quartile_75.at(num_countr).carbon);
            Square_dev_calculation(array, counter.at(num_countr).point_beg, counter.at(num_countr).point_end, sum.carbon, square_deviation.at(num_countr).carbon, average.at(num_countr).carbon);

            array.clear();
            for (int j = counter.at(num_countr).point_beg; j<=counter.at(num_countr).point_end; j++)
            {
                array.push_back(data.at(j).total);
                sum.forest_land+=data.at(j).total;
            }
            sort(array.begin(), array.end());
            Simple_calculation(array,counter.at(num_countr).point_beg, counter.at(num_countr).point_end, min.at(num_countr).total, max.at(num_countr).total, median.at(num_countr).total, quartile_25.at(num_countr).total, quartile_75.at(num_countr).total);
            Square_dev_calculation(array, counter.at(num_countr).point_beg, counter.at(num_countr).point_end, sum.total, square_deviation.at(num_countr).total, average.at(num_countr).total);
            
            array.clear();
            for (int j = counter.at(num_countr).point_beg; j<=counter.at(num_countr).point_end; j++)
            {
                array.push_back(data.at(j).percapita);
                sum.forest_land+=data.at(j).percapita;
            }
            sort(array.begin(), array.end());
            Simple_calculation(array,counter.at(num_countr).point_beg, counter.at(num_countr).point_end, min.at(num_countr).percapita, max.at(num_countr).percapita, median.at(num_countr).percapita, quartile_25.at(num_countr).percapita, quartile_75.at(num_countr).percapita);
            Square_dev_calculation(array, counter.at(num_countr).point_beg, counter.at(num_countr).point_end, sum.percapita, square_deviation.at(num_countr).percapita, average.at(num_countr).percapita);

            array.clear();
            for (int j = counter.at(num_countr).point_beg; j<=counter.at(num_countr).point_end; j++)
            {
                array.push_back(data.at(j).population);
                sum.forest_land+=data.at(j).population;
            }
            sort(array.begin(), array.end());
            Simple_calculation(array,counter.at(num_countr).point_beg, counter.at(num_countr).point_end, min.at(num_countr).population, max.at(num_countr).population, median.at(num_countr).population, quartile_25.at(num_countr).population, quartile_75.at(num_countr).population);
            Square_dev_calculation(array, counter.at(num_countr).point_beg, counter.at(num_countr).point_end, sum.population, square_deviation.at(num_countr).population, average.at(num_countr).population);

        num_countr++;
    }

    //int id=data.at(num_countr).carbon;
    return 0;
}
