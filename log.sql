-- Keep a log of any SQL queries you execute as you solve the mystery.

-- [[SUSPECTS]]
-- | Danielle (cleared?) | Elizabeth (cleared?) | Russell (cleared?) | Ernest (prime)|

-- Looking through all crimes that occurred July 28, 2020 (07 28 2020)
SELECT id, description FROM crime_scene_reports WHERE year = 2020 AND month = 07 AND day = 28;

-- Duck theft id = [[295]] time = 10:15 AM
-- Three witnesses. All three mention [[courthoue]]

-- Looking through interviews on 07/28/2020 which mention courthouse
SELECT id, name, transcript FROM interviews WHERE transcript LIKE "%courthouse%" AND year = 2020 AND month = 07 AND day = 28;

-- id [[161]] name [[Ruth]] = Within 10 minutes of the theft, thief got into car and drove away. Check video [[within 10 minutes]] of the crime
-- id [[162]] name [[Eugene]] = On [[Fifer Street]] on the same day, thief withdrew money from an ATM earlier that morning before Eugene arrived
-- id [[163]] name [[Raymond]] = As they were leaving the courthouse, thief talked for less than a minute on the phone, spoke about taking flight tomorrow ASAP
--              The person who was on the other line was to purchase the tickets

-- Ruth's transcript queries ---------------------------------------------------------------------------------------------------------------

--  Looking through security logs from 10:15--10:25, checking for license plate number, exits only
SELECT license_plate FROM courthouse_security_logs WHERE activity = 'exit' AND year = 2020 AND month = 07 AND day = 28 AND hour = 10 AND (minute > 15 AND minute < 26);

-- Identify people through license plates
SELECT * FROM people WHERE license_plate = '5P2BI95'; SELECT * FROM people WHERE license_plate = '94KL13X'; SELECT * FROM people WHERE license_plate = '6P58WS2';
SELECT * FROM people WHERE license_plate = '4328GD8'; SELECT * FROM people WHERE license_plate = 'G412CB7'; SELECT * FROM people WHERE license_plate = 'L93JTIZ';
SELECT * FROM people WHERE license_plate = '322W7JE'; SELECT * FROM people WHERE license_plate = '0NTHK55';

-- License plate and additional info
--id | name | phone_number | passport_number | license_plate
-- 221103 | Patrick | (725) 555-4692 | 2963008352 | 5P2BI95
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
-- 243696 | Amber | (301) 555-4174 | 7526138472 | 6P58WS2
-- 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
-- 398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
-- 396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
-- 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
-- 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55

-- Ruth's transcript queries complete ------------------------------------------------------------------------------------------------------

-- Eugene's transcript queries -------------------------------------------------------------------------------------------------------------

-- Find out when Eugene arrived at the courthouse that day
SELECT * FROM courthouse_security_logs WHERE year = 2020 AND month = 07 AND day = 28 AND license_plate =
(SELECT license_plate FROM people WHERE name = 'Eugene');

-- Query provided no results. Eugene didn't drive to the courthosue that day?
-- Look up people who withdrew from an ATM that day on [[Fifer Street]]
SELECT * FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 07 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw'));

-- Cross-reference with license plates from Ruth's queries
-- id | name | phone_number | passport_number | license_plate
-- 395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
-- 396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ               !!! SUSPECT: Elizabeth
-- 438727 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0
-- 449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
-- 458378 | Roy | (122) 555-4581 | 4408372428 | QX4YZN3
-- 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8                !!! SUSPECT: Danielle
-- 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE                 !!! SUSPECT: Russell
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X                  !!! SUSPECT: Ernest
-- 948985 | Robert | (098) 555-1164 | 8304650265 | I449449

-- Eugene's transcript queries complete  ---------------------------------------------------------------------------------------------------

-- Raymond's transcript queries ------------------------------------------------------------------------------------------------------------

