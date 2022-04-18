CREATE DATABASE IF NOT EXISTS IOTInfrastructure;
USE IOTInfrastructure;
CREATE TABLE IF NOT EXISTS Companies(
    companyID INT,
    company_name VARCHAR(250),
    contactID INT,
    addressID INT,
    PRIMARY KEY(companyID),
    FOREIGN KEY(addressID) REFERENCES Adresses(addressID)
);
CREATE TABLE IF NOT EXISTS Products(
    productID INT,
    productname VARCHAR(250),
    companyID INT,
    PRIMARY KEY(productID),
    FOREIGN KEY(companyID) REFERENCES Companies(companyID)
);
CREATE TABLE IF NOT EXISTS IOT(
    IOTID INT,
    serialNum INT,
    productID INT,
    FOREIGN KEY(productID) REFERENCES Products(productID)
);
CREATE TABLE IF NOT EXISTS IOTLog(
    logNumber INT,
    IOTID INT,
    logDate DATE,
    logData VARCHAR(250),
    PRIMARY KEY(logNumber),
    FOREIGN KEY(IOTID) REFERENCES IOT(IOTID)
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
    PRIMARY KEY(payID),
    FOREIGN KEY(companyID) REFERENCES Companies(companyID)
);
CREATE TABLE IF NOT EXISTS ContactPerson(
    contactID INT,
    companyID INT,
    phoneNumber INT,
    contactPersonName VARCHAR(250),
    email VARCHAR(250),
    PRIMARY KEY(contactID),
    FOREIGN KEY(contactID, companyID) REFERENCES Companies(contactID, companyID)
);