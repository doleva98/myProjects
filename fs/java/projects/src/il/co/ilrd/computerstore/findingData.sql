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
/* SELECT manufacturerID,
 AVG(screenSize)
 FROM computer
 JOIN computerAndManufacturer USING(modelID, vers)
 WHERE isLaptop = '1'
 GROUP BY manufacturerID; */
/* 20 */
/* SELECT manufacturerID
 FROM manufacturers
 WHERE manufacturerID IN (
 SELECT manufacturerID
 FROM computerAndManufacturer
 GROUP BY manufacturerID
 HAVING COUNT(DISTINCT modelID) >= 3
 );
 21 */
/* SELECT computerAndManufacturer.manufacturerID
 FROM computer c
 JOIN computerAndManufacturer cm USING (modelId, vers)
 JOIN (
 SELECT manufacturerID,
 MAX(price) AS price
 FROM computer
 JOIN computerAndManufacturer USING (modelId, vers)
 WHERE isLaptop = FALSE
 GROUP BY manufacturerID
 ) t_maxPrices ON cm.manufacturerID = t_maxPrices.manufacturerID
 WHERE c.price = t_maxPrices.price; 
 22*/
/* SELECT procssorSpeed,
 AVG(price)
 FROM computer
 WHERE procssorSpeed > 0.6
 AND isLaptop = FALSE
 GROUP BY procssorSpeed;
 23 */
SELECT *
FROM manufacturers
WHERE manufacturerID IN (
        SELECT t.manufacturerId
        FROM (
                SELECT cm.manufacturerId,
                    c.isLaptop
                FROM compsAndManu cm
                    JOIN computers c USING (modelId, cVersion)
                GROUP BY cm.manufacturerId,
                    c.isLaptop
                HAVING MAX(c.processorSpeed) >= 0.75
            ) as t
        GROUP BY t.manufacturerId
        HAVING COUNT(isLaptop) = 2
    );
/* 24
 SELECT *
 FROM manufacturers
 WHERE manufacturerId IN (
 SELECT manufacturerId
 FROM (
 SELECT manufacturerId
 FROM manufacturers
 JOIN printers USING (manufacturerId)
 ) t_also_make_printers
 WHERE manufacturerId IN (
 SELECT manufacturerId
 FROM compsAndManu cm
 JOIN computers c USING (modelId, cVersion)
 WHERE processorSpeed = (
 SELECT MAX(processorSpeed)
 FROM (
 SELECT processorSpeed
 FROM computers
 WHERE ram = (
 SELECT MIN(ram)
 FROM computers
 )
 ) t_min_rams
 )
 )
 );
 25
 SELECT SUM(price) / COUNT(price) as avg
 FROM (
 SELECT manufacturerId,
 price
 FROM printers p
 JOIN manufacturers m USING (manufacturerId)
 WHERE m.manufacturerName = 'LG'
 UNION
 SELECT manufacturerId,
 price
 FROM compsAndManu
 JOIN manufacturers m USING (manufacturerId)
 JOIN computers c USING (modelId, cVersion)
 WHERE m.manufacturerName = 'LG'
 AND c.isLaptop = FALSE
 ) as t
 GROUP BY manufacturerId;
 26
 SELECT filtered_manufacturers.*,
 AVG(hardDiscCapacity)
 FROM (
 SELECT m.*
 FROM manufacturers m
 JOIN printers USING (manufacturerId)
 GROUP BY manufacturerId
 ) as filtered_manufacturers
 JOIN compsAndManu USING (manufacturerId)
 JOIN computers USING (modelId, cVersion)
 WHERE isLaptop = FALSE
 GROUP BY manufacturerId;
 27
 SELECT modelId,
 cVersion,
 isLaptop,
 screenSize,
 ram,
 processorSpeed,
 hardDiscCapacity,
 cdDriverId,
 price
 FROM (
 SELECT modelId as 'origin modelID',
 modelId + 1000 as new_modelId,
 MIN(cVersion) + 20 as new_cVersion,
 -- isLaptop,     -- screenSize,     -- ram,     -- processorSpeed,     -- hardDiscCapacity,     -- cdDriverId,     -- price   
 FROM computers
 WHERE isLaptop = TRUE
 GROUP BY modelId
 );
 28
 DELETE FROM computers
 WHERE hardDiscCapacity = (
 SELECT *
 FROM (
 SELECT MIN(hardDiscCapacity)
 FROM computers
 ) t1
 )
 OR ram = (
 SELECT *
 FROM (
 SELECT MIN(ram)
 FROM computers
 ) t2
 );
 */