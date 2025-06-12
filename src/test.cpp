#include "Arduino.h"

typedef struct{
    int a;
    String b;
    void* x;

} test;

void setup()
{
	Serial.begin(115200);
	Serial.println("------Hello, World!------");
    test t;
    t.a = 1;
    t.b = "Hello, World!ghfhgfhgfghfhgfhgfhgfghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhffffffffffffffffffffffffffffff";
    Serial.printf("Sizeof struct: %d\n", sizeof(test));
    Serial.printf("Sizeof t: %d\n", sizeof(t));
    Serial.printf("t.x: %p\n", t.x);
    
    char *c = (char *)malloc(200);
    memcpy(c,&t,sizeof(test));
    test *t1 = (test *)c;
    //memcpy(&t1,c,sizeof(test));
    Serial.printf("t1.a: %d\n", t1->a);
    Serial.printf("t1.b: %s\n", t1->b.c_str());
    Serial.printf("t1.x: %p\n", t1->x);
    free(c);
    
}

void loop()
{
	vTaskDelete(NULL);
}

