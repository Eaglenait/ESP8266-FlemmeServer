#ifndef Rapi_h
#define Rapi_h
#include <Arduino.h>

#ifdef ESP8266
#include <pgmspace.h>
#endif

typedef struct restAction {
	int[] Pin;
	int Value;
}restAction;

class Rapi {
public:
	Rapi();

	//Check if called URI is handleable
	 restAction handleRest();

private:
	char** uriList;
	/*
		handle rest
			parse uri (parse l'uri handelable)
			vérifier si handelable
			si handelable
			get pin 
			set pin à la valeur passée (check valeur)

	*/
	
};
