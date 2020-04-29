int hallSensorPin1 = 4;
int hallSensorPin2 = 5;
int hallSensorPin3 = 6;
int ledPin1 = 0;
int ledPin2 = 1;
int ledPin3 = 2;
int state1 = 0;
int state2 = 0;
int state3 = 0;

// Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// create an RF24 object
RF24 radio(9, 8); // CE, CSN

// address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(hallSensorPin1, INPUT);
    pinMode(hallSensorPin2, INPUT);
    pinMode(hallSensorPin3, INPUT);

    radio.begin();

    // set the address
    radio.openWritingPipe(address);

    // Set module as transmitter
    radio.stopListening();
}

void loop()
{

    state1 = digitalRead(hallSensorPin1);

    if (state1 == HIGH)
    {
        digitalWrite(ledPin1, HIGH);

        // Send message to receiver
        const char text[] = "left";
        radio.write(&text, sizeof(text));
        delay(100);
    }

    else
    {
        digitalWrite(ledPin1, LOW);
    }

    state2 = digitalRead(hallSensorPin2);
    if (state2 == HIGH)
    {
        digitalWrite(ledPin2, HIGH);

        // Send message to receiver
        const char text[] = "forward";
        radio.write(&text, sizeof(text));
        delay(100);
    }
}