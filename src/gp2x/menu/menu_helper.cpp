#include "sysconfig.h"
#include "sysdeps.h"
#include "config.h"

#include "uae.h"
#include "options.h"
#include "menu.h"
#include "menu_config.h"
#include "sound.h"
#include "disk.h"
#include "memory-uae.h"
#include "custom.h"
#include "xwin.h"
#include "drawing.h"

#if defined(ANDROID)
#include <SDL_screenkeyboard.h>
#include <android/log.h>
#endif

#ifdef __PSP2__
#include "psp2_shader.h"
PSP2Shader *shader = NULL;
#endif

extern int screenWidth;
extern int mainMenu_case;

extern int lastCpuSpeed;
extern int ntsc;

extern char launchDir[300];
extern char currentDir[300];

int saveAdfDir() {
    char path[300];
    snprintf(path, 300, "%s/conf/adfdir.conf", launchDir);
    FILE *f = fopen(path, "w");
    if (!f) return 0;
    char buffer[310];
    snprintf((char *) buffer, 310, "path=%s\n", currentDir);
    fputs(buffer, f);
    fclose(f);
    return 1;
}

void extractFileName(char *str, char *buffer) {
    char *p = str + strlen(str) - 1;
    while (*p != '/')
        p--;
    p++;
    strcpy(buffer, p);
}

#ifdef ANDROIDSDL
void update_onscreen()
{
    SDL_ANDROID_SetScreenKeyboardFloatingJoystick(mainMenu_FloatingJoystick);
    if (mainMenu_case != MAIN_MENU_CASE_DISPLAY && mainMenu_case != MAIN_MENU_CASE_MEMDISK && mainMenu_onScreen==0)
    {
      SDL_ANDROID_SetScreenKeyboardShown(0);
    }
    else
    {
      SDL_ANDROID_SetScreenKeyboardShown(1);
        SDL_Rect pos_textinput, pos_dpad, pos_button1, pos_button2, pos_button3, pos_button4, pos_button5, pos_button6;
        pos_textinput.x = mainMenu_pos_x_textinput*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_textinput.y = mainMenu_pos_y_textinput*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_textinput.h=SDL_ListModes(NULL, 0)[0]->h / (float)10 * mainMenu_button_size;
        pos_textinput.w=pos_textinput.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_TEXT, &pos_textinput);
        pos_dpad.x = mainMenu_pos_x_dpad*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_dpad.y = mainMenu_pos_y_dpad*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_dpad.h=SDL_ListModes(NULL, 0)[0]->h / (float)2.5 * mainMenu_button_size;
        pos_dpad.w=pos_dpad.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_DPAD, &pos_dpad);
        pos_button1.x = mainMenu_pos_x_button1*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_button1.y = mainMenu_pos_y_button1*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_button1.h=SDL_ListModes(NULL, 0)[0]->h / (float)5 * mainMenu_button_size;
        pos_button1.w=pos_button1.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_0, &pos_button1);
        pos_button2.x = mainMenu_pos_x_button2*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_button2.y = mainMenu_pos_y_button2*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_button2.h=SDL_ListModes(NULL, 0)[0]->h / (float)5 * mainMenu_button_size;
        pos_button2.w=pos_button2.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_1, &pos_button2);
        pos_button3.x = mainMenu_pos_x_button3*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_button3.y = mainMenu_pos_y_button3*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_button3.h=SDL_ListModes(NULL, 0)[0]->h / (float)5 * mainMenu_button_size;
        pos_button3.w=pos_button3.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_2, &pos_button3);
        pos_button4.x = mainMenu_pos_x_button4*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_button4.y = mainMenu_pos_y_button4*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_button4.h=SDL_ListModes(NULL, 0)[0]->h / (float)5 * mainMenu_button_size;
        pos_button4.w=pos_button4.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_3, &pos_button4);
        pos_button5.x = mainMenu_pos_x_button5*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_button5.y = mainMenu_pos_y_button5*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_button5.h=SDL_ListModes(NULL, 0)[0]->h / (float)5 * mainMenu_button_size;
        pos_button5.w=pos_button5.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_4, &pos_button5);
        pos_button6.x = mainMenu_pos_x_button6*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_button6.y = mainMenu_pos_y_button6*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_button6.h=SDL_ListModes(NULL, 0)[0]->h / (float)5 * mainMenu_button_size;
        pos_button6.w=pos_button6.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_5, &pos_button6);

        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_TEXT, mainMenu_onScreen_textinput);
        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_DPAD, mainMenu_onScreen_dpad);
        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_0, mainMenu_onScreen_button1);
        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_1, mainMenu_onScreen_button2);
        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_2, mainMenu_onScreen_button3);
        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_3, mainMenu_onScreen_button4);
        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_4, mainMenu_onScreen_button5);
        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_5, mainMenu_onScreen_button6);
    }
}
#endif

