
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BYTES_TRANSACTION  34
#define BYTES_TIMESTAMP 19
#define BYTES_VEHICULO 8
#define BYTES_PRODUCT 1
#define BYTES_MILITERS 4
#define BYTES_TRANSACTION_ID 2
#define BYTES_DD 2
#define BYTES_MM 2
#define BYTES_YY 2
#define BYTES_HH 6

char aux_1[];
char aux_2[];
char aux_time[];
char aux_id[];
char aux_ml[];
char aux_pr[];
char aux_vh[];
char aux_dd[];
char aux_mm[];
char aux_yy[];
char aux_hh[];

char log_1[];
char log_id[];
char log_time[];
char log_vh[];
char log_ml[];
char log_pr[];
char log_sys[];
int  num_bytes;


int log_transactions(const char *data, char *log, size_t transaction_count)
{
        num_bytes = transaction_count * BYTES_TRANSACTION;


        ////// Con este for() se lee cada transacción que se ha guardada en el buffer /////////// 

        for (int i = 0; i < transaction_count; ++i)
        {    
                      
            strcpy (aux_1, data+i);  // Obtengo el Valor de la Transaccion 
             
             
            //////Se separa los bytes de la transaccion /////
            
            strncpy(aux_time, aux_1, BYTES_TIMESTAMP); // Separa los Byte correspondientes timestamp [mm/dd/yyyy hh:mm:ss]
            strncpy(aux_vh, aux_1 + BYTES_TIMESTAMP, BYTES_VEHICULO); // Separa los Byte correspondientes vehicle_registration
            strncpy(aux_pr, aux_1 + BYTES_TIMESTAMP + BYTES_VEHICULO, BYTES_PRODUCT); // Separa los Byte correspondientes product
            strncpy(aux_ml, aux_1 + BYTES_TIMESTAMP + BYTES_VEHICULO + BYTES_PRODUCT, BYTES_MILITERS); // Separa los Byte correspondientes mililiters
            strncpy(aux_id, aux_1 + BYTES_TIMESTAMP + BYTES_VEHICULO + BYTES_PRODUCT + BYTES_MILITERS2, BYTES_TRANSACTION_ID); // Separa los Byte correspondientes transaction_id


           ////// Con esta funcion se acomoda la fecha con el nuevo formato [dd/mm/yy hh:mm:ss] ///////
           formato_fecha(&aux_time);

            
          ////// Se genera el log de la transaccion //////////////////////////////////

            // [dd/mm/yy hh:mm:ss] id: DDDDD  
            strcat(log_time, aux_time);
            strcat(log_id, ' id: ');
            strcat(log_id, aux_id);

            // reg: AAA 1111
            strcat(log_vh, ' reg: ');
            strcat(log_vh, aux_vh);

            // prod: A
            strcat(log_pr, ' prod: ');
            strcat(log_pr, aux_pr);
            
            // ltrs: ±DDDDDDD\n
            strcat(log_ml, ' ltrs: ');
            strcat(log_ml, aux_ml);

            // Se combina cada uno de los log auxiliares 
            strcat(log_1, log_time);
            strcat(log_1, log_id);
            strcat(log_1, ',');
            strcat(log_1, log_vh);
            strcat(log_1, ',');
            strcat(log_1, log_pr);
            strcat(log_1, ',');
            strcat(log_1, log_ml);


           // Pongo el Valor de Log en el puntero

           *(log+i)= log_1;


        }


      ////// Con esta funcion se ordenadas por fecha de menos recientes a las más recientes /////////////////////
      ordenar_fecha(log, transaction_count);

      return num_bytes;


}


void ordenar_fecha(char *log, size_t transaction_count) {}
    
  




void formato_fecha(char *aux_time) 
{
   strcpy (aux_2, aux_time); // mm/dd/yyyy hh:mm:ss

   // Separo los bytes correspondientes a mm
   strncpy(aux_dd, aux_2, BYTES_DD); 
    
   // Separo los bytes correspondientes a dd
   strncpy(aux_mm, aux_2+BYTES_DD+1, BYTES_MM); 
    
   // Separo los bytes correspondientes a yy
   strncpy(aux_yy, aux_2+BYTES_DD+BYTES_MM+1, BYTES_YY); 
   
   // Separo los bytes correspondientes a  hh:mm:ss
   strncpy(aux_hh, aux_2+BYTES_DD+BYTES_MM+BYTES_YY+1, BYTES_HH); 

   // Los acomodo al nuevo formato dd/mm/yy hh:mm:ss
   

   // A la fecha con el nuevo formato lo guardo 
   *aux_time = aux_2;

}



int main(void)
{

 return 0;
 

}