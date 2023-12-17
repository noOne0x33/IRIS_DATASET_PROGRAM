#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FLOWERS 150

struct IRIS_DATASET{
    char ID[10];
    char SPECIES[20];
    float SEPAL_LENGTH;
    float SEPAL_WIDTH;
    float PETAL_LENGTH;
    float PETAL_WIDTH;
};


//Display length and removing the duplicate values

void displaySepalLength(struct IRIS_DATASET *Flowers, int NUM_SPECIES){

    float UNIQUE_SEPAL_LENGTHS[MAX_FLOWERS];
    int NUM_UNIQUE_LENGTHS = 0;

    for (int i = 0; i < NUM_SPECIES; i++){
        int is_duplicate = 0;

        for (int j = 0; j < NUM_UNIQUE_LENGTHS; j++){
            if (Flowers[i].SEPAL_LENGTH == UNIQUE_SEPAL_LENGTHS[j]){
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate) {
            UNIQUE_SEPAL_LENGTHS[NUM_UNIQUE_LENGTHS++] = Flowers[i].SEPAL_LENGTH;
        }

    }

    // Sort unique sepal lengths in ascending order
    for (int i = 0; i < NUM_UNIQUE_LENGTHS - 1; i++) {
        for (int j = 0; j < NUM_UNIQUE_LENGTHS - i - 1; j++) {
            if (UNIQUE_SEPAL_LENGTHS[j] > UNIQUE_SEPAL_LENGTHS[j + 1]){
                float temp = UNIQUE_SEPAL_LENGTHS[j];
                UNIQUE_SEPAL_LENGTHS[j] = UNIQUE_SEPAL_LENGTHS[j + 1];
                UNIQUE_SEPAL_LENGTHS[j + 1] = temp;
            }
        }
    }

    // Display unique sepal lengths
    printf("[+]Unique sepal lengths in ascending order:\n");
    for (int i = 0; i < NUM_UNIQUE_LENGTHS; i++) {
        printf("%.1f ", UNIQUE_SEPAL_LENGTHS[i]);
    }
    printf("\n");
}

int main() {
    FILE *CSV_file;
    CSV_file = fopen("file path here", "r");

    if (!CSV_file) {
        perror("Error opening file");
        return 1;
    }

    struct IRIS_DATASET FLOWERS[MAX_FLOWERS];
    int NUM_FLOWERS = 0;

    // Read header line
    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), CSV_file);

    // Read data
    while (fgets(line, sizeof(line), CSV_file)) {
        sscanf(line, "%[^,],%[^,],%f,%f,%f,%f",
               FLOWERS[NUM_FLOWERS].ID,
               &FLOWERS[NUM_FLOWERS].SPECIES,
               &FLOWERS[NUM_FLOWERS].SEPAL_LENGTH,
               &FLOWERS[NUM_FLOWERS].SEPAL_WIDTH,
               &FLOWERS[NUM_FLOWERS].PETAL_LENGTH,
               &FLOWERS[NUM_FLOWERS].PETAL_WIDTH);

        NUM_FLOWERS++;
    }

    fclose(CSV_file);


    // iv) Print number of unique species
    char UNIQUE_SPECIES[MAX_FLOWERS][20];
    int NUM_UNIQUE_SPECIES = 0;

    for (int i = 0; i < NUM_FLOWERS; i++) {
        int is_duplicate = 0;

        for (int j = 0; j < NUM_UNIQUE_SPECIES; j++) {
            if (strcmp(FLOWERS[i].SPECIES, UNIQUE_SPECIES[j]) == 0) {
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate) {
            strcpy(UNIQUE_SPECIES[NUM_UNIQUE_SPECIES++], FLOWERS[i].SPECIES);
        }
    }

    puts("-------------------------------------------------------------------------------------------------->");

    printf("[+]Number of unique species : %d\n", NUM_UNIQUE_SPECIES);

    puts("-------------------------------------------------------------------------------------------------->");

    // ii) Display unique sepal lengths
    displaySepalLength(FLOWERS, NUM_FLOWERS);

    puts("------------------------------------------------------------------------------------------------------>");
    // iii) Print all ID values stored in the flowers array
    printf("[+]All ID values stored in the FLOWERS array:\n");
    for (int i = 0; i < NUM_FLOWERS; i++) {
        printf("%s ", FLOWERS[i].ID);
    }
    printf("\n");

    puts("----------------------------------------------------------->");

    // iv) Find total length by ID input
    char input_id[10];
    printf("[+]To get the total length in CM\n");
    printf("[+]Enter the ID: ");
    scanf("%s", input_id);

    float TOTAL_LENGTH = 0.0;
    for (int i = 0; i < NUM_FLOWERS; i++) {
        if (strcmp(FLOWERS[i].ID, input_id) == 0) {
            TOTAL_LENGTH = FLOWERS[i].SEPAL_LENGTH + FLOWERS[i].SEPAL_WIDTH + FLOWERS[i].PETAL_LENGTH + FLOWERS[i].PETAL_WIDTH;
            break;
        }
    }

    if (TOTAL_LENGTH != 0.0) {
        printf("Total length for ID %s: %.2fcm\n", input_id, TOTAL_LENGTH);
    } else {
        printf("Flower with ID %s not found.\n", input_id);
    }

    return 0;
}
