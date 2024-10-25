#include "q1.h"


/*
 * A basic menu based structure has been provided
*/

int main(){

    //Our three Linked Lists
    struct car *available_head = NULL;
	struct car *rented_head = NULL;
	struct car *repair_head = NULL;

    read_file_into_list("available.txt", &available_head);
    read_file_into_list("rented.txt", &rented_head);
    read_file_into_list("repair.txt", &repair_head);

    int choice;
    int t = 1;
    do
    {
        prompt();

        char plate[7];
        int mileage;
        int return_date;

        printf("Enter a Choice: ");
        scanf("%d", &choice);
        
        /*
         * You will need to add all the cases
         * Call the appropriate functions
         * You would also need to save data to disc upon exit
         * File Format: plate,mileage,return_date
         * Error Handling needs to happen too
        */

        switch (choice)
        {
        case 1:
            
            printf("Enter the new car's licence plate: \n");
            scanf("%9s", plate);
            printf("Enter the new car's mileage: \n");
            scanf("%d", &mileage);

            if ((is_plate_in_list(available_head, plate)) != 1){
                insert_to_list(&available_head, plate, mileage, -1);
            } else {
                printf("The entered licence plate is already in the system.");
            }
            
            write_list_to_file("available.txt", available_head);
            write_list_to_file("rented.txt", rented_head);
            write_list_to_file("repair.txt", repair_head);

           
            break;
        case 2:

            printf("Enter the licence plate of the rented car: \n");
            scanf("%9s", plate);
            //struct car *car_to_return = is_plate_in_list(rented_head, plate);

            //if (car_to_return == NULL) {
            //    printf("Error: Car with plate %s not found in rented list.\n", plate);
            //    break;
            //}

            printf("Enter the mileage of the rented car: \n");
            scanf("%d", &mileage);
            
            struct car * copy2 = copyCar(&rented_head, plate);

            if (copy2 != NULL) {
                double charge = profit_calculator(copy2->mileage, mileage);
                printf("Charge for rental: $%.2f\n", charge);
            }
            remove_car_from_list(&rented_head, plate);

            insert_to_list(&available_head, plate, mileage, copy2->return_date);
            free(copy2);

            write_list_to_file("available.txt", available_head);
            write_list_to_file("rented.txt", rented_head);
            write_list_to_file("repair.txt", repair_head);

            break;

        case 3:

            printf("Enter the licence plate of the returned car: \n");
            scanf("%9s", plate);
            printf("Enter the mileage of the returned car: \n");
            scanf("%d", &mileage);
            
            struct car * copy3 = copyCar(&rented_head, plate);

            if (copy3 != NULL) {
                double charge = profit_calculator(copy3->mileage, mileage);
                printf("Charge for rental: $%.2f\n", charge);
            }

            remove_car_from_list(&rented_head, plate);
            
            insert_to_list(&repair_head, plate, mileage, copy3->return_date);

            free(copy3);

            write_list_to_file("available.txt", available_head);
            write_list_to_file("rented.txt", rented_head);
            write_list_to_file("repair.txt", repair_head);

            break;
        
        case 4:
            
            printf("Transfer a car from repair list to available-for-rent list\n");
            printf("Enter the new car's licence plate: \n");
            scanf("%19s", plate);

            printf("THIS CODE IS");
            printf("%s", plate);

            if ((is_plate_in_list(repair_head, plate)) != 1) {
                printf("Error: Car with plate %s not found in repair list.\n", plate);
                break;
            }

            struct car * copy4 = copyCar(&repair_head, plate);
            if (copy4 == NULL) {
                printf("plate %s, mileage %d, Return date %d\n", copy4->plate, copy4->mileage, copy4->return_date);
                break;
            }
            //print_list(available_head);

            remove_car_from_list(&repair_head, plate);
            //printf("dababy");
            // if ((is_plate_in_list(repair_head, plate)) != 1) {
            //     printf("still in list\n", plate);
            //     break;
            // }
            
            insert_to_list(&available_head, plate, copy4->mileage, -1);
            

            if ((is_plate_in_list(available_head, plate))) {
                printf("MOVED\n", plate);
            }
            

            write_list_to_file("available.txt", available_head);
            write_list_to_file("rented.txt", rented_head);
            write_list_to_file("repair.txt", repair_head);

            free(copy4);

            break;


        case 5:

            printf("Rent the first available car\n");
            printf("Enter your expected return date: \n");
            scanf("%d", &return_date);



            struct car * copy5 = copy_first(available_head);

            remove_first_from_list(&available_head);

            insert_to_list(&rented_head, copy5->plate, copy5->mileage, return_date);
            free(copy5);

            write_list_to_file("available.txt", available_head);
            write_list_to_file("rented.txt", rented_head);
            write_list_to_file("repair.txt", repair_head);

            break;

        case 6: 

            printf("Print all lists\n");
            printf("Available-for-rent list:\n");
            print_list(available_head);
            printf("Rented list:\n");
            print_list(rented_head);
            printf("Repair list:\n");
            print_list(repair_head);
            break;

        case 7:
            
            printf("Quit and save data\n");
            write_list_to_file("available.txt", available_head);
            write_list_to_file("rented.txt", rented_head);
            write_list_to_file("repair.txt", repair_head);
            printf("Action: All data saved to files\n");
            break;

        default:
            printf("please enter a valid choice");
            //write_list_to_file("available.txt", available_head);
            //write_list_to_file("rented.txt", rented_head);
            //write_list_to_file("repair.txt", repair_head);
            break;
        }
        
    } while (choice != 7);
    free(available_head);
    free(rented_head);
    free(repair_head);

    return 0;
}