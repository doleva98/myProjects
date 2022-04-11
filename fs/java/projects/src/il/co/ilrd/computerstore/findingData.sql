USE computerStore;
/* 1
 SELECT modelID,
 procssorSpeed,
 HDspace
 FROM computer
 WHERE price < 500;
 2
 SELECT DISTINCT nameOfManfacturer
 FROM manufacturers
 INNER JOIN printers ON manufacturers.manufacturerID = printers.manufacturerID;
 3
 SELECT modelID,
 RAM,
 screenSize
 FROM computer
 WHERE price > 5000 
 AND isLaptop = 1;
 4
 SELECT printerID
 FROM printers
 WHERE isBlackAndWhite = '0';
 5  */
/* SELECT modelID,
 procssorSpeed,
 HDspace
 FROM computer
 WHERE (
 CDID = 12
 OR CDID = 24
 )
 AND (price < 600); 
 6*/
/* SELECT manufacturerID,
 procssorSpeed
 FROM computer
 JOIN computerAndManufacturer USING(modelID, vers)
 WHERE isLaptop = 1
 AND HDspace >= 10; 
 7*/
/* SELECT computer.modelID,
 computer.price
 FROM computer
 JOIN computerAndManufacturer USING(modelID, vers)
 JOIN manufacturers USING(manufacturerID)
 WHERE nameOfManfacturer = 'HP'
 UNION
 SELECT printerID,
 price
 FROM printers
 JOIN manufacturers USING (manufacturerID)
 WHERE nameOfManfacturer = 'HP'; 
 8 */
/* SELECT nameOfManfacturer
 FROM manufacturers
 WHERE manufacturerID IN (
 SELECT manufacturerID
 FROM computerAndManufacturer
 JOIN computer USING (modelID, vers)
 GROUP BY manufacturerID
 HAVING MAX(isLaptop) = 0
 ); */
/*9 
 SELECT computerAndManufacturer.manufacturerID
 FROM computer
 JOIN computerAndManufacturer USING(modelID, vers)
 where computer.procssorSpeed > 450;
 10 */
/* SELECT printerID,
 price
 FROM printers
 WHERE price IN (
 SELECT MAX(price)
 FROM printers
 );
 11 */
/* SELECT AVG(procssorSpeed) FROM computer;
 12 */
/* SELECT AVG(procssorSpeed)
 FROM computer
 WHERE isLaptop = 1
 AND price > 1000;
 13 */
/* SELECT AVG(computer.procssorSpeed)
 FROM computer
 JOIN computerAndManufacturer USING(modelID, vers)
 JOIN manufacturers ON manufacturers.manufacturerID = computerAndManufacturer.manufacturerID
 AND manufacturers.nameOfManfacturer = 'HP'; 
 14 */
/* SELECT manufacturerID
 FROM computerAndManufacturer
 GROUP BY modelID, manufacturerID
 HAVING MAX(vers) != MIN(vers); */
/*15
 SELECT HDspace
 FROM computer
 GROUP BY HDspace
 HAVING COUNT(*) >= 2;
 16 */
/* SELECT MAX(modelId) AS maxId,
 MIN(modelId) AS minId,
 RAM,
 procssorSpeed
 FROM computer
 GROUP BY RAM,
 procssorSpeed
 HAVING maxId != minId; */
/* 17 */
/* SELECT modelID
 FROM computer
 WHERE isLaptop = '1'
 AND procssorSpeed IN (
 SELECT MIN(procssorSpeed)
 FROM computer
 WHERE isLaptop = '0'
 );
 18 */
/* SELECT manufacturerID,
 price
 FROM printers
 WHERE isBlackAndWhite = '0'
 AND price IN (
 SELECT MIN(price)
 FROM printers
 WHERE isBlackAndWhite = '0'
 );
 19 */
SELECT manufacturerID,
    AVG(screenSize)
FROM computer
    JOIN computerAndManufacturer USING(modelID, vers)
WHERE manufacturerID IN (
        SELECT
    )