void update_display() {
    char layersize[20];
    snprintf(layersize, 20, "%dx480", screenWidth);

#ifndef WIN32
#ifndef __PSP2__
    setenv("SDL_OMAP_LAYER_SIZE",layersize,1);
#endif
#endif

    char bordercut[20];
    snprintf(bordercut, 20, "%d,%d,0,0", mainMenu_cutLeft, mainMenu_cutRight);

#ifndef WIN32
#ifndef __PSP2__
    setenv("SDL_OMAP_BORDER_CUT",bordercut,1);
#endif
#endif

#ifdef ANDROIDSDL
    update_onscreen();
#endif

#ifdef __PSP2__
    if (prSDLScreen != NULL) {
        black_screen_now();
        SDL_FreeSurface(prSDLScreen);
    }
    prSDLScreen = SDL_SetVideoMode(visibleAreaWidth, mainMenu_displayedLines, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
    printf("update_display: SDL_SetVideoMode(%i, %i, 16)\n", visibleAreaWidth, mainMenu_displayedLines);
    //the commented out scaling fills the screen better
    //but looks horrible, due to the current lack of a good shader sharp bilinear scaler
    //so stick with simple 2* point filtering for now.
    //	float sh = 544;
    float sh = (float) (2 * mainMenu_displayedLines);
    // float sw = ((float)visibleAreaWidth*((float)544/(float)mainMenu_displayedLines));
    float sw = (float) (2 * visibleAreaWidth);
    int x = (960 - sw) / 2;
    int y = (544 - sh) / 2;
    SDL_SetVideoModeScaling(x, y, sw, sh);
    printf("update_display: SDL_SetVideoModeScaling(%i, %i, %i, %i)\n", x, y, (int)sw, (int)sh);
    SDL_SetVideoModeSync(0);

    /* disabled until we add a config option for this
    // set vita2d shader
    if(shader != NULL) {
        delete(shader);
    }
    shader = new PSP2Shader(PSP2Shader::Shader::SHARP_BILINEAR);
    */
#else
#if defined(PANDORA) && !(defined(WIN32) || defined(AROS))
    prSDLScreen = SDL_SetVideoMode(visibleAreaWidth, mainMenu_displayedLines, 16, SDL_SWSURFACE|SDL_FULLSCREEN|SDL_DOUBLEBUF);
#elif defined(PANDORA) && (defined(WIN32) || defined(AROS))
    prSDLScreen = SDL_SetVideoMode(visibleAreaWidth, mainMenu_displayedLines, 16, SDL_SWSURFACE|SDL_DOUBLEBUF);
#else
    prSDLScreen = SDL_SetVideoMode(visibleAreaWidth, mainMenu_displayedLines, 16, SDL_SWSURFACE|SDL_FULLSCREEN);
#endif
#endif
    SDL_ShowCursor(SDL_DISABLE);

    if (mainMenu_displayHires)
        InitDisplayArea(visibleAreaWidth >> 1);
    else
        InitDisplayArea(visibleAreaWidth);
}


static bool cpuSpeedChanged = false;

void setCpuSpeed() {
#ifndef __PSP2__
    char speedCmd[128];

    if(mainMenu_cpuSpeed != lastCpuSpeed)
    {
        snprintf((char*)speedCmd, 128, "unset DISPLAY; echo y | sudo -n /usr/pandora/scripts/op_cpuspeed.sh %d", mainMenu_cpuSpeed);
        system(speedCmd);
        lastCpuSpeed = mainMenu_cpuSpeed;
        cpuSpeedChanged = true;
    }
    if(mainMenu_ntsc != ntsc)
    {
        ntsc = mainMenu_ntsc;
        if(ntsc)
            system("sudo /usr/pandora/scripts/op_lcdrate.sh 60");
        else
            system("sudo /usr/pandora/scripts/op_lcdrate.sh 50");
    }
    update_display();
#endif
}


#ifdef PANDORA

void resetCpuSpeed(void) {
    if (cpuSpeedChanged) {
        FILE *f = fopen("/etc/pandora/conf/cpu.conf", "rt");
        if (f) {
            char line[128];
            for (int i = 0; i < 6; ++i) {
                fscanf(f, "%s\n", &line);
                if (strncmp(line, "default:", 8) == 0) {
                    int value = 0;
                    sscanf(line, "default:%d", &value);
                    if (value > 500 && value < 1200) {
                        lastCpuSpeed = value - 10;
                        mainMenu_cpuSpeed = value;
                        setCpuSpeed();
                        printf("CPU speed reset to %d\n", value);
                    }
                }
            }
            fclose(f);
        }
    }
}

#endif
