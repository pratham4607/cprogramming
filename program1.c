/* contact_book.c
   Simple contact book (no file version) in C
   Features:
     - Add contact
     - Display all contacts
     - Search by name
     - Edit contact
     - Delete contact
     - Sort contacts by name
     - In-memory only (no file I/O)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CONTACTS 100
#define NAME_LEN 50
#define PHONE_LEN 20
#define EMAIL_LEN 50
#define ADDR_LEN 100

typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
    char address[ADDR_LEN];
    int used; // 0 = empty slot, 1 = occupied
} Contact;

Contact contacts[MAX_CONTACTS];

/* Utility: trim newline from fgets */
void trim_newline(char *s) {
    size_t len = strlen(s);
    if (len && s[len-1] == '\n') s[len-1] = '\0';
}

/* Utility: case-insensitive comparison for names */
int name_icmp(const char *a, const char *b) {
    for (; *a && *b; a++, b++) {
        char ca = tolower((unsigned char)*a);
        char cb = tolower((unsigned char)*b);
        if (ca < cb) return -1;
        if (ca > cb) return 1;
    }
    if (*a) return 1;
    if (*b) return -1;
    return 0;
}

/* Find first free index, or -1 if full */
int find_free_slot() {
    for (int i = 0; i < MAX_CONTACTS; ++i)
        if (!contacts[i].used) return i;
    return -1;
}

/* Add a contact */
void add_contact() {
    int idx = find_free_slot();
    if (idx == -1) {
        printf("Contact book is full (max %d contacts).\n", MAX_CONTACTS);
        return;
    }
    printf("Enter name: ");
    fgets(contacts[idx].name, NAME_LEN, stdin);
    trim_newline(contacts[idx].name);

    printf("Enter phone: ");
    fgets(contacts[idx].phone, PHONE_LEN, stdin);
    trim_newline(contacts[idx].phone);

    printf("Enter email: ");
    fgets(contacts[idx].email, EMAIL_LEN, stdin);
    trim_newline(contacts[idx].email);

    printf("Enter address: ");
    fgets(contacts[idx].address, ADDR_LEN, stdin);
    trim_newline(contacts[idx].address);

    contacts[idx].used = 1;
    printf("Contact added at index %d.\n", idx+1);
}

/* Display one contact */
void print_contact(int i) {
    printf("---------- Contact %d ----------\n", i+1);
    printf("Name   : %s\n", contacts[i].name);
    printf("Phone  : %s\n", contacts[i].phone);
    printf("Email  : %s\n", contacts[i].email);
    printf("Address: %s\n", contacts[i].address);
}

/* Display all contacts */
void list_contacts() {
    int found = 0;
    for (int i = 0; i < MAX_CONTACTS; ++i) {
        if (contacts[i].used) {
            print_contact(i);
            found = 1;
        }
    }
    if (!found) printf("No contacts to display.\n");
}

