CREATE DATABASE IF NOT EXISTS computerStore;
USE computerStore;
CREATE TABLE IF NOT EXISTS computer(
    modelID INT,
    RAM INT,
    procssorSpeed INT,
    HDspace INT,
    CDID INT,
    screenSize INT,
    vers INT,
    price INT,
    isLaptop BOOL,
    PRIMARY KEY(modelID, vers)
);
CREATE TABLE IF NOT EXISTS manufacturers(
    manufacturerID INT,
    nameOfManfacturer VARCHAR(250),
    PRIMARY KEY(manufacturerID)
);
CREATE TABLE IF NOT EXISTS computerAndManufacturer(
    modelID INT,
    manufacturerID INT,
    vers INT,
    FOREIGN KEY (modelID, vers) REFERENCES computer(modelID, vers),
    FOREIGN KEY (manufacturerID) REFERENCES manufacturers(manufacturerID)
);
CREATE TABLE IF NOT EXISTS printers(
    printerID INT PRIMARY KEY,
    manufacturerID INT,
    isBlackAndWhite BOOL,
    price INT,
    FOREIGN KEY (manufacturerID) REFERENCES manufacturers(manufacturerID)
);