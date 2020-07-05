#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


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

/**
 * Структура для сохранения индексов столбцов в csv файле.
 * Позволяет столбцам во входном файле иметь произвольный порядок столбцов
 */
struct ColumnIndexes
{
    int country;
    int year;
    int crop_land;
    int grazing_land;
    int forest_land;
    int fishing_ground;
    int built_up_land;
    int carbon;
    int total;
    int percapita;
    int population;

    friend std::ostream &operator<< (std::ostream &out, ColumnIndexes &indexes)
    {
        return out << "country: " << indexes.country << ", year:" << indexes.year
                   << ", crop_land:" << indexes.crop_land << ", grazing_land:" << indexes.grazing_land
                   << ", forest_land:" << indexes.forest_land << ", fishing_ground:" << indexes.fishing_ground
                   << ", built_up_land:" << indexes.built_up_land << ", carbon:" << indexes.carbon
                   << ", total:" << indexes.total << ", percapita:" << indexes.percapita
                   << ", population:" << indexes.population;
    }
};

/**
 * Функция разбивает строку на вектор строк по разделителю
 */
std::vector<std::string> splitString (std::string toSplit, char separator)
{
    std::vector<std::string> result;
    int prevSeparator = -1;
    for (int i = 0; i < toSplit.length (); i++)
    {
        if (toSplit[i] == separator)
        {
            result.push_back (toSplit.substr (prevSeparator + 1, i - prevSeparator - 1));
            prevSeparator = i;
        }
        else if (i == toSplit.length () - 1)
        {
            result.push_back (toSplit.substr (prevSeparator + 1, i - prevSeparator));
        }
    }

    return result;
}

/**
 * Функция читает заголовки csv файла и возвращает позиции каждого столбца в файле
 */
ColumnIndexes extractColumnIndexes (std::string headString)
{
    std::vector<std::string> headers = splitString (headString, ',');


    ColumnIndexes result = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

    for (int i = 0; i < headers.size (); i++)
    {
        std::string headerName = headers.at (i);

        if (headerName == "country")
        {
            result.country = i;
        }
        else if (headerName == "year")
        {
            result.year = i;
        }
        else if (headerName == "crop_land")
        {
            result.crop_land = i;
        }
        else if (headerName == "grazing_land")
        {
            result.grazing_land = i;
        }
        else if (headerName == "forest_land")
        {
            result.forest_land = i;
        }
        else if (headerName == "fishing_ground")
        {
            result.fishing_ground = i;
        }
        else if (headerName == "built_up_land")
        {
            result.built_up_land = i;
        }
        else if (headerName == "carbon")
        {
            result.carbon = i;
        }
        else if (headerName == "total")
        {
            result.total = i;
        }
        else if (headerName == "percapita")
        {
            result.percapita = i;
        }
        else if (headerName == "population")
        {
            result.population = i;
        }
    }
    return result;
}

/**
 * Функция для чтения и парсинга csv файла
 */
std::vector<InputRow> csvReader (std::string fileName)
{
    std::vector<InputRow> result;

    std::ifstream fileReadStream (fileName);
    std::string headString;


    getline (fileReadStream, headString);

    ColumnIndexes columnIndexes = extractColumnIndexes (headString);

    std::string rowString;

    while (getline (fileReadStream, rowString))
    {
        std::vector<std::string> cells = splitString (rowString, ',');

        InputRow row = { "unknown", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

        for (int i = 0; i < cells.size (); i++)
        {
            std::string cellValue = cells.at (i);
            if (cellValue.empty ())
            {
                continue;
            }

            if (columnIndexes.country == i)
            {
                row.country = cellValue;
            }
            else if (columnIndexes.year == i)
            {
                row.year = ::atof (cellValue.c_str ());
            }
            else if (columnIndexes.crop_land == i)
            {
                row.crop_land = ::atof (cellValue.c_str ());
            }
            else if (columnIndexes.grazing_land == i)
            {
                row.grazing_land = ::atof (cellValue.c_str ());
            }
            else if (columnIndexes.forest_land == i)
            {
                row.forest_land = ::atof (cellValue.c_str ());
            }
            else if (columnIndexes.fishing_ground == i)
            {
                row.fishing_ground = ::atof (cellValue.c_str ());
            }
            else if (columnIndexes.built_up_land == i)
            {
                row.built_up_land = ::atof (cellValue.c_str ());
            }
            else if (columnIndexes.carbon == i)
            {
                row.carbon = ::atof (cellValue.c_str ());
            }
            else if (columnIndexes.total == i)
            {
                row.total = ::atof (cellValue.c_str ());
            }
            else if (columnIndexes.percapita == i)
            {
                row.percapita = ::atof (cellValue.c_str ());
            }
            else if (columnIndexes.population == i)
            {
                row.population = ::atof (cellValue.c_str ());
            }
        }
        result.push_back (row);
    }

    return result;
}
