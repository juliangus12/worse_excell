#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct nba {
  char team[100];
  char city[100];
  int wins;
  int losses;
  float winRate;
} teams;

// Functions
void startScreen();
void printGenInfo();
teams * readFile(teams *array, int * records);
int input(teams *array, int *sortedArray, int records);
void reset(teams *array, int *sortedArray, int records);
void printData(teams *array, int *sortedArray, int numRecords);
void search(teams *array, int *sortedArray, int records);
void sort(teams *array, int *sortedArray, int records);
teams * add(teams *array, int * sortedArray, int *records);
teams * rmv(teams * array, int * sortedArray, int *records);
void save(teams * array, int * sortedArray, int records);
void quit();


int main(void) {

  teams * arrayptr;
  
  int numRecords;
  int sortedArray[100];
  int finished = 0, i;

  

  /// fills the sorted array with integers in ascending order

  for (i = 0; i < 100; i++) {
    sortedArray[i] = i;
  }

  system("clear");

  startScreen();
  printGenInfo();
  arrayptr = readFile(arrayptr, &numRecords);
  printData(arrayptr, sortedArray, numRecords);
  input(arrayptr, sortedArray, numRecords);

  return 0;
}

void startScreen() {
  char jnk[100], junk;

  printf("\033[1;35m"); // sets color to purple
  printf("       ▄▄▌ ▐ ▄▌      ▄▄▄  .▄▄ · ▄▄▄ .    ▄▄▄ .▐▄• ▄  ▄▄· ▄▄▄ .▄▄▌    "
         "  \n");
  printf("       ██· █▌▐█▪     ▀▄ █·▐█ ▀. ▀▄.▀·    ▀▄.▀· █▌█▌▪▐█ ▌▪▀▄.▀·██•    "
         "  \n");
  printf("       ██▪▐█▐▐▌ ▄█▀▄ ▐▀▀▄ ▄▀▀▀█▄▐▀▀▪▄    ▐▀▀▪▄ ·██· ██ ▄▄▐▀▀▪▄██▪    "
         "  \n");
  printf("       ▐█▌██▐█▌▐█▌.▐▌▐█•█▌▐█▄▪▐█▐█▄▄▌    ▐█▄▄▌▪▐█·█▌▐███▌▐█▄▄▌▐█▌▐▌  "
         "  \n");
  printf("        ▀▀▀▀ ▀▪ ▀█▄▀▪.▀  ▀ ▀▀▀▀  ▀▀▀      ▀▀▀ •▀▀ ▀▀·▀▀▀  ▀▀▀ .▀▀▀   "
         "  \n");
  printf("\n                     ---[\033[0mPress Enter to "
         "Contiunue\033[1;35m]---    ");
  printf("\n\n");

  // contiunes into the next screen when they press enter
  scanf("%[^\n]", jnk);
  scanf("%c", &junk);

  printf("\033[0m"); // resets color
}

