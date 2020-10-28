/*
=========================================================================
                           < Hangman game >
=========================================================================
Nick Gkoutzas (C language)
Greece, September 2020

*** Important information ***

In the code below I use special characters from ascii table,
so you have to change the 'Encoding' to 'Western IBM850' to print them correctly.

If you use Linux,then:
1) Open a terminal
2) Go to preferences -> Compatibility -> Encoding
3) Select 'Western IBM850'
=========================================================================
Also, it is a good idea to turn off your blinking cursor: setterm -cursor off
You can turn it on again, using : setterm -cursor on  


Enjoy!

*/




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


char give_char();
char* RED();
char* GREEN();
char* YELLOW();
char* BLUE();
char* CYAN();
char* RESET();
int random_pos(char *word , int *pos_1 , int *pos_2 , int *pos_3 , int *pos_4 , int *pos_5);
char *get_word(char *player_A , char *player_B , int flag);
char *first_start_name(char *player_A , char *player_B , char **array_names);
char *give_your_name(int *turns);
void delay(int number_of_seconds) ;
void Loading();
void start_game(int *ptr_used_letters , char *word , char *incorrect_used_letters , int *turns_to_lose , int *score_A , int *score_B , char *A , char *B , char *start);
int *delete_elem_array(int length_array , int del_pos , int *array);
void encrypt_word(char *start , char *A , char *B , char *array_all_found_letters , char letter , char *word , int *ps_1 , int *ps_2 , int *ps_3 , int *ps_4 , int *ps_5);
void show_score(char *incorrect_used_letters , char my_letter , char *array_all_found_letters , char *player_A , char *player_B , int *score_A , int *score_B , char *word , int flag , int *turns_to_lose);
void press_y_to_play();
void show_HALF_word(int *ptr_used_letters , char *incorrect_used_letters , char *array_all_found_letters , int *turns_to_lose , char letter , char *word , int *ps_1 , int *ps_2 , int *ps_3 , int *ps_4 , int *ps_5);
int check_letter_in_word(char *array_all_found_letters , char letter , char *word);
int count_num_of_letters_in_word(char *array_pos_letters , char letter , char *word , int x);
void press_p();
int check_incorrect_used_letters_array(char *incorrect_used_letters , char letter);
int found_the_word_question();
char play_again();
int check_simple_word(char *word);
int empty_array(char *incorrect_used_letters);



