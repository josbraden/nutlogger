-- MySQL dump 10.17  Distrib 10.3.25-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: ups
-- ------------------------------------------------------
-- Server version	10.3.25-MariaDB-0ubuntu0.20.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `devices`
--

DROP TABLE IF EXISTS `devices`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `devices` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nut_name` varchar(64) NOT NULL,
  `time_added` datetime NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`id`),
  UNIQUE KEY `nut_name` (`nut_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `devices`
--

LOCK TABLES `devices` WRITE;
/*!40000 ALTER TABLE `devices` DISABLE KEYS */;
/*!40000 ALTER TABLE `devices` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `devices_extradata`
--

DROP TABLE IF EXISTS `devices_extradata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `devices_extradata` (
  `devices_id` int(11) NOT NULL,
  `battery_charge_low` int(11) DEFAULT NULL,
  `battery_charge_warning` int(11) DEFAULT NULL,
  `battery_mfr_date` varchar(64) DEFAULT NULL,
  `battery_runtime_low` int(11) DEFAULT NULL,
  `battery_type` varchar(64) DEFAULT NULL,
  `battery_voltage_nominal` float DEFAULT NULL,
  `device_mfr` varchar(64) DEFAULT NULL,
  `device_model` varchar(64) DEFAULT NULL,
  `device_serial` varchar(64) DEFAULT NULL,
  `device_type` varchar(64) DEFAULT NULL,
  `driver_name` varchar(64) DEFAULT NULL,
  `driver_version` varchar(64) DEFAULT NULL,
  `driver_version_data` varchar(64) DEFAULT NULL,
  `driver_version_internal` varchar(64) DEFAULT NULL,
  `input_voltage_nominal` float DEFAULT NULL,
  `ups_beeper_status` varchar(64) DEFAULT NULL,
  `ups_delay_shutdown` int(11) DEFAULT NULL,
  `ups_delay_start` int(11) DEFAULT NULL,
  `ups_mfr` varchar(64) DEFAULT NULL,
  `ups_model` varchar(64) DEFAULT NULL,
  `ups_productid` varchar(64) DEFAULT NULL,
  `ups_realpower_nominal` int(11) DEFAULT NULL,
  `ups_serial` varchar(64) DEFAULT NULL,
  `ups_test_result` varchar(64) DEFAULT NULL,
  `ups_timer_shutdown` int(11) DEFAULT NULL,
  `ups_timer_start` int(11) DEFAULT NULL,
  `ups_vendorid` int(11) DEFAULT NULL,
  UNIQUE KEY `devices_id` (`devices_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `devices_extradata`
--

LOCK TABLES `devices_extradata` WRITE;
/*!40000 ALTER TABLE `devices_extradata` DISABLE KEYS */;
/*!40000 ALTER TABLE `devices_extradata` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `events`
--

DROP TABLE IF EXISTS `events`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `events` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `devices_id` int(11) NOT NULL,
  `time` datetime NOT NULL DEFAULT current_timestamp(),
  `battery_charge` int(11) NOT NULL,
  `battery_runtime` int(11) NOT NULL,
  `battery_voltage` float NOT NULL,
  `input_voltage` float NOT NULL,
  `output_voltage` float NOT NULL,
  `ups_load` int(11) NOT NULL,
  `ups_status` varchar(8) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `events`
--

LOCK TABLES `events` WRITE;
/*!40000 ALTER TABLE `events` DISABLE KEYS */;
/*!40000 ALTER TABLE `events` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `upslog`
--

DROP TABLE IF EXISTS `upslog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `upslog` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `devices_id` int(11) NOT NULL,
  `time` datetime NOT NULL DEFAULT current_timestamp(),
  `battery_charge` int(11) NOT NULL,
  `battery_runtime` int(11) NOT NULL,
  `battery_voltage` float NOT NULL,
  `input_voltage` float NOT NULL,
  `output_voltage` float NOT NULL,
  `ups_load` int(11) NOT NULL,
  `ups_status` varchar(8) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `upslog`
--

LOCK TABLES `upslog` WRITE;
/*!40000 ALTER TABLE `upslog` DISABLE KEYS */;
/*!40000 ALTER TABLE `upslog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `upslog_archive`
--

DROP TABLE IF EXISTS `upslog_archive`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `upslog_archive` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `devices_id` int(11) NOT NULL,
  `time` datetime NOT NULL DEFAULT current_timestamp(),
  `battery_charge` int(11) NOT NULL,
  `battery_runtime` int(11) NOT NULL,
  `battery_voltage` float NOT NULL,
  `input_voltage` float NOT NULL,
  `output_voltage` float NOT NULL,
  `ups_load` int(11) NOT NULL,
  `ups_status` varchar(8) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 ROW_FORMAT=COMPRESSED;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `upslog_archive`
--

LOCK TABLES `upslog_archive` WRITE;
/*!40000 ALTER TABLE `upslog_archive` DISABLE KEYS */;
/*!40000 ALTER TABLE `upslog_archive` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-04-29 11:24:18
