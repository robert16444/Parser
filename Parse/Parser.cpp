#include "Parser.h"

void searchInFile (std::string const& fileName, FileMap & fileMap)
{
    std::vector<std::string> vectorWithFiles;
    std::string currentFile;

    boost::char_separator<char> lineSeparator("\"");
    boost::char_separator<char> fileNameSeparator("\\");

    boost::tokenizer<boost::char_separator<char>> tokens(fileName, fileNameSeparator);

    std::string line;
    std::ifstream file;
    file.open(fileName);
    if(!file.is_open())
    {
        perror("Error open");
        exit(EXIT_FAILURE);
    }

    for (auto const & token : tokens)
    {
        currentFile = token;
    }

    while(std::getline(file, line))
    {
        if(line.find("include") != std::string::npos)
        {
            tokenizer tokens(line, lineSeparator);

            for (tokenizer::iterator token_it = tokens.begin(); token_it != tokens.end(); ++token_it)
            {
                if (distance(tokens.begin(), token_it) == 1)
                {
                    vectorWithFiles.emplace_back(*token_it);
                }
            }
        }
    }

    if(currentFile == "Parser.cpp")
        vectorWithFiles.pop_back();

    fileMap.insert(std::pair<std::string, std::vector<std::string>>(currentFile,vectorWithFiles));
}

FileMap parse(std::vector<std::string> listOfFiles)
{

    FileMap fileMap;

    for(auto const& it: listOfFiles)
    {
        searchInFile(it, fileMap);
    }

    //////// If you want to print all map just uncomment below code ////////
    /*for(auto it = fileMap.cbegin(); it != fileMap.cend(); ++it)
    {
        std::cout <<"Nazwa pliku: " << it->first << std::endl;
        std::cout << "Jego powiazania: ";
        for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            std::cout << *it2 << " ";

        std::cout << std::endl;
    }*/

    return fileMap;
}