int main(void)
{
    int used_letters_var = 0;
    int *ptr_used_letters = &used_letters_var;
    char vowel[6] = {'a' , 'e' , 'i' , 'o' , 'u' , 'y'};
    srand(time(NULL));
    int score_A = 0;
    int score_B = 0;
    int turns_to_lose = 0;
    int pointer_name = 0;
    char *start = malloc(sizeof(char) * 20);
    char *array_names[2];
    char my_letter = ' ';
    char *word;
    char *incorrect_used_letters = malloc(sizeof(char));
    char *array_all_found_letters = malloc(sizeof(char) * 10);

    printf("%sWelcome to 'Hangman game' !!!%s\n" , GREEN() , RESET());
    for(int i = 1; i <= 35; i++)
    {
        printf("%c" , 205);
    }

    printf("\n%sLet's start by giving your names.%s\n" , BLUE() , RESET());
    for(int i = 1; i <= 35; i++)
    {
        printf("%c" , 176);
    }
    char *A = give_your_name(&pointer_name);
    char *B = give_your_name(&pointer_name);
    delay(1000);
    system("clear");
    show_score(incorrect_used_letters , my_letter , array_all_found_letters , A , B , &score_A , &score_B , " " , 0 , &turns_to_lose);
    press_y_to_play();
    system("clear");
    show_score(incorrect_used_letters , my_letter , array_all_found_letters , A , B , &score_A , &score_B , " " , 0 , &turns_to_lose);
    Loading();
    system("clear");
    show_score(incorrect_used_letters , my_letter , array_all_found_letters , A , B , &score_A , &score_B , " " , 0 , &turns_to_lose); 
    printf("\n");
    start = first_start_name(A , B , array_names);
    printf("\n%sThe player who starts first is %s. (Random Choice)%s" , YELLOW() , start , RESET());
    
    void match_again()
    {
        char your_answer = play_again();
        if(your_answer == 'n')
        {
            system("clear");
            printf("See you next time...\n");
            delay(2700);
            system("clear");
            exit(0);
        }
        else if(your_answer == 'y')
        {
            system("clear");
            system("./Hangman");
        }
    }


    if(start == array_names[0])
    {
        while(1)
        {
            word = get_word(A , B , 1);
            delay(1000);
            system("clear");
            show_score(incorrect_used_letters , my_letter , array_all_found_letters , A , B , &score_A , &score_B , " " , 1 , &turns_to_lose); 
            start_game(ptr_used_letters , word , incorrect_used_letters , &turns_to_lose , &score_A , &score_B , A , B , A);
            turns_to_lose = 0;

            if(score_A > score_B && score_A >= 5 && abs(score_A - score_B) >= 2)
            {
                printf("\n\nWe have a winner: %s\n\n" , A);
                break;
            }

            if(score_A < score_B && score_B >= 5 && abs(score_A - score_B) >= 2)
            {
                printf("\n\nWe have a winner: %s\n\n" , B);
                break;
            }

            word = get_word(B , A , 1);
            delay(1000);
            system("clear");
            show_score(incorrect_used_letters , my_letter , array_all_found_letters , A , B , &score_A , &score_B , " " , 1 , &turns_to_lose); 
            start_game(ptr_used_letters , word , incorrect_used_letters , &turns_to_lose , &score_A , &score_B , A , B , B);
            turns_to_lose = 0;

            if(score_A > score_B && score_A >= 5 && abs(score_A - score_B) >= 2)
            {
                printf("\n\nWe have a winner: %s\n\n" , A);
                break;
            }

            if(score_A < score_B && score_B >= 5 && abs(score_A - score_B) >= 2)
            {
                printf("\n\nWe have a winner: %s\n\n" , B);
                break;
            }
        }
    }


    else if(start == array_names[1])
    {
        while(1)
        {
            word = get_word(B , A , 1);
            delay(1000);
            system("clear");
            show_score(incorrect_used_letters , my_letter , array_all_found_letters , A , B , &score_A , &score_B , " " , 1 , &turns_to_lose); 
            start_game(ptr_used_letters , word , incorrect_used_letters , &turns_to_lose , &score_A , &score_B , A , B , B);
            turns_to_lose = 0;

            if(score_A > score_B && score_A >= 5 && abs(score_A - score_B) >= 2)
            {
                printf("\n\nWe have a winner: %s\n\n" , A);
                break;
            }

            if(score_A < score_B && score_B >= 5 && abs(score_A - score_B) >= 2)
            {
                printf("\n\nWe have a winner: %s\n\n" , B);
                break;
            }

            word = get_word(A , B , 1);
            delay(1000);
            system("clear");
            show_score(incorrect_used_letters , my_letter , array_all_found_letters , A , B , &score_A , &score_B , " " , 1 , &turns_to_lose); 
            start_game(ptr_used_letters , word , incorrect_used_letters , &turns_to_lose , &score_A , &score_B , A , B , A);
            turns_to_lose = 0;
            
            if(score_A > score_B && score_A >= 5 && abs(score_A - score_B) >= 2)
            {
                printf("\n\nWe have a winner: %s\n\n" , A);
                break;
            }

            if(score_A < score_B && score_B >= 5 && abs(score_A - score_B) >= 2)
            {
                printf("\n\nWe have a winner: %s\n\n" , B);
                break;
            }
        }
    }
    match_again();
}