-- Check which of our suspects made or recieved a call that day, duration less than a minute
SELECT * FROM phone_calls WHERE year = 2020 AND month = 07 AND day = 28 AND duration < 60 AND
((caller = (SELECT phone_number FROM people WHERE name = 'Elizabeth'))
OR
(receiver = (SELECT phone_number FROM people WHERE name = 'Elizabeth')));

-- no results

SELECT * FROM phone_calls WHERE year = 2020 AND month = 07 AND day = 28 AND duration < 60 AND
((caller = (SELECT phone_number FROM people WHERE name = 'Danielle'))
OR
(receiver = (SELECT phone_number FROM people WHERE name = 'Danielle')));

-- no results

SELECT * FROM phone_calls WHERE year = 2020 AND month = 07 AND day = 28 AND duration < 60 AND
((caller = (SELECT phone_number FROM people WHERE name = 'Russell'))
OR
(receiver = (SELECT phone_number FROM people WHERE name = 'Russell')));

-- id | caller | receiver | year | month | day | duration
-- 255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49

-- receiver's phone number: [[(725) 555-3243]]

SELECT * FROM people WHERE name = 'Russell';
-- 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE

SELECT * FROM phone_calls WHERE year = 2020 AND month = 07 AND day = 28 AND duration < 60 AND
((caller = (SELECT phone_number FROM people WHERE name = 'Ernest'))
OR
(receiver = (SELECT phone_number FROM people WHERE name = 'Ernest')));

--id | caller | receiver | year | month | day | duration
-- 233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45

-- receiver's phone number: [[(375) 555-8161]]

SELECT * FROM people WHERE name = 'Ernest';
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

-- Check all flights that occurred 2020 07 29
SELECT * FROM flights WHERE year = 2020 AND month = 07 AND day = 29 ORDER BY hour, minute;

-- Earliest flight is scheduled for 8:20 AM

-- Check if either Russell or Ernest took a flight the following day
SELECT * FROM flights WHERE year = 2020 AND month = 07 AND day = 29 AND id =
(SELECT flight_id FROM passengers WHERE passport_number =
(SELECT passport_number FROM people WHERE name = 'Russell')) ORDER BY year, month, day, hour, minute;

-- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
-- 18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0

SELECT * FROM flights WHERE year = 2020 AND month = 07 AND day = 29 AND id =
(SELECT flight_id FROM passengers WHERE passport_number =
(SELECT passport_number FROM people WHERE name = 'Ernest')) ORDER BY year, month, day, hour, minute;

--id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
-- 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20                  !!! Earliest flight. Dest airport id = [[4]]

-- Raymond's transcript queries complete ---------------------------------------------------------------------------------------------------

-- Conclusions -----------------------------------------------------------------------------------------------------------------------------

-- Based on the following testimony:
-- 161 | Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
-- If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

-- 162 | Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse,
-- I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

-- 163 | Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call,
-- I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person
-- on the other end of the phone to purchase the flight ticket.

-- The thief left the courthouse sometime between 10:15 and 10:25
-- The thief withdrew money from an ATM on Fifer Street
-- The thief spoke to someone over the phone for less than a minute
-- The thief took the earliest flight the next day

-- Several license plates were recorded leaving the courthouse between 10:15 and 10:25
-- This list of people was cross-referenced with a similar list of people who withdrew money from the Fifer ATM that day
-- This list was further cross-referenced with a list of people who took the earliest flight out of Fiftyville

-- {Ernest is the thief}

-- Checking where Ernest escaped to
SELECT city FROM airports WHERE id = 4;

-- {Ernest escaped to London}

-- Checking who purchased tickets for Ernest
-- Checking who Ernest spoke to
SELECT * FROM people WHERE phone_number = '(375) 555-8161';

-- id | name | phone_number | passport_number | license_plate
-- 864400 | Berthold | (375) 555-8161 |  | 4V16VO0

-- {Berthold is his accomplice}