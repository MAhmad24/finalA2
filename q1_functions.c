#include "q1.h"


/* function will display the primary user interface
    This is already done for you*/
void prompt(){

  printf("1. Add a new car to the available-for-rent list,\n");
  printf("2. Add a returned car to the available-for-rent list,\n");
  printf("3. Add a returned car to the repair list,\n");
  printf("4. Transfer a car from the repair list to the available-for-rent list,\n");
  printf("5. Rent the first available car,\n");
  printf("6. Print all the lists,\n");
  printf("7. Quit.\n");
  printf("Enter your choice: ");
}

/**
 * Inserts a new car into the linked list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @param mileage Integer representing the car's mileage.
 * @param return_date Integer representing the car's return date, you can have -1 represent no return date.
 * @return Pointer to the newly added car in the list.
 */
struct car * insert_to_list(struct car ** head, char plate[], int mileage, int return_date){
    //Allocate memeory for the new inserted car
    struct car * new_car = (struct car *)malloc(sizeof(struct car));

    //Check if the new car node is empty and handle the memory allocation faliure
    if (new_car == NULL){
        return NULL;
    }
    
    //Add the given info about the new car to the node
    strcpy(new_car->plate, plate);
    new_car->mileage = mileage;
    new_car->return_date = return_date;

    //make sure the new car is at the start of the linked list, replacing where the head is pointing to the address of
    //the new car while changing the new car's next pointer to the address of the original new car
    new_car->next = *head;
    *head = new_car;


    return NULL;
}

/**
 * Prints all the cars in the list.
 * @param head Pointer to the head of the list.
 * This function prints out the car details, it should not print return date if it does not exist.
 */
void print_list(struct car *head){
    struct car * print_all = head;
    while (print_all != NULL){
        printf("License Plate: %s \n", print_all->plate);
        printf("Mileage: %d \n", print_all->mileage);
        if (print_all->return_date != -1){
        printf("Return Date (yymmdd): %d \n\n");
        } else {
            printf("No return date.\n\n");
        }
        print_all = print_all->next;
    }
    return;
}

/**
 * Checks if a car's plate is already in the list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Boolean value indicating if the plate is found.
 */
bool is_plate_in_list(struct car * head, char plate[]){
    struct car * check_car = head;
    while (check_car != NULL){
        if (strcmp(check_car->plate, plate) == 0){
            return true;
        }
        check_car = check_car->next;
    }
    return false;
}


/** 
 * Creates a copy of the car at the end of a list.
 * @param head Pointer to the head of the list
 * @return the node and what it contains
 * I wanna be able to copy the node into another list.
 */
struct car * get_last(struct car **head){
    struct car * current = *head;
    while (current != NULL){
        current = current->next;
    }
    return current;
}


/** 
 * Creates a copy of the car at the beggining of a list.
 * @param head Pointer to the head of the list
 * @return the node and what it contains
 * I wanna be able to copy the node into another list.
 */
struct car * copy_first(struct car *head){
    
    struct car * current = head;

    struct car * copy = (struct car*)malloc(sizeof(struct car));
    strcpy(copy->plate, current->plate);
    copy->mileage = current->mileage;
    copy->return_date = copy->return_date;
    copy->next = NULL;
    
    return copy;
    
}

//and here I was thinking I came up with a more creative method
//void remove_first(struct car **head){

    //struct car * current = *head;

    //*head = current->next;

    //free(current);
    //return;
//}

/**
 * Creates a copy of a car so it can be inserted into another list before being deleted.
 * @param head Pointer to the head of the list
 * @param plate Character array containing the car's licence plate.
 * @return the node and what it contains
 * I wanna be able to copy the node into another list.
 */
struct car * copyCar(struct car **head, char plate[]){
    struct car * searchCar = *head;


    while (searchCar != NULL){
        if ((strcmp(searchCar->plate, plate)) == 0){
            return searchCar;
        } else {
            searchCar = searchCar->next;
        }
    }
}

/**
 * Swaps two cars in the list.
 * @param a Pointer to the first car.
 * @param b Pointer to the second car.
 * Swaps the plate, mileage, and return date of two cars.
 */
void swap(struct car *a, struct car *b){



    char temp_plate[7];
    int temp_mileage;
    int temp_date;
    //found out the hard way that swapping positions of nodes is not as easy
    //luckily I realised I don't have to at the moment :D
    //struct car *temp_next;

    strcpy(temp_plate, a->plate);
    temp_mileage = a->mileage;
    temp_date = a->return_date;
    //temp_next = a->next;

    strcpy(a->plate, b->plate);
    a->mileage = b->mileage;
    a->return_date = b->return_date;
    //a->next = b->next;

    strcpy(b->plate, temp_plate);
    b->mileage = temp_mileage;
    b->return_date = temp_date;
    //b->next = temp_next;

    return;
}

/**
 * Sorts the list of cars based on mileage or return date.
 * @param head Pointer to the head of the list.
 * @param sort_by_mileage Boolean to sort by mileage.
 * @param sort_by_return_date Boolean to sort by return date.
 */
