#include "../types.h"
#include <string>
#include <vector>
/**
@brief Вычисление первых разностей для нахождения статистических характеристик
@detailed Данная функция вычисляет первые разности по каждому столбцу в стране
и возвращает выборку, содержащую разности
@param Выборка данных
@return Выборка первых разностей
 */

std::vector<InputRow> differences (std::vector<InputRow> inputData)
{
    std::vector<InputRow> result;

    if (inputData.size () == 0) return result;

    std::string currentCountry = inputData[0].country;

    for (int i = 1; i < inputData.size (); i++)
    {
        std::string country = inputData[i].country;

        if (currentCountry == country)
        {
            InputRow prevRow = inputData[i - 1];
            InputRow nextRow = inputData[i];
            InputRow differenceRow = {
                .country = country,
                .year = nextRow.year - prevRow.year,
                .crop_land = nextRow.crop_land - prevRow.crop_land,
                .grazing_land = nextRow.grazing_land - prevRow.grazing_land,
                .forest_land = nextRow.forest_land - prevRow.forest_land,
                .fishing_ground = nextRow.fishing_ground - prevRow.fishing_ground,
                .built_up_land = nextRow.built_up_land - prevRow.built_up_land,
                .carbon = nextRow.carbon - prevRow.carbon,
                .total = nextRow.total - prevRow.total,
                .percapita = nextRow.percapita - prevRow.percapita,
                .population = nextRow.population - prevRow.population,
            };

            result.push_back (differenceRow);
        }
        else
        {
            currentCountry = country;
        }
    }

    return result;
}