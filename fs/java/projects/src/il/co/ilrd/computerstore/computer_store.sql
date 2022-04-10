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
    computerID INT,
    PRIMARY KEY(computerID)
);
CREATE TABLE IF NOT EXISTS manufacturers(
    manufacturerID INT,
    nameOfManfacturer VARCHAR(250),
    PRIMARY KEY(manufacturerID)
);
CREATE TABLE IF NOT EXISTS computerAndManufacturer(
    computerID INT,
    manufacturerID INT,
    FOREIGN KEY (computerID) REFERENCES computer(computerID),
    FOREIGN KEY (manufacturerID) REFERENCES manufacturers(manufacturerID)
);
CREATE TABLE IF NOT EXISTS printers(
    printerID INT PRIMARY KEY,
    manufacturerID INT,
    isBlackAndWhite BOOL,
    FOREIGN KEY (manufacturerID) REFERENCES manufacturers(manufacturerID)
);