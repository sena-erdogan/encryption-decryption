#include<stdio.h> /* This library is added to be able to use basic functions such as printf and scanf */
#include<stdlib.h> /* In part 3, enemy's camp is expected to be in random positions. To get random values, srand() and rand() functions are used */
#include<time.h> /* In srand() function the time will be used to feed the function */
#include<math.h> /* In part 3, in order to find the distance between two points, sqrt() function is used */

char decrypt_numbers(int number); /* Functions are pre-defined in order for the compiler to have an overview of the code */

int decrypt_characters(char c);

void decrypt_and_print(char* file_path);

void deep_decrypt_and_print(char* file_path);

void refresh_position(int *X, int *Y, double *D, double *R);

void track_machine();

void encrypt_messages(char* file_path);

void menu();

char decrypt_numbers(int number){ /* This function is used to rewrite secret messages written with numbers, using characters to form a text in the terminal. 
                                        Every number has a character matched to it */

    switch(number){

        case 48: return ' '; /* In part 1 and 2, every number scanned from the file will have their corresponding values from the ASCII table so 48 will be added to their original values */

                break;

        case 49: return '-';

                break;

        case 50: return '_';

                break;

        case 51: return '|';

                break;

        case 52: return '/';

                break;

        case 53: return '\\';

                break;

        case 54: return 'O';

                break;

        case '\n': return '\n'; /* If the value taken is \n then a \n will be printed on the terminal as well */

                break;

        case EOF: return '\n'; /* At the end of the file, \n will be printed */

    }

}

int decrypt_characters(char c){ /* This function is written to be used in part 4 */

        switch(c){ /* In part 4, the source file consists of characters and the target file should consist of numbers */

                case ' ': return 0;

                        break;

                case '-': return 1;

                        break;

                case '_': return 2;

                        break;

                case '|': return 3;

                        break;

                case '/': return 4;

                        break;

                case '\\': return 5;

                        break;

                case 'O': return 6;

        }

}

void decrypt_and_print(char* file_path){ /* PART 1 */ /* This function expects a file name as a parameter */

    FILE *filep; /* A file pointer is assigned to the file */
    filep = fopen(file_path,"r"); /* The file taken as the parameter is opened on read mode to be able to do operations on it */

    int num; /* num will be the number scanned from the file */

    while( !feof(filep) ){ /* The operations inside this while statement will be executed until the file pointer points to EOF */

        num = fgetc(filep); /* The number is taken from the file using the fgetc() function, so the number is taken as its ASCII value */

        printf("%c", decrypt_numbers(num)); /* The number taken will be sent to decrypt_numbers() function to get its corresponding character value and that value is printed */

    }

    fclose(filep); /* After all the operations are done on the file, the file is closed */

}

void deep_decrypt_and_print(char* file_path){ /* PART 2 */ /*  */

    FILE *filep; /* A file pointer is assigned to the file */
    filep = fopen(file_path,"r"); /* The file taken as the parameter is opened on read mode to be able to do operations on it */

    int first, second, third; /* first will be the first number taken from the file, second is the one after that and third is the last one we need to apply the formula */

    first = getc(filep); 

    second = getc(filep);

    third = getc(filep);   

    while( !feof(filep) ){ /* This while loop will continue executing until the file pointer is on the end of file */

            if(third == '\n'){ /* If the third value we get from the file is \n, that means the number before the last one will be first and second values.
                                         The formula will be applied to first and second and the third value will be 0. And the last number will be the second number and since we need two more numbers to apply the formmula, those two missing numbers will both be 0 */
 
                    printf("%c", decrypt_numbers( ( first + second -96 ) % 7 + 48 )); /* Since the values taken are ASCII values of the numbers,
                                                                                         the real numbers in the file will be 48 subtracted from them. Since there are two numbers, 
                                                                                         the number subtracted from them will be double of 48 */

                    printf("%c", decrypt_numbers( (  second - 48 ) % 7 + 48 )); /* The function used to get the character values of those numbers is the decrypt_numbers() funtion 
                                                                                        which takes 0 as 48 and so on. So at the end of the operation, 
                                                                                        the final number should be incremented by 48 */

                    printf("\n"); /* After first and second calues are printed, the file has a new line so in terminal, we should print a \n as well */

                    first = getc(filep); /* getc() will take the next character which is the first number of the new line */

                    second = getc(filep); /* Three new numbers are taken from the new line to star over */

                    third = getc(filep);

            }else{ /* If the third value isn't \n, the formula will be applied again but this time first will take the place of second */

                    printf("%c", decrypt_numbers( ( first + second + third - 144 ) % 7 + 48 )); /* The formula is applied for all three numbers since none of them are \n */

                    first = second; /* Shifting the numbers */

                    second = third;

                    third = getc(filep); /* Third doesn't have a number after it to shift its value with so a new nummber is taken from the file */
                
            }

    }
    
    fclose(filep); /*  File is closed after all the operations*/

    printf("\n");

}

