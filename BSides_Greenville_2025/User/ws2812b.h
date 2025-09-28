#ifndef _WS2812B_H
#define _WS2812B_H

// To stop warnings about unused functions.
static uint32_t EHSVtoHEX( uint8_t hue, uint8_t sat, uint8_t val ) __attribute__((used));

#ifndef LED_NUM
#define LED_NUM  256
#endif


//Array to hold color values for 256 WS2812Bs.
unsigned char led[LED_NUM][3] = {{0,0,0}};


static uint32_t EHSVtoHEX( uint8_t hue, uint8_t sat, uint8_t val )
{
	#define SIXTH1 43
	#define SIXTH2 85
	#define SIXTH3 128
	#define SIXTH4 171
	#define SIXTH5 213

	uint16_t or = 0, og = 0, ob = 0;

	hue -= SIXTH1; //Off by 60 degrees.

	//TODO: There are colors that overlap here, consider 
	//tweaking this to make the best use of the colorspace.

	if( hue < SIXTH1 ) //Ok: Yellow->Red.
	{
		or = 255;
		og = 255 - ((uint16_t)hue * 255) / (SIXTH1);
	}
	else if( hue < SIXTH2 ) //Ok: Red->Purple
	{
		or = 255;
		ob = (uint16_t)hue*255 / SIXTH1 - 255;
	}
	else if( hue < SIXTH3 )  //Ok: Purple->Blue
	{
		ob = 255;
		or = ((SIXTH3-hue) * 255) / (SIXTH1);
	}
	else if( hue < SIXTH4 ) //Ok: Blue->Cyan
	{
		ob = 255;
		og = (hue - SIXTH3)*255 / SIXTH1;
	}
	else if( hue < SIXTH5 ) //Ok: Cyan->Green.
	{
		og = 255;
		ob = ((SIXTH5-hue)*255) / SIXTH1;
	}
	else //Green->Yellow
	{
		og = 255;
		or = (hue - SIXTH5) * 255 / SIXTH1;
	}

	uint16_t rv = val;
	if( rv > 128 ) rv++;
	uint16_t rs = sat;
	if( rs > 128 ) rs++;

	//or, og, ob range from 0...255 now.
	//Need to apply saturation and value.

	or = (or * val)>>8;
	og = (og * val)>>8;
	ob = (ob * val)>>8;

	//OR..OB == 0..65025
	or = or * rs + 255 * (256-rs);
	og = og * rs + 255 * (256-rs);
	ob = ob * rs + 255 * (256-rs);
//printf( "__%d %d %d =-> %d\n", or, og, ob, rs );

	or >>= 8;
	og >>= 8;
	ob >>= 8;

	return or | (og<<8) | ((uint32_t)ob<<16);
}

static const unsigned char sintable[] = {
	0x80, 0x83, 0x86, 0x89, 0x8c, 0x8f, 0x92, 0x95, 0x99, 0x9c, 0x9f, 0xa2, 0xa5, 0xa8, 0xab, 0xad, 
	0xb0, 0xb3, 0xb6, 0xb9, 0xbc, 0xbe, 0xc1, 0xc4, 0xc6, 0xc9, 0xcb, 0xce, 0xd0, 0xd3, 0xd5, 0xd7, 
	0xda, 0xdc, 0xde, 0xe0, 0xe2, 0xe4, 0xe6, 0xe8, 0xe9, 0xeb, 0xed, 0xee, 0xf0, 0xf1, 0xf3, 0xf4, 
	0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfc, 0xfd, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfd, 0xfc, 0xfc, 0xfb, 0xfa, 0xf9, 0xf8, 0xf7, 0xf6, 
	0xf5, 0xf4, 0xf3, 0xf1, 0xf0, 0xee, 0xed, 0xeb, 0xe9, 0xe8, 0xe6, 0xe4, 0xe2, 0xe0, 0xde, 0xdc, 
	0xda, 0xd7, 0xd5, 0xd3, 0xd0, 0xce, 0xcb, 0xc9, 0xc6, 0xc4, 0xc1, 0xbe, 0xbc, 0xb9, 0xb6, 0xb3, 
	0xb0, 0xad, 0xab, 0xa8, 0xa5, 0xa2, 0x9f, 0x9c, 0x99, 0x95, 0x92, 0x8f, 0x8c, 0x89, 0x86, 0x83, 
	0x80, 0x7d, 0x79, 0x76, 0x73, 0x70, 0x6d, 0x6a, 0x67, 0x64, 0x61, 0x5e, 0x5b, 0x58, 0x55, 0x52, 
	0x4f, 0x4c, 0x49, 0x47, 0x44, 0x41, 0x3e, 0x3c, 0x39, 0x36, 0x34, 0x31, 0x2f, 0x2d, 0x2a, 0x28, 
	0x26, 0x24, 0x21, 0x1f, 0x1d, 0x1b, 0x1a, 0x18, 0x16, 0x14, 0x13, 0x11, 0x10, 0x0e, 0x0d, 0x0b, 
	0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x04, 0x03, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x03, 0x04, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
	0x0a, 0x0b, 0x0d, 0x0e, 0x10, 0x11, 0x13, 0x14, 0x16, 0x18, 0x1a, 0x1b, 0x1d, 0x1f, 0x21, 0x24, 
	0x26, 0x28, 0x2a, 0x2d, 0x2f, 0x31, 0x34, 0x36, 0x39, 0x3c, 0x3e, 0x41, 0x44, 0x47, 0x49, 0x4c, 
	0x4f, 0x52, 0x55, 0x58, 0x5b, 0x5e, 0x61, 0x64, 0x67, 0x6a, 0x6d, 0x70, 0x73, 0x76, 0x79, 0x7d };

