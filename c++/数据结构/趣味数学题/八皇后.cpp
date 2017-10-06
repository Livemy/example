#include <windows.h>
#include <stdio.h>
#define BOARD_ROWS 8 
#define BOARD_COLS 8 

int count =0; 
struct chess_board 
{ 
   int board_array[BOARD_ROWS][BOARD_ROWS]; 
   int chess_number; 
}; 
void init_chess_board(chess_board *ptr_board) 
{ 
   memset(ptr_board, 0, sizeof(chess_board)); 
} 

void print_result(chess_board *ptr_board) 
{ 
   printf("result: \n"); 
   for(int i=0; i<BOARD_ROWS; i++) 
   { 
     for(int j=0; j<BOARD_COLS; j++) 
         if(ptr_board->board_array[i][j] ==1) 
             printf("%1d ", ptr_board->board_array[i][j]); 
         else 
             printf("%1d ", 0); 
      
     printf("\n"); 
   } 
  

} 
void put_chess(chess_board *ptr_board, int row, int col) 
{ 
   //��������в��ܷ��ӵĵ�д��2 
   for(int i=0; i<BOARD_ROWS; i++) 
     if(ptr_board->board_array[i][col] ==0) 
         ptr_board->board_array[i][col] = 2; 

   for(int j=0; j<BOARD_COLS; j++) 
       if(ptr_board->board_array[row][j] ==0) 
       ptr_board->board_array[row][j] = 2;   

   for(i=row,j=col; i>=0 && j>=0; i--,j--) 
       if(ptr_board->board_array[i][j] ==0) 
         ptr_board->board_array[i][j] = 2;   

   for(i=row,j=col; i<BOARD_ROWS && j< BOARD_COLS; i++,j++) 
       if(ptr_board->board_array[i][j] ==0) 
         ptr_board->board_array[i][j] = 2;   
    
   for(i=row,j=col; i<BOARD_ROWS && j>=0; i++,j--) 
       if(ptr_board->board_array[i][j] ==0) 
         ptr_board->board_array[i][j] = 2;   

   for(i=row,j=col; i>=0 && j<=BOARD_COLS; i--,j++) 
       if(ptr_board->board_array[i][j] ==0) 
         ptr_board->board_array[i][j] = 2; 

   ptr_board->board_array[row][col] = 1; 
   ptr_board->chess_number++; 
} 

int try_chess(chess_board * ptr_board, int row, int col) 
{ 
 chess_board temp; 
 for(int i=0; i<BOARD_ROWS; i++) 
     for(int j=0; j<BOARD_COLS; j++) 
         if(ptr_board->board_array[i][j] == 0)  //ֻ�е���0�ĵ���ܷ��� 
         { 
             memcpy(&temp, ptr_board, sizeof(chess_board)); 
             put_chess(ptr_board, i, j); 
             if( 8 == ptr_board->chess_number ) 
             { 
                 print_result(ptr_board); 
               count++; 
               return 1; 
             } 
             if(try_chess(ptr_board, i, j)) 
                 return 1; 
             memcpy(ptr_board, &temp, sizeof(chess_board)); 
         } 

  
 return  0; 
} 

/*˼· 
 Ϊÿһ�������try_chess�ҳ�һ�ֽ�� 
*/ 
int main(int argc, char *argv[]) 
{   
 chess_board main_board; 
 for(int i=0; i<4; i++) 
     for(int j=0; j<8; j++) 
     { 
         init_chess_board(&main_board); 
         put_chess(&main_board, i, j); 
         try_chess(&main_board, i,j); 
     } 

     printf("����%d�����", count); 
return 0; 
} 