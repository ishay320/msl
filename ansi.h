// this is WIP, anything can be changed, added or removed, and the API is not stable yet, so use with caution
// FIXME:
// 1.
// int r = 255, g = 128, b = 0;
// printf("%s", AN_RGB(r, g, b)); // BUG: prints literal "r;g;b"
// 2. name consistency
// 3. for the movement macros i can use functions instead, since they not needed to be inside printf

/* core */
#define AN_ESC "\033"
// Set graphics modes for cell, separated by semicolon (;).
#define AN_SGR(param) AN_ESC "[" #param "m"
// reset all modes (styles and colors)
#define AN_RESET AN_ESC "[0m"

/* movement */
// moves cursor to home position (0, 0)
#define AN_MOVE_HOME AN_ESC "[H"
// moves cursor to line #, column #
#define AN_MOVE(line, column) AN_ESC "[" #line ";" #column "H"
// TODO: check this
#define AN_MOVE_REL(line, column) AN_ESC "[" #line ";" #column "f"
// moves cursor up # lines
#define AN_MOVE_UP(lines) AN_ESC "[" #lines "A"
// moves cursor down # lines
#define AN_MOVE_DOWN(lines) AN_ESC "[" #lines "B"
// moves cursor right # columns
#define AN_MOVE_RIGHT(columns) AN_ESC "[" #columns "C"
// moves cursor left # columns
#define AN_MOVE_LEFT(columns) AN_ESC "[" #columns "D"
// moves cursor to beginning of next line, # lines down
#define AN_MOVE_DOWN_START(lines) AN_ESC "[" #lines "E"
// moves cursor to beginning of previous line, # lines up
#define AN_MOVE_UP_START(lines) AN_ESC "[" #lines "F"
// moves cursor to column #
#define AN_MOVE_COLUMN(column) AN_ESC "[" #column "G"
// moves cursor one line up, scrolling if needed
#define AN_MOVE_UP_SCROLL AN_ESC "M"
// save cursor position(SCO)
#define AN_MOVE_POS_SAVE AN_ESC "[s"
// restores the cursor to the last saved position(SCO)
#define AN_MOVE_POS_RESTORE AN_ESC "[u"
// TODO: check this out
// request cursor position (reports as AN_ESC[#;#R)
#define AN_MOVE_REQ_POS AN_ESC "[6n"

/* erase */
// erase from cursor to end of screen (same as ESC[0J)
#define AN_ERASE_SCREEN_TO_END AN_ESC "[J"
// erase from cursor to beginning of screen
#define AN_ERASE_SCREEN_TO_START AN_ESC "[1J"
// erase entire screen
#define AN_ERASE_SCREEN AN_ESC "[2J"
// erase saved lines
#define AN_ERASE_SAVED_LINES AN_ESC "[3J"
// erase from cursor to end of line (same as ESC[0K)
#define AN_ERASE_LINE_TO_END AN_ESC "[K"
// erase start of line to the cursor
#define AN_ERASE_LINE_TO_START AN_ESC "[1K"
// erase the entire line
#define AN_ERASE_LINE AN_ESC "[2K"

/* colors */
// you can add attributes at the begining
#define AN_SGR_MULTI(...) AN_ESC "[" #__VA_ARGS__ "m"
// set bold mode.
#define AN_BOLD AN_ESC "[1m"
// reset
#define AN_BOLD_RES AN_ESC "[22m"
// set dim/faint mode.
#define AN_DIM AN_ESC "[2m"
// reset
#define AN_DIM_RES AN_ESC "[22m"
// set italic mode.
#define AN_ITALIC AN_ESC "[3m"
// reset
#define AN_ITALIC_RES AN_ESC "[23m"
// set underline mode.
#define AN_UNDERLINE AN_ESC "[4m"
// reset
#define AN_UNDERLINE_RES AN_ESC "[24m"
// set blinking mode
#define AN_BLINK AN_ESC "[5m"
// reset
#define AN_BLINK_RES AN_ESC "[25m"
// set inverse/reverse mode
#define AN_INVERSE AN_ESC "[7m"
// reset
#define AN_INVERSE_RES AN_ESC "[27m"
// set hidden/invisible mode
#define AN_HIDDEN AN_ESC "[8m"
// reset
#define AN_HIDDEN_RES AN_ESC "[28m"
// set strikethrough mode.
#define AN_STRIKETHROUGH AN_ESC "[9m"
// reset
#define AN_STRIKETHROUGH_RES AN_ESC "[29m"

