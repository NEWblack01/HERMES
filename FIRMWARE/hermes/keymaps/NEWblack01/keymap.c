#include QMK_KEYBOARD_H
#include "hermes.h"

#define _NUMPAD 0
#define _MACRO 1
#define _TESTS 2

bool is_alt_tab_active = false; //for alt tabbing
uint16_t alt_tab_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_NUMPAD] = KEYMAP /*DEFAULT*/(
		KC_NLCK,	KC_PSLS,	KC_PAST,	KC_PMNS,	KC_NO, 
		KC_P7,		KC_P8,		KC_P9,		KC_PPLS,	KC_NO, 
		KC_P4,		KC_P5,		KC_P6,		KC_TAB,		TO(1) /*LAYER KEY*/, 
		KC_P1,		KC_P2, 		KC_P3, 		RGB_TOG/*KC_BSPC*/, 	KC_NO /*ROTARY ENCODER 1 SWTITCH*/, 
		KC_PEQL, 	KC_P0, 		KC_PDOT, 	KC_PENT, 	KC_NO), /*ROTARY ENCODER 2 SWITCH*/
	/* Layer 1. Num pad keymap
		NumLock	|  /  |  *  |   -   |   null  |
		7		|  8  |  9  |   +   |	null  |
		4		|  5  |  6  |  tab  |   mod   |
		1		|  2  |  3  | backs | enc1 sw |
		=		|  0  | del | Enter | enc2 sw |
	*/

	[_MACRO] = KEYMAP /*MACRO LAYER*/(
		KC_F13,		KC_F14,		KC_F15,		KC_F16,		KC_NO, 
		KC_F17,		KC_F18,		KC_F19,		KC_F20,		KC_NO, 
		KC_F21,		KC_F22,		C(KC_F13),	C(KC_F14),	TO(2) /*LAYER KEY*/, 
		C(KC_F15),	C(KC_F16),	C(KC_F17), 	C(KC_F18), 	KC_NO /*ROTARY ENCODER 1 SWTITCH*/, 
		C(KC_F19), 	C(KC_F20), 	KC_F23, 	KC_F24, 	KC_NO)/*ROTARY ENCODER 2 SWITCH*/,
	/* Layer 2. Macro pad keymap
		M1	|  M2  |  M3  |   M4   |   M5  |
		M6  |  M7  |  M8  |   M9   |   M10 |
		M11	|  M12 |  M13 |   M14  |   M15 |
		M16	|  M17 |  M18 |   M19  |   M20 |
		M21	|  M22 |  M23 |   M24  |   M25 |
	*/
	[_TESTS] = KEYMAP /*TEST LAYER*/(
	RGB_TOG,	RGB_MOD,	RGB_M_B,		RGB_M_SW,	KC_NO, 
	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO, 
	KC_NO,		KC_NO,		KC_NO,		KC_NO,		TO(0) /*LAYER KEY*/, 
	KC_NO,		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO /*ROTARY ENCODER 1 SWTITCH*/, 
	KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO)/*ROTARY ENCODER 2 SWITCH*/,
	/* Layer 3. test keymap
		LED ON/OFF	|  CYCLE MODE  |  BREATHE MODE  |   SWIRL MODE   |   NO  |
		M6  |  M7  |  M8  |   M9   |   M10 |
		M11	|  M12 |  M13 |   M14  |   M15 |
		M16	|  M17 |  M18 |   M19  |   M20 |
		M21	|  M22 |  M23 |   M24  |   M25 |
	*/
};

#ifdef OLED_DRIVER_ENABLE
uint16_t startup_timer;//sets rotation of the oled and starts timer for logo, after timer regular information will appear

	oled_rotation_t oled_init_user(oled_rotation_t rotation){
		return OLED_ROTATION_270; //oled rotation
		startup_timer = timer_read(); //timer function
		return rotation;
	}

static void render_logo(void){ //function to render bitmap logo of hermes
	static const char PROGMEM NEWblack_logo[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x18, 0x00, 0x08, 0x18, 0xF8, 0xF8, 0x18,
		0x18, 0x18, 0x98, 0x18, 0x18, 0x38, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0x86,
		0x86, 0x8F, 0x9F, 0x80, 0x80, 0xC0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x81, 0xC1, 0x61, 0x31,
		0x31, 0x31, 0x61, 0xC1, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x30, 0x60, 0xC0,
		0xC0, 0xC0, 0x60, 0x30, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xC7, 0xC7, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x40, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x60, 0xC0, 0xC0,
		0xC0, 0x60, 0x60, 0x30, 0xFF, 0xFF, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x20, 0x20,
		0x40, 0x40, 0x40, 0x20, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x0E, 0x06, 0x03,
		0x03, 0x03, 0x03, 0x07, 0xFE, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0x1C, 0x06,
		0x06, 0x0E, 0x0E, 0x1C, 0x38, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0xC3, 0x87, 0x86,
		0x8E, 0x8C, 0xCC, 0x78, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xA0, 0x40, 0x00, 0xC0, 0xA0, 0xA0, 0x00, 0xE1, 0x01,
		0xC1, 0x21, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x20, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x02, 0x02, 0x00, 0x01, 0x02,
		0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x07, 0x0E, 0x3C, 0xF0, 0xC0, 0x00, 0x01, 0xFF, 0xFF,
		0x03, 0x01, 0xF8, 0xFC, 0x06, 0x02, 0x02, 0x02, 0x02, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x40, 0x7F, 0x7F, 0x40, 0x00, 0x00, 0x00, 0x03, 0x07, 0x1E, 0x3F, 0x7F,
		0x00, 0x00, 0xFF, 0xFF, 0x80, 0x00, 0x03, 0x03, 0x03, 0x06, 0xFC, 0xF8, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x38, 0x00, 0x44, 0x7C, 0x40, 0x00, 0x00,
		0x00, 0x00, 0x3F, 0x3F, 0x01, 0x01, 0x02, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00

	};

	oled_write_raw_P(NEWblack_logo, sizeof(NEWblack_logo)); //writes logo

}

