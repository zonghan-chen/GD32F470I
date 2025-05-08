#include <stdio.h>

#include "gd32f4xx.h"

#include "main.h"
#include "systick.h"

#include ".\Image\image1.h"
#include ".\Image\image2.h"
#include ".\Image\image3.h"
#include ".\Image\image4.h"
#include ".\Image\image5.h"
#include ".\Image\image6.h"
#include ".\Image\image7.h"
#include ".\Image\image8.h"
#include ".\Image\image9.h"
#include ".\Image\image10.h"
#include ".\Image\image11.h"
#include ".\Image\image12.h"

#ifdef __CC_ARM
#include ".\Image\logo.h"
#endif

#ifdef __IAR_SYSTEMS_ICC__
#include ".\Image\logo_iar.h"
#endif

#define HORIZONTAL_FRONT_PORCH 2
#define HORIZONTAL_BACK_PORCH 2
#define HORIZONTAL_SYNCHRONOUS_PULSE 41

#define VERTICAL_FRONT_PORCH 2
#define VERTICAL_BACK_PORCH 2
#define VERTICAL_SYNCHRONOUS_PULSE 10

#define ACTIVE_WIDTH 480
#define ACTIVE_HEIGHT 272

uint8_t blended_address_buffer[58292];

// IPA
static void ipa_config(uint32_t image_base_address); // Configure IPA peripheral

// TLI
static void tli_gpio_config(void);	// Configure TLI GPIO
static void tli_blend_config(void); // Configure TLI peripheral and display blend image
static void tli_config(void);		// Configure TLI peripheral

// LCD
static void lcd_config(void); // Configure LCD peripheral

int main(void)
{
	systick_config();

	// Configure LCD
	lcd_config();

	// Enable TLI layers
	tli_layer_enable(LAYER0);
	tli_layer_enable(LAYER1);
	tli_reload_config(TLI_FRAME_BLANK_RELOAD_EN);

	// Enable TLI
	tli_enable();

	// Configure TLI and display blend image
	tli_blend_config();
	tli_reload_config(TLI_REQUEST_RELOAD_EN);

	while (1)
	{
		ipa_config((uint32_t)&gImage_image1);
		ipa_transfer_enable();
		while (ipa_interrupt_flag_get(IPA_INT_FLAG_FTF) == RESET)
			;
		delay_1ms(50);

		ipa_config((uint32_t)&gImage_image2);
		ipa_transfer_enable();
		while (ipa_interrupt_flag_get(IPA_INT_FLAG_FTF) == RESET)
			;
		delay_1ms(50);

		ipa_config((uint32_t)&gImage_image3);
		ipa_transfer_enable();
		while (ipa_interrupt_flag_get(IPA_INT_FLAG_FTF) == RESET)
			;
		delay_1ms(50);

		ipa_config((uint32_t)&gImage_image4);
		ipa_transfer_enable();
		while (ipa_interrupt_flag_get(IPA_INT_FLAG_FTF) == RESET)
			;
		delay_1ms(50);

		ipa_config((uint32_t)&gImage_image5);
		ipa_transfer_enable();
		while (ipa_interrupt_flag_get(IPA_INT_FLAG_FTF) == RESET)
			;
		delay_1ms(50);

		ipa_config((uint32_t)&gImage_image6);
		ipa_transfer_enable();
		while (ipa_interrupt_flag_get(IPA_INT_FLAG_FTF) == RESET)
			;
		delay_1ms(50);

		ipa_config((uint32_t)&gImage_image7);
		ipa_transfer_enable();
		while (ipa_interrupt_flag_get(IPA_INT_FLAG_FTF) == RESET)
			;
		delay_1ms(50);

		ipa_config((uint32_t)&gImage_image8);
		ipa_transfer_enable();
		while (ipa_interrupt_flag_get(IPA_INT_FLAG_FTF) == RESET)
			;
		delay_1ms(50);

		ipa_config((uint32_t)&gImage_image9);
		ipa_transfer_enable();
		while (ipa_interrupt_flag_get(IPA_INT_FLAG_FTF) == RESET)
			;
		delay_1ms(50);

		ipa_config((uint32_t)&gImage_image10);
		ipa_transfer_enable();
		while (ipa_interrupt_flag_get(IPA_INT_FLAG_FTF) == RESET)
			;
		delay_1ms(50);

		ipa_config((uint32_t)&gImage_image11);
		ipa_transfer_enable();
		while (ipa_interrupt_flag_get(IPA_INT_FLAG_FTF) == RESET)
			;
		delay_1ms(50);

		ipa_config((uint32_t)&gImage_image12);
		ipa_transfer_enable();
		while (ipa_interrupt_flag_get(IPA_INT_FLAG_FTF) == RESET)
			;
		delay_1ms(50);
	}
}

