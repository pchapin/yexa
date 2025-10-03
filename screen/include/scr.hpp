/*! \file    scr.hpp
 *  \brief   Portable screen/keyboard handling functions.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 *
 * These functions provide the low level screen access used by the rest of the library. They
 * shield the library from differences in operating system platform and provide a uniform
 * interface for several different screen handling paradigms.
 */

#ifndef SCR_HPP
#define SCR_HPP

#include <cstddef>

//! Namespace for scr, the portable screen handling library.
namespace scr {

    //! The box drawing characters.
    /*!
     * These characters are used to draw the various types of borders. The characters are
     * integers so that the values can be represented without truncating signed characters. This
     * may cause problems down the road.
     */
    struct BoxChars {
        int horizontal;   //!< Horizontal line.
        int vertical;     //!< Vertical line.
        int upper_left;   //!< Upper left corner.
        int upper_right;  //!< Upper right corner.
        int lower_left;   //!< Lower left corner.
        int lower_right;  //!< Lower right corner.
        int left_stop;    //!< Vertical line with a horizontal line to the right.
        int right_stop;   //!< Vertical line with a horizontal line to the left.
        int top_stop;     //!< Horizontal line with a vertical line below.
        int bottom_stop;  //!< Horizontal line with a vertical line above.
        int cross;        //!< Intersection of two lines.
    };

    //! These are the permissible box types.
    /*!
     * The order of enumerators in this enumeration matters to the implementation, so don't
     * change it without first reviewing usages. The NO_BORDER enumerator is a special value
     * that is used to represent the absence of a border.
     *
     * \todo Does it really make sense to add NO_BORDER to this enumeration?
     */
    enum BoxType {
        DOUBLE_LINE,      //!< Double line border.
        SINGLE_LINE,      //!< Single line border.
        DARK_GRAPHIC,     //!< Dark "hash" border.
        LIGHT_GRAPHIC,    //!< Light "hash" border.
        SOLID,            //!< Solid border.
        ASCII,            //!< Border made entirely from standard ASCII characters.
        BLANK_BOX,        //!< Border made from spaces.
        NO_BORDER         //!< Special value to represent no border.
    };

    // Detailed documentation for the functions can be found in scr.cpp.

    // Start up and clean up.
    bool initialize( );
    void terminate( );

    // Look up the box drawing characters for a give box type.
    BoxChars *get_box_characters( BoxType the_type );

    // Informational.
    bool is_monochrome( );
    void adjust_dimensions( int &row, int &column, int &width, int &height );
    int  number_of_rows( );
    int  number_of_columns( );

    // Attribute manipulation.
    int convert_attribute( int attribute );
    int reverse_attribute( int attribute );

    // Fast transfer of material to and from screen.
    void read( int row, int column, int width, int height, char *buffer );
    void write( int row, int column, int width, int height, const char *buffer );
    void read_text( int row, int column, int width, int height, char *buffer );
    void write_text( int row, int column, int width, int height, const char *buffer );
    void print( int row, int column, std::size_t count, int attribute, const char *format, ... );
    void print_text( int row, int column, std::size_t count, const char *format, ... );

    // Manipulation of regions.
    void clear( int row, int column, int width, int height, int attribute );
    void set_color( int row, int column, int width, int height, int attribute );
    void clear_screen( );

    //! Used to specify a scroll direction for scr::Scroll.
    enum direction_t { UP, DOWN };

    // Scrolling.
    void scroll( direction_t direction,
                 int row, int column, int width, int height, int number_of_rows, int attribute );

    // Cursor manipulations.
    void set_cursor_position( int  row, int  column );
    void get_cursor_position( int &row, int &column );

    // Screen redraws and updates.
    void refresh( );
    void redraw( );
    void off( );
    void on( );

    // Keyboard handling.
    int  key( );
    void refresh_on_key( bool flag );
    int  key_wait( );

    //==============================
    //          Exceptions
    //==============================

    //! Exception thrown for invalid regions.
    /*!
     * A region is invalid if it overlaps the screen's boundaries or is entirely off the screen.
     * A width *and* height of zero or less is also invalid, although many functions absorb
     * those errors. The members of this structure specified the invalid region used.
     */
    struct BadRegion {
        int row;
        int column;
        int width;
        int height;

        BadRegion( int row, int column, int width, int height )
        {
            this->row    = row;
            this->column = column;
            this->width  = width;
            this->height = height;
        }
    };

