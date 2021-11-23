#include "databasehandler.h"
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QVariantMap>

DatabaseHandler::DatabaseHandler(QObject *parent) : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);

    // read data from firebase using get command
    m_networkReply = m_networkManager->get(QNetworkRequest(QUrl("https://spyuser-65ed7-default-rtdb.firebaseio.com/User_Database.json")));
    connect(m_networkReply, &QNetworkReply::readyRead, this, &DatabaseHandler::networkReplyReadyRead);




    // post data to firebase using post command
    QVariantMap newUser;
    newUser[ "Username" ] = "RandomUser3";
    newUser[ "Password" ] = "1234567";
    QJsonDocument jsonDoc = QJsonDocument::fromVariant( newUser);

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
}
