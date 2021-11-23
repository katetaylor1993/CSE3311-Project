#include "databasehandler.h"
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QVariantMap>
#include <QJsonObject>
#include <QFile>

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);

   // m_networkReply = m_networkManager->get(QNetworkRequest(QUrl("https://spyuser-65ed7-default-rtdb.firebaseio.com/User_Database.json")));

    //connect(this, &DatabaseHandler::userSignedIn, this, &DatabaseHandler::performAuthenticatedDatabaseCall);
    //connect(this, &DatabaseHandler::userSignedIn, this, &DatabaseHandler::performAuthenticatedDatabaseCall);


    //read data from firebase using get command // this messes up reading return msg from app outut
    //connect(m_networkReply, &QNetworkReply::readyRead, this, &DatabaseHandler::networkReplyReadyRead);


    // post data to firebase using post command
    QString val;
    QFile file;
    file.setFileName("C:/QT/sample2.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    qWarning() << val;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(val.toUtf8());


//    QVariantMap newUser;
//    newUser[ "Username" ] = "RandomUser4";
//    newUser[ "Password" ] = "1234567";
//    QJsonDocument jsonDoc = QJsonDocument::fromVariant( newUser );
    QNetworkRequest newUserRequest(QUrl("https://spyuser-65ed7-default-rtdb.firebaseio.com/User_Database.json"));
    newUserRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    m_networkManager->post(newUserRequest, jsonDoc.toJson());

}

DatabaseHandler::~DatabaseHandler()
{
    m_networkManager->deleteLater();
}

void DatabaseHandler::networkReplyReadyRead()
{
    qDebug() << m_networkReply->readAll();
    QByteArray response = m_networkReply->readAll();
    qDebug() << response;
    m_networkReply->deleteLater();

    parseResponse( response);
}

void DatabaseHandler::performAuthenticatedDatabaseCall()
{
    QString endPoint = "https://spyuser-65ed7-default-rtdb.firebaseio.com/User_Database.json?auth=" + m_idToken;
    m_networkReply = m_networkManager->get(QNetworkRequest(QUrl(endPoint)));
    connect(m_networkReply, &QNetworkReply::readyRead, this, &DatabaseHandler::networkReplyReadyRead);

}

void DatabaseHandler::performPOST(const QString &url, const QJsonDocument &payload)
{
    QNetworkRequest newRequest( (QUrl(url)) );
    newRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    m_networkReply = m_networkManager->post(newRequest, payload.toJson());
    connect(m_networkReply, &QNetworkReply::readyRead, this, &DatabaseHandler::networkReplyReadyRead);

}

void DatabaseHandler::parseResponse(const QByteArray &response)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson( response );
    if( jsonDocument.object().contains("error") )
    {
        qDebug() << "Error occured!" << response;
    }
    else if ( jsonDocument.object().contains("kind"))
    {
        QString idToken = jsonDocument.object().value("idToken").toString();
        //qDebug() << "Obtained user ID token: " << idToken;
        qDebug() << "User signed in Successfully!";
        m_idToken = idToken;
        emit userSignedIn();
    }
    else
    {
        qDebug() << "The response was: " << response;
    }
}

void DatabaseHandler::setAPIKey(const QString &apiKey)
{
    m_apiKey = apiKey;
}

void DatabaseHandler::signUserUp(const QString &emailAddress, const QString &password)
{
    QString signUpEndpoint = "https://identitytoolkit.googleapis.com/v1/accounts:signUp?key=" + m_apiKey;
    QVariantMap variantPayload;
    variantPayload["email"] = emailAddress;
    variantPayload["password"] = password;
    variantPayload["returnSecureToken"] = true;

    QJsonDocument jsonPayload = QJsonDocument::fromVariant( variantPayload);
    performPOST( signUpEndpoint, jsonPayload);

}

void DatabaseHandler::signUserIn(const QString &emailAddress, const QString &password)
{
    QString signInEndpoint = "https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=" + m_apiKey;
    QVariantMap variantPayload;
    variantPayload["email"] = emailAddress;
    variantPayload["password"] = password;
    variantPayload["returnSecureToken"] = true;

    QJsonDocument jsonPayload = QJsonDocument::fromVariant( variantPayload);
    performPOST( signInEndpoint, jsonPayload);

}
