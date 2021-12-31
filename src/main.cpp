#include <arduino.h>

struct Pin_definition {
    char name[20];
    uint8_t number;
};

Pin_definition pins[] = {
    {"LED_2", 2},
    {"LED_13", 13},
    {"SD_DETECT_PIN", 5},
    {"BUTTON_LED_GND_PIN", 12},
    {"BUTTON_LED_PIN", 14},
    {"RESET_A6_PIN", 15},
    {"RXD2", 16},
    {"TXD2", 4},
    {"TXD2_OLD", 17},
    {"LDR_PIN", 25},
    {"LED_PIN", 27},
    {"BUZZER_PIN", 26},
    {"RX2_PIN", 32},
    {"S_PIN", 33},
    {"TX2_PIN", 34},
    {"BROKEN_CIRCUIT_PIN", 35}
};

const uint8_t pins_count = sizeof(pins)/sizeof(pins[0]);

// ================================================ SETUP ================================================
void setup() {
    Serial.begin(115200);
    Serial.println();

    // for(int k=0; k<=39; k++) {
    //   Serial.println(k);
    //   delay (100);
    //   if (k<6 || k > 11) {
    //     if (k%2) {
    //       pinMode(k, OUTPUT);
    //       digitalWrite(k, HIGH);
    //     }
    //   }
    // };

    // while (1) {};

    // Init
    for(int k=0; k<pins_count;k++) {
        pinMode(pins[k].number, OUTPUT);
        digitalWrite(pins[k].number, LOW);
        pinMode(pins[k].number, INPUT_PULLDOWN);
    };

    // Cycle
    int counter = 0;
    for(int i=0; i<pins_count;i++) {
        // Init
        // for(int k=0; k<pins_count;k++) {
        //   pinMode(pins[k].number, OUTPUT);
        //   digitalWrite(pins[k].number, LOW);
        //   pinMode(pins[k].number, INPUT);
        // };

        pinMode(pins[i].number, OUTPUT);
        digitalWrite(pins[i].number, HIGH);
        delay(200);
        Serial.println("\tDebug: pin=" + String (pins[i].number) + " / " + pins[i].name);
        for(int j=i+1; j<pins_count;j++) {
        if (digitalRead(pins[j].number) == HIGH) {
            Serial.println("Shortened pins: ");
            Serial.println(String(pins[i].number)+": "+pins[i].name + " --- " + (pins[j].number)+": "+pins[j].name);
            counter++;
            delay(200);
        }
        digitalWrite(pins[j].number, LOW);
        };
        digitalWrite(pins[i].number, LOW);
        pinMode(pins[i].number, INPUT_PULLDOWN);
    };
    if (counter) {
        Serial.print ("Count of shortened pins: ");
        Serial.println (counter);
    } else {
        Serial.println ("None pins are shortened.");
    }
}

// ================================================ LOOP =================================================
void loop() {
}