/* 
 * File:   display.h
 * Author: dave Plater
 * Copyright: Dave Plater 2020
 *
 * Created on February 24, 2020, 12:15 PM
 * Use ST7565R on EA DOG L128-6 GRAPHIC display
 * via spi no feedback from this display.
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#include "mcc_generated_files/mcc.h"
//#include "gsm.h"
#include <string.h>
#include <stddef.h>



// +---------------------------+
// |      Set MUX Ratio        |
// +---------------------------+
// |        0xA8, 0x3F         |
// +---------------------------+
//              |
// +---------------------------+
// |    Set Display Offset     |
// +---------------------------+
// |        0xD3, 0x00         |
// +---------------------------+
//              |
// +---------------------------+
// |  Set Display Start Line   |
// +---------------------------+
// |          0x40             |
// +---------------------------+
//              |
// +---------------------------+
// |     Set Segment Remap     |
// +---------------------------+
// |       0xA0 / 0xA1         |
// +---------------------------+
//              |
// +---------------------------+
// |   Set COM Output Scan     |
// |        Direction          |
// +---------------------------+
// |       0xC0 / 0xC8         |
// +---------------------------+
//              |
// +---------------------------+
// |   Set COM Pins hardware   |
// |       configuration       |
// +---------------------------+
// |        0xDA, 0x02         |
// +---------------------------+
//              |
// +---------------------------+
// |   Set Contrast Control    |
// +---------------------------+
// |        0x81, 0x7F         |
// +---------------------------+
//              |
// +---------------------------+
// | Disable Entire Display On |
// +---------------------------+
// |          0xA4             |
// +---------------------------+
//              |
// +---------------------------+
// |    Set Normal Display     |
// +---------------------------+
// |          0xA6             |
// +---------------------------+
//              |
// +---------------------------+
// |    Set Osc Frequency      |
// +---------------------------+
// |       0xD5, 0x80          |
// +---------------------------+
//              |
// +---------------------------+
// |    Enable charge pump     |
// |        regulator          |
// +---------------------------+
// |       0x8D, 0x14          |
// +---------------------------+
//              |
// +---------------------------+
// |        Display On         |
// +---------------------------+
// |          0xAF             |
// +---------------------------+
  // Command definition
  // -----------------------------------

#define COMMAND 0x00
#define DATA    0x40

#define SSD1306_WRITECOMMAND(command)      i2c_writeByte(SSD1306_I2C_ADDR, 0x00, (command))
/* Write data */
#define SSD1306_WRITEDATA(data)            i2c_writeByte(SSD1306_I2C_ADDR, 0x40, (data))
/* Absolute value */
#define ABS(x)   ((x) > 0 ? (x) : -(x))