void render_info(void){ //regular info rendering function. Heavily inspired in YamPAD OLED display https://hackaday.io/project/163491-yampad-feature-packed-open-source-macropad

	
	oled_write_P(PSTR("LAYER"), false); 

	switch (get_highest_layer(layer_state)) {
		case _NUMPAD:
			oled_write_P(PSTR(" NUM "),false);
			break;
		case _MACRO:
			oled_write_P(PSTR(" MAC "),false);
			break;
		case _TESTS:
			oled_write_P(PSTR(" TST "),false);
			break;
		default:
			oled_write_P(PSTR("UNDEFINED\n"),false);
	}
	oled_write_P(PSTR("-----Stuff"),false);

	led_t led_state = host_keyboard_led_state();
	oled_write_P(PSTR("num:"),false);
	oled_write_P(led_state.num_lock ? PSTR("*") : PSTR("-"),false);
	oled_write_P(PSTR("cap:"),false);
	oled_write_P(led_state.caps_lock ? PSTR("*") : PSTR("-"),false);
	oled_write_P(PSTR("scr:"),false);
	oled_write_P(led_state.scroll_lock ? PSTR("*") : PSTR("-"),false);

	oled_write_P(PSTR("-----"),false);
	//RGB on or off and in what mode it is
	oled_write_P(PSTR("Light"),false);
	//oled_write_P(PSTR("RGB: "),false);
	oled_write_P(PSTR("M:"),false);
	switch(rgblight_get_mode()) {
		case RGBLIGHT_MODE_STATIC_LIGHT:
			oled_write_P(PSTR("-SL"),false);
			break;
		case RGBLIGHT_MODE_BREATHING:
			oled_write_P(PSTR("-B0"),false);
			break;
		case RGBLIGHT_MODE_BREATHING + 1:
			oled_write_P(PSTR("-B1"),false);
			break;
		case RGBLIGHT_MODE_BREATHING + 2:
			oled_write_P(PSTR("-B2"),false);
			break;
		case RGBLIGHT_MODE_BREATHING + 3:
			oled_write_P(PSTR("-B3"),false);
			break;
		case RGBLIGHT_MODE_RAINBOW_MOOD:
			oled_write_P(PSTR("-M0"),false);
			break;
		case RGBLIGHT_MODE_RAINBOW_MOOD + 1:
			oled_write_P(PSTR("-M1"),false);
			break;
		case RGBLIGHT_MODE_RAINBOW_MOOD + 2:
			oled_write_P(PSTR("-M2"),false);
			break;
		case RGBLIGHT_MODE_RAINBOW_SWIRL:
			oled_write_P(PSTR("SW0"),false);
			break;
		case RGBLIGHT_MODE_RAINBOW_SWIRL + 1:
			oled_write_P(PSTR("SW1"),false);
			break;
		case RGBLIGHT_MODE_RAINBOW_SWIRL + 2:
			oled_write_P(PSTR("SW2"),false);
			break;
		case RGBLIGHT_MODE_RAINBOW_SWIRL + 3:
			oled_write_P(PSTR("SW3"),false);
			break;
		case RGBLIGHT_MODE_RAINBOW_SWIRL + 4:
			oled_write_P(PSTR("SW4"),false);
			break;
		case RGBLIGHT_MODE_RAINBOW_SWIRL + 5:
			oled_write_P(PSTR("SW5"),false);
			break;
		case RGBLIGHT_MODE_SNAKE:
			oled_write_P(PSTR("SN0"),false);
			break;
		case RGBLIGHT_MODE_SNAKE + 1:
			oled_write_P(PSTR("SN1"),false);
			break;
		case RGBLIGHT_MODE_SNAKE + 2:
			oled_write_P(PSTR("SN2"),false);
			break;
		case RGBLIGHT_MODE_SNAKE + 3:
			oled_write_P(PSTR("SN3"),false);
			break;
		case RGBLIGHT_MODE_SNAKE + 4:
			oled_write_P(PSTR("SN4"),false);
			break;
		case RGBLIGHT_MODE_SNAKE + 5:
			oled_write_P(PSTR("SN5"),false);
			break;
		case RGBLIGHT_MODE_STATIC_GRADIENT:
			oled_write_P(PSTR("SG0"),false);
			break;
		case RGBLIGHT_MODE_STATIC_GRADIENT + 1:
			oled_write_P(PSTR("SG1"),false);
			break;
		case RGBLIGHT_MODE_STATIC_GRADIENT + 2:
			oled_write_P(PSTR("SG2"),false);
			break;
		case RGBLIGHT_MODE_STATIC_GRADIENT + 3:
			oled_write_P(PSTR("SG3"),false);
			break;
		case RGBLIGHT_MODE_STATIC_GRADIENT + 4:
			oled_write_P(PSTR("SG4"),false);
			break;
		case RGBLIGHT_MODE_STATIC_GRADIENT + 5:
			oled_write_P(PSTR("SG5"),false);
			break;
		case RGBLIGHT_MODE_STATIC_GRADIENT + 6:
			oled_write_P(PSTR("SG6"),false);
			break;
		case RGBLIGHT_MODE_STATIC_GRADIENT + 7:
			oled_write_P(PSTR("SG7"),false);
			break;
		case RGBLIGHT_MODE_STATIC_GRADIENT + 8:
			oled_write_P(PSTR("SG8"),false);
			break;
		case RGBLIGHT_MODE_STATIC_GRADIENT + 9:
			oled_write_P(PSTR("SG9"),false);
			break;
		default:
			oled_write_P(PSTR("off"),false);
	}
	oled_write_P(PSTR("-----"),false);
	
	//encoder1 and encoder 2 functions
	switch (get_highest_layer(layer_state)) {
		case _NUMPAD:
			oled_write_P(PSTR("E1:TB"),false);//VOLUME
			oled_write_P(PSTR("E2:UD"),false);//UP DOWN
			break;
		case _MACRO:
			oled_write_P(PSTR("E1:CZ"),false);//UNDO REDO
			oled_write_P(PSTR("E2:VL"),false);//VOL UP DOWN
			break;
		case _TESTS:
			oled_write_P(PSTR("E1:HU"),false);//HUE UP DOWN
			oled_write_P(PSTR("E2:VA"),false);//VALUE UP DOWN
			break;
		default:
			oled_write_P(PSTR("E1:ND"),false);//UNDEFINED
			oled_write_P(PSTR("E2:ND"),false);//UNDEFINED
	}
}


