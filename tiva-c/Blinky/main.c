#define RCGCGPIO *((unsigned int *) 0x400FE608)
#define GPIOF_DIR *((unsigned int *) 0x40025400)
#define GPIOF_DEN *((unsigned int *) 0x4002551C)
#define GPIOF_DATA *((unsigned int *) 0x400253FC)


#define GREEN_LED (1U<<3)

void delay(int time); //A delay function

int main(void)
{
    RCGCGPIO |= (1U<<5);
    GPIOF_DIR |= GREEN_LED;
    GPIOF_DEN |= GREEN_LED;

    while(1) {
				delay(2000000);
		    GPIOF_DATA ^= GREEN_LED;
				delay(2000000);

		}

	return 0;
}

void delay(int time) {
	int delay = 0;
	while (delay < time) {
		delay++;
}
}