void show_score(char *incorrect_used_letters , char my_letter , char *array_all_found_letters , char *player_A , char *player_B , int *score_A , int *score_B , char *word , int flag , int *turns_to_lose)
{
    int len_A = strlen(player_A);
    int len_B = strlen(player_B);
    
    for(int i = 1; i <= len_A + len_B + 80; i++)
    {
        if(i == 1)
        {
            printf("%c" , 201);
        }

        else if(i == 65)
        {
            printf("%c" , 203);
        }

        else if(i == len_A + len_B + 80)
        {
            printf("%c" , 187);
            if(flag == 1)
            {
                printf("             [Ctrl + c] to exit.");
            }
        }

        else
        {
            printf("%c" , 205);
        }
    }
    printf("\n%c%sWelcome to 'Hangman game' !!!\t%s\t\t%c  SCORE:\t%c %s%s%s     vs     %s%s%s %c            " , 186 , GREEN() , RESET() , 254 , 186 , BLUE() , player_A , RESET() , BLUE() , player_B , RESET() , 186);
    if(flag == 1)
    {
        printf("%s English alphabet vowels:   a , e , i , o , u , y%s\n" , GREEN() , RESET());
    }
    else if(flag == 0)
    {
        printf("\n");
    }

    if(*score_A >= 10 || *score_B >= 10)
    {
        printf("%c                                  \t\t      \t\t%c %s%d%s " , 186 ,  186 , CYAN() , *score_A , RESET());
    }
    else if(*score_A < 10 || *score_B < 10)
    {
        printf("%c                                  \t\t      \t\t%c %s%d%s" , 186 ,  186 , CYAN() , *score_A , RESET());
    }
    if(*score_A >= 10)
    {
        printf("%*c" , 12 + len_A - 2 , ' ');
    }
    else if(*score_A < 10)
    {
        printf("%*c" , 12 + len_A - 1 , ' ');
    }
     // how many spaces I want...
    if(*score_B >= 10)
    {
        printf("\b%s%d%s" , CYAN() , *score_B , RESET());
    }
    else if(*score_B < 10)
    {
        printf("%s%d%s" , CYAN() , *score_B , RESET());
    }
    for(int i = 1; i <= len_B; i++)
    {
        printf(" ");
    }

    if(*score_A >= 10 || *score_B >= 10)
    {
        printf("\b%c" , 186);
    }
    else
    {
        printf("%c" , 186);
    }
    if(flag == 1)
    {
        printf("             %sBy using them, will cost you 1 chance...%s\n" , RED() , RESET());
    }
    else if(flag == 0)
    {
        printf("\n");
    }
    
    printf("%c" , 186);
    printf("%*c" , 63 , ' ');
    printf("%c" , 200);
    
    for(int i = 1; i <= len_A + len_B + 14; i++)
    {
        printf("%c" , 205);
    }
    printf("%c" , 185);
    if(flag == 1)
    {
        printf("             %sWrong answers:%s  %s%d%s/%s%d%s" , CYAN() , RESET() , GREEN() , *turns_to_lose , RESET() , RED() , 11 , RESET());
    }
    printf("\n");
    printf("%c%sThe winner will be the one who is ahead by 2 points & score is >= 5.%s" , 186 ,  RED() , RESET());
    printf("%*c" , len_A + len_B + 10 , ' ');
    printf("%c" , 186);
    printf("\n%c%sPurpose of the game is to fill out the whole word/sentence...%s" , 186 , YELLOW() , RESET());
    printf("%*c" , len_A + len_B + 17 , ' ');
    printf("%c" , 186);

    if(flag == 1)
    {
        if(empty_array(incorrect_used_letters) == 1)
        {
            printf("             %sUsed letters that not exist in word:%s" , YELLOW() , RESET());
            printf("   None so far!");
        }
        else
        {
            printf("             %sUsed letters that not exist in word:%s" , YELLOW() , RESET());
        }
    }
    printf("\n");
    for(int i = 1; i <= 69; i++)
    {
        if(i == 1)
        {
            printf("%c" , 200);
        }
        else
        {
            printf("%c" , 205);
        }
    }
    for(int i = 1; i <= len_A + len_B + 10; i++)
    {
        printf("%c" , 205);
    }
    printf("%c             " , 188);
    
    if(flag == 1)
    {
        for(int i = 0; i < *turns_to_lose; i++)
        {
            printf("%c " , incorrect_used_letters[i]);
        }
    }
}

