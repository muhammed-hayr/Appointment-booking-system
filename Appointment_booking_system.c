#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATIENTS 100
#define MAX_TRIES 3
#define PASSWORD "1234"

// Struct to store patient information
typedef struct {
    char name[50];
    int age;
    char gender[10];
    int id;
} Patient;

// Struct to store reservation information
typedef struct {
    int id;
    char slot[20];
} Reservation;

Patient patients[MAX_PATIENTS];
Reservation reservations[5];
int patientCount = 0;

// Initializes the reservation slots with default times and sets IDs to -1 indicating they are available
void initReservations() {
    strcpy(reservations[0].slot, "2pm to 2:30pm");
    strcpy(reservations[1].slot, "2:30pm to 3pm");
    strcpy(reservations[2].slot, "3pm to 3:30pm");
    strcpy(reservations[3].slot, "4pm to 4:30pm");
    strcpy(reservations[4].slot, "4:30pm to 5pm");
    for(int i = 0; i < 5; i++) {
        reservations[i].id = -1;
    }
}

// Finds a patient by their ID and returns the index in the patients array, or -1 if not found
int findPatientByID(int id) {
    for(int i = 0; i < patientCount; i++) {
        if(patients[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Adds a new patient record to the system
void addPatient() {
    if(patientCount >= MAX_PATIENTS) {
        printf("Patient list is full!\n");
        return;
    }

    Patient newPatient;
    printf("Enter name: ");
    scanf("%s", newPatient.name);
    printf("Enter age: ");
    scanf("%d", &newPatient.age);
    printf("Enter gender: ");
    scanf("%s", newPatient.gender);
    printf("Enter ID: ");
    scanf("%d", &newPatient.id);

    if(findPatientByID(newPatient.id) != -1) {
        printf("ID already exists. Entry rejected.\n");
        return;
    }

    patients[patientCount++] = newPatient;
    printf("Patient added successfully!\n");
}

// Edits an existing patient's information based on their ID
void editPatient() {
    int id;
    printf("Enter patient ID to edit: ");
    scanf("%d", &id);
    int index = findPatientByID(id);
    if(index == -1) {
        printf("Incorrect ID. Patient not found.\n");
        return;
    }

    printf("Enter new name: ");
    scanf("%s", patients[index].name);
    printf("Enter new age: ");
    scanf("%d", &patients[index].age);
    printf("Enter new gender: ");
    scanf("%s", patients[index].gender);
    printf("Patient record updated successfully!\n");
}

// Reserves a slot with the doctor for a patient
void reserveSlot() {
    printf("Available slots:\n");
    for(int i = 0; i < 5; i++) {
        if(reservations[i].id == -1) {
            printf("%d. %s\n", i+1, reservations[i].slot);
        }
    }

    int slotNum;
    printf("Enter desired slot number: ");
    scanf("%d", &slotNum);
    if(slotNum < 1 || slotNum > 5 || reservations[slotNum-1].id != -1) {
        printf("Invalid slot number or slot already reserved.\n");
        return;
    }

    int id;
    printf("Enter patient ID: ");
    scanf("%d", &id);
    if(findPatientByID(id) == -1) {
        printf("Incorrect ID. Patient not found.\n");
        return;
    }

    reservations[slotNum-1].id = id;
    printf("Slot reserved successfully!\n");
}

// Cancels a reservation for a patient based on their ID
void cancelReservation() {
    int id;
    printf("Enter patient ID to cancel reservation: ");
    scanf("%d", &id);
    for(int i = 0; i < 5; i++) {
        if(reservations[i].id == id) {
            reservations[i].id = -1;
            printf("Reservation canceled successfully!\n");
            return;
        }
    }
    printf("No reservation found for the given ID.\n");
}

// Views the record of a specific patient based on their ID
void viewPatientRecord() {
    int id;
    printf("Enter patient ID to view record: ");
    scanf("%d", &id);
    int index = findPatientByID(id);
    if(index == -1) {
        printf("Incorrect ID. Patient not found.\n");
        return;
    }

    printf("Name: %s\n", patients[index].name);
    printf("Age: %d\n", patients[index].age);
    printf("Gender: %s\n", patients[index].gender);
    printf("ID: %d\n", patients[index].id);
}

// Views all reservations for the day, listing the patient ID for each reserved slot
void viewReservations() {
    printf("Today's reservations:\n");
    for(int i = 0; i < 5; i++) {
        if(reservations[i].id != -1) {
            printf("%s - Patient ID: %d\n", reservations[i].slot, reservations[i].id);
        }
    }
}

// Handles admin mode functionality, including password protection
void adminMode() {
    char password[20];
    int tries = 0;

    while(tries < MAX_TRIES) {
        printf("Enter admin password: ");
        scanf("%s", password);
        if(strcmp(password, PASSWORD) == 0) {
            int choice;
            do {
                printf("\nAdmin Menu:\n");
                printf("1. Add new patient record\n");
                printf("2. Edit patient record\n");
                printf("3. Reserve a slot with the doctor\n");
                printf("4. Cancel reservation\n");
                printf("5. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                switch(choice) {
                    case 1: addPatient(); break;
                    case 2: editPatient(); break;
                    case 3: reserveSlot(); break;
                    case 4: cancelReservation(); break;
                    case 5: printf("Exiting admin mode...\n"); break;
                    default: printf("Invalid choice. Try again.\n");
                }
            } while(choice != 5);
            return;
        } else {
            printf("Incorrect password. Try again.\n");
            tries++;
        }
    }

    printf("Too many incorrect attempts. System closing.\n");
    exit(0);
}

// Handles user mode functionality
void userMode() {
    int choice;
    do {
        printf("\nUser Menu:\n");
        printf("1. View patient record\n");
        printf("2. View today's reservations\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: viewPatientRecord(); break;
            case 2: viewReservations(); break;
            case 3: printf("Exiting user mode...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while(choice != 3);
}

// Main function to start the program and handle mode selection
int main() {
    initReservations();
    int mode;
    printf("Welcome to the Clinic Management System\n");
    printf("1. Admin mode\n");
    printf("2. User mode\n");
    printf("Enter mode: ");
    scanf("%d", &mode);
    switch(mode) {
        case 1: adminMode(); break;
        case 2: userMode(); break;
        default: printf("Invalid mode. Exiting...\n");
    }
    return 0;
}
