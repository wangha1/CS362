// For this test program the goal is to producing error message when reaching specific condition.

// In main function, 

// 	if (c == '[' && state == 0) state = 1;
//     if (c == '(' && state == 1) state = 2;
//     if (c == '{' && state == 2) state = 3;
//     if (c == ' ' && state == 3) state = 4;
//     if (c == 'a' && state == 4) state = 5;
//     if (c == 'x' && state == 5) state = 6;
//     if (c == '}' && state == 6) state = 7;
//     if (c == ')' && state == 7) state = 8;
//     if (c == ']' && state == 8) state = 9;
//     if (s[0] == 'r' && s[1] == 'e'
//        && s[2] == 's' && s[3] == 'e'
//        && s[4] == 't' && s[5] == '\0'
//        && state == 9)
//     {
//       printf("error ");
//       exit(200);
//     }

// when it gets to the condition of state = 9 and string = "reset " it gives an error.

// Thus, in inputChar function, it return a random character that is picked from arr, 
// which contains "[({ ax})]".

// char inputChar(){
//     int returnVal;
//     char arr[] = { '[', '(', '{', ' ', 'a', 'x', '}', ')', ']' };

//     returnVal = rand()%sizeof(arr);
    
//     return arr[returnVal];
// }



// In inputString function, arr stores string " reset",
// in for loop it randomly pick character from arr into arr2, 6 characters long

// char *inputString(){

//     int i;

//     char arr[] = {'\0', 'r', 'e', 's', 't'} ;
//     char * arr2 = (char*) malloc(6 * sizeof(char));

//     for (i = 0; i < 6; i++){
//         arr2[i] = arr[rand()%(sizeof(arr))];
//     }
//     return arr2;
// }


// In main function, in the while loop inputChar and inputString are called. When the test condition
// for c are all met and state = 9 then when it iterates to getting the return value of inputString
// as " reset" it then generates the error message:
// Iteration 2073: c =  , s = rrsr, state = 9
// Iteration 2074: c = }, s = , state = 9
// Iteration 2075: c = x, s = eeer, state = 9
// Iteration 2076: c = ], s = errs, state = 9
// Iteration 2077: c = ), s = tt, state = 9
// Iteration 2078: c = x, s = reset, state = 9
// error 
