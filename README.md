# Clinic Management System

This is a simple Clinic Management System implemented in C. The system provides two modes: admin mode and user mode, each with different functionalities.

## Features

### Admin Mode
- **Password Protected**: Requires a password to access. The default password is `1234`. The system allows 3 attempts for the password entry. If the entered password is incorrect for 3 consecutive times, the system will close.
- **Add New Patient Record**: Admin can add new patient records including name, age, gender, and unique ID.
- **Edit Patient Record**: Admin can edit existing patient records by entering the patient's ID.
- **Reserve a Slot with the Doctor**: Admin can reserve a slot with the doctor for a patient. Available slots are from 2pm to 5pm in half-hour intervals.
- **Cancel Reservation**: Admin can cancel an existing reservation by entering the patient's ID.

### User Mode
- **View Patient Record**: Users can view patient records by entering the patient ID.
- **View Today's Reservations**: Users can view all reservations for the day along with the patient IDs.

## Getting Started

### Prerequisites
- GCC Compiler
- Make sure to have a C development environment set up on your machine.


