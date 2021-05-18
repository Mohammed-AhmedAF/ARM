#include "LCD_interface.h"




char * name = "Mohamed \0";

int main(void) {
	LCD_vidInit();
	LCD_vidWriteString(name);
}