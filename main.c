#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[20];
    char email[50];
    struct Contact *next;
};

struct Contact *head = NULL;

// ADD NEW CONTACT
void addContact() {
    struct Contact *newContact = (struct Contact *)malloc(sizeof(struct Contact));

    printf("Enter Name: ");
    scanf("%s", newContact->name);
    printf("Enter Phone: ");
    scanf("%s", newContact->phone);
    printf("Enter Email: ");
    scanf("%s", newContact->email);

    newContact->next = NULL;

    if (head == NULL) {
        head = newContact;
    } else {
        struct Contact *temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newContact;
    }

    printf("\nContact Added Successfully!\n");
}

// DISPLAY ALL CONTACTS
void displayContacts() {
    if (head == NULL) {
        printf("\nNo contacts found.\n");
        return;
    }

    struct Contact *temp = head;
    printf("\n--- Contact List ---\n");
    while (temp != NULL) {
        printf("Name: %s\nPhone: %s\nEmail: %s\n\n",
               temp->name, temp->phone, temp->email);
        temp = temp->next;
    }
}

// SEARCH CONTACT BY NAME
void searchContact() {
    char name[50];
    printf("Enter name to search: ");
    scanf("%s", name);

    struct Contact *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("\nContact Found:\n");
            printf("Name: %s\nPhone: %s\nEmail: %s\n",
                   temp->name, temp->phone, temp->email);
            return;
        }
        temp = temp->next;
    }

    printf("\nContact Not Found!\n");
}

// DELETE CONTACT
void deleteContact() {
    char name[50];
    printf("Enter name to delete: ");
    scanf("%s", name);

    struct Contact *temp = head, *prev = NULL;

    while (temp != NULL && strcmp(temp->name, name) == 0) {
        head = temp->next;
        free(temp);
        printf("\nContact Deleted!\n");
        return;
    }

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nContact Not Found!\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("\nContact Deleted!\n");
}

// SAVE CONTACTS TO FILE
void saveToFile() {
    FILE *fp = fopen("contacts.txt", "w");
    if (!fp) return;

    struct Contact *temp = head;
    while (temp != NULL) {
        fprintf(fp, "%s|%s|%s\n", temp->name, temp->phone, temp->email);
        temp = temp->next;
    }
    fclose(fp);
}

// LOAD FROM FILE
void loadFromFile() {
    FILE *fp = fopen("contacts.txt", "r");
    if (!fp) return;

    char line[200];

    while (fgets(line, sizeof(line), fp)) {
        struct Contact *newContact = (struct Contact *)malloc(sizeof(struct Contact));
        sscanf(line, "%[^|]|%[^|]|%[^\n]",
               newContact->name, newContact->phone, newContact->email);

        newContact->next = NULL;

        if (head == NULL) {
            head = newContact;
        } else {
            struct Contact *temp = head;
            while (temp->next != NULL) temp = temp->next;
            temp->next = newContact;
        }
    }

    fclose(fp);
}

// MAIN PROGRAM
int main() {
    int choice;

    loadFromFile();

    while (1) {
        printf("\n--- Contact Book ---\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: displayContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5:
                saveToFile();
                printf("Contacts Saved. Exiting...\n");
                exit(0);
            default: printf("Invalid Choice!\n");
        }
    }

    return 0;
}