void track_machine(){ /* PART 3 */

        int x = 1 , y = 1 ; /* x and y represent initial position of the enemy which is (1,1) */
        double displacement = 0.0 , distance = sqrt( 6 * 6 + 6 * 6 ); /* Initial displacement of the enemy's camp is 0, and the initial distance to our camp is sqrt(72) 
                                                                        since our initial position is (6,6) */
        char command; 

        for(int i=1; i<12; i++){ /* Inıtial look of the 11 by 11 battleground using a nested loop. i represents x and j represents y.*/

                for(int j=1; j<12; j++){

                        if( i == 6 && j == 6 ){ /* Our camp's position is always (6,6) */

                                printf("O\t");

                        }else if( i == 1 && j == 1 ){ /* Enemy's initial position is (1,1) */

                                printf("E\t");

                        }else{

                                printf(".\t");

                        }

                }

        printf("\n");

        }

        printf("Enemy's X position: %d, Y position: %d, Displacement: %.2lf, Distance to our camp: %.2lf\n", x, y, displacement, distance);

        printf("Command waiting...:");
        scanf(" %c", &command);

        while( command == 'R' ){ /* If the command entered by the user is R the enemy camp will change its position to a random position in the battleground */

                refresh_position(&x, &y, &displacement, &distance); /* The new position of enemy camp, the displacement and the distance to our camp is taken
                                                                         using pointers for all these variables */

                for(int i=1; i<12; i++){ /* This nested for loops will print the new battleground with the refreshed position of the enemy camp */

                        for(int j=1; j<12; j++){

                                if( i == 6 && j == 6 ){ /* Our position is always (6,6) */

                                        printf("O\t");

                                }else if( i == x && j == y ){ /* The new x and y value will be the position of the enemy camp */

                                        printf("E\t");

                                }else{

                                        printf(".\t");

                                }

                        }

                        printf("\n");

                }

                printf("Enemy's X position: %d, Y position: %d, Displacement: %.2lf, Distance to our camp: %.2lf\n", x, y, displacement, distance);

                printf("Command waiting...:");
                scanf(" %c", &command);

        }

        if( command == 'E' ){ /* If the user enters E as the command, the machine will stop refreshing */

                printf("Enemy camp's final position: (%d,%d)\n\n", x , y ); /* The final position of the enemy camp is printed */

                menu(); /* Going back to the menu */

        }else{

                printf("\n\nINVALID COMMAND\nSTARTING OVER\n\n"); /* If a character other than E and R is entered, a warning message will be printed and the machine will start over */

                track_machine(); /* To start over, the function is called again */

        }

}

void refresh_position(int *X, int *Y, double *D, double *R){ /* Pointers are used since this function is void and can't return any value, and also there won't be too many variables */

        int previous_X = *X , previous_Y = *Y ; /* previous_x and previous_y will hold the values of the old x and y positions of the enemy so that we can find the displacement of them */

        srand(time(0)); /* srand function is used so the rand function will have an initial value ,which is time, to feed it */

        *X = rand() % 11 + 1; /* x pointer will have a random value's module with 11 and incremented by 1 assigned to it so can't be greater than 11 */

        *Y = rand() % 11 + 1;

        if( *X == 6 && *Y == 6 ){ /* If the enemy camp's random position is (6,6), which is our camp's positon, following will be executed */

                char command;

                for(int i=1; i<12; i++){ /* If the enemy finds our camp, O will be replaced by E */

                        for(int j=1; j<12; j++){

                                if( i == 6 && j == 6 ){ 

                                        printf("E\t");

                                }else{

                                        printf(".\t");

                                }

                        }

                }

                printf("Position of the enemy is (6,6)\n\nTHE ENEMY FOUND YOUR CAMP AND DEFEATED YOU\n\n");
                printf("Enter Q to restart\t");
                scanf(" %c", &command);

                if(command == 'Q'){ /* If the user enters Q, the machine will start over */

                        printf("Starting over\n\n");

                        track_machine();

                }


        }

        *D = sqrt( (( previous_X - *X ) * ( previous_X - *X )) + (( previous_Y - *Y ) * ( previous_Y - *Y )) ); /* Displacement is found by applying pythagorean theorem using
                                                                                                                 how much it moved on the x-axis and the y-axis */

        *R = sqrt( ( (*X - 6) * (*X - 6) ) + ( (*Y - 6) * (*Y - 6) ) ); /* Distance is also found by applying pythagorean theorem using enemy camp's new position and our position (6,6) */

}

