#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
#pragma warning( disable : 4267)
#pragma warning( disable : 4996)

using namespace std;

char T1[100][100][80];
char T2[100][100][80];


void printTable(char T[100][100][80])
{
   int i = 0, j = 0;
   while (T[i][j][0]) {        // look for null char at T[i][j][0]
      while (T[i][j][0]) {
         cout << left << setw(20) << T[i][j];// string at T[i][j]
         j++;
      }
      cout << endl;
      i++; j = 0;
   }
   cout << endl;
}


void eraseTable(char T[100][100][80])
{
   // erase the destination array
   for (int i = 0; i < 100; i++)          // rows
      for (int j = 0; j < 100; j++)      // cols
         for (int k = 0; k < 80; k++)   // chars
            T[i][j][k] = 0;

}


void eraseArray(int A[], int size)
{
   for (int i = 0; i < size; i++)
      A[i] = 0;
}

void filltable(const char filename[80], char Table[100][100][80])
{
   // open source file
   ifstream fin(filename);
   if (!fin) { cerr << "Input file could not be opened\n"; exit(1); }

   char line[80];
   char buf[80];

   // table rows and cols
   int row = 0; int col = 0;

   // Copy file into table
   fin.getline(line, 80);
   while (line[0]) {
      col = 0;   // reset col
      //cout << line << endl << endl;

      // parse this line
      int i = 0; int j = 0;
      int len = strlen(line);
      for (i = 0; i <= len; i++) {
         if ((line[i] == ',') || (line[i] == 0)) { // delimiters
            strncpy(buf, line + j, i - j);
            buf[i - j] = 0;  // null terminator
            j = i + 1;         // scoot up j

            // copy buffer to table array
            strcpy(Table[row][col], buf);
            col++;
            //cout << "Hey: " <<  buf << endl;
         }
      }

      // get another line
      fin.getline(line, 80);
      row++;
   }
}


void select(char Tout[100][100][80], char Tin[100][100][80], int col, const char* value)
{
   // erase the destination array
   eraseTable(Tout);

   // YOU WRITE THIS
    int i1 = 0;
    int i2 = 0;
    int j = 0;

    while (Tin[i1][0][0]) {
        if (strcmp(Tin[i1][col], value) == 0) {
            while (Tin[i1][j][0]) {
               strcpy(Tout[i2][j], Tin[i1][j]);
               j++;
            }
            
            i2++;
        }
        
        i1++;
        j = 0;
    }

}


/*
Performs a project operation on a table.

Receives a table.
Returns a table consisting of the specified cols.
*/
void project(char Tout[100][100][80], char Tin[100][100][80], int cols[100])
{
   eraseTable(Tout);

    int i = 0;
    int j1 = 0;
    int j2 = 0;
    
    while (Tin[i][0][0]) {
        while(Tin[i][j1][0]) {
            if (cols[j1]) {
                strcpy(Tout[i][j2], Tin[i][j1]);
                j2++;
            }
            j1++;
        }
        i++;
        j1 = 0;
        j2 = 0;
    }
    
}


/*
Performs a join operation on a table.

Receives 2 tables and joins them.
Returns only the rows where the value in table1's T1col
matches the value in table2's T2col
*/
void join(char Tout[100][100][80], char T1[100][100][80], char T2[100][100][80], int T1col, int T2col)
{
   eraseTable(Tout);

    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    int j1 = 0;
    int j2 = 0;
    int j3 = 0;
    

    while (T1[i1][0][0]) {
       

       while (T2[i2][0][0]) {

          if (strcmp(T1[i1][T1col], T2[i2][T2col]) == 0) {

             while (T1[i1][j1][0]) {
                strcpy(Tout[i3][j3], T1[i1][j1]);
                j1++;
                j3++;
             }

              
             while (T2[i2][j2][0]) {
                if (j2 != T2col) {
                   strcpy(Tout[i3][j3], T2[i2][j2]);
                   j3++;
                }
                j2++;
             }

            i3++;
            j1 = j2 = j3 = 0;
          }

          i2++;
       }

        i1++;
        i2 = 0;
    }
 

        
        

}

/*
Makes a 3rd table containing all the stuff in 2 other tables.
The 2 input tables must have the same schema.
*/
void Union(char Tout[100][100][80], char T1[100][100][80], char T2[100][100][80])
{
   eraseTable(Tout);

    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    int j = 0;
    
    while (T1[i1][0][0]) {
        while (T1[i1][j][0]) {
            strcpy(Tout[i3][j], T1[i1][j]);
            j++;
        }
        j = 0;
        i1++;
        i3++;
    }
    while (T2[i2][0][0]) {
        while (T2[i1][j][0]) {
            strcpy(Tout[i3][j], T2[i2][j]);
            j++;
        }
        j = 0;
        i2++;
        i3++;
    }

}


int main(void)
{
   filltable("/Users/mengfeijin/Desktop/CISP 440 relations/Professors.txt", T1);
   filltable("/Users/mengfeijin/Desktop/CISP 440 relations/Students.txt", T2);

   cout << "Original Professors table:\n";
   printTable(T1);

   cout << "Original Students table:\n";
   printTable(T2);

   // select
   // locals are created in the stack (except statics)
   // so use a static to prevent stack overflow
   static char Temp1[100][100][80];
   select(Temp1, T2, 1, "555 Riley");
   cout << "\nSELECT TEST: Temp1 = Students[Address = 555 Riley]\n";
   printTable(Temp1);

   // project
   cout << "\nPROJECT TEST: Temp2 = Students[Name, Phone]\n";
   static char Temp2[100][100][80];
   // dynamic arrays are also easy on the stack
   // cuz they point to the heap
   int* cols = new int[100];  eraseArray(cols, 100);
   cols[0] = cols[2] = 1;
   project(Temp2, T2, cols);
   printTable(Temp2);

   // join
   cout << "\nJOIN TEST: Temp3 = Students[address = address]Professors\n";
   static char Temp3[100][100][80];
   join(Temp3, T1, T2, 1, 1);
   printTable(Temp3);

   // union
   cout << "\nUNION TEST: Temp4 = Students UNION MoreStudents\n";
   static char T3[100][100][80];
   filltable("/Users/mengfeijin/Desktop/CISP 440 relations/MoreStudents.txt", T3);
   static char Temp4[100][100][80];
   Union(Temp4, T2, T3);
   printTable(Temp4);

}
