#include "../output/output.h"
#include "../types.h"
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

int columnWidth = 25;
int canvasHeight = 800;
int horizontalPadding = 20;
int verticalPadding = 10;
int bottomNamesHeight = 150;
int leftValuesWidth = 150;
int columnsGap = 2;
int vercticalMarksCount = 10;

int maxHeight = canvasHeight - verticalPadding * 2 - bottomNamesHeight;

/**
 * Функция возвращает значение из строки таблицы на основе индекса столбца
 **/
long double getValueOfColumnByIndex (InputRow row, int columnIndex)
{
    switch (columnIndex)
    {
    case 0:
        return row.year;
    case 1:
        return row.crop_land;
    case 2:
        return row.grazing_land;
    case 3:
        return row.forest_land;
    case 4:
        return row.fishing_ground;
    case 5:
        return row.built_up_land;
    case 6:
        return row.carbon;
    case 7:
        return row.total;
    case 8:
        return row.percapita;
    case 9:
        return row.population;
    }

    return 0;
}

/**
 * Функция переводит числовую переменную в строку с округлением до целого
 **/
std::string toString (int __val)
{
    return std::to_string (__val);
}

/**
 * Функция возвращает название столбца таблицы на основе индекса
 **/
std::string getNameOfColumnByIndex (int columnIndex)
{
    switch (columnIndex)
    {
    case 0:
        return "year";
    case 1:
        return "crop_land";
    case 2:
        return "grazing_land";
    case 3:
        return "forest_land";
    case 4:
        return "fishing_ground";
    case 5:
        return "built_up_land";
    case 6:
        return "carbon";
    case 7:
        return "total";
    case 8:
        return "percapita";
    case 9:
        return "population";
    }

    return "unknown";
}

/**
 * Функция для рендеринга гистограм
 */
void histogramRender (std::vector<std::vector<InputRow>> tables, std::vector<std::string> names, std::string outputPath)
{

    for (int tableIndex = 0; tableIndex < tables.size (); tableIndex++)
    {
        std::vector<InputRow> table = tables.at (tableIndex);

        for (int column = 1; column < 10; column++)
        {


            std::string svgMarkup = "";

            int countries = table.size ();
            int canvasWidth = countries * columnWidth;

            svgMarkup += "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" +
                         toString (canvasWidth) + "\" height=\"" + toString (canvasHeight) + "\">";


            long double maxValue = 0;
            long double minValue = 0;


            for (int countryIndex = 0; countryIndex < countries; countryIndex++)
            {
                InputRow row = table.at (countryIndex);
                long double value = getValueOfColumnByIndex (row, column);

                if (value == -1)
                {
                    continue;
                }

                if (value > maxValue)
                {
                    maxValue = value;
                }
                if (value < minValue)
                {
                    minValue = value;
                }
            }


            for (int markIndex = 0; markIndex < vercticalMarksCount; markIndex++)
            {
                long double part = (long double)(markIndex) / (long double)(vercticalMarksCount);
                long double value = (maxValue - minValue) * (1 - part);
                int y = verticalPadding + maxHeight * part;
                svgMarkup += "<line x1=\"" + toString (horizontalPadding) + "\" y1=\"" +
                             toString (y) + "\" x2=\"" + toString (canvasWidth) + "\" y2=\"" +
                             toString (y) + "\" stroke=\"grey\" />";


                svgMarkup += "<text x=\"" + toString (horizontalPadding) + "\" y=\"" +
                             toString (y + 15) + "\">" + std::to_string (value) + "</text>";
            }


            svgMarkup += "	<g transform=\"translate(" + toString (horizontalPadding) + "," +
                         toString (verticalPadding) + ")\">";

            int oneColumnSpace = ((canvasWidth - leftValuesWidth - horizontalPadding * 2) / countries);

            for (int countryIndex = 0; countryIndex < countries; countryIndex++)
            {
                InputRow row = table.at (countryIndex);
                long double value = getValueOfColumnByIndex (row, column);

                if (value == -1)
                {
                    continue;
                }


                int x = oneColumnSpace * countryIndex + leftValuesWidth;
                int width = oneColumnSpace - columnsGap;
                int height = maxValue != 0 ? (value - minValue) / maxValue * maxHeight : 0;
                int y = canvasHeight - verticalPadding - bottomNamesHeight - height;

                svgMarkup += "<rect fill=\"black\" x=\"" + toString (x) + "\" width=\"" + toString (width) +
                             "\" y=\"" + toString (y) + "\" height=\"" + toString (height) + "\" />";

                int textY = canvasHeight - bottomNamesHeight;

                svgMarkup += "<g transform=\"translate(" + toString (x) + ", " + toString (textY) +
                             ")\" width=\"" + toString (width) +
                             "\" height=\"20\" ><text transform=\"rotate(50)\">" + row.country + "</text></g>";
            }
            svgMarkup += "	</g>";

            svgMarkup += "</svg>";

            outputString (svgMarkup, outputPath + "/" + names.at (tableIndex) + "_" +
                                     getNameOfColumnByIndex (column) + ".svg");
        }
    }

    std::string htmlMarkup = "<style>div { max-width: 100vw; overflow: auto; }</style>";

    for (int tableIndex = 0; tableIndex < tables.size (); tableIndex++)
    {
        htmlMarkup += "<h1>" + names.at (tableIndex) + "</h1>";

        for (int column = 1; column < 10; column++)
        {
            htmlMarkup += "<h2>" + getNameOfColumnByIndex (column) + "</h2>";

            htmlMarkup += "<div><img src=\"./" + names.at (tableIndex) + "_" +
                          getNameOfColumnByIndex (column) + ".svg\" /></div>";
        }
    }

    outputString (htmlMarkup, outputPath + "/index.html");
}
