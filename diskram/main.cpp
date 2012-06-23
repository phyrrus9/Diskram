#include "diskram.cpp" //sorry I couldnt figure out how to do it with .h
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
using namespace std;
using namespace diskram;


int main()
{
    init__();
    char message[] = "Hey, look, dynamically allocated ramdisk works!";
    drm *d;
    d = new drm(strlen(message)); //dynamic mem allocate for string
    d->set(message); //set the value
    char * returnvalue = new char[d->getsize()]; //allocate a placeholder in RAM
    d->get(returnvalue); //get the string
    cout << returnvalue << endl; //display it
    delete returnvalue; //free the ram
    delete d; //so I can re-use the name
    d = new drm(256); //256-byte integer
    d->set((char*)"1234567890123456789");
    //d->set(itoa(rand(), buffer, 10)); //normally what you would use (but i cant get it to work)
    returnvalue = new char[d->getsize()]; //dynamic allocation
    d->get(returnvalue);
    cout << atol(returnvalue) << endl; //so it actually IS an int
    //of course, using a 256-byte integer as a lint is not a good idea
    delete d;
    delete returnvalue;
    ramexit(0);
}