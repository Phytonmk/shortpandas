
#include "../csv-reader/csv-reader.h"
#include <iostream>
#include <set>
#include <string>
#include <vector>

/**
 * Функция для вычисления количественных характеристик
 */
int quantitativeComputations (std::vector<InputRow> data, int &all, int &unique_values, int &empty_values)
{
    std::multiset<long double> unique;
    std::set<long double> unique_search; //коллекция для поиска уникальных значений
    long double agent = 0;
    for (int i = 0; i < data.size (); i++) //записываем все значения в две коллекции
    {
        agent = data.at (i).crop_land;
        unique.insert (agent);
        unique_search.insert (agent);
        agent = data.at (i).grazing_land;
        unique.insert (agent);
        unique_search.insert (agent);
        agent = data.at (i).forest_land;
        unique.insert (agent);
        unique_search.insert (agent);
        agent = data.at (i).fishing_ground;
        unique.insert (agent);
        unique_search.insert (agent);
        agent = data.at (i).built_up_land;
        unique.insert (agent);
        unique_search.insert (agent);
        agent = data.at (i).carbon;
        unique.insert (agent);
        unique_search.insert (agent);
        agent = data.at (i).total;
        unique.insert (agent);
        unique_search.insert (agent);
        agent = data.at (i).percapita;
        unique.insert (agent);
        unique_search.insert (agent);
        agent = data.at (i).population;
        unique.insert (agent);
        unique_search.insert (agent);
    }
    unique_values = 0;
    std::set<long double>::iterator it = unique_search.begin ();
    while (it != unique_search.end ()) //подсчет числа вхождений значения во множество
    {
        if (unique.count (*it) == 1) unique_values++;
        it++;
    }
    empty_values = 0;
    empty_values = unique.count (-1); //количество пустых значений
    int all_values = 0;
    all_values = unique.size () - empty_values; //количественные данные без пустых значений
    std::multiset<std::string> countries;
    std::multiset<int> years;
    for (int i = 0; i < data.size (); i++) //записываем данные из столбца "страна" в коллекцию
    {
        countries.insert (data.at (i).country);
    }
    int all_countries = 0;
    all_countries = countries.size (); //количество данных в столбце страны
    for (int i = 0; i < data.size (); i++) //записываем данные из столбца "год" в коллекцию
    {
        years.insert (data.at (i).year);
    }
    int all_years = 0;
    all_years = years.size (); //количество данных в столбце год
    all = all_values + all_years + all_countries; //количество всех данных без пустых значений
    return 0;
}
