#include <MIDI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

/* BEGIN MIDI Settings */

// MIDI Notes
#define NOTE_F4 77
#define NOTE_G4 79
#define NOTE_A4 81
#define NOTE_B4 83
#define NOTE_C5 84
#define NOTE_D5 86
#define NOTE_E5 88
#define NOTE_F5 89

#define NOTE_G5 91
#define NOTE_A5 93
#define NOTE_B5 95
#define NOTE_C6 96
#define NOTE_D6 98
#define NOTE_E6 100
#define NOTE_F6 101
#define NOTE_G6 103

// Override the default MIDI baudrate for FeatherWing
struct CustomBaudRateSettings : public MIDI_NAMESPACE::DefaultSerialSettings {
  static const long BaudRate = 31250;
};

// Leonardo, Due and other USB boards use Serial1 by default.
MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings> serialMIDI(Serial1);
MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>> MIDI((MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>&)serialMIDI);

/* END MIDI Settings */

/* BEGIN NeoPixel Settings */

// Digital signal pinout communcating with NeoPixel.
#define PIN 6

// Max is 255, 32 is a conservative value to not overload
// a USB power supply (500mA) for 12x12 pixels.
#define BRIGHTNESS 32

// Define matrix width and height.
#define mw 8
#define mh 8
Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(mw, mh, 
  PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800 );

// This could also be defined as matrix->color(255,0,0) but those defines
// are meant to work for adafruit_gfx backends that are lacking color()
#define LED_BLACK		0

#define LED_RED_VERYLOW 	(3 <<  11)
#define LED_RED_LOW 		(7 <<  11)
#define LED_RED_MEDIUM 		(15 << 11)
#define LED_RED_HIGH 		(31 << 11)

#define LED_GREEN_VERYLOW	(1 <<  5)   
#define LED_GREEN_LOW 		(15 << 5)  
#define LED_GREEN_MEDIUM 	(31 << 5) 
#define LED_GREEN_HIGH 		(63 << 5)  

#define LED_BLUE_VERYLOW	3
#define LED_BLUE_LOW 		7
#define LED_BLUE_MEDIUM 	15
#define LED_BLUE_HIGH 		31

#define LED_ORANGE_HIGH		(LED_RED_HIGH    + LED_GREEN_HIGH)
#define LED_PURPLE_HIGH		(LED_RED_HIGH    + LED_BLUE_HIGH)
#define LED_WHITE_HIGH		(LED_RED_HIGH    + LED_GREEN_HIGH    + LED_BLUE_HIGH)

// IBM EGA 8x8 Font https://int10h.org/oldschool-pc-fonts/fontlist/font?ibm_ega_8x8
// Created black/white 8x8 PNGs in GIMP
// Converted to code at https://javl.github.io/image2cpp/
// - Invert Image Colors
// - Flip Image: Horizontally (sometimes?)
static const uint8_t PROGMEM
    RGB_bmp[][8] = {
      // 0: One
      { 0x00, 0x18, 0x1c, 0x18, 0x18, 0x18, 0x18, 0x7e, },
      // 1: Two
      { 0x00, 0x3c, 0x66, 0x06, 0x38, 0x30, 0x66, 0x7e, },
      // 2: Three
      { 0x00, 0x3c, 0x66, 0x06, 0x1c, 0x06, 0x66, 0x3c, },
      // 3: Four
      { 0x00, 0x0e, 0x78, 0x36, 0x66, 0x7f, 0x60, 0x0f, },
      // 4: Five
      { 0x00, 0x7e, 0x06, 0x7c, 0x60, 0x06, 0x66, 0x3c, },
      // 5: Six
      { 0x00, 0x1c, 0x0c, 0x60, 0x3e, 0x66, 0x66, 0x3c, },
      // 6: Seven
      { 0x00, 0x7e, 0x66, 0x06, 0x30, 0x18, 0x18, 0x18, },
      // 6: Eight
      { 0x00, 0x3c, 0x66, 0x66, 0x3c, 0x66, 0x66, 0x3c, },
};

/* END NeoPixel Settings */

