USE computerStore;
INSERT IGNORE INTO computer (
        modelID,
        RAM,
        procssorSpeed,
        HDspace,
        CDID,
        screenSize,
        vers,
        price,
        isLaptop
    )
VALUES (
        0,
        8000,
        500,
        1000,
        0,
        18,
        0,
        1500,
        '1'
    );
INSERT IGNORE INTO computer (
        modelID,
        RAM,
        procssorSpeed,
        HDspace,
        CDID,
        screenSize,
        vers,
        price,
        isLaptop
    )
VALUES (
        0,
        8000,
        500,
        1500,
        0,
        18,
        1,
        1500,
        '1'
    );
INSERT IGNORE INTO computer (
        modelID,
        RAM,
        procssorSpeed,
        HDspace,
        CDID,
        screenSize,
        vers,
        price,
        isLaptop
    )
VALUES (
        1,
        8000,
        500,
        1500,
        900,
        0,
        0,
        1500,
        '0'
    );
INSERT IGNORE INTO manufacturers (manufacturerID, nameOfManfacturer)
VALUES (0, 'HP');
INSERT IGNORE INTO manufacturers (manufacturerID, nameOfManfacturer)
VALUES (1, 'Tushiba');
INSERT IGNORE INTO computerAndManufacturer (modelID, manufacturerID, vers)
VALUES (0, 0, 0);
INSERT IGNORE INTO computerAndManufacturer (modelID, manufacturerID, vers)
VALUES (0, 0, 1);
INSERT IGNORE INTO computerAndManufacturer (modelID, manufacturerID, vers)
VALUES (1, 1, 0);
INSERT IGNORE INTO printers (
        printerID,
        manufacturerID,
        isBlackAndWhite,
        price
    )
VALUES (0, 0, '0', 5000);
INSERT IGNORE INTO printers (
        printerID,
        manufacturerID,
        isBlackAndWhite,
        price
    )
VALUES (1, 1, '1', 10000);