#ifndef PP_SETTINGS_H
#define PP_SETTINGS_H

const std::string SETTINGS_FILE_NAME = "config/settings.txt";

struct ScreenResolution
{
    int w, h;
    bool fullscreen;
};

struct Settings
{
    ScreenResolution Resolution;
};

Settings LoadSettings();

#endif // PP_SETTINGS_H
