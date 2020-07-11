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
        if (row.year != -1 && row.year != -11 && row.year != -2) out << row.year;
        out << ",";
        if (row.crop_land != -1 && row.crop_land != -11 && row.crop_land != -2)
            out << row.crop_land;
        out << ",";
        if (row.grazing_land != -1 && row.grazing_land != -11 && row.grazing_land != -2)
            out << row.grazing_land;
        out << ",";
        if (row.forest_land != -1 && row.forest_land != -11 && row.forest_land != -2)
            out << row.forest_land;
        out << ",";
        if (row.fishing_ground != -1 && row.fishing_ground != -11 && row.fishing_ground != -2)
            out << row.fishing_ground;
        out << ",";
        if (row.built_up_land != -1 && row.built_up_land != -11 && row.built_up_land != -2)
            out << row.built_up_land;
        out << ",";
        if (row.carbon != -1 && row.carbon != -11 && row.carbon != -2) out << row.carbon;
        out << ",";
        if (row.total != -1 && row.total != -11 && row.total != -2) out << row.total;
        out << ",";
        if (row.percapita != -1 && row.percapita != -11 && row.percapita != -2)
            out << row.percapita;
        out << ",";
        if (row.population != -1 && row.population != -11 && row.population != -2)
            out << row.population;

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