// IPA
// Configure IPA peripheral
static void ipa_config(uint32_t image_base_address)
{
	ipa_foreground_parameter_struct ipa_foreground_init_struct;
	ipa_destination_parameter_struct ipa_destination_init_struct;

	rcu_periph_clock_enable(RCU_IPA);

	ipa_deinit();

	// Configure IPA pixel format convert mode
	ipa_pixel_format_convert_mode_set(IPA_FGTODE); // No pixel format conversion

	// Configure IPA foreground
	ipa_foreground_init_struct.foreground_memaddr = image_base_address;
	ipa_foreground_init_struct.foreground_lineoff = 0x0;
	ipa_foreground_init_struct.foreground_prealpha = 0x0;
	ipa_foreground_init_struct.foreground_alpha_algorithm = IPA_FG_ALPHA_MODE_0; // No effect
	ipa_foreground_init_struct.foreground_pf = FOREGROUND_PPF_RGB565;			 // Foreground pixel format RGB565
	ipa_foreground_init_struct.foreground_prered = 0x0;
	ipa_foreground_init_struct.foreground_pregreen = 0x0;
	ipa_foreground_init_struct.foreground_preblue = 0x0;

	// IPA foreground initialization
	ipa_foreground_init(&ipa_foreground_init_struct);

	// Configure IPA destination
	ipa_destination_init_struct.destination_memaddr = (uint32_t)&blended_address_buffer;
	ipa_destination_init_struct.destination_lineoff = 0x0;
	ipa_destination_init_struct.destination_prealpha = 0x0;
	ipa_destination_init_struct.destination_pf = IPA_DPF_RGB565; // Destination pixel format RGB565
	ipa_destination_init_struct.destination_prered = 0x0;
	ipa_destination_init_struct.destination_pregreen = 0x0;
	ipa_destination_init_struct.destination_preblue = 0x0;
	ipa_destination_init_struct.image_width = 247;
	ipa_destination_init_struct.image_height = 118;

	// IPA destination initialization
	ipa_destination_init(&ipa_destination_init_struct);
}