void oled_task_user(void) {	//writing in the actual oled function
	static bool finished_logo = false;

	if((timer_elapsed(startup_timer)<3000) && (finished_logo==false)){ //if timer less than 3s and logo finished is false logo will be rendered
		render_logo();
	}

	else {
		finished_logo = true; //after 3s had passed, logo regular info will appear and logo will no longer be called again.
		
		render_info();
	}
}

void encoder_update_kb(uint8_t index, bool clockwise){
	switch(get_highest_layer(layer_state)){
    	case _NUMPAD:
			if(index==0){ //alt tab code courtesy of https://docs.splitkb.com/hc/en-us/articles/360010513760-How-can-I-use-a-rotary-encoder-
				if(clockwise){
					if (!is_alt_tab_active)
					{
						is_alt_tab_active=true;
						register_code(KC_LALT);
					}
					alt_tab_timer = timer_read();
					tap_code16(KC_TAB);
				} 
				else{
					alt_tab_timer = timer_read();
					tap_code16(S(KC_TAB));
				}
			}
			else if(index==1){ //mouse wheel
				if (clockwise)
				{
					tap_code16(KC_WH_U);
				}
				else{
					tap_code16(KC_WH_D);
				}
			}
			break;
		case _MACRO:
			if(index==0){
				if (clockwise)
				{
					tap_code16(C(KC_Z)); //undo
				}
				else{
					tap_code16(C(KC_Y)); //redu
				}
			}
			else if(index==1){
				if (clockwise)
				{
					tap_code(KC_VOLU); //vol up 
				}
				else{
					tap_code(KC_VOLD);//vol down
				}
			}
			break;
		case _TESTS:
			if(index==0){
				if (clockwise)
				{
					rgblight_increase_hue(); //undo
				}
				else{
					rgblight_decrease_hue(); //redu
				}
			}
			else if(index==1){
				if (clockwise)
				{
					rgblight_increase_val(); //val up 
				}
				else{
					rgblight_decrease_val();//val down
				}
			}
			
			break;
		
			
    }
}

void matrix_scan_user (void){
	if(is_alt_tab_active){ //unchecks lalt
		if(timer_elapsed(alt_tab_timer)> 1250) {
			unregister_code(KC_LALT);
			is_alt_tab_active=false;
		}
	}
}	


#endif