
#pragma once

// TEXTS
#define T_BLACK "\x1b[30m"
#define T_RED "\x1b[31m"
#define T_GREEN "\x1b[32m"
#define T_YELLOW "\x1b[33m"
#define T_BLUE "\x1b[34m"
#define T_MAGENTA "\x1b[35m"
#define T_CYAN "\x1b[36m"
#define T_WHITE "\x1b[37m"
#define T_RESET "\x1b[39m"
#define BRIGHT_BLACK "\x1b[90m"
#define BRIGHT_RED "\x1b[91m"
#define BRIGHT_GREEN "\x1b[92m"
#define BRIGHT_YELLOW "\x1b[93m"
#define BRIGHT_BLUE "\x1b[94m"
#define BRIGHT_MAGENTA "\x1b[95m"
#define BRIGHT_CYAN "\x1b[96m"
#define BRIGHT_WHITE "\x1b[97m"

// BACKGROUNDS
#define BG_BLACK "\x1b[40m"
#define BG_RED "\x1b[41m"
#define BG_GREEN "\x1b[42m"
#define BG_YELLOW "\x1b[43m"
#define BG_BLUE "\x1b[44m"
#define BG_MAGENTA "\x1b[45m"
#define BG_CYAN "\x1b[46m"
#define BG_WHITE "\x1b[47m"
#define BG_BRIGHT_BLACK "\x1b[100m"
#define BG_BRIGHT_RED "\x1b[101m"
#define BG_BRIGHT_GREEN "\x1b[102m"
#define BG_BRIGHT_YELLOW "\x1b[103m"
#define BG_BRIGHT_BLUE "\x1b[104m"
#define BG_BRIGHT_MAGENTA "\x1b[105m"
#define BG_BRIGHT_CYAN "\x1b[106m"
#define BG_BRIGHT_WHITE "\x1b[107m"

// SPECIAL
#define T_BOLD "\x1b[01m"
#define T_BOLD_RESET "\x1b[22m"
#define T_FAINT "\x1b[02m"
#define T_FAINT_RESET "\x1b[22m"
#define T_UNDERLINE "\x1b[04m"
#define T_UNDERLINE_RESET "\x1b[24m"
#define T_BLINK "\x1b[05m"
#define T_BLINK_RESET "\x1b[25m"

// RESET COLORS
#define T_BG_RESET "\x1b[00m"
#define T_RESET "\x1b[39m"
#define BG_RESET "\x1b[49m"

#define T_LINK(link, text) "\x1b]8;;" link "\x1b\\" text "\x1b]8;;\x1b\\\n"
