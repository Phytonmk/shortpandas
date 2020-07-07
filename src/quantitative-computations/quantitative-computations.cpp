/**
 * Функция для вычисления количественных характеристик
 */
#include <vector>
#include <set>
#include <iostream>
#include "../csv-reader/csv-reader.h"
#include <string>

int quantitativeComputations (std::vector<InputRow> data, int &all, int &unique_values, int &empty_values)
{
    std::multiset <long double> unique;
    for(int i=0;i<data.size();i++) //записываем все значения в коллекцию
    {
        unique.insert(data.at(i).crop_land);
        unique.insert(data.at(i).grazing_land);
        unique.insert(data.at(i).forest_land);
        unique.insert(data.at(i).fishing_ground);
        unique.insert(data.at(i).built_up_land);
        unique.insert(data.at(i).carbon);
        unique.insert(data.at(i).total);
        unique.insert(data.at(i).percapita);
        unique.insert(data.at(i).population);
    }
    unique_values=0;
    for (int i=0; i<data.size();i++)//подсчет числа вхождений значения во множество
    {
        if(unique.count(data.at(i).crop_land)==1)
            unique_values++;
        if(unique.count(data.at(i).grazing_land)==1)
            unique_values++;
        if(unique.count(data.at(i).forest_land)==1)
            unique_values++;
        if(unique.count(data.at(i).fishing_ground)==1)
            unique_values++;
        if(unique.count(data.at(i).built_up_land)==1)
            unique_values++;
        if(unique.count(data.at(i).carbon)==1)
            unique_values++;
        if(unique.count(data.at(i).total)==1)
            unique_values++;
        if(unique.count(data.at(i).percapita)==1)
            unique_values++;
        if(unique.count(data.at(i).population)==1)
            unique_values++;
    }
    empty_values=0;
    empty_values=unique.count(-1);//количество пустых значений
    int all_values=0;
    all_values=unique.size()-empty_values;//количество значений без пустых и без годов и стран
    std::multiset <std::string> countries;
    std::multiset <int> years;
    for (int i=0;i<data.size();i++)
    {
        countries.insert(data.at(i).country);
    }
    int all_countries = 0;
    all_countries = countries.size();//количество данных в столбце страны
    for (int i=0;i<data.size();i++)
    {
        years.insert(data.at(i).year);
    }
    int all_years = 0;
    all_years = years.size();//количество данных в столбце год
    all=all_values+all_years+all_countries;//количество всех данных без пустых значений
    return 0;
}
