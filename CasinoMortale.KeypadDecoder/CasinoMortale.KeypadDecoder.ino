/*
 Name:		CasinoMortale.ino
 Created:	12/9/2021 8:29:58 PM
 Author:	baspa
*/

// the setup function runs once when you press reset or power the board
#include <SoftwareSerial.h>

const int rxPin = 9;
const int txPin = 10;
SoftwareSerial softwareSerial(rxPin, txPin);

char receivedChars[7];
int numCharsWritten;
bool isWritingCharacters;
bool isPinCodeReceived;

void setup() {
	Serial.begin(9600);
		
	softwareSerial.begin(4800);
	softwareSerial.flush();
}

// the loop function runs over and over again until power down or reset
void loop() {

	if (!isPinCodeReceived && softwareSerial.available())
	{		
		char character = softwareSerial.read();

		if (character == '*')
		{
			isWritingCharacters = true;
		}
		else if (isWritingCharacters)
		{
			if (character == '#' || numCharsWritten == 6)
			{
				receivedChars[numCharsWritten] = '\0';
				isWritingCharacters = false;
				isPinCodeReceived = true;
			}
			else
			{
				receivedChars[numCharsWritten] = character;
				numCharsWritten++;
			}			
		}
	}
	else
	{
		Serial.print("Received pinCode:");
		Serial.println(receivedChars);

		softwareSerial.print('U');
		softwareSerial.flush();
	}
}
