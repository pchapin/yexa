/*! \file    overview.hpp
 *  \brief   Overview documentation of the scr library.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

/*!
 * \mainpage
 *
 * \section Introduction
 * 
 * This library contains a number of screen and keyboard handling functions at both a low and
 * high level. The functions are suitable for dealing with a *text mode* screen where the
 * screen is divided into fixed sized character positions. This is not a graphics package.
 * Functions are provided for both reading the screen as well as writing to the screen.
 * Functions are provided for dealing with strings as well as blocks of text. Functions are
 * provided to move the cursor. Finally, functions are provided to get keystrokes from the user.
 *
 * One of Scr's main features is support for various operating systems and screen handling
 * techniques. At the time of this writing Scr supports DOS, OS/2, Win32, and Unix/Posix systems
 * (Linux, macOS) using curses. Programs that use Scr will display correctly on the text
 * displays of all these environments. Furthermore, keyboard input will be handled in a uniform
 * manner. Scr was originally created under DOS where it did direct video access. The design of
 * Scr reflects this heritage. See "future directions" below for more information.
 *
 * Scr's model of the screen is one of delayed action. All functions that output to the screen
 * only update Scr's internal representation of the screen. You must call the function
 * `scr::refresh` to actually synchronize the real screen with Scr's internal representation.
 * However in some cases `scr::refresh` is called automatically.
 *
 * Scr makes no static assumption about the size of the screen. You must call the functions
 * `scr::number_of_rows` and `scr::number_of_columns` at runtime to learn about the screen's
 * dimensions. If the application requires screens of a certain minimum size, the application
 * should exit with an error message if the actual size is inappropriate. The current version of
 * *Scr does assume that the screen size will not change during the lifetime of the program*.
 * This is not true on some platforms. A future version of Scr may address this issue.
 *
 * \section Compiling
 * 
 * Scr is written in C++98 and intended to be compilable using the Open Watcom compiler. Since
 * Open Watcom supports several legacy platforms such as DOS and OS/2, it is the intention that
 * Scr also support those platforms.
 *
 * Scr uses several macros to control its compilation. These are in addition to the symbols
 * defined in environ.hpp (see environ.hpp for more information). The symbols used specifically
 * by Scr are as follows.
 *
 * + SCR_ANSI and SCR_DIRECT
 *
 *   These symbols define which screen handling method Scr will use. If SCR_ANSI is defined, Scr
 *   will use ANSI escape sequences to position the cursor and select colors. This tends to be
 *   highly portable and is a good choice if you are attempting to get Scr to work on a platform
 *   which is not specifically supported It can also be a good choice for low-speed serial
 *   connections to a single board computer. Scr will try to move the cursor somewhat optimally
 *   when you specify SCR_ANSI so screen updates are reasonably fast despite the overhead.
 *
 *   If SCR_DIRECT is defined, Scr will use "direct" video access in a way that makes sense for
 *   the platform you are using. In the original MS-DOS implementation of Scr, direct video
 *   access was exactly that. However, on the currently supported platforms direct video
 *   access involves going through some appropriate console API. Nevertheless this is often
 *   faster than using the SCR_ANSI approach.
 *
 *   You must specify either SCR_ANSI or SCR_DIRECT when you compile Scr on a non-Unix-like
 *   system. There is no default, except that on Unix-like systems curses is automatically used.
 *
 * + SCR_ASCIIBOXES
 *
 *   When SCR_ASCIIBOXES is defined, Scr will only use ASCII characters for box drawing
 *   characters. This will be true even if the host environment supports box drawing characters
 *   normally. Scr will still honor requests to use fancy boxes, but it will translate all such
 *   requests into plain ASCII character boxes.
 *
 * + SCR_ASCIIKEYS
 *
 *   When SCR_ASCIIKEYS is defined, Scr will simulate the special keys (function keys, alt keys,
 *   arrow keys, etc) using control characters. Note that the POSIX version of Scr normally
 *   supports this simulation in addition to honoring whatever special characters the current
 *   terminal can supply. Since not all terminals can supply all special characters, the
 *   SCR_ASCIIKEYS option is always active when the environment is POSIX. However, if you
 *   explicit define SCR_ASCIIKEYS, then *only* the simulated keys are active.
 *
 * \section Defining Screen Regions
 *
 * The upper left corner of the screen is row 1, column 1. The maximum supported row and column
 * numbers are determined by Scr when you call `scr::initialize`. You must use the functions
 * `scr::number_of_rows` and `scr::number_of_columns` at runtime to learn these values. A screen
 * region is defined by specifying the row and column of the upper left corner of the region
 * followed by the size of the region. The size is always given as the width in columns followed
 * by the height in rows.
 *
 * The functions are guaranteed to work only for regions sized between 1x1 and the entire
 * screen. Do not attempt to use them on a zero sized region. Do not specify dimensions that
 * overlap any of the screen's edges or that have negative sizes. Scr *may* provide checks
 * against some of these errors, but it is better if your program avoids them.
 *
 * \subsection Defining Screen Attributes
 *
 * A screen attribute is an 8-bit quantity specified by ORing together the following symbols.
 *
 * 
 *     WHITE           REV_WHITE
 *     BLACK           REV_BLACK
 *     RED             REV_RED
 *     GREEN           REV_GREEN
 *     BLUE            REV_BLUE
 *     CYAN            REV_CYAN
 *     MAGENTA         REV_MAGENTA
 *     BROWN           REV_BROWN
 *
 *     BLINK
 *     BRIGHT
 *
 * Foreground colors are specified using the first column, and background colors are specified
 * using the second column. Black is the default color. Thus you can specify only a foreground
 * color if you want the background to be black (or vice-versa).
 *
 * The 8 bits of the attribute are composed of 3 bits for the foreground color, 3 bits for the
 * background color, and 1 bit each for the blink and the bright attribute. Each color is really
 * just a combination of the 3 primitive colors red, green, and blue. Each primitive color has
 * one bit associated with it. A color (or blink or bright) is activated when it's bit is on.
 * For example, MAGENTA is really just RED | BLUE. Similarly WHITE is just RED | GREEN | BLUE.
 *
 * Although attribute parameters are generally declared as int, only the lower 8 bits of the int
 * (the unsigned char part) is used. Note that when the attributes are stored in the arrays used
 * by `scr::read` and `scr::write`, they are stored as plain char.
 *
 * Some platforms do not support color. In that case the function `scr::is_monochrome` returns
 * true. You can test for that case in your application and adjust the colors accordingly. The
 * function `scr::convert_attribute` is provided to facilitate converting color attributes from
 * general colors to colors suitable for a monochrome display.
 * 
 * \section Screen Access Levels
 * 
 * Scr provides three levels of screen access. Although it is possible to use the features of a
 * lower level on top of a higher level, this should be done with care. The levels are
 * independent of each other and do not know about each other (except that the implementation of
 * the higher levels is done in terms of the lower levels). Applications should decide which
 * level is to be used and employ lower level functionality only in specialized, focused
 * situations.
 * 
 * Note that Scr takes control of the keyboard as well as the screen and manages all input and
 * output. Once any of the levels is initialized, no further use of the standard console I/O
 * functions is possible. However, Scr does provide a way for applications to temporarily
 * suspend Scr so that the standard console I/O functions can be used again. See `scr::off` and
 * `scr::on` for more information. The intent of this facility is to allow Scr-based
 * applications a way of "shelling out" to other programs that might not be Scr-aware.
 * 
 * + Level 1: Direct Screen Access
 * 
 *   Level one uses the functions that are directly contained in the `scr`  or `scr::ansi`
 *   namespaces. These functions provide direct access to arbitrary screen regions but provide
 *   no additional services such as boundary checking, automatic scrolling, etc. Using these
 *   functions it is possible to write text anywhere on the screen with no consideration of what
 *   might already be there.
 * 
 * + Level 2: Simple Window
 * 
 *   Level two uses the class hierarchy rooted at `scr::SimpleWindow`. Simple Windows do provide
 *   boundaries, borders, and (in some cases) scrolling support. Simple Windows also manage
 *   their background, restoring the material that was behind a window automatically when a
 *   Simple Window is closed. However, Simple Windows do not give the user any direct control
 *   over their size and placement. They layout of Simple Windows is determined by the
 *   application's logic.
 * 
 * + Level 3: Window Manager
 * 
 *   Level three uses the class hierarchy rooted at `scr::Window`. These windows are all
 *   coordinated via a `scr::Manager` object. Users can communicate with the Manager to control
 *   the size and placement of an application's windows independently of the application's
 *   logic. However, at this time there is no mouse support; all interaction with the Manager is
 *   done using key commands in a special input mode called *system mode*.
 * 
 * \section Future Directions
 * 
 * Scr is a work in progress. The following is a list of possible future enhancements.
 * 
 * + Support for more modern key bindings
 * 
 *   Scr currently supports only the traditional IBM PC key bindings. This reflects Scr's
 *   heritage as a DOS application library. Such applications traditionally made very heavy use
 *   of function keys as a way of giving users convenient access to application functionality.
 *   Unfortunately, many modern systems use the functions keys for communication with the
 *   desktop or overarching window manager. This makes it difficult for Scr-based applications
 *   to use the function keys in a portable way.
 * 
 *   The point of the SCR_ASCIIKEYS option is to allow Scr-based applications to simulate the
 *   old-style function keys without redefining the meaning of the physical function keys. While
 *   this can work, it leads to an awkward UI experience for users of Scr applications. However,
 *   to continue supporting DOS and non-GUI installations of other systems (such as Linux),
 *   completely dropping support for native function keys seems undesirable. One possible
 *   solution would be to provide an ability to create virtual, on-screen function keys that Scr
 *   applications could present to the user in some convenient way. The details still need to be
 *   envisioned.
 * 
 * + Support for screen size changes
 * 
 *   Scr currently assumes that the screen size will not change during the lifetime of the
 *   program. This is not true on some platforms. For example, on Unix-like systems it is
 *   commonly possible to dynamically resize the window of a terminal emulator. Scr should be
 *   able to handle this situation.
 * 
 *   Unfortunately, this will require a major redesign of Scr's internal data structures. It
 *   will also require redesigning applications that make use of Scr to deal with unexpected
 *   changes to the screen size. This would be a non-trivial task.
 * 
 * + Support for mouse input
 * 
 *   It would be convenient for Level 3 users to have mouse support for moving and resizing
 *   windows. This would require accessing mouse location information inside a text-mode
 *   console. It is not clear how to do this in a portable way.
 * 
 * + Support for a full GUI
 * 
 *   It would be nice for applications written to the Scr interface to be compilable as native
 *   GUI applications on the platforms that support GUIs. It should be noted, however, that Scr
 *   does assume that a fixed-width font is being used, which might appear unnatural in many GUI
 *   environments.
 * 
 *   Note that support for a full GUI will require the same sort of internal redesign effort as
 *   required to handle screen size changes *and* mouse support. This would be a major
 *   undertaking.
 */