void sort_list(struct car ** head, bool sort_by_mileage, bool sort_by_return_date){
    
    struct car * current_car = *head;

    int count;

    if (current_car != NULL){

        count = 1;

        while (current_car->next != NULL){
            count++;
            current_car = current_car->next;
        }
    }
    
    struct car * carArray = (struct car*)malloc(count * sizeof(struct car));

    if (carArray == NULL){
        return;
    }

    int i = 0;

    while (current_car != NULL){
        carArray[i] = *current_car;
        current_car = current_car->next;
         i++;
    }

    if (sort_by_mileage){
        
    } else if (sort_by_return_date){
        
    }

    return;
}

/**
 * Removes a car from the list by its plate number.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Pointer to the removed car.
 */
struct car * remove_car_from_list(struct car **head, char plate[]){

    bool done = 0;
    struct car *current = *head;

    if (strcmp(current->plate, plate) == 0){
        *head = current->next;
        free(current);
        done = 1;
    } else {
        while (done != 1){
            if (strcmp(current->next->plate, plate) == 0){
                struct car *temp_next = current->next->next;
                free(current->next);
                current->next = temp_next;
                done = 1;
            }
            else {
                current = current->next;
            }
        }
    }
    if (done == 0){
        printf("The provided licence plate isn't registered in the system");
    }

    return NULL;
}




/**
 * Removes the first car from the list.
 * @param head Pointer to the head of the list.
 * @return Pointer to the removed car.
 */
struct car * remove_first_from_list(struct car **head){

    struct car * temp = *head;
    *head = temp->next;
    free(temp);
    return *head;
}

/**
 * Calculates the profit based on the mileage difference.
 * @param initial_mileage Integer representing the car's starting mileage.
 * @param final_mileage Integer representing the car's final mileage.
 * @return Double value representing the calculated profit.
 */
double profit_calculator(int initial_mileage, int final_mileage){

    int additionalMileage;
    int rentedMileage = final_mileage - initial_mileage;

    if (rentedMileage <= 0){
        printf("Invalid final mileage.");
    }

    if (rentedMileage > 200 && rentedMileage <= 0){
        additionalMileage = rentedMileage - 200;
    }

    double charge = 80.00 + (additionalMileage * 0.15);

    return charge;
}

/**
 * Writes the list of cars to a file.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Writes the details of each car in the list to a file.
 */
void write_list_to_file(char *filename, struct car *head){

    struct car * current = head;

    FILE *file = fopen(filename, "w");

    while (current != NULL){
        fprintf(file, "%s,%d,%d \n",current->plate, current->mileage, current->return_date);
        
        current = current->next;
    }
    fclose(file);


    return;
}

/**
 * Reads car details from a file and adds them to the list.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Reads data from the file and inserts each car into the list.
 */
void read_file_into_list(char *filename, struct car **head){

    struct car * current = *head;

    FILE * file = fopen(filename, "r");
    int mileageInt, return_dateInt;

    if (file == NULL){
        perror("Error opening file, check the file name or if the file exists");
        return;
    }

    //while((l = fgetc(file)) != EOF){
    //    count++;
    //}

    int c;
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL){

        char plate[20];
        if (sscanf(line, "%9[^,],%d,%d", plate, &mileageInt, &return_dateInt)!= 3){
            printf("Invalid format in line: %s", line);
            continue;
        }

        //if (plate != NULL && mileageStr != NULL && returnDateStr != NULL){
        //    mileageInt = atoi(mileageStr);
        //    return_dateInt = atoi(returnDateStr);
        //}

        struct car * new_car = (struct car*)malloc(sizeof(struct car));
        if (new_car == NULL){
            printf("Error allocating memory for new car");
            return;
        }
        strcpy(new_car->plate, plate);
        new_car->mileage = mileageInt;
        new_car->return_date = return_dateInt;

        new_car->next = NULL;

        if (*head == NULL) {
        *head = new_car;
        } else {
            struct car *current = *head;
            while (current->next != NULL){
                current = current->next;
            }
            current->next = new_car;
        }
    }

    fclose(file);

    return;
}

/**
 * Prints the date in the format of year/month/day.
 * @param date Integer representing the date in YYMMDD format.
 */
void date(int date){

    char dateStr[9];
    sprintf(dateStr, "%06d", date);
     
     dateStr[8] = '\0';
     dateStr[7] = dateStr[5];
     dateStr[6] = dateStr[4];
     dateStr[5] = '/';
     dateStr[4] = dateStr[3];
     dateStr[3] = dateStr[2];
     dateStr[2] = '/';
     //dateStr[1] = dateStr[1];

    printf("%s\n", dateStr);
    return;
}

/**
 * Frees all the memory allocated for the cars in the list.
 * @param head Pointer to the head of the list.
 * Frees each car node in the list.
 */
void free_list(struct car ** head){
    struct car * current = *head;
    struct car * temp_next;

    while (current != NULL){
        temp_next = current->next;
        free(current);
        current = temp_next;
    }

    *head = NULL;

    return;
}