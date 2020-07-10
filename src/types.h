#include <istream>
#include <string>


#ifndef SHORTPANDAS_TYPES
#define SHORTPANDAS_TYPES

/**
 * Структура для представления одной строчки входного csv файла
 */
struct InputRow
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

    friend std::ostream &operator<< (std::ostream &out, InputRow &row)
    {
        return out << row.country << "," << row.year << "," << row.crop_land << "," << row.grazing_land
                   << "," << row.forest_land << "," << row.fishing_ground << "," << row.built_up_land << ","
                   << row.carbon << "," << row.total << "," << row.percapita << "," << row.population;
    }
};

#endif