// TLI
// Configure TLI GPIO
static void tli_gpio_config(void)
{
	// Enable GPIO clock
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOE);
	rcu_periph_clock_enable(RCU_GPIOF);
	rcu_periph_clock_enable(RCU_GPIOG);
	rcu_periph_clock_enable(RCU_GPIOH);
	rcu_periph_clock_enable(RCU_GPIOI);

	// Configure TLI pins alternative functions
	gpio_af_set(GPIOE, GPIO_AF_14, GPIO_PIN_4); // LCD_B0(PE4)
	gpio_af_set(GPIOE, GPIO_AF_14, GPIO_PIN_5); // LCD_G0(PE5)
	gpio_af_set(GPIOE, GPIO_AF_14, GPIO_PIN_6); // LCD_G1(PE6)

	gpio_af_set(GPIOF, GPIO_AF_14, GPIO_PIN_10); // LCD_DE(PF10)

	gpio_af_set(GPIOG, GPIO_AF_14, GPIO_PIN_6);	 // LCD_R7(PG6)
	gpio_af_set(GPIOG, GPIO_AF_14, GPIO_PIN_7);	 // LCD_CLK(PG7)
	gpio_af_set(GPIOG, GPIO_AF_14, GPIO_PIN_10); // LCD_B2(PG10)
	gpio_af_set(GPIOG, GPIO_AF_14, GPIO_PIN_11); // LCD_B3(PG11)
	gpio_af_set(GPIOG, GPIO_AF_14, GPIO_PIN_12); // LCD_B1(PG12)

	gpio_af_set(GPIOH, GPIO_AF_14, GPIO_PIN_2);	 // LCD_R0(PH2)
	gpio_af_set(GPIOH, GPIO_AF_14, GPIO_PIN_3);	 // LCD_R1(PH3)
	gpio_af_set(GPIOH, GPIO_AF_14, GPIO_PIN_8);	 // LCD_R2(PH8)
	gpio_af_set(GPIOH, GPIO_AF_14, GPIO_PIN_9);	 // LCD_R3(PH9)
	gpio_af_set(GPIOH, GPIO_AF_14, GPIO_PIN_10); // LCD_R4(PH10)
	gpio_af_set(GPIOH, GPIO_AF_14, GPIO_PIN_11); // LCD_R5(PH11)
	gpio_af_set(GPIOH, GPIO_AF_14, GPIO_PIN_12); // LCD_R6(PH12)
	gpio_af_set(GPIOH, GPIO_AF_14, GPIO_PIN_13); // LCD_G2(PH13)
	gpio_af_set(GPIOH, GPIO_AF_14, GPIO_PIN_14); // LCD_G3(PH14)
	gpio_af_set(GPIOH, GPIO_AF_14, GPIO_PIN_15); // LCD_G4(PH15)

	gpio_af_set(GPIOI, GPIO_AF_14, GPIO_PIN_0);	 // LCD_G5(PI0)
	gpio_af_set(GPIOI, GPIO_AF_14, GPIO_PIN_1);	 // LCD_G6(PI1)
	gpio_af_set(GPIOI, GPIO_AF_14, GPIO_PIN_2);	 // LCD_G7(PI2)
	gpio_af_set(GPIOI, GPIO_AF_14, GPIO_PIN_4);	 // LCD_B4(PI4)
	gpio_af_set(GPIOI, GPIO_AF_14, GPIO_PIN_5);	 // LCD_B5(PI5)
	gpio_af_set(GPIOI, GPIO_AF_14, GPIO_PIN_6);	 // LCD_B6(PI6)
	gpio_af_set(GPIOI, GPIO_AF_14, GPIO_PIN_7);	 // LCD_B7(PI7)
	gpio_af_set(GPIOI, GPIO_AF_14, GPIO_PIN_9);	 // LCD_VSYNC(PI9)
	gpio_af_set(GPIOI, GPIO_AF_14, GPIO_PIN_10); // LCD_HSYNC(PI10)

	// Configure TLI GPIO
	gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);
	gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);

	gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10);
	gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

	gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);
	gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);

	gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
	gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

	gpio_mode_set(GPIOI, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10);
	gpio_output_options_set(GPIOI, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10);

	// Configure LCD PWM BackLight(PB15)
	gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_15);
	gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_15);
	gpio_bit_set(GPIOB, GPIO_PIN_15);
}