    //===============================
    //          Color Codes
    //===============================

    /// @cond NEVER

    // The following constants are used to specify foreground and background colors. The
    // original values are from the IBM PC BIOS and are native to DOS, but these values will
    // work on all platforms supported by Scr.

    const int BLACK       = 0x00;  // No foreground color.
    const int BLUE        = 0x01;  // Primitive foreground color.
    const int GREEN       = 0x02;  // Primitive foreground color.
    const int CYAN        = 0x03;  // GREEN|BLUE
    const int RED         = 0x04;  // Primitive foreground color.
    const int MAGENTA     = 0x05;  // RED|BLUE
    const int BROWN       = 0x06;  // RED|GREEN
    const int WHITE       = 0x07;  // RED|GREEN|BLUE
    const int REV_BLACK   = 0x00;  // No background color.
    const int REV_BLUE    = 0x10;  // Primitive background color.
    const int REV_GREEN   = 0x20;  // Primitive background color.
    const int REV_CYAN    = 0x30;  // REV_GREEN|REV_BLUE
    const int REV_RED     = 0x40;  // Primitive background color.
    const int REV_MAGENTA = 0x50;  // REV_RED|REV_BLUE
    const int REV_BROWN   = 0x60;  // REV_RED|REV_GREEN
    const int REV_WHITE   = 0x70;  // REV_RED|REV_GREEN|REV_BLUE
    const int BRIGHT      = 0x08;  // Effect: Bold.
    const int BLINK       = 0x80;  // Effect: Blink (not always supported).


    //==============================
    //           Key codes
    //==============================

    // The following constants are used to specify keys. The original values are from the IBM PC
    // BIOS and are native to DOS, but these values will work on all platforms supported by Scr.

    //! Extended flag. Special keys have codes > XF.
    const int XF = 0x100;

    // Function keys.
    const int K_F1        = (  59 + XF );
    const int K_F2        = (  60 + XF );
    const int K_F3        = (  61 + XF );
    const int K_F4        = (  62 + XF );
    const int K_F5        = (  63 + XF );
    const int K_F6        = (  64 + XF );
    const int K_F7        = (  65 + XF );
    const int K_F8        = (  66 + XF );
    const int K_F9        = (  67 + XF );
    const int K_F10       = (  68 + XF );
    const int K_F11       = ( 133 + XF );
    const int K_F12       = ( 134 + XF );  // Same code as K_CPGUP. Why??

    // Shift + function keys.
    const int K_SF1       = (  84 + XF );
    const int K_SF2       = (  85 + XF );
    const int K_SF3       = (  86 + XF );
    const int K_SF4       = (  87 + XF );
    const int K_SF5       = (  88 + XF );
    const int K_SF6       = (  89 + XF );
    const int K_SF7       = (  90 + XF );
    const int K_SF8       = (  91 + XF );
    const int K_SF9       = (  92 + XF );
    const int K_SF10      = (  93 + XF );
    const int K_SF11      = ( 135 + XF );
    const int K_SF12      = ( 136 + XF );

    // Ctrl + function keys.
    const int K_CF1       = (  94 + XF );
    const int K_CF2       = (  95 + XF );
    const int K_CF3       = (  96 + XF );
    const int K_CF4       = (  97 + XF );
    const int K_CF5       = (  98 + XF );
    const int K_CF6       = (  99 + XF );
    const int K_CF7       = ( 100 + XF );
    const int K_CF8       = ( 101 + XF );
    const int K_CF9       = ( 102 + XF );
    const int K_CF10      = ( 103 + XF );
    const int K_CF11      = ( 137 + XF );
    const int K_CF12      = ( 138 + XF );

    // Alt + function keys.
    const int K_AF1       = ( 104 + XF );
    const int K_AF2       = ( 105 + XF );
    const int K_AF3       = ( 106 + XF );
    const int K_AF4       = ( 107 + XF );
    const int K_AF5       = ( 108 + XF );
    const int K_AF6       = ( 109 + XF );
    const int K_AF7       = ( 110 + XF );
    const int K_AF8       = ( 111 + XF );
    const int K_AF9       = ( 112 + XF );
    const int K_AF10      = ( 113 + XF );
    const int K_AF11      = ( 139 + XF );
    const int K_AF12      = ( 140 + XF );

