#define DCSBIOS_IRQ_SERIAL
#define  BLACK   0x0000
#define WHITE    0xFFFF
#define GREEN    0x07E0
#include "DcsBios.h"
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

//if the IC model is known or the modules is unreadable,you can use this constructed function
LCDWIKI_KBV mylcd(ILI9486,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset

uint16_t text_color = WHITE;
float leftnozzleangle = 0.0;
float rightnozzleangle = 0.0;

void onCockkpitLightModeSwChange(unsigned int newValue) {
    switch (newValue)
	{
	case 0:
		text_color = WHITE;
		break;
	case 1:
		text_color = GREEN;
		break;
	case 2:
		text_color = GREEN;
	}
	display_layout();
}
DcsBios::IntegerBuffer cockkpitLightModeSwBuffer(0x74c8, 0x0600, 9, onCockkpitLightModeSwChange);

void draw_text(char* text, int16_t x, int16_t y, uint8_t max, int align, int visible){
    String txt = String(text);
    txt.trim();
    int len = txt.length();
    int offset = 0;
	switch(align) {
		case 1:
        offset = (20 * (max - len) / 2) + (4 * (max - len) / 2);
		break;
		case 2:
        offset = (20 * (max - len)) + (4 * (max - len));
		break;
	}
    if (visible == 0) {
        txt = " ";
        for(int i = 0; i < max; i++){
            txt += " ";
        }
    } else {
        String temp = "";
        for(int i = 0; i < max - len; i++){
            temp += " ";
        }
        txt = temp + txt;
    }
     mylcd.Print_String(txt, x, y);
     //mylcd.Print_String(String(len),10,40);
     //mylcd.Print_String(text,10,80);
     //mylcd.Print_String(String(len),x,y);
}

void draw_hour(char* h, int16_t x, int16_t y){
	mylcd.Set_Text_Size(4);
	mylcd.Print_String(h,x,y);
}
void draw_minute(char* m, int16_t x, int16_t y){
	mylcd.Set_Text_Size(4);
	mylcd.Print_String(m,x+58,y);
}
void draw_second(char* s, int16_t x, int16_t y){
	mylcd.Set_Text_Size(4);
	mylcd.Print_String(s,x+116,y);
}
void draw_time_colons(int16_t x, int16_t y){
	mylcd.Set_Text_Size(3);
	mylcd.Print_String(":",x+44,y+5);
	mylcd.Set_Text_Size(3);
	mylcd.Print_String(":",x+102,y+5);
}
void onIfeiBingoChange(char* newValue) {
   mylcd.Set_Text_Size(4);
   draw_text(newValue,320,160,6,2,1);
}
DcsBios::StringBuffer<5> ifeiBingoBuffer(0x7468, onIfeiBingoChange);
void onIfeiRpmLChange(char* newValue) {
    mylcd.Set_Text_Size(4);
    draw_text(newValue,0,40,3,2,1);
}
DcsBios::StringBuffer<3> ifeiRpmLBuffer(0x749e, onIfeiRpmLChange);
void onIfeiRpmRChange(char* newValue) {
    mylcd.Set_Text_Size(4);
    draw_text(newValue,200,40,3,2,1);
}
DcsBios::StringBuffer<3> ifeiRpmRBuffer(0x74a2, onIfeiRpmRChange);
void onIfeiTempLChange(char* newValue) {
    mylcd.Set_Text_Size(4);
    draw_text(newValue,0,80,3,2,1);
}
DcsBios::StringBuffer<3> ifeiTempLBuffer(0x74a6, onIfeiTempLChange);
void onIfeiTempRChange(char* newValue) {
    mylcd.Set_Text_Size(4);
    draw_text(newValue,200,80,3,2,1);
}
DcsBios::StringBuffer<3> ifeiTempRBuffer(0x74aa, onIfeiTempRChange);
void onIfeiFfLChange(char* newValue) {
    mylcd.Set_Text_Size(4);
    draw_text(newValue,00,120,3,2,1);
}
DcsBios::StringBuffer<3> ifeiFfLBuffer(0x7482, onIfeiFfLChange);
void onIfeiFfRChange(char* newValue) {
    mylcd.Set_Text_Size(4);
    draw_text(newValue,200,120,3,2,1);
}
DcsBios::StringBuffer<3> ifeiFfRBuffer(0x7486, onIfeiFfRChange);
void onIfeiFuelUpChange(char* newValue) {
    mylcd.Set_Text_Size(4);
    draw_text(newValue,320,40,6,2,1);
}
DcsBios::StringBuffer<6> ifeiFuelUpBuffer(0x7490, onIfeiFuelUpChange);
void onIfeiFuelDownChange(char* newValue) {
    mylcd.Set_Text_Size(4);
    draw_text(newValue,320,80,6,2,1);
}
DcsBios::StringBuffer<6> ifeiFuelDownBuffer(0x748a, onIfeiFuelDownChange);
void onIfeiDd1Change(char* newValue) {
    
}
DcsBios::StringBuffer<1> ifeiDd1Buffer(0x747a, onIfeiDd1Change);

void onIfeiDd2Change(char* newValue) {
    
}
DcsBios::StringBuffer<1> ifeiDd2Buffer(0x747c, onIfeiDd2Change);
void onIfeiDd3Change(char* newValue) {
    /* your code here */
}
DcsBios::StringBuffer<1> ifeiDd3Buffer(0x747e, onIfeiDd3Change);
void onIfeiDd4Change(char* newValue) {
    /* your code here */
}
DcsBios::StringBuffer<1> ifeiDd4Buffer(0x7480, onIfeiDd4Change);

void onIfeiClockHChange(char* newValue) {
	draw_hour(newValue,300,240);
}
DcsBios::StringBuffer<2> ifeiClockHBuffer(0x746e, onIfeiClockHChange);

void onIfeiClockMChange(char* newValue) {
    draw_minute(newValue,300,240);
}
DcsBios::StringBuffer<2> ifeiClockMBuffer(0x7470, onIfeiClockMChange);

void onIfeiClockSChange(char* newValue) {
    draw_second(newValue,300,240);
}
DcsBios::StringBuffer<2> ifeiClockSBuffer(0x7472, onIfeiClockSChange);
void onIfeiTimerHChange(char* newValue) {
    draw_hour(newValue,300,280);
}
DcsBios::StringBuffer<2> ifeiTimerHBuffer(0x7474, onIfeiTimerHChange);
void onIfeiTimerMChange(char* newValue) {
    draw_minute(newValue,300,280);
}
DcsBios::StringBuffer<2> ifeiTimerMBuffer(0x7476, onIfeiTimerMChange);
void onIfeiTimerSChange(char* newValue) {
    draw_second(newValue,300,280);
}
DcsBios::StringBuffer<2> ifeiTimerSBuffer(0x7478, onIfeiTimerSChange);
void onIfeiOilPressLChange(char* newValue) {
    mylcd.Set_Text_Size(4);
    draw_text(newValue,0,280,3,2,1);
}
DcsBios::StringBuffer<3> ifeiOilPressLBuffer(0x7496, onIfeiOilPressLChange);
void onIfeiOilPressRChange(char* newValue) {
    mylcd.Set_Text_Size(4);
    draw_text(newValue,200,280,3,2,1);
}
DcsBios::StringBuffer<3> ifeiOilPressRBuffer(0x749a, onIfeiOilPressRChange);
void onIfeiBingoTextureChange(char* newValue) {
    mylcd.Set_Text_Size(3);
    draw_text("BINGO",345,125,5,0,String(newValue).toInt());
}
DcsBios::StringBuffer<1> ifeiBingoTextureBuffer(0x74c6, onIfeiBingoTextureChange);
void onIfeiFfTextureChange(char* newValue) {
    mylcd.Set_Text_Size(3);
    draw_text("FF",120,125,2,0,String(newValue).toInt());
}
DcsBios::StringBuffer<1> ifeiFfTextureBuffer(0x74c0, onIfeiFfTextureChange);
void onIfeiOilTextureChange(char* newValue) {
    mylcd.Set_Text_Size(3);
    draw_text("OIL",110,280,3,0,String(newValue).toInt());
}
DcsBios::StringBuffer<1> ifeiOilTextureBuffer(0x74c4, onIfeiOilTextureChange);
void onIfeiRpmTextureChange(char* newValue) {
    mylcd.Set_Text_Size(3);
    draw_text("RPM",110,45,3,0,String(newValue).toInt());
}
DcsBios::StringBuffer<1> ifeiRpmTextureBuffer(0x74bc, onIfeiRpmTextureChange);
void onIfeiTempTextureChange(char* newValue) {
    mylcd.Set_Text_Size(3);
    draw_text("TEMP",100,85,4,0,String(newValue).toInt());
}
DcsBios::StringBuffer<1> ifeiTempTextureBuffer(0x74be, onIfeiTempTextureChange);
void onIfeiRTextureChange(char* newValue) {
    mylcd.Set_Text_Size(2);
    draw_text("L",470,45,1,0,String(newValue).toInt());
    draw_text("R",470,85,1,0,String(newValue).toInt());
}
DcsBios::StringBuffer<1> ifeiRTextureBuffer(0x7584, onIfeiRTextureChange);
void onIfeiZTextureChange(char* newValue) {
    mylcd.Set_Text_Size(2);
    draw_text("z",470,255,1,0,String(newValue).toInt());
}
DcsBios::StringBuffer<1> ifeiZTextureBuffer(0x74dc, onIfeiZTextureChange);
void onIfeiSpChange(char* newValue) {
    mylcd.Set_Text_Size(4);
    draw_text(newValue,0,80,3,2,1);
}
DcsBios::StringBuffer<3> ifeiSpBuffer(0x74b2, onIfeiSpChange);
void onIfeiCodesChange(char* newValue) {
    mylcd.Set_Text_Size(4);
    draw_text(newValue,200,80,3,2,1);
}
DcsBios::StringBuffer<3> ifeiCodesBuffer(0x74ae, onIfeiCodesChange);
void onExtNozzlePosLChange(unsigned int newValue) {
    display_left_nozzle(0);
    leftnozzleangle = 1.5708 / 65535 * (65535 - newValue);
    display_left_nozzle(1);
}
DcsBios::IntegerBuffer extNozzlePosLBuffer(0x757a, 0xffff, 0, onExtNozzlePosLChange);
void onExtNozzlePosRChange(unsigned int newValue) {
    display_right_nozzle(0);
    rightnozzleangle = -1.5708 / 65535 * (65535 - newValue);
    display_right_nozzle(1);
}
DcsBios::IntegerBuffer extNozzlePosRBuffer(0x7578, 0xffff, 0, onExtNozzlePosRChange);
void demo_data(){
    mylcd.Set_Text_Size(4);
    draw_text("99",0,40,3,2,1);
    draw_text("99",200,40,3,2,1);
    draw_text("850",00,80,3,2,1);
    draw_text("850",200,80,3,2,1);
    draw_text("50", 00, 120,3,2,1);
    draw_text("50", 200, 120,3,2,1);
    draw_text("145", 00, 280,3,2,1);
    draw_text("145", 200, 280,3,2,1);
    draw_text("10540T",320,40,6,2,1);
    draw_text("10540I",320,80,6,2,1);
    draw_text("4000",320,160,6,2,1);
    onIfeiClockSChange("00");
    onIfeiTimerSChange("00");
}
void display_left_scale(int x, int y){
    float start = 0.0;
    float end = 1.5708;
    float steps = 10;
    int radius = 70;
    int len = 10;
    int line = 0;
    mylcd.Set_Text_Size(1);
    for(float i = start; i <= end; i+= (end - start)/steps){
        if((line == 0) || (line == 5) || (line == 10)){
            mylcd.Draw_Line(x + radius * sin(i), y + radius * cos(i), x + ((radius + len*2) * sin(i)), y + ((radius + len*2) * cos(i)));
            mylcd.Print_String(String(100 - line*10),x + ((radius + len*2 + 2) * sin(i)), y + ((radius + len*2 + 2) * cos(i)));
        } else {
            mylcd.Draw_Line(x + radius * sin(i), y + radius * cos(i), x + ((radius + len) * sin(i)), y + ((radius + len) * cos(i)));
        }
        line++;
    }
}
void display_right_scale(int x, int y){
    float start = 0.0;
    float end = -1.5708;
    float steps = 10;
    int radius = 70;
    int len = 10;
    int line = 0;
    mylcd.Set_Text_Size(1);
    for(float i = end; i <= start; i+= (-end - start)/steps){
        if((line == 0) || (line == 5) || (line == 10)){
            mylcd.Draw_Line(x + radius * sin(i), y + radius * cos(i), x + ((radius + len*2) * sin(i)), y + ((radius + len*2) * cos(i)));
            mylcd.Print_String(String(line*10),x + ((radius + len*2 + line) * sin(i)), y + ((radius + len*2) * cos(i)));
        } else {
            mylcd.Draw_Line(x + radius * sin(i), y + radius * cos(i), x + ((radius + len) * sin(i)), y + ((radius + len) * cos(i)));
        }
        line++;
    }
}

void display_left_nozzle(int vis){
    float start = 0.0;
    float end = 1.5708;
    int pstart = 10;
    int pend = 65;
    if (vis == 1){
        mylcd.Set_Draw_color(text_color);
    } else {
        mylcd.Set_Draw_color(BLACK);
    }
    mylcd.Draw_Line(20 + pstart * sin(leftnozzleangle), 170 + pstart * cos(leftnozzleangle), 20 + pend * sin(leftnozzleangle), 170 + pend * cos(leftnozzleangle));
}

void display_right_nozzle(int vis){
    float start = 0.0;
    float end = -1.5708;
    int pstart = 10;
    int pend = 65;
    if (vis == 1){
        mylcd.Set_Draw_color(text_color);
    } else {
        mylcd.Set_Draw_color(BLACK);
    }
    mylcd.Draw_Line(260 + pstart * sin(rightnozzleangle), 170 + pstart * cos(rightnozzleangle), 260 + pend * sin(rightnozzleangle), 170 + pend * cos(rightnozzleangle));
}

void display_layout() {
    mylcd.Set_Text_colour(text_color);
    mylcd.Set_Text_Size(4);
    mylcd.Print_String("L", 20, 0);
    mylcd.Print_String("ENGINE", 60, 0);
    mylcd.Print_String("R", 220, 0);
    mylcd.Set_Text_Size(3);
    mylcd.Print_String("RPM", 110, 45);
    mylcd.Print_String("TEMP", 100, 85);
    mylcd.Print_String("FF", 120, 125);
    mylcd.Print_String("OIL", 110, 280);
    mylcd.Print_String("FUEL", 355, 5);
    mylcd.Print_String("BINGO", 345, 125);
    mylcd.Print_String("TIME", 355, 205);
    draw_time_colons(300,240);
    draw_time_colons(300,280);
  
  // Separator
  mylcd.Set_Draw_color(WHITE);
  int i;
  for(i=288;i<293;i++){
    mylcd.Draw_Fast_VLine(i,0,mylcd.Get_Display_Height());
  }
  mylcd.Set_Draw_color(text_color);

  //Helpers para circulos
  //mylcd.Draw_Circle_Helper(20,170,70,4);
  //mylcd.Draw_Circle_Helper(20,170,80,4);
  //mylcd.Draw_Circle_Helper(260,170,70,8);
  //mylcd.Draw_Circle_Helper(260,170,80,8);

  //display_left_scale();
  display_left_scale(20, 170);
  display_right_scale(260,170);

  // L Nozzle
  /*mylcd.Set_Text_Size(1);
  mylcd.Draw_Line(110,170,120,170); // 0
  mylcd.Print_String("0",125,167);
  mylcd.Draw_Line(20,240,20,250); // 100
  mylcd.Print_String("100",12,255);
  mylcd.Draw_Line(60,210,65,215); // 50
  mylcd.Print_String("50",67,217);*/
}

void setup() {
    DcsBios::setup();
    //Serial.begin(9600);
    mylcd.Init_LCD(); //initialize lcd
    //Serial.println(mylcd.Read_ID(), HEX);
    mylcd.Set_Rotation(1);
    mylcd.Fill_Screen(BLACK);
    mylcd.Set_Text_Back_colour(BLACK);
    mylcd.Set_Text_colour(text_color);
    mylcd.Set_Text_Size(4);
    display_layout();
    demo_data();
    //draw_text("1      ",10,0,6,2,1);
   
    onExtNozzlePosLChange(65536/2);
    onExtNozzlePosRChange(65536/2);
}

void loop() {
  // put your main code here, to run repeatedly:
  DcsBios::loop();
}