static const unsigned char hue_r[] = {
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 250, 244, 238, 232, 226,
    220, 214, 208, 202, 196, 190, 184, 178, 172, 166, 160, 154, 148, 142, 136, 130,
    124, 118, 112, 106, 100,  94,  88,  82,  76,  70,  64,  58,  52,  46,  40,  34,
     28,  22,  16,  10,   4,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   6,  12,  18,  24,  30,  36,  42,  48,
     54,  60,  66,  72,  78,  84,  90,  96, 102, 108, 114, 120, 126, 132, 138, 144,
    150, 156, 162, 168, 174, 180, 186, 192, 198, 204, 210, 216, 222, 228, 234, 240,
    246, 252, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
};

static const unsigned char hue_g[] = {
      0,   6,  12,  18,  24,  30,  36,  42,  48,  54,  60,  66,  72,  78,  84,  90,
     96, 102, 108, 114, 120, 126, 132, 138, 144, 150, 156, 162, 168, 174, 180, 186,
    192, 198, 204, 210, 216, 222, 228, 234, 240, 246, 252, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 250, 244, 238, 232, 226, 220, 214, 208, 202, 196, 190,
    184, 178, 172, 166, 160, 154, 148, 142, 136, 130, 124, 118, 112, 106, 100,  94,
     88,  82,  76,  70,  64,  58,  52,  46,  40,  34,  28,  22,  16,  10,   4,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

static const unsigned char hue_b[] = {
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,  12,  18,  24,  30,
     36,  42,  48,  54,  60,  66,  72,  78,  84,  90,  96, 102, 108, 114, 120, 126,
    132, 138, 144, 150, 156, 162, 168, 174, 180, 186, 192, 198, 204, 210, 216, 222,
    228, 234, 240, 246, 252, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 250,
    244, 238, 232, 226, 220, 214, 208, 202, 196, 190, 184, 178, 172, 166, 160, 154,
    148, 142, 136, 130, 124, 118, 112, 106, 100,  94,  88,  82,  76,  70,  64,  58,
     52,  46,  40,  34,  28,  22,  16,  10,   4,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

static inline uint32_t FastMultiply( uint32_t big_num, uint32_t small_num ) __attribute__((section(".srodata")));
static inline uint32_t FastMultiply( uint32_t big_num, uint32_t small_num )
{
	// The CH32V003 is an EC core, so no hardware multiply. GCC's way multiply
	// is slow, so I wrote this.
	//
	// This basically does this:
	//	return small_num * big_num;
	//
	// Note: This does NOT check for zero to begin with, though this still
	// produces the correct results, it is a little weird that even if
	// small_num is zero it executes once.
	//
	// Additionally note, instead of the if( m&1 ) you can do the following:
	//  ret += multiplciant & neg(multiplicand & 1).
	//
	// BUT! Shockingly! That is slower than an extra branch! The CH32V003
	//  can branch unbelievably fast.
	//
	// This is functionally equivelent and much faster.
	//
	// Perf numbers, with small_num set to 180V.
	//  No multiply:         21.3% CPU Usage
	//  Assembly below:      42.4% CPU Usage  (1608 bytes for whole program)
	//  C version:           41.4% CPU Usage  (1600 bytes for whole program)
	//  Using GCC (__mulsi3) 65.4% CPU Usage  (1652 bytes for whole program)
	//
	// The multiply can be done manually:
	uint32_t ret = 0;
	uint32_t multiplicand = small_num;
	uint32_t mutliplicant = big_num;
	do
	{
		if( multiplicand & 1 )
			ret += mutliplicant;
		mutliplicant<<=1;
		multiplicand>>=1;
	} while( multiplicand );
	return ret;

	// Which is equivelent to the following assembly (If you were curious)
/*
	uint32_t ret = 0;
	asm volatile( "\n\
		.option   rvc;\n\
	1:	andi t0, %[small], 1\n\
		beqz t0, 2f\n\
		add %[ret], %[ret], %[big]\n\
	2:	srli %[small], %[small], 1\n\
		slli %[big], %[big], 1\n\
		bnez %[small], 1b\n\
	" :
		[ret]"=&r"(ret), [big]"+&r"(big_num), [small]"+&r"(small_num) : :
		"t0" );
	return ret;
*/
}


//WS2812B [1 = H - 0.7uS L-0.6uS] [0 = H-0.37uS L- 0.8uS] [REs L - >50uS]
void WS2812B_SendBit(uint8_t bit)
{
    if (bit)
    {
        // Bit "1": High for 0.66 ?s, Low for 0.59 ?s
        GPIOC->BSHR = GPIO_Pin_6;  // Set pin high.
        __asm__ volatile (
            "li t0, 5 \n"        // Load the cycle count for high time
            "1: \n"              // Label for the loop start
            "addi t0, t0, -1 \n" // Decrement the cycle count
            "bnez t0, 1b \n"     // Branch to label 1 if the cycle count is not zero
        );

        GPIOC->BCR = GPIO_Pin_6;  // Set pin low
        __asm__ volatile (
            "li t0, 1 \n"        // Load the cycle count for low time
            "1: \n"              // Label for the loop start
            "addi t0, t0, -1 \n" // Decrement the cycle count
            "bnez t0, 1b \n"     // Branch to label 1 if the cycle count is not zero
        );
    }
    else
    {
        // Bit "0": High for 0.33 ?s, Low for 0.92 ?s
        GPIOC->BSHR = GPIO_Pin_6;  // Set pin high
        __asm__ volatile (
            "li t0, 1 \n"        // Load the cycle count for high time
            "1: \n"              // Label for the loop start
            "addi t0, t0, -1 \n" // Decrement the cycle count
            "bnez t0, 1b \n"     // Branch to label 1 if the cycle count is not zero
        );

        GPIOC->BCR = GPIO_Pin_6;  // Set pin low
        __asm__ volatile (
            "li t0, 5 \n"        // Load the cycle count for low time
            "1: \n"              // Label for the loop start
            "addi t0, t0, -1 \n" // Decrement the cycle count
            "bnez t0, 1b \n"     // Branch to label 1 if the cycle count is not zero
        );
    }
}

void WS2812B_SendByte(uint8_t byte)
{
    for (int i = 0; i < 8; i++)
    {
        WS2812B_SendBit((byte << i) & 0x80);
    }
}

void show(){
	for(int i=0; i<LED_NUM; i++){
		WS2812B_SendByte(led[i][1]);		
		WS2812B_SendByte(led[i][0]);
    	WS2812B_SendByte(led[i][2]);
	}
	Delay_Ms(1);
}

void setLed(uint8_t led_num, uint8_t red, uint8_t green, uint8_t blue){
	led[led_num][0] = red;
	led[led_num][1] = green;
	led[led_num][2] = blue;

}

void WS2812B_Rainbow_Chase(uint8_t d, uint8_t brightness){
	for(int j=0; j<255; j++){
		for(int i=0; i<LED_NUM; i++){
			setLed(i, hue_r[((j)+i*16)%256]/brightness, hue_g[((j)+i*16)%256]/brightness, hue_b[((j)+i*16)%256]/brightness);
		}
		show();
		Delay_Ms(d);
	}
}
void WS2812B_FadeColors(uint8_t d, uint8_t brightness) {
    uint8_t red, green, blue;
    int step = 5; // Adjust step size for smoother transition
        // Fade from Red to Blue
        for (red = 255, blue = 0; red > 0; red -= step, blue += step)
        {
            for(int i=0; i<LED_NUM; i++){            
                setLed(i, red/brightness, 0, blue/brightness);
            }
			show();
			Delay_Ms(d);
        }

        // Fade from Blue to Green
        for (blue = 255, green = 0; blue > 0; blue -= step, green += step)
        {
            for(int i=0; i<LED_NUM; i++){
                setLed(i, 0, green/brightness, blue/brightness);
            }
			show();
			Delay_Ms(d);
        }

        // Fade from Green to Red
        for (green = 255, red = 0; green > 0; green -= step, red += step)
        {
            for(int i=0; i<LED_NUM; i++){
                setLed(i, red/brightness, green/brightness, 0);
            }
			show();
			Delay_Ms(d);
        }
}

void WS2812B_ChaseColor(uint8_t d, uint8_t brightness)
{
        for(int j = 0; j<16; j++)
        {
                for(int i=0; i<LED_NUM; i++){ 
                    if((i+j%4)%2){           
                        setLed(i, 0, 0, 255/brightness);
                    }else{
                        setLed(i, 0, 0, 0);
                    }
                }
				show();
				Delay_Ms(d);
        }
        for(int j = 0; j<16; j++)
        {
                for(int i=0; i<LED_NUM; i++){
                    if((i+j%4)%2){
                        setLed(i, 0, 255/brightness, 0);
                    }else{
                        setLed(i, 0, 0, 0);
                    }
                }
				show();
				Delay_Ms(d);
        }
        
        for(int j = 0; j<16; j++)
        {
            // Fade from Green to Red

                for(int i=0; i<LED_NUM; i++){
                    if((i+j%4)%2){
                        setLed(i, 255/brightness, 0, 0);
                    }else{
                        setLed(i, 0, 0, 0);
                    }
                }
				show();
				Delay_Ms(d);
        }
}
#endif