/* Search contacts by (partial) name (case-insensitive) */
void search_contact() {
    char key[NAME_LEN];
    printf("Enter name to search (partial OK): ");
    fgets(key, NAME_LEN, stdin);
    trim_newline(key);
    if (strlen(key) == 0) {
        printf("Empty search key.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < MAX_CONTACTS; ++i) {
        if (!contacts[i].used) continue;
        // case-insensitive substring search
        char name_lower[NAME_LEN], key_lower[NAME_LEN];
        for (int a = 0; contacts[i].name[a] && a < NAME_LEN-1; ++a) name_lower[a] = tolower((unsigned char)contacts[i].name[a]);
        name_lower[strlen(contacts[i].name)] = '\0';
        for (int b = 0; key[b] && b < NAME_LEN-1; ++b) key_lower[b] = tolower((unsigned char)key[b]);
        key_lower[strlen(key)] = '\0';
        if (strstr(name_lower, key_lower) != NULL) {
            print_contact(i);
            found = 1;
        }
    }
    if (!found) printf("No matching contacts found.\n");
}

/* Edit a contact (select by index after listing) */
void edit_contact() {
    list_contacts();
    printf("Enter contact index to edit (1..%d), or 0 to cancel: ", MAX_CONTACTS);
    int index;
    if (scanf("%d", &index) != 1) {
        while (getchar() != '\n'); // clear input
        printf("Invalid input.\n");
        return;
    }
    while (getchar() != '\n'); // consume newline
    if (index <= 0 || index > MAX_CONTACTS) { printf("Cancelled or invalid index.\n"); return; }
    int i = index - 1;
    if (!contacts[i].used) { printf("No contact at that index.\n"); return; }

    char buf[ADDR_LEN];

    printf("Editing contact #%d (leave blank to keep current)\n", index);
    printf("Current name: %s\nNew name: ", contacts[i].name);
    fgets(buf, NAME_LEN, stdin); trim_newline(buf);
    if (strlen(buf)) strncpy(contacts[i].name, buf, NAME_LEN);

    printf("Current phone: %s\nNew phone: ", contacts[i].phone);
    fgets(buf, PHONE_LEN, stdin); trim_newline(buf);
    if (strlen(buf)) strncpy(contacts[i].phone, buf, PHONE_LEN);

    printf("Current email: %s\nNew email: ", contacts[i].email);
    fgets(buf, EMAIL_LEN, stdin); trim_newline(buf);
    if (strlen(buf)) strncpy(contacts[i].email, buf, EMAIL_LEN);

    printf("Current address: %s\nNew address: ", contacts[i].address);
    fgets(buf, ADDR_LEN, stdin); trim_newline(buf);
    if (strlen(buf)) strncpy(contacts[i].address, buf, ADDR_LEN);

    printf("Contact updated.\n");
}

/* Delete a contact by index */
void delete_contact() {
    list_contacts();
    printf("Enter contact index to delete (1..%d), or 0 to cancel: ", MAX_CONTACTS);
    int index;
    if (scanf("%d", &index) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }
    while (getchar() != '\n');
    if (index <= 0 || index > MAX_CONTACTS) { printf("Cancelled or invalid index.\n"); return; }
    int i = index - 1;
    if (!contacts[i].used) { printf("No contact at that index.\n"); return; }

    printf("Are you sure you want to delete contact '%s'? (y/n): ", contacts[i].name);
    int c = getchar();
    while (getchar() != '\n');
    if (c == 'y' || c == 'Y') {
        contacts[i].used = 0; // simple deletion (slot becomes free)
        printf("Contact deleted.\n");
    } else {
        printf("Deletion cancelled.\n");
    }
}

/* Count contacts */
int count_contacts() {
    int cnt = 0;
    for (int i = 0; i < MAX_CONTACTS; ++i) if (contacts[i].used) ++cnt;
    return cnt;
}

/* Sort contacts in ascending order by name (simple stable insertion sort using used entries) */
void sort_contacts() {
    // build a temporary array of used contacts
    int n = count_contacts();
    if (n <= 1) { printf("Not enough contacts to sort.\n"); return; }

    Contact *temp = malloc(sizeof(Contact) * n);
    if (!temp) { printf("Memory allocation failed.\n"); return; }
    int k = 0;
    for (int i = 0; i < MAX_CONTACTS; ++i)
        if (contacts[i].used) temp[k++] = contacts[i];

    // insertion sort on temp by name (case-insensitive)
    for (int i = 1; i < n; ++i) {
        Contact keyc = temp[i];
        int j = i - 1;
        while (j >= 0 && name_icmp(temp[j].name, keyc.name) > 0) {
            temp[j+1] = temp[j];
            j--;
        }
        temp[j+1] = keyc;
    }

    // clear original and copy back sorted contacts into earliest slots
    for (int i = 0; i < MAX_CONTACTS; ++i) contacts[i].used = 0;
    for (int i = 0; i < n; ++i) {
        contacts[i] = temp[i];
        contacts[i].used = 1;
    }

    free(temp);
    printf("Contacts sorted by name.\n");
}

/* Show menu */
void show_menu() {
    printf("\n==== Contact Book ====\n");
    printf("1. Add contact\n");
    printf("2. List contacts\n");
    printf("3. Search contact by name\n");
    printf("4. Edit contact\n");
    printf("5. Delete contact\n");
    printf("6. Sort contacts by name\n");
    printf("7. Count contacts\n");
    printf("0. Exit\n");
    printf("----------------------\n");
    printf("Choose an option: ");
}

int main() {
    // initialize
    for (int i = 0; i < MAX_CONTACTS; ++i) contacts[i].used = 0;

    int choice;
    while (1) {
        show_menu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        while (getchar() != '\n'); // clear newline after number

        switch (choice) {
            case 1: add_contact(); break;
            case 2: list_contacts(); break;
            case 3: search_contact(); break;
            case 4: edit_contact(); break;
            case 5: delete_contact(); break;
            case 6: sort_contacts(); break;
            case 7: printf("Total contacts: %d\n", count_contacts()); break;
            case 0: printf("Exiting. Goodbye!\n"); exit(0);
            default: printf("Unknown option. Try again.\n"); break;
        }
    }

    return 0;
}