int empty_array(char *incorrect_used_letters)
{
    int empty = 1;
    for(int i = 0; i < 11; i++)
    {
        if(incorrect_used_letters[i] != '\0')
        {
            empty = 0;
        }
    }
    return empty;
}

char play_again()
{
    char ans;
    do
    {
        printf("%sDo you want to play again? (y/n):%s " , CYAN() , RESET());
        scanf(" %c" , &ans);
    }
    while(ans != 'y' && ans != 'n');
    return ans;
}




void start_game(int *ptr_used_letters , char *word , char *incorrect_used_letters , int *turns_to_lose , int *score_A , int *score_B , char *A , char *B , char *start)
{
        unsigned char aposiop1 = 174;
        unsigned char aposiop2 = 175;
        char my_letter = '@';
        int main_words;
        int ps_1 , ps_2 , ps_3 , ps_4 , ps_5;
        char *array_all_found_letters = malloc(sizeof(char) * (strlen(word)));
        for(int i = 0; i < strlen(word) - 1; i++)
        {
            array_all_found_letters[i] = ' ';
        }

        random_pos(word , &ps_1 , &ps_2 , &ps_3 , &ps_4 , &ps_5);

        
        
        int play = 1;
        while(play == 1)
        {
            encrypt_word(start , A , B , array_all_found_letters , my_letter , word , &ps_1 , &ps_2 , &ps_3 , &ps_4 , &ps_5);
            my_letter = give_char();
            show_HALF_word(ptr_used_letters , incorrect_used_letters , array_all_found_letters , turns_to_lose , my_letter , word , &ps_1 , &ps_2 , &ps_3 , &ps_4 , &ps_5);
            
            if(*turns_to_lose < 11)
            {
                if(strcmp(word , array_all_found_letters) == 0)
                {
                            if(start == A) 
                            {
                                ++*score_B;
                            }
                            else if(start == B)
                            {
                                ++*score_A;
                            }

                            char *not_start;
                            if(start == A)
                            {
                                not_start = B;
                            }
                            else
                            {
                                not_start = A;
                            }

                            fflush(stdout);
                            system("clear");
                            show_score(incorrect_used_letters , my_letter , array_all_found_letters , A , B , score_A , score_B , word , 0 , turns_to_lose);
                            for(int i = 0; i < 11; i++)
                            {
                                incorrect_used_letters[i] = '\0';
                            }
                            *ptr_used_letters = 0;
                            printf("\n%sBravo %s!!!%s\n%sYou found the hidden word %c%s%s%s%c.%s" , GREEN() , not_start  , RESET() ,  GREEN() , aposiop1 , YELLOW() , word , GREEN() , aposiop2 , RESET());
                            break;
                }
                else
                {
                            press_p();
                            fflush(stdout);
                            system("clear");
                            show_score(incorrect_used_letters , my_letter , array_all_found_letters , A , B , score_A , score_B , word , 1 , turns_to_lose);
                }
            }
        
                else if(*turns_to_lose == 11)
                {
                    if(start == A) 
                        {
                            ++*score_A;
                        }
                        else if(start == B) 
                        {
                            ++*score_B;
                        }

                        char *not_start;
                        if(start == A)
                        {
                            not_start = B;
                        }
                        else
                        {
                            not_start = A;
                        } 

                        fflush(stdout);
                        system("clear");
                        show_score(incorrect_used_letters , my_letter , array_all_found_letters , A , B , score_A , score_B , word , 0 , turns_to_lose);
                        for(int i = 0; i < 11; i++)
                        {
                            incorrect_used_letters[i] = '\0';
                        }
                        *ptr_used_letters = 0;
                        printf("\n%sYou lost %s.%s\nFailed to find the hidden word.%s\n%sHidden word was %c%s" , RED() , not_start , RED() , RESET() , CYAN() , aposiop1 , YELLOW());
                        for(int i = 0; i < strlen(word); i++)
                        {
                            printf("%c" , word[i]);
                        }
                        printf("%s%c.%s" , CYAN() , aposiop2 , RESET());
                        break;
                    }
                }
        
}



