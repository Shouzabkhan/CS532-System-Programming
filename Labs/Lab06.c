#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1024
#define MAX_LISTINGS 22555

// Structure for the Listings.csv file
struct Listing {
    int id, host_id, minimum_nights, number_of_reviews, calculated_host_listings_count, availability_365;
    char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
    float latitude, longitude, price;
};

// Function to parse a CSV line into a struct Listing
struct Listing attribute(char *line) {
    struct Listing item;
    char *token;

    // Initialize item.id and parse other attributes
    token = strtok(line, ",");
    if (token == NULL) {
        // Handle error or return a default value
        // Example: memset(&item, 0, sizeof(struct Listing));
        return item;
    }
    item.id = atoi(token);

    token = strtok(NULL, ",");
    if (token == NULL) {
        // Handle error or return a default value
        // Example: memset(&item, 0, sizeof(struct Listing));
        return item;
    }
    item.host_id = atoi(token);

    token = strtok(NULL, ",");
    if (token == NULL) {
        // Handle error or return a default value
        // Example: memset(&item, 0, sizeof(struct Listing));
        return item;
    }
    item.host_name = strdup(token);

    // Continue parsing other fields similarly...

    return item;
}

// Function prototypes
void sortByHostName(struct Listing list[], int n);
void sortByPrice(struct Listing list[], int n);

int main() {
    struct Listing items[MAX_LISTINGS];
    char line[LINESIZE];
    int count = 0;

    FILE *fptr = fopen("listings.csv", "r");
    if (fptr == NULL) {
        printf("Error reading input file listings.csv\n");
        return 1;
    }

    // Read and parse each line
    while (fgets(line, LINESIZE, fptr) != NULL) {
        items[count++] = attribute(line);
    }
    fclose(fptr);

    // Sort by host_name
    sortByHostName(items, count);

    // Write sorted by host_name to file
    FILE *fp_by_name = fopen("sorted_by_name.csv", "w");
    if (fp_by_name == NULL) {
        printf("Error creating sorted_by_name.csv\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp_by_name, "%s,%.2f\n", items[i].host_name, items[i].price);
    }
    fclose(fp_by_name);

    // Sort by price
    sortByPrice(items, count);

    // Write sorted by price to file
    FILE *fp_by_price = fopen("sorted_by_price.csv", "w");
    if (fp_by_price == NULL) {
        printf("Error creating sorted_by_price.csv\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp_by_price, "%s,%.2f\n", items[i].host_name, items[i].price);
    }
    fclose(fp_by_price);

    return 0;
}

void sortByHostName(struct Listing list[], int n) {
    struct Listing temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(list[j].host_name, list[j + 1].host_name) > 0) {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

void sortByPrice(struct Listing list[], int n) {
    struct Listing temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (list[j].price > list[j + 1].price) {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}
