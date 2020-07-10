
#include "../csv-reader/csv-reader.h"
#include "../types.h"
#include <iostream>
#include <set>
#include <string>
#include <vector>

/**
 * Функция для вычисления количественных характеристик
 */
Quantitatives quantitativeComputations (std::vector<InputRow> data)
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
    int unique_values = 0;
    std::set<long double>::iterator it = unique_search.begin ();
    while (it != unique_search.end ()) //подсчет числа вхождений значения во множество
    {
        if (unique.count (*it) == 1) unique_values++;
        it++;
    }
    int empty_values = 0;
    empty_values = unique.count (-1); //количество пустых значений
    int all_values = unique.size () - empty_values; //количественные данные без пустых значений
    std::multiset<std::string> countries;
    std::multiset<int> years;
    std::set<std::string> unique_countries;
    std::set<int> unique_years;
    for (int i = 0; i < data.size (); i++) //записываем данные из столбца "страна" в коллекцию
    {
        countries.insert (data.at (i).country);
        unique_countries.insert (data.at (i).country);
    }
    std::set<std::string>::iterator it1 = unique_countries.begin ();
    while (it1 != unique_countries.end ()) //подсчет числа вхождений значения во множество
    {
        if (countries.count (*it1) == 1) unique_values++;
        it1++;
    }
    int all_countries = 0;
    all_countries = countries.size (); //количество данных в столбце страны
    for (int i = 0; i < data.size (); i++) //записываем данные из столбца "год" в коллекцию
    {
        years.insert (data.at (i).year);
        unique_years.insert (data.at (i).year);
    }
    std::set<int>::iterator it2 = unique_years.begin ();
    while (it2 != unique_years.end ()) //подсчет числа вхождений значения во множество
    {
        if (years.count (*it2) == 1) unique_values++;
        it2++;
    }
    int all_years = 0;
    all_years = years.size (); //количество данных в столбце год

    Quantitatives result = {
        .all = all_values,
        .unique = unique_values,
        .empty = empty_values,
    };

    return result;
}