void press_y_to_play()
{
    char *message_1 = "Press any key to start game ";
    int m = 0;
    printf("\n\n%s" , BLUE());
    while(message_1[m] != '\0')
    {
        printf("%c" , message_1[m]);
        fflush(stdout);
        delay(50);
        m++;
    }
    printf("%s" , CYAN());
    char *message_2 = "[ENTER]";
    m = 0;
    while(message_2[m] != '\0')
    {
        printf("%c" , message_2[m]);
        fflush(stdout);
        delay(50);
        m++;
    }
    printf("%s: %s" , BLUE() , RESET());

    char ch;
    scanf(" %c" , &ch);
    printf("%sLet's get started%s" , YELLOW() , RESET());
    fflush(stdout);
    delay(500);
    for(int i = 1; i <= 3; i++)
    {
        delay(360);
        printf("%s.%s" , YELLOW() , RESET());
        fflush(stdout);
    }
    delay(2000);
}






void encrypt_word(char *start , char *A , char *B , char *array_all_found_letters , char letter , char *word , int *ps_1 , int *ps_2 , int *ps_3 , int *ps_4 , int *ps_5)
{
    if(start == A)
        {
            printf("\n\n%s%s find the hidden word...%s\n" , BLUE() , B , RESET());
        }

        else
        {
            printf("\n\n%s%s find the hidden word...%s\n" , BLUE() , A , RESET());
        }
    printf("\nHidden word:    ");
    array_all_found_letters[*ps_1] = word[*ps_1];
    array_all_found_letters[*ps_2] = word[*ps_2];
    array_all_found_letters[*ps_3] = word[*ps_3];
    if(strlen(word) >= 9 && strlen(word) <= 13)
    {
        array_all_found_letters[*ps_4] = word[*ps_4];
    }
    if(strlen(word) > 13)
    {
        array_all_found_letters[*ps_4] = word[*ps_4];
        array_all_found_letters[*ps_5] = word[*ps_5];
    }


    for(int i = 0; i < strlen(word); i++)
    {   
        if(word[i] == ' ')
        {
            printf("    ");
        }
        
        else if(array_all_found_letters[i] == word[i])
        {
             printf(" %c " , word[i]);
        }

        else
        {
            printf(" _ ");
        }
    }
}


int check_incorrect_used_letters_array(char *incorrect_used_letters , char letter)
{
    int exist = 0;
    for(int i = 0; i < 11; i++)
    {
        if(letter == incorrect_used_letters[i])
        {
            exist = 1;
        }
    }
    return exist;
}

