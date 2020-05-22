#include <iostream>
#include <fstream>
#include <sstream>
#include "pp_logger.h"
#include "pp_settings.h"

Settings LoadSettings()
{
    Settings s;

    Log("Loading " + SETTINGS_FILE_NAME, LOG_INFO);

    std::ifstream settingFile(SETTINGS_FILE_NAME);

    std::stringstream buffer;

    buffer << settingFile.rdbuf();

    std::string line;

    while (std::getline(buffer, line))
    {
        int delimIndex = line.find('=');

        std::string name = line.substr(0, delimIndex);
        std::string value = line.substr(delimIndex + 1, line.length() - delimIndex);

        Log(name + " = " + value, LOG_INFO);

        if (name == "width")
        {
            s.Resolution.w = std::stoi(value);
        }
        else if (name == "height")
        {
            s.Resolution.h = std::stoi(value);
        }
        else if (name == "fullscreen")
        {
            s.Resolution.fullscreen = (value == "true");
        }
    }

    return s;
}