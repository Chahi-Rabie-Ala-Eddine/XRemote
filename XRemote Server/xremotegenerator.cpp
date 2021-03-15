#include <QCryptographicHash>

#include <QtWidgets>

#include <random>
#include <string>

using namespace std;

/*Generate random number*/
unsigned int generateRandomDigit(int lower, int upper){

    srand(time(0));
    return (rand() % (upper - lower + 1)) + lower;
}

/*Generate random string*/
string generateRandomString(string::size_type sampleTextLength)
{
    string hexadecimal;
    static auto& hexForm = "0123456789ABCDEF";

    thread_local static mt19937 generated
    {
        random_device
        {

        }()
    };

    thread_local static uniform_int_distribution<string::size_type> pick(0, sizeof(hexForm) - 2);

    hexadecimal.reserve(sampleTextLength);

    while(--sampleTextLength)
        hexadecimal += hexForm[pick(generated)];

    return (string)hexadecimal;
}

/*Generate Keccak 512 bits hash*/
QString generateKeccak512Hash(string random){

    return QString(QCryptographicHash::hash((random.c_str()), QCryptographicHash::Keccak_512).toHex());
}

/*Generate strong hazard*/
QString XRemoteHazard(unsigned const int length){

    string hazard = generateKeccak512Hash(generateRandomString(generateRandomDigit(100, 200))).toUtf8().constData();

    return QString::fromStdString(hazard.substr(generateRandomDigit(0, 127),length));
}