// -----------------------------------------------------------------------------
// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation here:
// https://github.com/FortySevenEffects/arduino_midi_library/wiki/Using-Callbacks
void handleNoteOn(byte channel, byte pitch, byte velocity)
{
    // Do whatever you want when a note is pressed.

    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.
    // Serial.print("Note on: ");
    // Serial.println(pitch);
    
    switch(pitch) {
      // RED BG
      case NOTE_F4:
        printBeat(0, true, true);
        break;

      case NOTE_G4:
        printBeat(1, true, true);
        break;

      case NOTE_A4:
        printBeat(2, true, true);
        break;

      case NOTE_B4:
        printBeat(3, true, true);
       break;

      case NOTE_C5:
        printBeat(4, true, true);
        break;

      case NOTE_D5:
        printBeat(5, true, true);
        break;

      case NOTE_E5:
        printBeat(6, true, true);
        break;

      case NOTE_F5:
        printBeat(7, true, true);
        break;

      // BLUE BG
      case NOTE_G5:
        printBeat(0, true, false);
        break;

      case NOTE_A5:
        printBeat(1, true, false);
        break;

      case NOTE_B5:
        printBeat(2, true, false);
        break;

      case NOTE_C6:
        printBeat(3, true, false);
       break;

      case NOTE_D6:
        printBeat(4, true, false);
        break;

      case NOTE_E6:
        printBeat(5, true, false);
        break;

      case NOTE_F6:
        printBeat(6, true, false);
        break;

      case NOTE_G6:
        printBeat(7, true, false);
        break;

      default:
        clearBeat();
        break;
    }
  }

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
    // Serial.print("Note off: ");
    // Serial.println(pitch);

    switch(pitch) {
      case NOTE_F4:
        printBeat(0, false, false);
        break;

      case NOTE_G4:
        printBeat(1, false, false);
        break;

      case NOTE_A4:
        printBeat(2, false, false);
        break;

      case NOTE_B4:
        printBeat(3, false, false);
       break;

      case NOTE_C5:
        printBeat(4, false, false);
        break;

      case NOTE_D5:
        printBeat(5, false, false);
        break;

      case NOTE_E5:
        printBeat(6, false, false);
        break;

      case NOTE_F5:
        printBeat(7, false, false);
        break;

      case NOTE_G5:
        printBeat(0, false, false);
        break;

      case NOTE_A5:
        printBeat(1, false, false);
        break;

      case NOTE_B5:
        printBeat(2, false, false);
        break;

      case NOTE_C6:
        printBeat(3, false, false);
        break;

      case NOTE_D6:
        printBeat(4, false, false);
        break;

      case NOTE_E6:
        printBeat(5, false, false);
        break;

      case NOTE_F6:
        printBeat(6, false, false);
        break;

      case NOTE_G6:
        printBeat(7, false, false);
        break;

      default:
        clearBeat();
        break;
    }
}

void printBeat(int beat, bool on, bool red) {
  if ( on ) {
    matrix->clear();
    if ( red ) {
      matrix->fillScreen(LED_RED_MEDIUM);
    } else {
      matrix->fillScreen(LED_BLUE_MEDIUM);
    }
    matrix->drawBitmap(0, 0,  RGB_bmp[beat], mw, mh, LED_ORANGE_HIGH);
    matrix->show();
  } else {
    matrix->clear();
    matrix->fillScreen(LED_BLACK);
    matrix->drawBitmap(0, 0,  RGB_bmp[beat], mw, mh, LED_ORANGE_HIGH);
    matrix->show();
  }
}

void clearBeat() {
  matrix->clear();
  matrix->fillScreen(LED_BLACK);
  matrix->show();
}

// -----------------------------------------------------------------------------

void setup()
{
    // Serial setup
    // Serial.begin(115200);
    // Wait for the serial interface to be ready.
    // while (!Serial) ;
    // Serial.println("MIDI visual metronome");

    // LED Setup
    matrix->begin();
    matrix->setBrightness(BRIGHTNESS);
    // Test full bright of all LEDs. If brightness is too high
    // for your current limit (i.e. USB), decrease it.
    matrix->fillScreen(LED_WHITE_HIGH);
    matrix->show();
    delay(1000);
    matrix->clear();
    matrix->fillScreen(LED_BLACK);
    matrix->show();

    // MIDI Setup
    // Connect the handler function(s) to the library,
    MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function
    MIDI.setHandleNoteOff(handleNoteOff);

    // Initiate MIDI communications, listen to all channels
    MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop()
{
    // Call MIDI.read the fastest you can for real-time performance.
    MIDI.read();
    // There is no need to check if there are messages incoming
    // if they are bound to a Callback function.
    // The attached method will be called automatically
    // when the corresponding message has been received.
}
