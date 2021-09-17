-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Getting basic Information on the case
SELECT * FROM crime_scene_reports
WHERE
year = 2020 AND
month = 7 AND
day = 28 AND
street = "Chamberlin Street";
-- Knowledge Gained: Case ID = 295
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

-- Finding witness interview
SELECT * FROM interviews
WHERE
year = 2020 AND
month = 7 AND
day = 28 AND
transcript LIKE "%courthouse%";
-- Knowldge Gained: IDs of 3 witnesses (161, 162, 163) and their testimonies - Below

-- 161:  Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
-- If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- 162:  I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse,
-- I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- 163:  As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say
-- that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Hoping to Find llicense plate of the crimnal
SELECT license_plate FROM courthouse_security_logs
WHERE
year = 2020 AND
month = 7 AND
day = 28 AND
hour = 10 AND
minute BETWEEN 15 and 26 AND
activity = "exit";
-- Possible liscence plates :
--(5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55)

-- Looking at phone calls < 60s
SELECT caller FROM phone_calls
WHERE
month = 7 AND
day = 28 AND
duration < 90;

-- Checking how many possible suspects remain
SELECT * FROM people
WHERE phone_number IN
(SELECT caller FROM phone_calls
WHERE
month = 7 AND
day = 28 AND
duration < 90) AND
license_plate IN
(
SELECT license_plate FROM courthouse_security_logs
WHERE
year = 2020 AND
month = 7 AND
day = 28 AND
hour = 10 AND
minute BETWEEN 15 and 26 AND
activity = "exit"
);
-- 4 SUSPECTS REMAIN
-- ROGER (ID 398010, PASSPORT 1695452385)
-- RUSSELL (ID 514354, PASSPORT 3592750733)
-- EVELYN (ID 560886, PASSPORT 8294398571)
-- ERNEST (ID 686048, PASSPORT 5773159633)
    -- SIDE NOTE: Anyone with the name Ernest sketches me out, my money is on him

-- Looking to see if atm_transactions has any useful info
SELECT people.id FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE
year = 2020 AND
month = 7 AND
day = 28 AND
atm_location = "Fifer Street";

-- PEOPLE REMAINING
-- RUSSELL (ID 514354, PASSPORT 3592750733)
-- ERNEST (ID 686048, PASSPORT 5773159633)
-- NOTE: I did do a larger query to prove this, not manually filtration,
-- but the code is longer, and this gets the point accross
-- PS: It's definatly my boy Ernest

SELECT id FROM airports
WHERE full_name LIKE "%fiftyville%";
-- Fiftyville is airport ID 8

-- Getting information on Flights leaving the Ville the next day
SELECT * FROM flights
WHERE
origin_airport_id = 8 AND
year = 2020 AND
month = 7 AND
day = 29
ORDER BY hour;

SELECT name, full_name FROM passengers
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.destination_airport_id = airports.id
JOIN people ON passengers.passport_number = people.passport_number
WHERE
-- Planes leaving from the ville
origin_airport_id = 8 AND
-- Day after crime
year = 2020 AND
month = 7 AND
day = 29 AND
-- Passport numbers of remaining suspects
passengers.passport_number IN (3592750733, 5773159633)
-- The theif left "First thing in the morning"
ORDER BY HOUR;
-- THE THEIF LEFT FIFTYVILL THE NEXT DAY TO LONDON "HEATHROW AIRPORT"
-- Ernest (I was right) left to Heathrow Airport

-- The accomplice was whoever Ernest called before the crim
SELECT name FROM people
WHERE phone_number = (
SELECT receiver FROM phone_calls
WHERE
month = 7 AND
day = 28 AND
caller = "(367) 555-5533"
);
-- The accomplice is Berthold