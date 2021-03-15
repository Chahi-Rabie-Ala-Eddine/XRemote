#ifndef XREMOTEAUTHENTICATION_H
#define XREMOTEAUTHENTICATION_H

#include <iostream>

using namespace std;

/*Sign up client*/
void _SignUp();

/*Sign in client*/
void _SignIn(const string mail, const string password);

/*TDD CHECK SIGN IN*/
bool _CheckSignIn(const string mail, const string password);

/*Sign out client*/
void _SignOut();

#endif // XREMOTEAUTHENTICATION_H