// Success
  // -------------------------------------------
  #define SSD1306_SUCCESS           0

  // Error
  // -------------------------------------------
  #define SSD1306_ERROR             1

  // Address definition
  // -----------------------------------
  #define SSD1306_ADDRESS           0x3C

  // Command definition
  // -----------------------------------
  #define SSD1306_COMMAND           0x80  // Continuation bit=1, D/C=0; 1000 0000
  #define SSD1306_COMMAND_STREAM    0x00  // Continuation bit=0, D/C=0; 0000 0000
  #define SSD1306_DATA              0xC0  // Continuation bit=1, D/C=1; 1100 0000
  #define SSD1306_DATA_STREAM       0x40  // Continuation bit=0, D/C=1; 0100 0000

  #define SSD1306_SET_MUX_RATIO     0xA8
  #define SSD1306_DISPLAY_OFFSET    0xD3
  #define SSD1306_DISPLAY_ON        0xAF
  #define SSD1306_DISPLAY_OFF       0xAE
  #define SSD1306_DIS_ENT_DISP_ON   0xA4
  #define SSD1306_DIS_IGNORE_RAM    0xA5
  #define SSD1306_DIS_NORMAL        0xA6
  #define SSD1306_DIS_INVERSE       0xA7
  #define SSD1306_DEACT_SCROLL      0x2E
  #define SSD1306_ACTIVE_SCROLL     0x2F
  #define SSD1306_SET_START_LINE    0x40
  #define SSD1306_MEMORY_ADDR_MODE  0x20
  #define SSD1306_SET_COLUMN_ADDR   0x21
  #define SSD1306_SET_PAGE_ADDR     0x22
  #define SSD1306_SEG_REMAP         0xA0
  #define SSD1306_SEG_REMAP_OP      0xA1
  #define SSD1306_COM_SCAN_DIR      0xC0
  #define SSD1306_COM_SCAN_DIR_OP   0xC8
  #define SSD1306_COM_PIN_CONF      0xDA
  #define SSD1306_SET_CONTRAST      0x81
  #define SSD1306_SET_OSC_FREQ      0xD5
  #define SSD1306_SET_CHAR_REG      0x8D
  #define SSD1306_SET_PRECHARGE     0xD9
  #define SSD1306_VCOM_DESELECT     0xDB

  // Clear Color
  // -----------------------------------
  #define CLEAR_COLOR               0x00

  // Init Status
  // -----------------------------------
  #define INIT_STATUS               0xFF

  // AREA definition
  // -----------------------------------
  #define START_PAGE_ADDR           0
  #define END_PAGE_ADDR             7
  #define START_COLUMN_ADDR         0
  #define END_COLUMN_ADDR           127

  #define CACHE_SIZE_MEM            (1 + END_PAGE_ADDR) * (1 + END_COLUMN_ADDR)

  #define MAX_X                     END_COLUMN_ADDR
  #define MAX_Y                     (END_PAGE_ADDR+1)*8




  // 0xAE = Set Display OFF 1
 static const uint8_t disp_off[] = {1,SSD1306_DISPLAY_OFF};
  // 0xA8 2
 static const uint8_t set_mux[] = {2, SSD1306_SET_MUX_RATIO, 0x3F};
  // 0x20 = Set Memory Addressing Mode 3
  // -----------------------------------
  // 0x00 - Horizontal Addressing Mode
  // 0x01 - Vertical Addressing Mode
  // 0x02 - Page Addressing Mode (RESET) 4
  static const uint8_t  mem_addr_mode[] = {2, SSD1306_MEMORY_ADDR_MODE, 0x00};
  // 0x21 = Set Column Address 5
  // -----------------------------------
  // 0x00 - Start Column Address
  // 0xFF - End Column Address
  static const uint8_t set_col_add[] = {3, SSD1306_SET_COLUMN_ADDR, START_COLUMN_ADDR, END_COLUMN_ADDR};
  // 0x22 = Set Page Address 6
  // -----------------------------------
  // 0x00 - Start Column Address 7
  // 0x07 - End Column Address
  static const uint8_t set_page_add[] = {3, SSD1306_SET_PAGE_ADDR, START_PAGE_ADDR, END_PAGE_ADDR};
  // 0x40 8
  static const uint8_t set_start_line[] = {1, SSD1306_SET_START_LINE};
  // 0xD3 9
  static const uint8_t dsp_offset[] = {2, SSD1306_DISPLAY_OFFSET, 0x00};
  // 0xA0 / remap 0xA1 10
  static const uint8_t seg_remap[] = {1, SSD1306_SEG_REMAP_OP};
  // 0xC0 / remap 0xC8 11
  static const uint8_t com_scan_dir[] = {1, SSD1306_COM_SCAN_DIR_OP};
  // 0xDA 12
  static const uint8_t com_pin_conf[] = {2, SSD1306_COM_PIN_CONF, 0x12};
  // 0x81 13
  static const uint8_t set_contrast[] = {2, SSD1306_SET_CONTRAST, 0x7F};
  // 0xA4 14
  static const uint8_t set_ent_dsp_on[] = {1, SSD1306_DIS_ENT_DISP_ON};
  // 0xA6 15
  static const uint8_t dsp_normal[] = {1, SSD1306_DIS_NORMAL};
  // 0xD5 16
  static const uint8_t set_osc_freq[] = {2, SSD1306_SET_OSC_FREQ, 0x80};
  // 0xD9, 1st Period = higher value less blinking 17
  static const uint8_t set_precharge[] = {2, SSD1306_SET_PRECHARGE, 0xc2};
  // Set V COMH Deselect, reset value 0x22 = 0,77xUcc  18
  static const uint8_t vcom_desel[] = {2, SSD1306_VCOM_DESELECT, 0x20};
  // 0x8D 19
  static const uint8_t set_char_reg[] = {2, SSD1306_SET_CHAR_REG, 0x14};
  // 0xAF = Set Display ON 20
  static const uint8_t display_on[] = {1, SSD1306_DISPLAY_ON};



