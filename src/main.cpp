/**
 * Extremely basic utility to write a string to the given position
 * in the EEPROM.
 *
 * I stored my device id in the EEPROM so any calls to any MQTT service or
 * online storage (ThingSpeak) I know where it came from.
 *
 * @author Shaun Norman <shaun@speedfreaks.com.au>
 **/

#include <Arduino.h>
#include <EEPROM.h>

String device_id = "dev001";
int position = 0;

/**
 * Reads values from the EEPROM
 *
 * @param int start Address to start reading from
 * @param int length Number of bytes to read
 * @return The EEPROM value
 */
String eeprom_read(int start=0, int length=5) {
    Serial.println("Reading from EEPROM, position " + String(start) + " to " + String(start + length));
    EEPROM.begin(512);
    String string;
    for (int index=0; index < length; index++) {
        int position = start + index;
        char f = EEPROM.read(position);
        string += (f);
    }
    Serial.println("Value read: " + string);
    return string;
}

/**
 * Writes the given string into the EEPROM
 *
 * @param String write_string Value to write
 * @param int start_addr Start address to write too
 */
void eeprom_write(String write_string, int start_addr=0) {
    Serial.println("WRITING string: \"" + write_string + "\" at position " + String(start_addr));

    EEPROM.begin(512);

    for (int index=0; index < write_string.length(); index++) {
        int position = start_addr + index;
        EEPROM.write(position, write_string[index]);
    }

    EEPROM.commit();
}

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    // Insert our device id at the start of the EEPROM
    eeprom_write(device_id, position);

    // Another testing string starting at position 50
    eeprom_write("ABC456GHI01", 50);
}

void loop() {
    // Read in our device id
    eeprom_read(position, 6);

    // Read in the second test string we added.
    eeprom_read(50, 11);

    delay(5000);
}