    // Miscellaneous special keys.
    const int K_HOME      = (  71 + XF );
    const int K_END       = (  79 + XF );
    const int K_PGUP      = (  73 + XF );
    const int K_PGDN      = (  81 + XF );
    const int K_LEFT      = (  75 + XF );
    const int K_RIGHT     = (  77 + XF );
    const int K_UP        = (  72 + XF );
    const int K_DOWN      = (  80 + XF );
    const int K_INS       = (  82 + XF );
    const int K_DEL       = (  83 + XF );

    // Ctrl + miscellaneous special keys.
    const int K_CHOME     = ( 119 + XF );
    const int K_CEND      = ( 117 + XF );
    const int K_CPGUP     = ( 134 + XF );  // Same code as K_F12. Why??
    const int K_CPGDN     = ( 118 + XF );
    const int K_CLEFT     = ( 115 + XF );
    const int K_CRIGHT    = ( 116 + XF );
    const int K_CUP       = ( 141 + XF );
    const int K_CDOWN     = ( 145 + XF );
    const int K_CINS      = ( 146 + XF );
    const int K_CDEL      = ( 147 + XF );

    // Control characters.
    const int K_CTRLA     = 1;
    const int K_CTRLB     = 2;
    const int K_CTRLC     = 3;
    const int K_CTRLD     = 4;
    const int K_CTRLE     = 5;
    const int K_CTRLF     = 6;
    const int K_CTRLG     = 7;
    const int K_CTRLH     = 8;
    const int K_CTRLI     = 9;
    const int K_CTRLJ     = 10;
    const int K_CTRLK     = 11;
    const int K_CTRLL     = 12;
    const int K_CTRLM     = 13;
    const int K_CTRLN     = 14;
    const int K_CTRLO     = 15;
    const int K_CTRLP     = 16;
    const int K_CTRLQ     = 17;
    const int K_CTRLR     = 18;
    const int K_CTRLS     = 19;
    const int K_CTRLT     = 20;
    const int K_CTRLU     = 21;
    const int K_CTRLV     = 22;
    const int K_CTRLW     = 23;
    const int K_CTRLX     = 24;
    const int K_CTRLY     = 25;
    const int K_CTRLZ     = 26;
    const int K_ESC       = 27;
    const int K_SPACE     = 32;
    const int K_TAB       = K_CTRLI;
    const int K_BACKSPACE = K_CTRLH;
    const int K_RETURN    = K_CTRLM;  // Also CR (carriage return)
    const int K_CRETURN   = K_CTRLJ;  // Also LF (line feed)

    // Alt + letter keys.
    const int K_ALTA      = (  30 + XF );
    const int K_ALTB      = (  48 + XF );
    const int K_ALTC      = (  46 + XF );
    const int K_ALTD      = (  32 + XF );
    const int K_ALTE      = (  18 + XF );
    const int K_ALTF      = (  33 + XF );
    const int K_ALTG      = (  34 + XF );
    const int K_ALTH      = (  35 + XF );
    const int K_ALTI      = (  23 + XF );
    const int K_ALTJ      = (  36 + XF );
    const int K_ALTK      = (  37 + XF );
    const int K_ALTL      = (  38 + XF );
    const int K_ALTM      = (  50 + XF );
    const int K_ALTN      = (  49 + XF );
    const int K_ALTO      = (  24 + XF );
    const int K_ALTP      = (  25 + XF );
    const int K_ALTQ      = (  16 + XF );
    const int K_ALTR      = (  19 + XF );
    const int K_ALTS      = (  31 + XF );
    const int K_ALTT      = (  20 + XF );
    const int K_ALTU      = (  22 + XF );
    const int K_ALTV      = (  47 + XF );
    const int K_ALTW      = (  17 + XF );
    const int K_ALTX      = (  45 + XF );
    const int K_ALTY      = (  21 + XF );
    const int K_ALTZ      = (  44 + XF );

    // Alt + number keys.
    const int K_ALT1      = ( 120 + XF );
    const int K_ALT2      = ( 121 + XF );
    const int K_ALT3      = ( 122 + XF );
    const int K_ALT4      = ( 123 + XF );
    const int K_ALT5      = ( 124 + XF );
    const int K_ALT6      = ( 125 + XF );
    const int K_ALT7      = ( 126 + XF );
    const int K_ALT8      = ( 127 + XF );
    const int K_ALT9      = ( 128 + XF );
    const int K_ALT0      = ( 129 + XF );

    /// @endcond
}

#endif