void encrypt_messages(char* file_path){ /* PART 4 */

        FILE *filep;
        filep = fopen(file_path,"r"); /* The file that was sent to this function is opened in reading mode and assigned to file pointer */

        FILE *fp; /* The file that we will write to is also opened in writing mode and aassigned to a separate file pointer */
        fp = fopen("encrypted_p4.img","w");

        int first = 0, second = 0, third = 0, num = 0, temp; /* first, second and third are the three numbers we will that we will work with.
                                                                 Temp is used to get the character from the file and num is the value temp has in numbers */

        temp = getc(filep); /* First, a character is taken from the file */
        
        num = decrypt_characters(temp); /* That character turns into the corresponding number */
                                
                first = num; /* The first number in the formula will be that number */
                fprintf(fp, "%d", first); /* And since the characters before that one are accepted as 0, the first number will be "first" */

                temp = getc(filep); /* Second value is taken */

                num = decrypt_characters(temp);

                second = num - first; /* According to the formula we can say that (first + second) % 7 = num since they are small numbers this equation can be simplified into 
                                        second = num - first */
 
                        if(second < 0 && second >= -7){ /* After the operation, second can be negative. To make second positive it is şşncremented by 7 or 14 
                                                        since adding 7 or 14 won't change (second % 7)'s value */

                                second += 7;

                        }else if(second < -7){

                                second += 14;

                        }

                fprintf(fp, "%d", second); /* Second is printed as the second number of the target file */

                temp = getc(filep); /* A new character is taken from the source file and turned into its integer value */
                num = decrypt_characters(temp);
                                

        while( temp != EOF ){ /* While the number taken from the source file isn't EOF */

              while( temp != '\n' ){ /* If the new value is not \n then there are still characters to be read from that file */

                third = num - first - second; /* The third number is found in the same way as the second one */

                if(third < 0 && third >= -7){

                        third += 7;

                }else if(third < -7){

                        third += 14;

                }
                
                fprintf(fp, "%d", third);

                first = second; /* After printing the third number the variables are shifted to have the one after them's value. 
                                The third number's order is the order the new number added to the target file */
                second = third;
                temp = getc(filep);
                num = decrypt_characters(temp);

                }

                while(temp == '\n'){ /* If it's end of the line */

                        num = decrypt_characters(temp); /* That value is printed which is \n */
                        fprintf(fp, "%c", num);
                        temp = getc(filep); /* Another value is taken */

                                while(temp == '\n'){ /* While the next value is \n, \n will keep being printed */

                                        fprintf(fp,"%c",'\n');
                                        temp = getc(filep);

                                }

                        if(temp != EOF){ /* While the next character isn't EOF */
                        
                                num = decrypt_characters(temp); /* The formula keeps being applied */
                                first = num;
                                fprintf(fp, "%d", first);

                                temp = getc(filep);

                                num = decrypt_characters(temp);

                                second = num - first;

                                if(second < 0 && second >= -7){

                                        second += 7;

                                }else if(second < -7){

                                        second += 14;

                                }

                                fprintf(fp, "%d", second);

                        }

                        if(temp != EOF){

                                temp = getc(filep);
                                num = decrypt_characters(temp);

                        }
                        
                        }

        }
        
        fclose(filep); /* Files are closed */
        fclose(fp);

}

void menu(){ /* PART 5 */

    int choice;

    printf("1-) Decrypt and print encrypted_p1.img\n2-) Decrypt and print encrypted_p2.img\n3-) Switch on the tracking machine\n4-) Encrypt the message\n5-) Switch off\n\nPlease make your choice:\n");
    scanf(" %d", &choice);

    switch(choice){

        case 1: decrypt_and_print("encrypted_p1.img");

                menu();

                break;

        case 2: deep_decrypt_and_print("encrypted_p2.img");

                menu();

                break;

        case 3: track_machine(); /* Part 3 already calls menu() function if the user enters a specific character */

                break;

        case 4: encrypt_messages("decrypted_p4.img");

                menu();

                break;

        case 5:  /* If 5 is entered the program will switch off */

		break;

        default: printf("\nINVALID CHOICE.\n\n"); /* If any number other than those 5 cases is entered, a warning will be printed and the menu will be called */

                 menu();

    }

}

void main(){

	menu();

}