// Configure TLI peripheral and display blend image
static void tli_blend_config(void)
{
	tli_parameter_struct tli_init_struct;
	tli_layer_parameter_struct tli_layer_init_struct;

	rcu_periph_clock_enable(RCU_TLI);

	tli_gpio_config();

#ifdef __CC_ARM
	// Configure the PLLSAI clock to generate the LCD clock
	if (rcu_pllsai_config(192, 2, 3) == ERROR)
	{
		while (1)
			;
	}
#endif

#ifdef __IAR_SYSTEMS_ICC__
	// Configure the PLLSAI clock to generate the LCD clock
	if (rcu_pllsai_config(192, 2, 3) == ERROR)
	{
		while (1)
			;
	}
#endif

	// Configure the TLI clock division selection
	rcu_tli_clock_div_config(RCU_PLLSAIR_DIV8); // CK_PLLSAIR/8

	// Turn on the oscillator
	rcu_osci_on(RCU_PLLSAI_CK);

	// Wait for oscillator stabilization flag is set or oscillator startup is timeout
	if (rcu_osci_stab_wait(RCU_PLLSAI_CK) == ERROR)
	{
		while (1)
			;
	}

	// Configure TLI parameter struct
	// Configure LCD display timing
	tli_init_struct.synpsz_vpsz = VERTICAL_SYNCHRONOUS_PULSE - 1;
	tli_init_struct.synpsz_hpsz = HORIZONTAL_SYNCHRONOUS_PULSE - 1;
	tli_init_struct.backpsz_vbpsz = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH - 1;
	tli_init_struct.backpsz_hbpsz = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH - 1;
	tli_init_struct.activesz_vasz = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH + ACTIVE_HEIGHT - 1;
	tli_init_struct.activesz_hasz = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH + ACTIVE_WIDTH - 1;
	tli_init_struct.totalsz_vtsz = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH + ACTIVE_HEIGHT + VERTICAL_FRONT_PORCH - 1;
	tli_init_struct.totalsz_htsz = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH + ACTIVE_WIDTH + HORIZONTAL_FRONT_PORCH - 1;

	// Configure LCD background RGB values(0xFFFFFF white)
	tli_init_struct.backcolor_red = 0xFF;
	tli_init_struct.backcolor_green = 0xFF;
	tli_init_struct.backcolor_blue = 0xFF;

	// Configure LCD pulse signal polarity
	tli_init_struct.signalpolarity_hs = TLI_HSYN_ACTLIVE_LOW;
	tli_init_struct.signalpolarity_vs = TLI_VSYN_ACTLIVE_LOW;
	tli_init_struct.signalpolarity_de = TLI_DE_ACTLIVE_LOW;
	tli_init_struct.signalpolarity_pixelck = TLI_PIXEL_CLOCK_TLI;

	tli_init(&tli_init_struct);

	// Configure TLI layer one
	// Configure window position
	tli_layer_init_struct.layer_window_rightpos = 80 + 247 + HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH - 1;
	tli_layer_init_struct.layer_window_leftpos = 80 + HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH;
	tli_layer_init_struct.layer_window_bottompos = 20 + 118 + VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH - 1;
	tli_layer_init_struct.layer_window_toppos = 20 + VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH;

	// Configure packeted pixel format
	tli_layer_init_struct.layer_ppf = LAYER_PPF_RGB565; // Layer pixel format RGB565

	// Configure specified alpha
	tli_layer_init_struct.layer_sa = 0xFF;

	// Configure default colour values
	tli_layer_init_struct.layer_default_alpha = 0x0;
	tli_layer_init_struct.layer_default_red = 0x0;
	tli_layer_init_struct.layer_default_green = 0x0;
	tli_layer_init_struct.layer_default_blue = 0x0;

	// Configure alpha calculation factors
	tli_layer_init_struct.layer_acf1 = LAYER_ACF1_PASA;
	tli_layer_init_struct.layer_acf2 = LAYER_ACF2_PASA;

	// Configure layer one frame
	tli_layer_init_struct.layer_frame_bufaddr = (uint32_t)&blended_address_buffer;
	tli_layer_init_struct.layer_frame_buf_stride_offset = (247 * 2);
	tli_layer_init_struct.layer_frame_line_length = ((247 * 2) + 3);
	tli_layer_init_struct.layer_frame_total_line_number = 118;

	tli_layer_init(LAYER1, &tli_layer_init_struct);
}