/** @array Init commands */
static const uint8_t INIT_SSD1306[] = {
  // 0xAE = Set Display OFF 1
  1, SSD1306_DISPLAY_OFF,
  // 0xA8 2
  2, SSD1306_SET_MUX_RATIO, 0x3F,
  // 0x20 = Set Memory Addressing Mode 3
  // -----------------------------------
  // 0x00 - Horizontal Addressing Mode
  // 0x01 - Vertical Addressing Mode
  // 0x02 - Page Addressing Mode (RESET) 4
  2, SSD1306_MEMORY_ADDR_MODE, 0x00,
  // 0x21 = Set Column Address 5
  // -----------------------------------
  // 0x00 - Start Column Address
  // 0xFF - End Column Address
  3, SSD1306_SET_COLUMN_ADDR, START_COLUMN_ADDR, END_COLUMN_ADDR,
  // 0x22 = Set Page Address 6
  // -----------------------------------
  // 0x00 - Start Column Address 7
  // 0x07 - End Column Address
  3, SSD1306_SET_PAGE_ADDR, START_PAGE_ADDR, END_PAGE_ADDR,
  // 0x40 8
  1, SSD1306_SET_START_LINE,
  // 0xD3 9
  2, SSD1306_DISPLAY_OFFSET, 0x00,
  // 0xA0 / remap 0xA1 10
  1, SSD1306_SEG_REMAP_OP,
  // 0xC0 / remap 0xC8 11
  1, SSD1306_COM_SCAN_DIR_OP,
  // 0xDA 12
  2, SSD1306_COM_PIN_CONF, 0x12,
  // 0x81 13
  2, SSD1306_SET_CONTRAST, 0x7F,
  // 0xA4 14
  1, SSD1306_DIS_ENT_DISP_ON,
  // 0xA6 15
  1, SSD1306_DIS_NORMAL,
  // 0xD5 16
  2, SSD1306_SET_OSC_FREQ, 0x80,
  // 0xD9, 1st Period = higher value less blinking 17
  2, SSD1306_SET_PRECHARGE, 0xc2,
  // Set V COMH Deselect, reset value 0x22 = 0,77xUcc  18
  2, SSD1306_VCOM_DESELECT, 0x20,
  // 0x8D 19
  2, SSD1306_SET_CHAR_REG, 0x14,
  // 0xAF = Set Display ON 20
  1, SSD1306_DISPLAY_ON
};

//4 bit spi defines
#define dsp_all_points 0xA5
#define dsp_off 0xAE
#define dsp_on 0XAF
#define dsp_start_line 0x40 //or with 6 lower address bits
#define dsp_page_addr 0xB0 //or with 4 bit page addr
#define dsp_column_upper 0x10 //or wit upper 4 column address bits
#define dsp_column_lower 0x00 //or wit lower 4 column address bits
#define dsp_orient_norm 0xA0
#define dsp_orient_rev 0xA1
#define dsp_normal 0xA6
#define dsp_reverse 0xA7
#define dsp_allp_on 0xA5
#define dsp_allp_off 0xA4
#define dsp_bias_19 0xA2
#define dsp_bias_17 0xA3
#define dsp_reset 0xE2
#define dsp_scan_n 0xC0
#define dsp_scan_rev 0xC8
//I2C defines
//I2C2_MESSAGE_STATUS messstat;

#define I2CAdd    0x3C //The actual 7 bit address is 0x3C but the R/W bit extends the byte to 8 bits
#define I2Ccont   0x81 // The following byte sets contrast 0 = low 0x7f = high
#define I2Cdspon  0xA4 // Switch on display
#define I2Cnormds 0xA6 //Normal display
#define I2Cinvds  0xA7 //Invert pixels
#define I2Cdspwu  0xAF //Display awake
#define I2Cdspslp 0xAE // Display Sleep

#define SLAVE_I2C_GENERIC_RETRY_MAX           100
#define SLAVE_I2C_GENERIC_DEVICE_TIMEOUT      65535   // define slave timeout 
// I2C2_MESSAGE_STATUS *pstatus;
//#define dsp_

