#ifndef TOKEN_H
#define TOKEN_H

enum class RequestTypes
{
    DOWNLOAD = 1, UPLOAD = 2, PLAY = 3, PAUSE = 5
};

typedef struct Token Token;
struct Token
{
    string id;
    unsigned int timestamp;
};

#endif // TOKEN_H
