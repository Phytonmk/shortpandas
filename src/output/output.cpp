#include "../types.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * Функция для вывода результатов вычислений в csv файл
 */
void output (std::vector<InputRow> table, std::string filename, std::string tableHeader = inputRowHeader)
{
    std::ofstream out (filename);
    out << tableHeader << "\n";
    for (int i = 0; i < table.size (); i++)
    {
        out << table[i] << "\n";
    }
    out.close ();
    std::cout << "Wrote " << table.size () << " rows to " << filename << "\n";
}
void output (std::vector<CorrelRate> table, std::string filename, std::string tableHeader = inputRowHeader)
{
    std::ofstream out (filename);
    out << tableHeader << "\n";
    for (int i = 0; i < table.size (); i++)
    {
        out << table[i] << "\n";
    }
    out.close ();
    std::cout << "Wrote " << table.size () << " rows to " << filename << "\n";
}

void outputString (std::string content, std::string filename)
{
    std::ofstream out (filename);
    out << content;
    out.close ();
    std::cout << "Wrote " << content.size () << " bytes to " << filename << "\n";
}