void show_HALF_word(int *ptr_used_letters , char *incorrect_used_letters , char *array_all_found_letters , int *turns_to_lose , char letter , char *word , int *ps_1 , int *ps_2 , int *ps_3 , int *ps_4 , int *ps_5)
{
    char *array_pos_letters;
    array_pos_letters = malloc(sizeof(char) * strlen(word));
    int exist = check_letter_in_word(array_all_found_letters , letter , word);
    int num_of_letters = count_num_of_letters_in_word(array_pos_letters , letter , word , 1);

    char s_or_none = ' ';
    if(num_of_letters > 1)
    {
        s_or_none = 's';
    }

        if(exist == 0)
        {
            if(letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u' || letter == 'y')
            {   
                if(check_incorrect_used_letters_array(incorrect_used_letters , letter) == 0)
                {
                    incorrect_used_letters[*ptr_used_letters] = letter;
                    ++*ptr_used_letters;
                }
                printf("%sYou just used a vowel.%s\n" , RED() , RESET());
                printf("%sLetter '%c' is not exist%c in word.%s\n" , RED() , letter , s_or_none , RESET());
                ++*turns_to_lose;
            }
            else
            {
                if(check_incorrect_used_letters_array(incorrect_used_letters , letter) == 0)
                {
                    incorrect_used_letters[*ptr_used_letters] = letter;
                    ++*ptr_used_letters;
                }
                printf("%sLetter '%c' is not exist%c in word.%s\n" , RED() , letter , s_or_none , RESET());
                ++*turns_to_lose;
            }
        }
        else if(exist == 1)
        {
            if(letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u' || letter == 'y')
            {
                printf("%sYou just used a vowel.%s\n" , RED() , RESET());
                (*turns_to_lose)++;
            }
            if(s_or_none == ' ')
            {
                printf("%sYou found '%c' at position " , GREEN() , letter);
            }
            if(s_or_none == 's')
            {
                printf("%sYou found '%c' at positions" , GREEN() , letter);
            }
            int count = 1;
            for(int i = 0; i < strlen(word); i++)
            {
                if(word[i] == letter)
                {
                    if(num_of_letters == 1)
                    {
                        printf("%d.\n" , i + 1);
                    }
                    else
                    {
                        if(count <= num_of_letters - 2)
                        {
                            printf(" %d ," , i + 1);
                        }

                        else if(count == num_of_letters - 1)
                        {
                            printf(" %d" , i + 1);
                        }

                        else
                        {
                            printf(" and %d.\n" , i + 1);
                        }
                        count++;
                    }
                }
            }
            printf("%s" , RESET());
        }
        else if(exist == 2)
        {
            printf("%sLetter%c '%c' already exist%c in word.%s\n" , CYAN() , s_or_none , letter , s_or_none , RESET());
        }
    
}




void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds); 
} 



char *first_start_name(char *player_A , char *player_B , char **array_names)
{
    array_names[0] = player_A;
    array_names[1] = player_B;
    int start = rand() % 101 + 1;
    if(start < 50)
    {
        return array_names[0];
    }
    return array_names[1];
}




void Loading()
{
    char *array[4] = {"/" , "-" , "\\" , "|"};
    printf("\n\nLoading player to start...\nPlease wait...");
    for(int j = 1; j <= 13; j++)
    {
        for(int i = 0; i <= 3; i++)
        {
            printf("%s%s%s" , BLUE() ,array[i] , RESET());
            fflush(stdout);
            delay(100);
            printf("\b \b");
        }
    }
    printf("\n%sDone.%s\n" , GREEN() , RESET());
    delay(1000);
}


int found_the_word_question()
{
    printf("\n\n");
    char found;
    do
    {
        printf("Did you found the hidden word? (y/n): ");
        scanf(" %c" , &found);
    }
    while(found != 'y' && found != 'n');
    return found;
}




int *delete_elem_array(int length_array , int del_pos , int *array)
{
    array[del_pos] = array[length_array];
    return array;
}



int random_pos(char *word , int *pos_1 , int *pos_2 , int *pos_3 , int *pos_4 , int *pos_5)
{
    int real_length = strlen(word);
    int length_word = strlen(word);
    int array[length_word];
    for(int i = 0; i <= length_word; i++)
    {
        array[i] = i;
    }
    printf("\n\n");


    *pos_1 = rand() % (length_word);
    *pos_1 = array[*pos_1];
    //printf("pos_1 => %d\n",*pos_1);
    length_word--;
    delete_elem_array(length_word , *pos_1 , array);
    


    *pos_2 = rand() % (length_word);
    *pos_2 = array[*pos_2];
    //printf("pos_2 => %d\n",*pos_2);
    length_word--;
    delete_elem_array(length_word , *pos_2 , array);

    

    *pos_3 = rand() % (length_word);
    *pos_3 = array[*pos_3];
    //printf("pos_3 => %d\n",*pos_3);
    length_word--;
    delete_elem_array(length_word , *pos_3 , array);



    if(real_length >= 9 && real_length <= 13)
    {
 
        *pos_4 = rand() % (length_word);
        *pos_4 = array[*pos_4];
        //printf("pos_4 => %d\n",*pos_4);
        length_word--;
        delete_elem_array(length_word , *pos_4 , array);
 
    }

    else if(real_length > 13)
    {

        *pos_4 = rand() % (length_word);
        *pos_4 = array[*pos_4];
        //printf("pos_4 => %d\n",*pos_4);
        length_word--;
        delete_elem_array(length_word , *pos_4 , array);

        
  
        *pos_5 = rand() % (length_word);
        *pos_5 = array[*pos_5];
        //printf("pos_5 => %d\n\n\n",*pos_5);
        length_word--;
        delete_elem_array(length_word , *pos_5 , array);

    }
}




