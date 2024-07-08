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
    item.id = atoi(token);

    token = strtok(NULL, ",");
    item.host_id = atoi(token);

    token = strtok(NULL, ",");
    item.host_name = strdup(token);

    token = strtok(NULL, ",");
    item.neighbourhood_group = strdup(token);

    token = strtok(NULL, ",");
    item.neighbourhood = strdup(token);

    token = strtok(NULL, ",");
    item.latitude = atof(token);

    token = strtok(NULL, ",");
    item.longitude = atof(token);

    token = strtok(NULL, ",");
    item.room_type = strdup(token);

    token = strtok(NULL, ",");
    item.price = atof(token);

    token = strtok(NULL, ",");
    item.minimum_nights = atoi(token);

    token = strtok(NULL, ",");
    item.number_of_reviews = atoi(token);

    token = strtok(NULL, ",");
    item.calculated_host_listings_count = atoi(token);

    token = strtok(NULL, ",");
    item.availability_365 = atoi(token);

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

    // Read and skip the header line
    if (fgets(line, LINESIZE, fptr) == NULL) {
        printf("Error reading header line from listings.csv\n");
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

    // Write header
    fprintf(fp_by_name, "id,host_id,host_name,neighbourhood_group,neighbourhood,latitude,longitude,room_type,price,minimum_nights,number_of_reviews,calculated_host_listings_count,availability_365\n");

    // Write sorted data
    for (int i = 0; i < count; i++) {
        fprintf(fp_by_name, "%d,%d,%s,%s,%s,%f,%f,%s,%f,%d,%d,%d,%d\n",
                items[i].id, items[i].host_id, items[i].host_name,
                items[i].neighbourhood_group, items[i].neighbourhood,
                items[i].latitude, items[i].longitude, items[i].room_type,
                items[i].price, items[i].minimum_nights, items[i].number_of_reviews,
                items[i].calculated_host_listings_count, items[i].availability_365);
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

    // Write header
    fprintf(fp_by_price, "id,host_id,host_name,neighbourhood_group,neighbourhood,latitude,longitude,room_type,price,minimum_nights,number_of_reviews,calculated_host_listings_count,availability_365\n");

    // Write sorted data
    for (int i = 0; i < count; i++) {
        fprintf(fp_by_price, "%d,%d,%s,%s,%s,%f,%f,%s,%f,%d,%d,%d,%d\n",
                items[i].id, items[i].host_id, items[i].host_name,
                items[i].neighbourhood_group, items[i].neighbourhood,
                items[i].latitude, items[i].longitude, items[i].room_type,
                items[i].price, items[i].minimum_nights, items[i].number_of_reviews,
                items[i].calculated_host_listings_count, items[i].availability_365);
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
