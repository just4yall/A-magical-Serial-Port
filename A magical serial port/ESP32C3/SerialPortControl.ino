/*
 Name:		SerialPortControl.ino
 Created:	2022/7/1 16:26:52
 Author:	OCEAN
*/
constexpr auto KEY1 = 12;
constexpr auto KEY2 = 13;
int TimeKeeperKey1 = 0;
int TimeKeeperKey2 = 0;
int TimeKeeperAll = 0;
int stateKey1 = 0;
int stateKey2 = 0;
bool compareflag = false;
// the setup function runs once when you press reset or power the board
void setup() 
{
	Serial.begin(115200);
	pinMode(KEY1, INPUT);
	pinMode(KEY2, INPUT);
}

// the loop function runs over and over again until power down or reset
void loop() 
{

	if(digitalRead(KEY1) == 1 && stateKey1 != 4 && stateKey2 != 4)
	{
		
		while (1)
		{
			if (digitalRead(KEY1) == 0)
			{
				stateKey1++;
				if (stateKey1 > 3)
				{
					stateKey1 = 3;
				}
				TimeKeeperKey1 = millis();
				break;
			}
			if (digitalRead(KEY2) == 1)
			{
				stateKey1 = 4;
				TimeKeeperKey1 = millis();
				break;
			}
			delay(50);
		}
	}

	if (digitalRead(KEY2) == 1 && stateKey1 != 4 && stateKey2 != 4)
	{

		while (1)
		{
			if (digitalRead(KEY2) == 0)
			{
				stateKey2++;
				if (stateKey2 > 3)
				{
					stateKey2 = 3;
				}
				TimeKeeperKey2 = millis();
				break;
			}
			if (digitalRead(KEY1) == 1)
			{
				stateKey2 = 4;
				TimeKeeperKey2 = millis();
				break;
			}
			delay(50);
		}
	}
	if (millis() - TimeKeeperKey1 > 250)
	{
		switch (stateKey1)
		{
		case 1:
		{
			Serial.println("Key1 Once");
			compareflag = true;
			break;
		}
		case 2:
		{
			Serial.println("Key1 Twice");
			compareflag = true;
			break;
		}
		case 3:
		{
			Serial.println("Key1 Tripple");
			compareflag = true;
			break;
		}
		case 4:
		{
			Serial.println("Key1+Key2");
			compareflag = true;
			break;
		}
		default:
			break;
		}
		
		stateKey1 = 0;
		
	}
	if (millis() - TimeKeeperKey2 > 250)
	{
		switch (stateKey2)
		{
		case 1:
		{
			Serial.println("Key2 Once");
			compareflag = true;
			break;
		}
		case 2:
		{
			Serial.println("Key2 Twice");
			compareflag = true;
			break;
		}
		case 3:
		{
			Serial.println("Key2 Tripple");
			compareflag = true;
			break;
		}
		case 4:
		{
			Serial.println("Key2+Key1");
			compareflag = true;
			break;
		}
		default:
			break;
		}
		stateKey2 = 0;
	}
	if (compareflag == true)
	{
		if (digitalRead(KEY1) == 1 || digitalRead(KEY2) == 1)
		{
			delay(500);
		}
		compareflag = false;
	}
}
