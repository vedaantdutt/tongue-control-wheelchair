const int in1 = 7;
const int in2 = 6;
const int in3 = 5;
const int in4 = 4;
const int enA = 3;
const int enB = 10;

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

    // Set all the motor control pins to outputs
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    // Turn off motors - Initial state
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    while (!Serial)
    {
        Serial.begin(9600);
        radio.begin();

        // set the address
        radio.openReadingPipe(0, address);

        // Set module as receiver
        radio.startListening();
    }
}

void loop()
{

    analogWrite(enA, 255);
    analogWrite(enB, 255);

    // Read the data if available in buffer
    if (radio.available())
    {

        char text[32] = {0};
        radio.read(&text, sizeof(text));
        Serial.println(text);

        if (text == "forward")
        {

            // forward
            digitalWrite(in1, HIGH);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, HIGH);
            digitalWrite(in4, HIGH);
        }
        else if (text == "left")
        {

            // left
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, HIGH);
            digitalWrite(in4, LOW);
        }
        else if (text == "right")
        {

            // right
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);
        }
        else
        {

            // stop
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            digitalWrite(in3, LOW);
            digitalWrite(in4, LOW);
        }
    }
}