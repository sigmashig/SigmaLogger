#include <Arduino.h>
#include <SigmaLoger.h>

void my_publisher(SigmaLogLevel level, const char *message)
{
  // You can add any function here: send log to MQTT, to Serial, to SD card, etc.
  // You can add any filters based on level here
  Serial.printf("[%d] %s\n", level, message);
}

void my_publisher1(SigmaLogLevel level, const char *message)
{
  // You can add any function here: send log to MQTT, to Serial, to SD card, etc.
  // You can add any filters based on level here

  // No extra changes for the message
  Serial.printf("%s\n", message);
}


const char *my_timestamp()
{
  // You can add any function here: get timestamp from RTC, from NTP, etc.
  static char timestamp[16];
  sprintf(timestamp, "{ts=%.3f}", millis() / 1000.0);
  return timestamp;
}

const char *my_timestamp1()
{
  // You can add any function here: get timestamp from RTC, from NTP, etc.
  static char timestamp[100];
  sprintf(timestamp, "{TIMESTAMP1: ts=%.3f}", millis() / 1000.0);
  return timestamp;
}


void setup()
{
  Serial.begin(115200);
  Serial.println("--------------------");
  // The maximum length of one line is 512 chars. You have got an error when you try to add more chars.
  // But it will not crash an application
  SigmaLoger *sigmaLoger = new SigmaLoger(512, my_publisher, my_timestamp);
  
  sigmaLoger->Append(F("LOG1.Hello, ")).Append("World!").Debug();
  sigmaLoger->Debug("LOG1.Just a simple message");
  SigmaLogLevel level = SIGMALOG_INFO;
  sigmaLoger->Printf("LOG1.This is a %s message", "formatted").Log(level);

  // The second Loger with default settings:
  SigmaLoger *sigmaLoger2 = new SigmaLoger(512);
  sigmaLoger2->Append(F("LOG2.Hello, ")).Append("World!").Debug();
  sigmaLoger2->Debug("LOG2.Just a simple message");
  sigmaLoger2->Printf("LOG2.This is a %s message", "formatted").Log(level);

  // The third Loger with no log and no timestamp settings.
  // All the messages will be ignored
  SigmaLoger *sigmaLoger3 = new SigmaLoger(512, NULL, NULL);
  sigmaLoger3->Append("LOG3.Hello, ").Append("World!").Debug();
  sigmaLoger3->Debug("LOG3.Just a simple message");
  sigmaLoger3->Printf("LOG3.This is a %s message", "formatted").Log(level);

  // Alternative way to set publisher and timestamp
  SigmaLoger *sigmaLoger4 = new SigmaLoger(512);
  sigmaLoger4->Append("LOG4.Hello, ").Append("World! Default Publisher, Default Timestamp").Debug();
  sigmaLoger4->SetPublisher(my_publisher1);
  sigmaLoger4->SetTimestamp(my_timestamp1);
  sigmaLoger4->Append("LOG4.Changed publisher and timestamp").Debug();
  sigmaLoger4->Append("LOG4.Hello, ").Append("World!").Debug();
  sigmaLoger4->Debug("LOG4.Just a simple message");
  
  sigmaLoger4->Printf("LOG4.This is a %s message", "formatted").Log(SIGMALOG_ERROR);
}

void loop()
{
  // put your main code here, to run repeatedly:
}