// Configure TLI peripheral
static void tli_config(void)
{
	tli_parameter_struct tli_init_struct;
	tli_layer_parameter_struct tli_layer_init_struct;

	rcu_periph_clock_enable(RCU_TLI);

	tli_gpio_config();

#ifdef __CC_ARM
	// Configure the PLLSAI clock to generate the LCD clock
	if (rcu_pllsai_config(192, 2, 3) == ERROR)
	{
		while (1)
			;
	}
#endif

#ifdef __IAR_SYSTEMS_ICC__
	// Configure the PLLSAI clock to generate the LCD clock
	if (rcu_pllsai_config(192, 2, 3) == ERROR)
	{
		while (1)
			;
	}
#endif

	// Configure the TLI clock division selection
	rcu_tli_clock_div_config(RCU_PLLSAIR_DIV8); // CK_PLLSAIR/8

	// Turn on the oscillator
	rcu_osci_on(RCU_PLLSAI_CK);

	// Wait for oscillator stabilization flag is set or oscillator startup is timeout
	if (rcu_osci_stab_wait(RCU_PLLSAI_CK) == ERROR)
	{
		while (1)
			;
	}

	// Configure TLI parameter struct
	// Configure LCD display timing
	tli_init_struct.synpsz_vpsz = VERTICAL_SYNCHRONOUS_PULSE - 1;
	tli_init_struct.synpsz_hpsz = HORIZONTAL_SYNCHRONOUS_PULSE - 1;
	tli_init_struct.backpsz_vbpsz = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH - 1;
	tli_init_struct.backpsz_hbpsz = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH - 1;
	tli_init_struct.activesz_vasz = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH + ACTIVE_HEIGHT - 1;
	tli_init_struct.activesz_hasz = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH + ACTIVE_WIDTH - 1;
	tli_init_struct.totalsz_vtsz = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH + ACTIVE_HEIGHT + VERTICAL_FRONT_PORCH - 1;
	tli_init_struct.totalsz_htsz = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH + ACTIVE_WIDTH + HORIZONTAL_FRONT_PORCH - 1;

	// Configure LCD background RGB values(0xFFFFFF white)
	tli_init_struct.backcolor_red = 0xFF;
	tli_init_struct.backcolor_green = 0xFF;
	tli_init_struct.backcolor_blue = 0xFF;

	// Configure LCD pulse signal polarity
	tli_init_struct.signalpolarity_hs = TLI_HSYN_ACTLIVE_LOW;
	tli_init_struct.signalpolarity_vs = TLI_VSYN_ACTLIVE_LOW;
	tli_init_struct.signalpolarity_de = TLI_DE_ACTLIVE_LOW;
	tli_init_struct.signalpolarity_pixelck = TLI_PIXEL_CLOCK_TLI;

	tli_init(&tli_init_struct);

	// Configure TLI layer zero
	// Configure window position
	tli_layer_init_struct.layer_window_rightpos = 80 + 320 + HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH - 1;
	tli_layer_init_struct.layer_window_leftpos = 80 + HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH;
	tli_layer_init_struct.layer_window_bottompos = 150 + 100 + VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH - 1;
	tli_layer_init_struct.layer_window_toppos = 150 + VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH;

	// Configure packeted pixel format
	tli_layer_init_struct.layer_ppf = LAYER_PPF_RGB565; // Layer pixel format RGB565

	// Configure specified alpha
	tli_layer_init_struct.layer_sa = 0xFF;

	// Configure default colour values
	tli_layer_init_struct.layer_default_alpha = 0x0;
	tli_layer_init_struct.layer_default_red = 0xFF;
	tli_layer_init_struct.layer_default_green = 0xFF;
	tli_layer_init_struct.layer_default_blue = 0xFF;

	// Configure alpha calculation factors
	tli_layer_init_struct.layer_acf1 = LAYER_ACF1_PASA;
	tli_layer_init_struct.layer_acf2 = LAYER_ACF2_PASA;

	// Configure layer one frame
	tli_layer_init_struct.layer_frame_bufaddr = (uint32_t)gImage_logo;
	tli_layer_init_struct.layer_frame_buf_stride_offset = (320 * 2);
	tli_layer_init_struct.layer_frame_line_length = ((320 * 2) + 3);
	tli_layer_init_struct.layer_frame_total_line_number = 100;

	tli_layer_init(LAYER0, &tli_layer_init_struct);
}

// LCD
// Configure LCD peripheral
static void lcd_config(void)
{
	tli_gpio_config();
	tli_config();
}
