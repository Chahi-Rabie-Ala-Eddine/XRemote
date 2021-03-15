#include "xremotedbmanagement.h"
#include "xremoteauthentication.h"
#include "xremotesecurity.h"

#include <QCryptographicHash>

using namespace std;

/*Sign up client*/
void _SignUp(const string mail, const string password, const string passwordConfirmation){

    if(_isInWhiteList(mail) && _isInWhiteList(password) && _isInWhiteList(passwordConfirmation)){

        if(password.compare(passwordConfirmation) == 0){

            if(_isStrong(password)){
                /*Insérer le client dans la table user*/
                _DBInsertElement("user", mail, password);

                /*Le connecter avec un token*/

            }

            else{
                //Afficher à l'écran que le mot de passe est faible et rappeller comment il doit être construit
            }
        }

        else{
            //Afficher à l'écran que les mots de passe sont différents.
        }
    }

    else{
        //Afficher à l'écran qu'il y'a des caractères non autorisés et signaler l'incident sur les logs.
    }
}

/*Sign in client*/
void _SignIn(const string mail, const string password){

    /*Check SQL, XML, Shell... Injections*/
    if(_isInWhiteList(mail) && _isInWhiteList(password)){
        /*Check if user exist*/
        if(_DBCheckElementByMail("user", mail)){
            /*Check if passwords match*/
            if(_DBSelectElementByMail("user", mail).compare(QString(QCryptographicHash::hash(password.c_str(), QCryptographicHash::Keccak_512).toHex()).toUtf8().constData()) == 0){

                /*Le connecter avec un token*/

            }

            else{
                //Afficher à l'écran que les mots de passe ne correspondent pas
            }
        }

        else{
            //Afficher à l'écran que l'utilisateur n'existe pas !
        }
    }

    else{
        //Afficher à l'écran qu'il y a des caractères non autorisés et signaler l'incident sur les logs.
    }
}

/*Sign in client*/
bool _CheckSignIn(const string mail, const string password){

    /*Check if user exist*/
    if(_DBCheckElementByMail("user", mail)){
        /*Check if passwords match*/
        if(_DBSelectElementByMail("user", mail).compare(QString(QCryptographicHash::hash(password.c_str(), QCryptographicHash::Keccak_512).toHex()).toUtf8().constData()) == 0){
            return true;
        }
    }

    return false;
}

/*Sign out client*/
void _SignOut(){

    /*Détruire le token et réafficher la fenêtre intiale*/
}