char give_char()
{
    char character;
    printf("\n\nGive a character: ");
    scanf(" %c" , &character);
    return character;
}




char *get_word(char *player_A , char *player_B , int flag)
{

  int len_A = strlen(player_A);
    int len_B = strlen(player_B);
    printf("\n\n");
    for(int i = 1; i <= 68; i++)
    {
        printf("%c" , 223);
    }
    for(int i = 1; i <= len_A + len_B + 12; i++)
    {
        printf("%c" , 223);
    }

    char *word = malloc(sizeof(char) * 100);

    printf("\n%sLength of word/sentence must be larger than 3!%s\n" , GREEN() , RESET());
    for(int i = 1; i <= 46; i++)
    {
        printf("-");
    }
    printf("\n%s give a word/sentence without %s looking at it: " , player_A , player_B);

    fgets(word , sizeof(word) , stdin);   
    size_t len;
    
    void foo()
    {
        while (fgets(word,100,stdin) != NULL)
        {
            break;
        }
        len = strlen(word) - 1;
        if (word[len] == '\n') //without newline
        {
            word[len] = '\0';
        }
    }

    foo();

    while(len <= 3)
    {
        printf("%sWARNING%s\n" , BLUE() , RESET());
        printf("%sLength of word '%s' is %ld.%sTry again.%s\n" , RED() , word , len , BLUE() , RESET());
        printf("%s give a word/sentence without %s looking at it: " , player_A , player_B);
        foo();
    }
    return word;
}





int count_num_of_letters_in_word(char *array_pos_letters , char letter , char *word , int x)
{
    int numbers = 0;

    for(int i = 0; i < strlen(word); i++)
    {
        if(word[i] == letter)
        {
            numbers++;
            if(x == 1)
            {
                array_pos_letters[i] = letter;  
            }
        }
    }
    return numbers;
}



void press_p()
{
    char c = ' ';
    
    do
    {
        printf("Press p + [ENTER] to continue: ");
        scanf(" %c" , &c);
    }
    while(c != 'p');
}



int check_letter_in_word(char *array_all_found_letters , char letter , char *word)
{
    int flag = 0;
    int count = 0;
    for(int i = 0; i < strlen(word); i++)
    {
        if(word[i] == letter && array_all_found_letters[i] != letter)
        {
            word[i] = letter;
            array_all_found_letters[i] = letter;
            flag = 1;
        }
        else if(array_all_found_letters[i] == letter)
        {
            count++;
            if(count == count_num_of_letters_in_word(array_all_found_letters , letter , word , 0))
            {
                flag = 2;
            }
        }
    }
    return flag;
}


//colours is below...

char* RED()
{
    return "\033[0;31m";
}

char* YELLOW()
{
    return "\x1B[33m";
}


char* GREEN()
{
    return "\x1B[32m";
}

char* RESET()
{
    return "\x1B[0m";
}

char* BLUE()
{
    return "\033[0;34m";
}


char* CYAN()
{
    return "\033[0;36m";
}


char *give_your_name(int *turns)
{
    char *name = malloc(sizeof(char) * 15);
    printf("\nGive your name: ");
    scanf("%s" , name);
    (*turns)++;
    printf("%sHey %s !%s\n" , BLUE() , name , RESET());
    if(*turns == 1)
    {
        printf("Now, it's turn of the other player to give his/her name.");
    }
    return name;
}