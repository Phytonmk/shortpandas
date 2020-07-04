#include <fstream>
#include <iostream>
#include <string>

const std::string defaultInputExampleFileName = "input-example.csv";
/**
 * Функция для проверки что файл существует
 */
bool fileExists (const std::string &fileName)
{
    std::ifstream f (fileName.c_str ());

    return f.good ();
}

/**
 * Функция для взаимодействия с пользователем через командую строку
 */
std::string cliPrompt ()
{
    std::cout << "Enter the path to .csv file to be handled or drag & drop file to terminal\n\n";
    std::string fileName = "";
    while (true)
    {
        std::cout << "Path to file";
        if (fileExists (defaultInputExampleFileName))
        {
            fileName = defaultInputExampleFileName;
            std::cout << " [" << defaultInputExampleFileName << "]";
        }
        std::cout << ": ";

        std::string userInput = "";
        std::getline (std::cin, userInput);
        if (!userInput.empty ())
        {
            fileName = userInput;
        }


        if (fileExists (fileName))
        {
            std::cout << "\n";

            return fileName;
        }
        else
        {
            std::cout << "The file \"" << fileName << "\" doesn't seem to exist, try again\n\n";
        }
    }

    return fileName;
}