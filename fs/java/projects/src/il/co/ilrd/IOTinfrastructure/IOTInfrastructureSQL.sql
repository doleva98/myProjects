CREATE DATABASE IF NOT EXISTS IOTInfrastructure;
USE IOTInfrastructure;
CREATE TABLE IF NOT EXISTS Companies(
    companyID INT,
    company_name VARCHAR(250),
    contactID INT,
    addressID INT,
    PRIMARY KEY(companyID)
);
CREATE TABLE IF NOT EXISTS Products(
    productID INT,
    productname VARCHAR(250),
    companyID INT,
    PRIMARY KEY(productID),
    FOREIGN KEY(companyID) REFERENCES Companies(companyID)
);
CREATE TABLE IF NOT EXISTS IOT(IOTID INT, serialNum INT, productID INT);
CREATE TABLE IF NOT EXISTS IOTLog(
    logNumber INT,
    IOTID INT,
    logDate DATE,
    logData VARCHAR(250),
    PRIMARY KEY(logNumber)
);
CREATE TABLE IF NOT EXISTS Adresses(
    addressID INT,
    zipcode INT,
    city VARCHAR(250),
    street VARCHAR(250),
    PRIMARY KEY(addressID)
);
CREATE TABLE IF NOT EXISTS Payments(
    payID INT,
    companyID INT,
    creditDetails VARCHAR(250),
    PRIMARY KEY(payID)
);
CREATE TABLE IF NOT EXISTS ContactPerson(
    contactID INT,
    companyID INT,
    phoneNumber INT,
    contactPersonName VARCHAR(250),
    email VARCHAR(250),
    PRIMARY KEY(contactID)
);