void printGenInfo() {
  system("clear");

  printf("\033[1;35m"); // sets color to purple; all of these just change the color

  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|\033[1m\033[37m                           General Information       "
         "                    \033[1;35m|\n");
  printf("|\033[1m\033[37m                          ---------------------      "
         "                    \033[1;35m|\n");
  printf("|\033[1m\033[37m 1. What can this program do that Excell cant?       "
         "                    \033[1;35m|\n");
  printf("|\033[0m Nothing! It's actually so much worse.                       "
         "            \033[1;35m|\n");
  printf("|\033[1m\033[37m                                                     "
         "                    \033[1;35m|\n");
  printf("|\033[1m\033[37m 2. Ok.. So what is the purpose of this program?     "
         "                    \033[1;35m|\n");
  printf("|\033[0m Below, you will see the names of .txt files. You can enter "
         "a file to    \033[1;35m|\n");
  printf("|\033[0m be opened and read by this program. Enter the file name to "
         "open it.     \033[1;35m|\n");
  printf("|\033[0m Once a file is opened, the data inside will be displayed "
         "along with     \033[1;35m|\n");
  printf("|\033[0m possible options to interact and view the data.             "
         "            \033[1;35m|\n");
  printf("|\033[1m\033[37m                                                     "
         "                    \033[1;35m|\n");
  printf("|\033[1m\033[37m 3. What is mydata.txt?                              "
         "                    \033[1;35m|\n");
  printf("|\033[0m A dataset containing the following information on NBA teams "
         "in 2020     \033[1;35m|\n");
  printf("|\033[0m - Team name                                                 "
         "            \033[1;35m|\n");
  printf("|\033[0m - City name                                                 "
         "            \033[1;35m|\n");
  printf("|\033[0m - Number of wins                                            "
         "            \033[1;35m|\n");
  printf("|\033[0m - Number of losses                                          "
         "            \033[1;35m|\n");
  printf("|\033[0m - Win percentage                                            "
         "            \033[1;35m|\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n");

  printf("\n\n\033[0mAvailable files: ");
  printf("\033[35m");
  printf("\n");
  
  // Displays the .txt files in the current directory
  system("ls | grep \".txt\"");
}

// stores the csv into the array and returns the number of records
teams * readFile(teams *array, int *records) {
  FILE *ifile;
  char fileName[100], input, junk, jnk[50];
  int i = 0;

  *records = 0;
  
  printf("\033[37m\nThe default file is \"mydata.txt\". Would you like to open it? (\033[32mY\033[37m)es [\033[31mN\033[37m]o");

  printf("\033[0m");
  printf("\n\n>");
  scanf("%c", &input);

  if(input != '\n') {
    scanf("%[^\n]", jnk);
    scanf("%c", &junk);
  }

  if (input == 'Y' || input == 'y' || input == '\n') {
    strcpy(fileName, "mydata.txt");
  } 
  else if (input == 'N' || input == 'n') {
  printf("\n What file do you want to open?\n");
  fflush(stdout);
  printf("\n>");
  scanf("%[^\n]s", fileName);
  scanf("%[^\n]s", jnk);
  scanf("%c", &junk);
  }


  // if the entered file doesn't exist
  ifile = fopen(fileName, "r");
  if (ifile == NULL) {
    system("clear");
    printf("\033[31m+----------------------------------------------------------"
           "---------------+\n");
    printf("|\033[1m\033[31m                                 ERROR             "
           "                      \033[31m| \n");
    printf("|\033[37m                       invalid input try again            "
           "               \033[31m|\n");
    printf("+------------------------------------------------------------------"
           "-------+\n");
    // sends user back to the gen info screen
    sleep(1);
    main();
    return 0;
  } else {
    system("clear");

    
    // warns about over writing the file. Another warning will come when saving

    printf("\033[31m+----------------------------------------------------------"
           "---------------+\n");
    printf("|\033[1m\033[31m                                 CAUTION           "
           "                      \033[31m| \n");
    printf("|\033[37m    Any changes saved to this file will overwrite the "
           "currrent data      \033[31m|\n");
    printf("|\033[37m                            (P)roceed [E]xit              "
           "               \033[31m|\n");
    printf("+------------------------------------------------------------------"
           "-------+\033[37m\n");

    printf("\n\n>");
    scanf("%c", &input);

  if(input != '\n') {
    scanf("%[^\n]", jnk);
    scanf("%c", &junk);
  }

    // calculates the number of records in the file
    while (fscanf(ifile, "%c", &junk) != EOF) {
      if (junk == '\n') {
        *records = *records + 1;
      }
    }
    array = (teams *) malloc(*records*sizeof(teams));

    // after seening the warning they are asked if they want to contiune
    // p is to contiune e will send them back to the geninfo screen with the file names
    if (input == 'P' || input == 'p' || input == '\n') {
      ifile = fopen(fileName, "r");
    } else if (input == 'E' || input == 'e') {
      printGenInfo();
      readFile(array, records);
    } else {
      system("clear");
      printf("\033[31m+--------------------------------------------------------"
             "-----------------+\n");
      printf("|\033[1m\033[31m                                 ERROR           "
             "                        \033[31m| \n");
      printf("|\033[37m                           Command not found            "
             "                 \033[31m|\n");
      printf("+----------------------------------------------------------------"
             "---------+\n");
      sleep(1);
      printGenInfo();
      readFile(array, records);
      }
  }
  // initialize the array with the values stored in the file
  for (i = 0; i < *records; i++) {
    fscanf(ifile, "%[^,]%c", (array[i].team), &junk);
    fscanf(ifile, "%[^,]%c", (array[i].city), &junk);
    fscanf(ifile, "%d%c", &(array[i].wins), &junk);
    fscanf(ifile, "%d%c", &(array[i].losses), &junk);
    fscanf(ifile, "%f%c", &(array[i].winRate), &junk);
  }
  
  fclose(ifile);
  return (array);
}

// Prints the current array and menu
void printData(teams *array, int *sortedArray, int numRecords) {

  int i = 0, j = 0;
  system("clear");

  // table contents

  printf(" \033[1m\033[37m         Name\033[1;35m            \033[1m\033[37m   "
         "   City\033[35m       \033[1m\033[37m Wins\033[35m  \033[1m\033[37m "
         "Losses \033[35m \033[1m\033[37m    Win Rate  \033[1;35m\n");
  printf("\033[1;35m+------------------------+----------------+------+--------+"
         "-------------+--[\033[32m0\033[1;35m]\n");

  // prints out the information with | that seperate them

  for (i = 1; i < numRecords + 1; i++) {
    printf("\033[35m|\033[37m %-22s \033[35m|\033[37m %-14s \033[35m|\033[37m  "
           "%-2d  \033[35m|\033[37m   %-2d   \033[35m|\033[37m     %-.3f   "
           "\033[35m|\n",
           array[sortedArray[i - 1]].team, array[sortedArray[i - 1]].city,
           array[sortedArray[i - 1]].wins, array[sortedArray[i - 1]].losses,
           array[sortedArray[i - 1]].winRate);

  // every 5 records there is a seperator with a numerical counter 
    if (i % 5 == 0) {
      j++;
      printf("\033[1;35m+------------------------+----------------+------+-----"
             "---+-------------+--[\033[32m%d\033[1;35m]\n",
             j * 5);
    }
    // losing brace with numerical counter
    else if (i == numRecords) {
       printf("\033[1;35m+------------------------+----------------+------+-----"
             "---+-------------+--[\033[32m%d\033[1;35m]\n", i);
    }
  }
  // menu
  printf("\n        s[E]arch s[O]rt dis(P)lay [A]dd [D]elete [S]ave [Q]uit");
  printf("\n\033[37m>");
}

int input(teams *array, int *sortedArray, int records) {
  char input, junk, jnk[100];
  int finished = 0;
  int * recordsptr = &records;

  scanf("%c", &input);

  if(input != '\n') {
    scanf("%[^\n]", jnk);
    scanf("%c", &junk);
  }

  // runs the user's desired command

  // search
  if (input == 'e' || input == 'E') {
    search(array, sortedArray, records);
  } 
  // sort
  else if (input == 'o' || input == 'O') {
    sort(array, sortedArray, records);
  } 
  // disply the data
  else if (input == 'p' || input == 'P' || input == '\n') {
    reset(array, sortedArray, records);
  } 
  // add a new entry/record
  else if (input == 'a' || input == 'A') {
    array = add(array, sortedArray, recordsptr);
  } 
  // delete an entry/record
  else if (input == 'd' || input == 'D') {
    array = rmv(array, sortedArray, recordsptr);
  } 
  // save 
  else if (input == 's' || input == 'S') {
    save(array, sortedArray, records);
  } 
  // exists program
  else if (input == 'q' || input == 'Q') {
    free(array);
    quit();
  } 
    // if the user doesn't enter a valid option
  else {
    printf("\nInvalid input, please try again.\n");
    fflush(stdout);
    sleep(1);
    reset(array, sortedArray, records);
  }
  return (0);
}

void sort(teams *array, int *sortedArray, int records) {
  char input, junk, jnk[100], temp;
  int i, j;

  // ask the user what they want to sort by
  printf("\033[31mAlphabetical order\033[37m: [C]ity or (T)eam |\033[34m "
         "Highest to lowest\033[37m: [W]ins, "
         "[L]osses, or win [R]ate\n");
  
  printf("\n\n>");
  scanf("%c", &input);

  if(input != '\n') {
    scanf("%[^\n]", jnk);
    scanf("%c", &junk);
  }
  
  // Sorts the team names in alphabetical order
  if (input == 't' || input == 'T' || input == '\n') {
    for (i = 0; i < records - 1; i++) {
      for (j = 0; j < records - 1; j++) {
        if (strcmp(array[sortedArray[j]].team, array[sortedArray[j + 1]].team) >
            0) {
          temp = sortedArray[j];
          sortedArray[j] = sortedArray[j + 1];
          sortedArray[j + 1] = temp;
        }
      }
    }
    // sends the user back to the data screen with the menu present
    printf("\033[32mSort complete\033[37m");
    fflush(stdout);
    sleep(1);
    reset(array, sortedArray, records);
  }
  // Sorts the city names in alphabetical order
  else if (input == 'c' || input == 'C') {
    for (i = 0; i < records - 1; i++) {
      for (j = 0; j < records - 1; j++) {
        if (strcmp(array[sortedArray[j]].city, array[sortedArray[j + 1]].city) >
            0) {
          temp = sortedArray[j];
          sortedArray[j] = sortedArray[j + 1];
          sortedArray[j + 1] = temp;
        }
      }
    }
    // sends them back
    printf("\033[32mSort complete\033[37m");
    fflush(stdout);
    sleep(1);
    reset(array, sortedArray, records);
  } // Sorts the Wins Highest to lowest
  else if (input == 'w' || input == 'W') {
    for (i = 0; i < records - 1; i++) {
      for (j = 0; j < records - 1; j++) {
        if (array[sortedArray[j]].wins < array[sortedArray[j + 1]].wins) {
          temp = sortedArray[j];
          sortedArray[j] = sortedArray[j + 1];
          sortedArray[j + 1] = temp;
        }
      }
    }
    // sends them back
    printf("\033[32mSort complete\033[37m");
    fflush(stdout);
    sleep(1);
    reset(array, sortedArray, records);
  } // Sorts losses highest to lowest
  else if (input == 'l' || input == 'L') {
    for (i = 0; i < records - 1; i++) {
      for (j = 0; j < records - 1; j++) {
        if (array[sortedArray[j]].losses < array[sortedArray[j + 1]].losses) {
          temp = sortedArray[j];
          sortedArray[j] = sortedArray[j + 1];
          sortedArray[j + 1] = temp;
        }
      }
    }
    // sends them back
    printf("\033[32mSort complete\033[37m");
    fflush(stdout);
    sleep(1);
    reset(array, sortedArray, records);
  } // sorts highest win rate to lowest
  else if (input == 'r' || input == 'R') {
    for (i = 0; i < records - 1; i++) {
      for (j = 0; j < records - 1; j++) {
        if (array[sortedArray[j]].winRate < array[sortedArray[j + 1]].winRate) {
          temp = sortedArray[j];
          sortedArray[j] = sortedArray[j + 1];
          sortedArray[j + 1] = temp;
        }
      }
    }
    // sends them back
    printf("\033[32mSort complete\033[37m");
    fflush(stdout);
    sleep(1);
    reset(array, sortedArray, records);
  }
  else {
    printf("Invlid input please try again\n");
    fflush(stdout);
    sleep(1);
    reset(array, sortedArray, records);
  }
}

void search(teams *array, int *sortedArray, int records) {
  char input, junk, jnk[100], choice = 'a';
  char teamName[100], cityName[100];
  int i, found = 0;
  int min, max;
  float fmin, fmax;

  // ask the user what they want

  printf("\033[34mNames\033[37m: (T)eam or [C]ity | \033[31mStats "
         "range\033[37m: [W]ins, [L]osses, or win [R]ate\n");

  
  printf("\n>");
  scanf("%c", &input);

  if(input != '\n') {
    scanf("%[^\n]", jnk);
    scanf("%c", &junk);
  }

  // exicutes the respective command
  
  if (input == 't' || input == 'T' || input == '\n') {
    printf("Please enter the team name you want to search for: ");
    scanf("%[^\n]s%c", teamName, &junk);
    system("clear");
    choice = input;
    for (i = 0; i < records; i++) {
      if ((strcmp(array[sortedArray[i]].team, teamName)) == 0) {
        printf("\n\033[37m                             Results of search \n\n");
        printf(" \033[1m\033[37m         Name\033[1;35m            "
               "\033[1m\033[37m   "
               "   City\033[35m       \033[1m\033[37m Wins\033[35m  "
               "\033[1m\033[37m "
               "Losses \033[35m \033[1m\033[37m  Win Rate  \033[1;35m\n");
        printf("\033[1;35m+------------------------+----------------+------+---"
               "-----+"
               "-------------+\n");
        printf("\033[35m|\033[37m %-22s \033[35m|\033[37m %-14s "
               "\033[35m|\033[37m  "
               "%-2d  \033[35m|\033[37m   %-2d   \033[35m|\033[37m     %-.3f   "
               "\033[35m|\n",
               array[sortedArray[i]].team, array[sortedArray[i]].city,
               array[sortedArray[i]].wins, array[sortedArray[i]].losses,
               array[sortedArray[i]].winRate);
        printf("\033[1;35m+------------------------+----------------+------+---"
               "-----+"
               "-------------+\n");
        found = 1; // found a record
      }
    }
  }
  // this searches using city name
  else if (input == 'c' || input == 'C') {
    choice = input;
    printf("\nPlease enter the city name you want to search for: ");
    scanf("%[^\n]s%c", cityName, &junk);
    system("clear");
    for (i = 0; i < records; i++) {
      if ((strcmp(array[sortedArray[i]].city, cityName)) == 0) {
        printf("\n\033[37m                             Results of search \n\n");
        printf(" \033[1m\033[37m         Name\033[1;35m            "
               "\033[1m\033[37m   "
               "   City\033[35m       \033[1m\033[37m Wins\033[35m  "
               "\033[1m\033[37m "
               "Losses \033[35m \033[1m\033[37m  Win Rate  \033[1;35m\n");
        printf("\033[1;35m+------------------------+----------------+------+---"
               "-----+"
               "-------------+\n");
        printf("\033[35m|\033[37m %-22s \033[35m|\033[37m %-14s "
               "\033[35m|\033[37m  "
               "%-2d  \033[35m|\033[37m   %-2d   \033[35m|\033[37m     %-.3f   "
               "\033[35m|\n",
               array[sortedArray[i]].team, array[sortedArray[i]].city,
               array[sortedArray[i]].wins, array[sortedArray[i]].losses,
               array[sortedArray[i]].winRate);
        printf("\033[1;35m+------------------------+----------------+------+---"
               "-----+"
               "-------------+\n");
        found = 1; // found a record
      }
    }
  }
  // this searches using a range of wins
  else if (input == 'w' || input == 'W') {
      printf("Minimum amount of wins: "); 
      scanf("%[^\n]s%c", teamName, &junk);
      printf("Maximum amount of wins: ");
      scanf("%d%c", &max, &junk);
      system("clear");
    
      for (i = 0; i < records; i++){ 
        if (array[sortedArray[i]].wins >= min && array[sortedArray[i]].wins <= max){ 
        printf("\n\033[37m                             Results of search \n\n");
        printf(" \033[1m\033[37m         Name\033[1;35m            "
               "\033[1m\033[37m   "
               "   City\033[35m       \033[1m\033[37m Wins\033[35m  "
               "\033[1m\033[37m "
               "Losses \033[35m \033[1m\033[37m  Win Rate  \033[1;35m\n");
        printf("\033[1;35m+------------------------+----------------+------+---"
               "-----+"
               "-------------+\n");
        printf("\033[35m|\033[37m %-22s \033[35m|\033[37m %-14s "
               "\033[35m|\033[37m  "
               "%-2d  \033[35m|\033[37m   %-2d   \033[35m|\033[37m     %-.3f   "
               "\033[35m|\n",
               array[sortedArray[i]].team, array[sortedArray[i]].city,
               array[sortedArray[i]].wins, array[sortedArray[i]].losses,
               array[sortedArray[i]].winRate);
        printf("\033[1;35m+------------------------+----------------+------+---"
               "-----+"
               "-------------+\n");
          found = 1;
        }
      }
    }
  // This search uses a range of win rates
  else if (input == 'r' || input == 'R') {
      printf("Minimum win rate (decimal 3 digits): "); 
      scanf("%f%c", &fmin, &junk);
      printf("Maximum win rate (decimal 3 digits): ");
      scanf("%f%c", &fmax, &junk);
      system("clear");
    
      for (i = 0; i < records; i++){ 
        if (array[sortedArray[i]].winRate >= fmin && array[sortedArray[i]].winRate <= fmax){ 
        printf("\n\033[37m                             Results of search \n\n");
        printf(" \033[1m\033[37m         Name\033[1;35m            "
               "\033[1m\033[37m   "
               "   City\033[35m       \033[1m\033[37m Wins\033[35m  "
               "\033[1m\033[37m "
               "Losses \033[35m \033[1m\033[37m  Win Rate  \033[1;35m\n");
        printf("\033[1;35m+------------------------+----------------+------+---"
               "-----+"
               "-------------+\n");
        printf("\033[35m|\033[37m %-22s \033[35m|\033[37m %-14s "
               "\033[35m|\033[37m  "
               "%-2d  \033[35m|\033[37m   %-2d   \033[35m|\033[37m     %-.3f   "
               "\033[35m|\n",
               array[sortedArray[i]].team, array[sortedArray[i]].city,
               array[sortedArray[i]].wins, array[sortedArray[i]].losses,
               array[sortedArray[i]].winRate);
        printf("\033[1;35m+------------------------+----------------+------+---"
               "-----+"
               "-------------+\n");
          found = 1;
        }
      }
    }
  // this search uses a range of losses
  else if (input == 'l' || input == 'L') {
      printf("Minimum amount of losses: "); 
      scanf("%d%c", &min, &junk);
      printf("Maximum amount of losses: ");
      scanf("%d%c", &max, &junk);
      system("clear");
    
      for (i = 0; i < records; i++){ 
        if (array[sortedArray[i]].losses >= min && array[sortedArray[i]].losses <= max){ 
        printf("\n\033[37m                             Results of search \n\n");
        printf(" \033[1m\033[37m         Name\033[1;35m            "
               "\033[1m\033[37m   "
               "   City\033[35m       \033[1m\033[37m Wins\033[35m  "
               "\033[1m\033[37m "
               "Losses \033[35m \033[1m\033[37m  Win Rate  \033[1;35m\n");
        printf("\033[1;35m+------------------------+----------------+------+---"
               "-----+"
               "-------------+\n");
        printf("\033[35m|\033[37m %-22s \033[35m|\033[37m %-14s "
               "\033[35m|\033[37m  "
               "%-2d  \033[35m|\033[37m   %-2d   \033[35m|\033[37m     %-.3f   "
               "\033[35m|\n",
               array[sortedArray[i]].team, array[sortedArray[i]].city,
               array[sortedArray[i]].wins, array[sortedArray[i]].losses,
               array[sortedArray[i]].winRate);
        printf("\033[1;35m+------------------------+----------------+------+---"
               "-----+"
               "-------------+\n");
          found = 1;
        }
      }
    }
    // if the user doesn't neter an option
  else {
    printf("\nInvalid input, please try again.\n");
    fflush(stdout);
    sleep(1);
    reset(array, sortedArray, records);
    found = 1;
  }
  // if the search term the user provided gives no records
  if (found == 0) {
      printf("\n There are no records that match your search term. Searching is case sensitive.\n");
    fflush(stdout);
    sleep(1);
    reset(array, sortedArray, records);
    // sends them back after they press enter. is only exicuted if there is something found
  }    
  else if(found == 1) {
    if (choice == 'T' || choice == 't' || choice == 'c' || choice == 'C' || choice == '\n') {
      printf("\n                     ---[\033[0mPress Enter to "
         "Contiunue\033[1;35m]---    ");
    fflush(stdout);
    printf("\n\n");
    getchar();
    scanf("%c", &junk);
    reset(array, sortedArray, records);
    }
    else {
      printf("\n                     ---[\033[0mPress Enter to "
         "Contiunue\033[1;35m]---    ");
    fflush(stdout);
    printf("\n\n");
    scanf("%c", &junk);
    reset(array, sortedArray, records);
    }
  }
}

teams * add(teams *array, int * sortedArray, int *records) {
  char junk, jnk[100];
  int i, valid, wins, losses;
  float rate;

  array = (teams*) realloc(array, (*records + 1)*sizeof(teams));

  // have the user fill out the structure for a new record
  printf("Team Name: ");
  scanf("%[^\n]%c", array[sortedArray[*records]].team, &junk);
  printf("City: ");
  scanf("%[^\n]%c", array[sortedArray[*records]].city, &junk);
  printf("Wins: ");
  scanf("%d", &array[sortedArray[*records]].wins);
  scanf("%[^\n]", jnk);
  scanf("%c", &junk);
  printf("Losses: ");
  scanf("%d", &array[sortedArray[*records]].losses);
  scanf("%[^\n]", jnk);
  scanf("%c", &junk);
  printf("Win rate: ");
  scanf("%f", &array[sortedArray[*records]].winRate);
  scanf("%[^\n]", jnk);
  scanf("%c", &junk);
  printf("\n\n%d\n\n", array[sortedArray[*records]].losses);
  // need to increase records as the number of records just increased by one
  *records = (*records + 1);
  
  printf("\n \033[32mThis record has been recorded.\033[37m\n");

  // sends them back
  reset(array, sortedArray, *records);

  return(array);
}

teams * rmv(teams * array, int * sortedArray, int *records) {

  char teamName[100], junk, jnk[100];
  int i, j, found = 0;
  int recordLoca;
  
  printf("\nName of the team you want to delete: ");
  scanf("%[^\n]%c", teamName, &junk);
   for (i=0; i < *records; i++) { //if name matches user entry (via strcmp), delete that data set

    if ((strcmp(array[sortedArray[i]].team, teamName)) == 0) {
      recordLoca = i;
      found = 1;

      printf("\n\033[31mRecord removed\033[37m\n");
      for (j = recordLoca; j < *records - 1; j++){
        array[sortedArray[j]] = array[sortedArray[j + 1]];
      } 

      array = (teams*) realloc(array, (*records - 1)*sizeof(teams));
    *records = (*records - 1);
    // updates the structure locations inside of the array

      i--;



    }
  }
  // no records found based on user entry
  if (found == 0) { 
    printf("\n\033[31mThere are no records that match your entry. \033[37mSearching is case sensitive.\n");
    fflush_unlocked(stdout);
    sleep(1);
    reset(array, sortedArray, *records);
    }
  else if (found == 1) {
    fflush_unlocked(stdout);
    sleep(1);
    reset(array, sortedArray, *records);
  }
  return(array);
} 

void quit() {
  exit(0);
}

void save(teams * array, int * sortedArray, int records) {
  char fileName[50], junk, jnk[100], input;
  int i;
  int exists = 1;

  FILE *ifile;

  printf("Please a name for your file: ");
  scanf("%[^\n]s", fileName);
  scanf("%c", &junk);

    ifile = fopen(fileName, "r"); 
  
  // if the file doesn't exist make a file with that name and save the data
    if (ifile == NULL) { 
      ifile = fopen(fileName, "w");
      // saving file
      printf("Saved as %s!\n.", fileName);
      for (i = 0; i < records; i++) {
        fprintf(ifile, "%s,",(array[sortedArray[i]].team));
        fprintf(ifile, "%s,",(array[sortedArray[i]].city));
        fprintf(ifile, "%d,", (array[sortedArray[i]].wins)); 
        fprintf(ifile, "%d,", (array[sortedArray[i]].losses));
        fprintf(ifile, "%.3f", (array[sortedArray[i]].winRate));
        fprintf(ifile, "\n");
        
      }
      fclose(ifile);
      printf("\033[32mFile Saved");
      fflush(stdout);
      sleep(1);
      reset(array, sortedArray, records);
    }
    else {
      fclose(ifile);
      while (exists != 0) { //if file exists, ask if they wanna overwite
        printf("A file named %s already exists, saving would mean overwritting the current data. Would you still like to save? (\033[32mY\033[37m)es [\033[31mN\033[37m]o \n", fileName);
        printf("\033[0m");
        printf("\n>");
        scanf("%c", &input);
      
        if(input != '\n') {
          scanf("%[^\n]", jnk);
          scanf("%c", &junk);
        }
        
        if (input == 'Y' || input == 'y' || input == '\n') {

          // saving file
          ifile = fopen(fileName, "w"); 
          for (i = 0; i < records; i++) {
            fprintf(ifile, "%s,",(array[sortedArray[i]].team));
            fprintf(ifile, "%s,",(array[sortedArray[i]].city));
            fprintf(ifile, "%d,", (array[sortedArray[i]].wins)); 
            fprintf(ifile, "%d,", (array[sortedArray[i]].losses));
            fprintf(ifile, "%.3f", (array[sortedArray[i]].winRate));
            fprintf(ifile, "\n");
          }
          // sends them back
          exists = 0;
          fclose(ifile);
          printf("\033[32mFile Saved");
          fflush(stdout);
          sleep(1);
          reset(array, sortedArray, records);
        }
        else if (input == 'n' || input == 'N') {
          reset(array, sortedArray, records);
        }
        else {
          // sends the back
          system("clear");
          printf("Invalid entry. ");
          fflush(stdout);
          sleep(1);
          reset(array, sortedArray, records);
        }
      }
    }  
}

// sends them back
void reset(teams *array, int *sortedArray, int records) {
  system("clear");
  printData(array, sortedArray, records);
  input(array, sortedArray, records);
}