/* 8-16 colors */
#define AN_BLACK AN_SGR(30)
#define AN_BLACK_BG AN_SGR(40)
#define AN_RED AN_SGR(31)
#define AN_RED_BG AN_SGR(41)
#define AN_GREEN AN_SGR(32)
#define AN_GREEN_BG AN_SGR(42)
#define AN_YELLOW AN_SGR(33)
#define AN_YELLOW_BG AN_SGR(43)
#define AN_BLUE AN_SGR(34)
#define AN_BLUE_BG AN_SGR(44)
#define AN_MAGENTA AN_SGR(35)
#define AN_MAGENTA_BG AN_SGR(45)
#define AN_CYAN AN_SGR(36)
#define AN_CYAN_BG AN_SGR(46)
#define AN_WHITE AN_SGR(37)
#define AN_WHITE_BG AN_SGR(47)
#define AN_DEFAULT AN_SGR(39)
#define AN_DEFAULT_BG AN_SGR(49)

#define AN_BLACK_BRIGHT AN_SGR(90)
#define AN_BLACK_BRIGHT_BG AN_SGR(100)
#define AN_RED_BRIGHT AN_SGR(91)
#define AN_RED_BRIGHT_BG AN_SGR(101)
#define AN_GREEN_BRIGHT AN_SGR(92)
#define AN_GREEN_BRIGHT_BG AN_SGR(102)
#define AN_YELLOW_BRIGHT AN_SGR(93)
#define AN_YELLOW_BRIGHT_BG AN_SGR(103)
#define AN_BLUE_BRIGHT AN_SGR(94)
#define AN_BLUE_BRIGHT_BG AN_SGR(104)
#define AN_MAGENTA_BRIGHT AN_SGR(95)
#define AN_MAGENTA_BRIGHT_BG AN_SGR(105)
#define AN_CYAN_BRIGHT AN_SGR(96)
#define AN_CYAN_BRIGHT_BG AN_SGR(106)
#define AN_WHITE_BRIGHT AN_SGR(97)
#define AN_WHITE_BRIGHT_BG AN_SGR(107)

/* 256 colors
0-7: standard colors (as in ESC [ 30-37 m)
8-15: high intensity colors (as in ESC [ 90-97 m)
16-231: 6 x 6 x 6 cube (216 colors): 16 + 36 x r + 6 x g + b (0 <= r, g, b <= 5)
    Some emulators interpret these steps as linear increments (256 / 24) on all three channels while others may explicitly define these values.
232-255: grayscale from dark to light in 24 steps.
*/
#define AN_FG_256(id) AN_ESC "[38;5;" #id "m"
#define AN_BG_256(id) AN_ESC "[48;5;" #id "m"

/* RGB colors - truecolors */
// Set foreground color as RGB
#define AN_RGB(r, g, b) AN_ESC "[38;2;" #r ";" #g ";" #b "m"
// Set background color as RGB
#define AN_RGB_BG(r, g, b) AN_ESC "[48;2;" #r ";" #g ";" #b "m"

/* private modes */
// make cursor invisible
#define AN_CURSOR_INV AN_ESC "[?25l"
// make cursor visible
#define AN_CURSOR_VIS AN_ESC "[?25h"
// restore screen
#define AN_SCREEN_RESTORE AN_ESC "[?47l"
// save screen
#define AN_SCREEN_SAVE AN_ESC "[?47h"
// enables the alternative buffer
#define AN_BUFFER_ALT AN_ESC "[?1049h"
// disables the alternative buffer
#define AN_BUFFER_ALT_DISABLE AN_ESC "[?1049l"