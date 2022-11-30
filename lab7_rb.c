 //Lab 7 Simon Says
 //Raja Batra
 //November 1, 2021

 //ec:randomly generated sequen
#include <stdint.h>
#include <stdbool.h>
#include

typedef struct {
    volatile uint32_t value;
    volatile uint32_t input_en;
    volatile uint32_t output_en;
    volatile uint32_t output_val;
    volatile uint32_t pue;
    volatile uint32_t ds;
    volatile uint32_t rise_ie;
    volatile uint32_t rise_ip;
    volatile uint32_t fall_ie;
    volatile uint32_t fall_ip;
    volatile uint32_t high_ie;
    volatile uint32_t high_ip;
    volatile uint32_t low_ie;
    volatile uint32_t low_ip;
    volatile uint32_t iof_en;
    volatile uint32_t iof_sel;
    volatile uint32_t out_xor;
} GPIO;
#define GPIO0_BASE (0x10012000U)
#define GPIO0 ((GPIO *) GPIO0_BASE)
#define BUTTON1 2
#define BUTTON2 9
#define LED1 0
#define LED2 1
#define N 500000

volatile int roundN = 2; 
volatile int current = 2;
bool game; 
int buttonSequence[12] = {1,1,0,1,0,0,1,1,0,1,0,1};
  17

void setup(){
    GPIO0-> iof_en &= ~(1 << 2); //set top button
    GPIO0-> input_en |= (1 << 2);

    GPIO0-> iof_en &= ~(1 << 0); //set top led
    GPIO0-> output_en |= (1 << 0);

    GPIO0-> iof_en &= ~(1 << 9); //set bottom button
    GPIO0-> input_en |= (1 << 9);

    GPIO0-> iof_en &= ~(1 << 1); //set bottom led
    GPIO0-> output_en |= (1 << 1);
}

void myWriter(int gpio_pin, int val) {
    if (val) GPIO0->output_val |= (1 << gpio_pin); 
    else GPIO0->output_val &= ~(1 << gpio_pin);
}
int myReader(int gpio_pin) {
    return (GPIO0->value >> gpio_pin) & 0x1;
}

int clicked() { //return whic button is pressed
  if (myReader(BUTTON1) != 0) {
    return 0;
  } else if (myReader(BUTTON2) != 0) {
    return 1;
  }  else {
    return 2;   
  }
}


int main(void) {
    setup();
    while(1){      
  volatile int k;
   volatile int j;
  if (game == false) {  //check if game needs to be restarted 
    roundN = 1;           
    for(k=0;k<N;k++); 
    for (j=0;j<13;j++){
        buttonSequence[j]= rand() % 2;
    }               
    game = true;         
  }
    volatile int i;
    
    for (i = 0; i <= roundN; i++) { //loop to show leds
    myWriter(buttonSequence[i], 1);
    for(k=0;k<N;k++);//delqy
    myWriter(buttonSequence[i], 0);                                   
    for(k=0;k<N;k++);//delay
  }
  for (int i = 0; i <= roundN; i++) { //loop to check if buttons clicked are right
    while (game == true) { 
      current = clicked();      
      if (current < 2) {                
        if (current == buttonSequence[i]) { 
          for(k=0;k<N;k++);                  
          break;                        
        } else {                          
          game = false;              
          break;                        
        }
      }  
    }
  }

  if (game == true) {  //check to go to next round
    roundN = roundN + 1;      
    if (roundN >= 11) {              
      game=false;                     
    }
    for(k=0;k<N;k++);                           
  }
}

}


    
