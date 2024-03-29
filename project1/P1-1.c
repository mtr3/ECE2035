/*            Diamond Sort


<date>     	               <your name here>

This program sorts a diamond array of disks of varying hues and
diameters. */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   int	Array[169];
   int	NumVals;
   int  Load_Mem(char *, int *);
   void	Print_Array(int *);

   if (argc != 2) {
     printf("usage: %s valuefile\n", argv[0]);
     exit(1);
   }
   NumVals = Load_Mem(*++argv, Array);
   if (NumVals != 85) {
      printf("not enough values in %s\n", argv[0]);
      exit(1);
   }

// Code starts here

  /*   
   int i = 0;
   int count = 0;
   for (int i = 0; i < 169; i++)
   {
      printf("%02i:%02i  " , Array[i] / 64, Array[i] % 64);
      count++;
      if (count == 13)
      {
         printf("\n");
         count = 0;
      }
   }
   */
   

   /********************** Inefficient Algorithm for C *************************
    **********************************************************************/
   int i = 0;
   int k = 0;
   int c = 0;
   int j = 0;
   int hue1,hue2,diam1,diam2;
   int temp;
   for (k = 0; k < 10; k++)      // Arbitrary value selected until sorted
   {
      for (i = 0; i < 13; i++)           
      {
         for (c = 0; c < 13; c++)                    // Sort Hues
          {
              for (j = c + 1; j < 13; ++j)
              {
               hue1 = Array[c + (i * 13)] % 64;
               hue2 = Array[j + (i * 13)] % 64;
                  if (hue1 > hue2 && Array[c + (i * 13)] != -1 && Array[j + (i * 13)] != -1)        
                  {
                      temp =  Array[c + (i * 13)];          
                      Array[c + (i * 13)] = Array[j + (i * 13)];
                      Array[j + (i * 13)] = temp;

                  }
              }
          }
          for (c = 0; c < 169; c = c + 13)           // Sort Diameter
          {
              for (j = c + 13; j < 169; j = j + 13)
              {
               diam1 = Array[c + i] / 64;
               diam2 = Array[j + i] / 64;
                  if (diam1 > diam2 && Array[c + i] != -1 && Array[j + i] != -1)        
                  {
                      temp =  Array[c + i];          
                      Array[c + i] = Array[j + i];
                      Array[j + i] = temp;

                  }
              }
          }
      }
   }

   printf("\n\n");

   Print_Array(Array);
   exit(0);
}

/* This routine initializes a 13 x 13 array with zeros. Then it loads
85 memory elements from the input file. The values are loaded in
address: value tuples. The first value is loaded into position 6. All
other values are positioned relative to the address of the first word.
The number of loaded values are returned. */

int Load_Mem(char *InputFileName, int Array[]) {
   int	N, Addr, Value, Index, NumVals;
   int	Base = -1;
   FILE	*FP;

   for (N=0; N < 169; N++)
     Array[N] = -1;
   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
      printf("%s could not be opened; check the filename\n", InputFileName);
      return 0;
   } else {
      for (N=0; N < 85; N++) {
         NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
         if (NumVals != 2)
            break;
         else
            if (Base == -1)
               Base = Addr - 24;
            Index = (Addr - Base) / 4;
            Array[Index] = Value;
      }
      fclose(FP);
      return N;
   }
}

/* This routine prints a diamond. The hue and diameter are unpacked before printing.
Empty array cells are printed as blanks. */

void Print_Array(int Array[]) {
   int	N, Value, Diameter, Hue;

   for (N=0; N < 169; N++) {
      Value = Array[N];
      if (Value == -1)
         printf("      ");
      else {
         Diameter = Value / 64;
         Hue = Value % 64;
         printf("%02d:%02d ", Diameter, Hue);
      }
      if ((N % 13) == 12)
         printf("\n");
   }
}
