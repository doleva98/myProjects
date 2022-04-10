USE computerStore;
-- INSERT INTO computer (
--         modelID,
--         RAM,
--         procssorSpeed,
--         HDspace,
--         CDID,
--         screenSize,
--         vers,
--         price,
--         isLaptop
--     )
-- VALUES (
--         132123,
--         600,
--         303,
--         500,
--         43,
--         0,
--         1,
--         5001,
--         '0'
--     );

INSERT INTO manufacturers (manufacturerID, nameOfManfacturer)
VALUES (
    1,
    'TUSHIBA'
  );

INSERT INTO printers (printerID, manufacturerID, isBlackAndWhite)
VALUES (
    435432,
    56,
    '0'
  );