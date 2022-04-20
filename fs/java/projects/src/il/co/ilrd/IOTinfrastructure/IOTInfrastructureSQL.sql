CREATE DATABASE IF NOT EXISTS IOTInfrastructure;
USE IOTInfrastructure;
CREATE TABLE IF NOT EXISTS Adresses(
    addressID INT,
    zipcode INT NOT NULL,
    city VARCHAR(250) NOT NULL,
    street VARCHAR(250) NOT NULL,
    PRIMARY KEY(addressID)
);
CREATE TABLE IF NOT EXISTS ContactPerson(
    contactID INT,
    phoneNumber INT NOT NULL,
    contactPersonName VARCHAR(250) NOT NULL,
    email VARCHAR(250) NOT NULL,
    PRIMARY KEY(contactID)
);
CREATE TABLE IF NOT EXISTS Companies(
    companyID INT,
    company_name VARCHAR(250) NOT NULL,
    contactID INT NOT NULL,
    addressID INT NOT NULL,
    PRIMARY KEY(companyID),
    FOREIGN KEY(addressID) REFERENCES Adresses(addressID),
    FOREIGN KEY(contactID) REFERENCES ContactPerson(contactID)
);
CREATE TABLE IF NOT EXISTS Products(
    productID INT,
    productname VARCHAR(250) NOT NULL,
    companyID INT NOT NULL,
    PRIMARY KEY(productID),
    FOREIGN KEY(companyID) REFERENCES Companies(companyID)
);
CREATE TABLE IF NOT EXISTS IOT(
    IOTID INT,
    serialNum INT NOT NULL,
    productID INT NOT NULL,
    PRIMARY KEY(IOTID),
    FOREIGN KEY(productID) REFERENCES Products(productID)
);
CREATE TABLE IF NOT EXISTS IOTLog(
    logNumber INT,
    IOTID INT NOT NULL,
    logDate DATETIME DEFAULT CURRENT_TIMESTAMP,
    logData VARCHAR(250) NOT NULL,
    PRIMARY KEY(logNumber),
    FOREIGN KEY(IOTID) REFERENCES IOT(IOTID)
);
CREATE TABLE IF NOT EXISTS Payments(
    payID INT,
    companyID INT NOT NULL,
    creditDetails VARCHAR(250) NOT NULL,
    PRIMARY KEY(payID),
    FOREIGN KEY(companyID) REFERENCES Companies(companyID)
);