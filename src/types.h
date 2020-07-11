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
        if (row.country != "") out << "\"" << row.country << "\"";
        out << ",";
        if (row.year != -1) out << row.year;
        out << ",";
        if (row.crop_land != -1) out << row.crop_land;
        out << ",";
        if (row.grazing_land != -1) out << row.grazing_land;
        out << ",";
        if (row.forest_land != -1) out << row.forest_land;
        out << ",";
        if (row.fishing_ground != -1) out << row.fishing_ground;
        out << ",";
        if (row.built_up_land != -1) out << row.built_up_land;
        out << ",";
        if (row.carbon != -1) out << row.carbon;
        out << ",";
        if (row.total != -1) out << row.total;
        out << ",";
        if (row.percapita != -1) out << row.percapita;
        out << ",";
        if (row.population != -1) out << row.population;

        return out;
    }
};

struct CorrelRate
{
    std::string country;
    long double rate;

    friend std::ostream &operator<< (std::ostream &out, CorrelRate &row)
    {
        return out << row.country << "," << row.rate;
    }
};

std::string inputRowHeader = "country,year,crop_land,grazing_land,forest_land,fishing_ground,built_"
                             "up_land,carbon,total,percapita,population";

struct Quantitatives
{
    int all;
    int unique;
    int empty;
};

#endif
