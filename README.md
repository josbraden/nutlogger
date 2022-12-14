# nutlogger

Nut (Network UPS Tools) client to log info to a MySQL database

## Requirements

To build you'll need

- g++
- GNU make
- libboost
- libmysqlcppconn
- libmysqlclient
- libnutclient-dev

On Ubuntu/Debian you can run: `apt install make g++ libboost-dev libmysqlcppconn-dev libmysqlclient-dev libnutclient-dev`

Update: on my raspbian bullseye raspberry pi I had to also install libmysql++-dev to compile

## Getting Started

1. Create a database on your MySQL/Mariadb server and a user and password
2. Import the database schema SQL file with something similar to this: `mysql -u username -p ups < ups.sql`
3. Copy the example config file from nutlogger-example.cnf to nutlogger.cnf and change variables to fit your environment
4. Run nutlogger executable

See nutlogger.cron for an example to automatically launch the executable

## Database Schema

- Tables
  - devices
    - Hold essential device info (name)
  - devices_extradata
    - Holds device extra data fields
  - upslog
    - Has log of recent UPS usage metrics
  - upslog_archive
    - Same as upslog, hold rotated data on compressed rows

### Database Log Rotation

This query is used to rotate logs older than one day into the archive table

```
INSERT INTO upslog_archive (SELECT * FROM upslog WHERE timestamp < NOW() - INTERVAL 1 DAY);
DELETE FROM upslog WHERE id IN (SELECT id FROM upslog_archive);
```
