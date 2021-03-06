/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "Defines.h"



const int SCREEN_WIDTH				= 800;
const int SCREEN_HEIGHT				= 600;


extern const int DIR_UP				= 0;
extern const int DIR_RIGHT			= 1;
extern const int DIR_DOWN			= 2;
extern const int DIR_LEFT			= 3;
extern const int DIR_UP_RIGHT		= 4;
extern const int DIR_DOWN_RIGHT		= 5;
extern const int DIR_DOWN_LEFT		= 6;
extern const int DIR_UP_LEFT		= 7;


const short NPC_SPEED				= 1;


const char* DIR_RES_IMAGES			= "../res/images/";
const char* DIR_RES_MUSIC			= "../res/music/";
const char* DIR_RES					= "../res/";
const char* DIR_FONTS				= "../res/fonts/";
const char* DIR_SCRIPTS				= "../res/scripts/";



int stringToInt(const char* a) {
    int c = 0, sign = 0, offset = 0, n = 0;
    if (a[0] == '-') {
        sign = -1;
    }
    if (sign == -1) {
        offset = 1;
    } else {
        offset = 0;
    }
    n = 0;
    for (c = offset; a[c] != '\0'; c++) {
        n = n * 10 + a[c] - '0';
    }
    if (sign == -1) {
        n = -n;
    }
    return n;
}

DG_ArrayInt* stringToArrayOfInt(std::string s) {
    int str_length = s.length();
    int* arr { new int[str_length + 1] { 0 } };
    int i = 0, j = 0;
    while (s[i] != '\0') {
        if ((s[i] != 13 && s[i] != 32 && s[i] != 10)) {
            if (s[i] == ',') {
                j++;
            }
            else {
                arr[j] = arr[j] * 10 + (s[i] - 48);
            }
        }
        i++;
    }
    j++;
    arr[j] = arr[j] * 10 + (s[i] - 48);
    DG_ArrayInt* array = new DG_ArrayInt();
    array->size = j;
    array->arr = arr;
    return array;
}

std::string charArrayToString(char* a) {
    std::string str = "";
    int c = 0;
    while (a[c] != '\0') {
        str = str + a[c];
        c++;
    }
    return str;
}