static int fontpos = 0;
static int ypos = 0;
static int pagepos = 0;

// Sample qr code for test
/* XPM  40 x 41 */
static const uint8_t qrcode_xpm[] = \
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBE"\
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBE"\
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBE"\
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBE"\
"BBBBFFFFFFFBFBBBBFBFFFFFFFBFBBFFFFFFFBBBBE"\
"BBBBFBBBBBFBFBFBBFBBFBFBFBFFFBFBBBBBFBBBBE"\
"BBBBFBFFFBFBBBFFFBBBBFBBFBBFBBFBFFFBFBBBBE"\
"BBBBFBFFFBFBFBBBFBFBFBBFBBFBBBFBFFFBFBBBBE"\
"BBBBFBFFFBFBBBFFFFFBBBBBFFBBFBFBFFFBFBBBBE"\
"BBBBFBBBBBFBBBBBBFFBBBBFBFBBFBFBBBBBFBBBBE"\
"BBBBFFFFFFFBFBFBFBFBFBFBFBFBFBFFFFFFFBBBBE"\
"BBBBBBBBBBBBFBFFFBBBBFFBFBBBFBBBBBBBBBBBBE"\
"BBBBFBFFBFFFBFBBBFFBFFFFBFBFFBFBBFBFFBBBBE"\
"BBBBBFFFFBBFBFBFFBBFFBFFBBBFBBFFBFFFFBBBBE"\
"BBBBBFFBBBFBFFBBBBFBFFBBFFFFBFBFFFBBFBBBBE"\
"BBBBBBFBBFBFFBFBFFFFFBFBFBFFFBBFBFBFFBBBBE"\
"BBBBFBFFFFFBBFFBBBBFBBFFFBFFFBBBFFBFBBBBBE"\
"BBBBBFBFFFBFBFFBFFBBFBFFFBFBFFBBBFBFBBBBBE"\
"BBBBFFBBFFFFFBFFBBBFFFFFBBFBFBFBFBBBBBBBBE"\
"BBBBBFFBFFBFFFBFBFBBFBBBBFFBBFFBBFFBBBBBBE"\
"BBBBFFBFBBFFBFFBBBBFBBBBFFFBBFFBFFFBBBBBBE"\
"BBBBBBFBFBBFBFFBBFBBBFBBFBBFBBFBFFBBFBBBBE"\
"BBBBFFFFFFFFBFFFBFFFFFBBFFFBBBBFFBFFBBBBBE"\
"BBBBFFBFBBBFFBFFBBBFFBBBFBBBBFFBFBBFFBBBBE"\
"BBBBBFFFBBFBFFFBFBFFBBFFFFFBBFBBBFFFFBBBBE"\
"BBBBFBFFBFBBBFFBBBFFBFFFBFFFBBFBBBBBFBBBBE"\
"BBBBBBFFBBFBBFFBBFFBFBFBFBBFFBFFBBBFFBBBBE"\
"BBBBBFBBFBBFBFFBFBFBFBFFBBFBBFBBBBBFBBBBBE"\
"BBBBFBFFBBFBBFFBBFFFBFBBBBFBFFFFFFBFBBBBBE"\
"BBBBBBBBBBBBFBFBFBFFBFFFBFFBFBBBFFBFBBBBBE"\
"BBBBFFFFFFFBFBBFBBFBFBBFFBBFFBFBFBBBBBBBBE"\
"BBBBFBBBBBFBFBBFFFFBBBBFBFFFFBBBFFFFFBBBBE"\
"BBBBFBFFFBFBBBFFFFBBBFBBBFBFFFFFFBFBFBBBBE"\
"BBBBFBFFFBFBFFBFBFBBBBFBBBBFFBBFBFFBFBBBBE"\
"BBBBFBFFFBFBFBBFFBBBBBFBFBBFBBFFBFBBBBBBBE"\
"BBBBFBBBBBFBBBFFBFFFFFFBFBFFFFFFFBBBFBBBBE"\
"BBBBFFFFFFFBFFBBFFBFBFFFBFBFBFFBFBFBBBBBBE"\
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBE"\
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBE"\
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBE"\
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBE";


#endif	/* DISPLAY_H */

