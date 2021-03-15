#ifndef XREMOTEGENERATOR_H
#define XREMOTEGENERATOR_H

#include <QtWidgets>

using namespace std;

/*Generate random number*/
unsigned int generateRandomDigit(int lower, int upper);

/*Generate random string*/
string generateRandomString(string::size_type sampleTextLength);

/*Generate Keccak 512 bits hash*/
QString generateKeccak512Hash(string random);

/*Generate strong hazard*/
QString XRemoteHazard(unsigned const int length);

#endif // XREMOTEGENERATOR_H
