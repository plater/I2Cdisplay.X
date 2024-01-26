/* 
 * File:   gsm.c
 * Author: Dave Plater
 * Ported from PIC18F47KXX
 *
 * Created on 20 June 2020, 1:46 PM
 */
#include "gsm.h"
#include "buffers.h"

uint8_t slaveDeviceAddress;
uint8_t gsmbyte;
uint8_t gsmusd[128];
uint8_t gsmusm[24];

uint8_t gsmtim[23];

#if 1
struct 
{
    unsigned retransmit : 1;
    unsigned meerror : 1;
    unsigned mtn : 1;
    unsigned msgavl : 1;
    unsigned abrtmsg : 1;
    unsigned eomsg : 1;
    unsigned msggod : 1;
    unsigned sigtest : 1;
} gsmflags;
#endif
//uint8_t gsmusd;
//uint8_t transid[24] __attribute__((section("tcpsection")));
///Wait for buffer empty
void gsm_waitx(void)
{
    U2STAbits.UTXEN = 1;
    while(U2STAbits.UTXBF)
    {
    }
}
//Wait for buffer empty
void gsm_waitr(void)
{
    while(!(U2STAbits.URXDA == 1))
    {
    }
}

void gsm_transmit(uint8_t txbyte)
{
    U2STAbits.UTXEN = 1;
    UART2_Write(txbyte);
    while(!U2STAbits.TRMT){}
}

void gsm_zerobuff(uint8_t* gsmsgbuf, uint16_t count )
{
    uint16_t x = 0;
    while(x < count)
    {
        gsmsgbuf[x] = 0x00;
        x++;
    }
    
}

void gsm_msg(uint8_t *msgadd)
{
    uint32_t msgbkup = msgadd;
    retrans:
    msgadd = msgbkup;
    gsmflags.retransmit = 0;
    
    for(uint8_t gsmstr = 0; msgadd[gsmstr] != 0x00; gsmstr++)
    {
        gsmbyte = msgadd[gsmstr];
        gsm_transmit(gsmbyte);
    }
    if(gsmflags.retransmit)
    {
        goto retrans;
    }
//     __delay_us(500);
}

//BAUDCONbits.ABDEN
void gsm_init(void)
{
//    PIE3bits.RC2IE =1; P18 rx int enable
    gsmflags.meerror = 0;
//    eusart2RxCount = 512;
//    gsm_zerobuff(gsmusd, 0x80);
    int i = 0;
  //Make sure that 5 seconds have passed.
     while(!TMR2_GetElapsedThenClear())
    {
        TMR2_Tasks_32BitOperation();
    }
    TMR2_Stop();      
    //Transmit AT\r to sync baud rate. 
    gsm_txAT();
    gsm_transmit(0x0D);
    //Response AT\r\r\nOK\r\n
    //No AT means no GSM
    gsm_receive(1, gsmusd);
    if(gsmusd[0] != '0')
    {
        gsm_receive(1, gsmusm);
    }
    gsm_msg((uint8_t*)noecho);
    gsm_receive(1, gsmusd);
    //
	gsm_msg((uint8_t*)"AT+CREG=0\r");
	gsm_receive(1, gsmusd);
	gsmwait:
	gsm_msg((uint8_t*)"AT+CREG?\r");
	gsm_receive(2, gsmusd);
	if(gsmusd[9] != '1')
	{
		goto gsmwait;
	}
	gsm_msg((uint8_t*)"AT+CSQ\r");
	gsm_receive(2, gsmusd);
    gsm_msg((uint8_t*)tsoftid);
    gsm_receive(2, gsmusd);
}

void delay_second(uint8_t stime)
{
    TMR2_Initialize();
    TMR2_Start();
    more_seconds:
    while(!IFS0bits.T3IF){}
    if(--stime > 0)
    {
        TMR2_Initialize();
        TMR2_Start();
        goto more_seconds;
    }
}

void delay_milli(uint8_t mtime)
{
    TMR1_Initialize();
    TMR1_Start();TMR1_Start();
   more_mili:
    while(!IFS0bits.T1IF){}
    if(--mtime > 0)
    {
        TMR1_Initialize();
        TMR1_Start();
        goto more_mili;
    }
}

/*
    gsm_msg((uint8_t*)smstxt);
    gsm_receive(1, gsmusd);
    
    gsm_msg((uint8_t*)smsdel);
    gsm_receive(1, gsmusd);
    
    gsm_getbalance();
    
    gsm_msg((uint8_t*)smslst);
    gsm_receive(1,gsmusd);
    
    gsm_msg((uint8_t*)smdqry);
    gsm_receive(1, gsmusd);
    
    gsm_msg((uint8_t*)engqry);
    gsm_receive(2, gsmusd);
    
    gsm_msg((uint8_t*)netoff);
    gsm_receive(2, gsmusd);
   
    gsm_msg((uint8_t*)facres);
    gsm_receive(1, gsmusd);
    goto gsminit;
    __asm__("nop");
*/
void clock_display(void)
{
    gsmflags.sigtest = 0;
    sig_strength();
//    INTCONbits.PEIE = 0;//Disable interrupt
//    PIE3bits.RC2IE =0; //Usart Disable interrupt
    dispclka:
    TMR2_Initialize();
    TMR2_Start();
    gsm_gettime();
    disp_clock();
//    INTCONbits.PEIE = 0;
    gsmflags.msgavl = 0;
    if(1 == 1)
    {
        if(U2STAbits.URXDA)
        {//This detects and ignores rings 2\r\n or 3\r\n.
            gsm_receive(1, gsmusm);
            if(gsmusm[0] != '+')
            {
                gsmflags.msgavl = 0;
            }
            else
            {
                gsmflags.msgavl = 1;
            }
        }
    }
    if(gsmflags.msgavl)
    {
//        lcd_string(gsmusm, line1);
        parse_sms();
        __asm__("NOP");
    }
//    INTCONbits.PEIE = 0;
//    gsm_msg((uint8_t*)smstxt);
//    gsm_receive(1);
//    gsm_msg((uint8_t*)smslst);
 //   gsm_receive(71);
    
 //   goto dispclka;
}

void get_radio(void)
{
    uint16_t x = 0;
    uint16_t y = x;
    gsm_zerobuff(gsmusd, 0x80);
    gsmflags.eomsg = 1;
    gsmflags.msggod = 1;
    gsm_msg((uint8_t*)engqry);
    gsm_receive(1, gsmusd);
    while(gsmflags.eomsg)
    {
        gsmbyte = EUSARTG_Read();
        gsmusd[x] = gsmbyte;
        if(gsmbyte == 0x0A)
        {
            y = x - 2;
            if(gsmusd[y] == 0x30)
            {
                gsmflags.eomsg = 0;
            }
            if(gsmflags.msggod)
            {
                gsm_msg((uint8_t*)engoff);
                gsmflags.msggod = 0;
            }
        }
        x++;
        if(x > 0x1FF)
        {
            gsmflags.eomsg = 0;
        }
    }
}

void sig_strength(void)
{
    while(gsmflags.sigtest)
    {//((uint8_t*) &pnvcash)
        uint32_t *convte;
//        lcd_write(dispclr);
        get_radio();
//        lcd_dispadd(line2 + 4);
        convte = gsmusd;
        displ_hex(convte[5] & 0x00FFFF);
    }
}

void check_num(void)
{//int memcmp(const void *s1, const void *s2, size_t n);
uint16_t pnindex = (gsmusm[0x0C] & 0x0F) * 2;
    gsm_msg((uint8_t*)smstxt);
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)smslst);
    gsm_receive(++pnindex, gsmusd);
    gsmflags.msggod = 0;
    //Phone number starts gsmusd[24]
    int diffr = memcmp(gsmusd + 24, spnum, 0x0B);
    if(diffr == 0x00)
    {
        gsmflags.msggod = 1;
    }
    else
    {
        gsm_msg((uint8_t*)smstxt);
        gsm_receive(1, gsmusm);
        gsm_msg((uint8_t*)smsdel);
        gsm_receive(1, gsmtim);
    }
}

void parse_sms(void)
{
    int diffr = memcmp(gsmusm, cmti, 0x05);
    while(diffr == 0x00)
    {
        check_num();
        if(!gsmflags.msggod)
        {
            break;
        }
        gsm_msg((uint8_t*)setgsm);
        gsm_receive(1, gsdate);
        gsm_msg((uint8_t*)smstxt);
        gsm_receive(1, gstime);
        gsm_msg((uint8_t*)sendms);
        gsm_msg((uint8_t*)pnum);
        gsm_numack();
        //if gsmflags.abrtmsg send call me instead
        gsm_msg((uint8_t*)ackmsg);
        //Send ^Z or SUB to terminate sms
        gsm_transmit(0x1A);
        gsm_transmit(0x0D);
        gsm_receive(1, gsdate);
        __asm__("NOP"); //gsm_receive(1, gsdate); needs to be fixed!
        gsm_msg((uint8_t*)smstxt);
        gsm_receive(1, gsmusm);
        gsm_msg((uint8_t*)smsdel);
        gsm_receive(1, gsmtim);
        sms_report();
        __asm__("NOP");
        diffr = 0xFF;
    }
}

void start_sms(void)
{
    gsm_msg((uint8_t*)setgsm);
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)smstxt);
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)sendms);
    gsm_msg((uint8_t*)pnum);
    gsm_numack();
    //if gsmflags.abrtmsg send call me instead
}

void gsm_numack(void)
{
    gsmbyte = 0x00;
    uint8_t x = 4;
    gsmflags.abrtmsg = 0;
    
    while(x > 0)
    {
        gsmbyte = EUSARTG_Read();
        if(gsmbyte == '4')
        {
            gsmflags.abrtmsg = 1;
            break;
        }
        if(gsmbyte == '\"')
        {
            gsmflags.abrtmsg = 0;
            break;
        }
        x--;
    }
}

void sms_report(void)
{
/*    uint8_t i = 0;
    uint8_t z = i;
    gsm_getbalance();
    gsm_gettime();
    
    gsm_zerobuff(gsmusd, 0x200);
    gsmusd[i] = 0x20;
    //Read in "Date "
    i = write_sms(i,clockdate);
    //Read in actual date.
    i = write_sms(i,gsdate);
    gsmusd[i++] = 0x20;
    //Things go wrong!
    i = write_sms(i,clocktime);
    i = write_sms(i,gstime);
    gsmusd[i++] = 0x20;
    gsmusd[i++] = ',';
    gsmusd[i++] = 0x20;
    gsmusd[i++] = 'R';
//    Read_NVstore(cashinv, ((uint8_t*) &pvcash), 0x02);
//    Read_NVstore(cashint, ((uint8_t*) &pnvcash), 0x03);
//    uint8_t *gsmval = convert_hex((uint32_t) pvcash);
    i = write_sms(i,gsmval);
    gsmusd[i++] = ',';
    gsmusd[i++] = 0x20;
    gsmusd[i++] = 'R';
//    gsmval = convert_hex(pnvcash);
    i = write_sms(i,gsmval);
    gsmusd[i++] = ',';
//    i = write_sms(i, totalvendsm);
    //Total vends
//    uint16_t vendstores = vendstore;
    for(char x = 0; x < 0x08; x++)
    {
        gsmusd[i++] = (x +1) | 0x30;
        gsmusd[i++] = '=';
//        gsmbyte = DATAEE_ReadByte(vendstores + x);
        gsmval = convert_hex((uint32_t) gsmbyte);
        i = write_sms(i,gsmval);
        gsmusd[i++] = ',';
    }
    gsmusd[i++] = 0x20;
    //Display change coins given
//    i = write_sms(i,coinsout);
//    Read_NVstore(cashoutv, ((uint8_t*) &pvcash), 0x02);
//    gsmval = convert_hex((uint32_t) pvcash);
    i = write_sms(i,gsmval);
//    i = write_sms(i,coinvalu);
//    gsmbyte = DATAEE_ReadByte(hopcoin);
    gsmusd[i++] = gsmbyte | 0x30;
    i = write_sms(i, gsmusd);
    //Null string terminator
    gsmusd[i] = 0x00;
    start_sms();
    //if gsmflags.abrtmsg send call me instead
    if(gsmflags.abrtmsg)
    {
        
    }
    gsm_msg((uint8_t*)gsmums);
    gsm_transmit(0x1A);
    gsm_transmit(0x0D);*/
}

uint8_t write_sms(uint8_t i, uint8_t *msgpnt)
{
    uint8_t x = 0x00;
    gsmbyte = 0x20;
    while(gsmbyte != 0x00)
    {
        gsmbyte = msgpnt[x++];
        gsmusd[i++] = gsmbyte;
    }
    return --i;
}

//Take a 24 bit hex value and convert it.
// Return pointer to eight ASCII digits lsd first.
uint8_t* convert_hex(uint32_t hexnum)
{
    signed char x = 0;
    uint8_t value[8];
    uint8_t xvalue[8];
    uint32_t hexnumsave = hexnum;
    while(hexnum > 0)
    {
        xvalue[x] = hexnum % 10;
        hexnum /= 10;
        xvalue[x] = xvalue[x] | 0x30;
        x++;
    }
    //insert null string terminator
    value[x--] = 0x00;
    uint8_t y = 0;
    while(x >= 0)
    {
        value[x--] = xvalue[y++];
    }
    
        //In case hexnum is zero
    if(hexnumsave == 0)
    {
       value[0] = 0x30;
       value[1] = 0x00;
    }
    return value;

}
void parse_date_time(void)
{
    gsm_zerobuff(gsdate, 0x014);
    gsm_zerobuff(gstime, 0x014);
    uint8_t x = 8;
    uint8_t i = 0x07;
    //Adjust hour to SAST
    gsmbyte = gsmusd[27];
    gsmbyte = gsmbyte & 0x0F;
    gsmbyte = gsmbyte/4;
    uint8_t hour = (gsmusd[18] & 0x0F) + gsmbyte;
    uint8_t hhour = gsmusd[17] & 0x0F;
    if(hour > 9)
    {
        gsmusd[18] = 0x30;
        gsmusd[17]++;
        if(gsmusd[17] > 0x32)
        {
            gsmusd[17] = 0x30;
        }
        while(hour > 0x0A)
        {
            hour--;
            gsmusd[18]++;
        }
    }
    else
    {
        gsmusd[18] = hour | 0x30;
    }
    while(x < 0x10)
    {
        gsdate[i - 1] = gsmusd[x++];
        gsdate[i--] = gsmusd[x++];
        gsdate[--i] = gsmusd[x++];
        i--;
    }
    i = 0;
    while(i < 0x08)
    {
        gstime[i++] = gsmusd[x++];
    }
}

void gsm_gettime(void)
{
    gsm_msg((uint8_t*)clockr);
    
    gsm_receive(2,gsmusd);
    parse_date_time();
}

//past first 0A to 0X0C spaces 
void gsm_getbalance(void)
{
    gsm_msg((uint8_t*)setgsm);
    gsm_receive(1,gsmusd);
    uint8_t x = 0x0C;
    uint8_t y = 0x00;
    gsmusd[y++] = ' ';
    gsmflags.eomsg = 1;
// For mtn each line remove 0x0A
// Parse until 0A  0A
    if(gsmflags.mtn)
    {
        gsm_msg((uint8_t*)ussdwm);
        gsm_receive(11,gsmusd);
        gsmusd[y++] = gsmusd[x++];
        while(gsmflags.eomsg)
        {
            gsmbyte = gsmusd[x++];
            if(gsmbyte == 0x0A)
            {//Add 0x20 inplace of 0A
                gsmusd[y++] = ',';
                gsmusd[y++] = ' ';
                gsmbyte = gsmusd[x++];
                if(gsmbyte == 0x0A)
                {
                    gsmflags.eomsg = 0;
                    gsmusd[y++] = 0x22;
                    gsmbyte = 0x00;
                }
            }
            gsmusd[y++] = gsmbyte;
        }
    }
//For vodacom parse to first 0x0A
    else
    {
        gsm_msg((uint8_t*)ussdwv);
        gsm_receive(3,gsmusd);
        gsmusd[y++] = gsmusd[x++];
        while(gsmflags.eomsg)
        {
            gsmbyte = gsmusd[x++];
            if(gsmbyte == 0x0A)
            {
                gsmflags.eomsg = 0;
                gsmusd[y++] = 0x22;
                gsmbyte = 0x00;
            }
            gsmusd[y++] = gsmbyte;
        }
    }
    gsm_msg((uint8_t*)ussdwc);
    gsm_receive(1,gsmusd);
}

void gsm_setime(void)
{
    gsm_zerobuff(gsmusd, 0x200);
    gsm_msg((uint8_t*)nettst);
//    gsm_receive(5,gsmusd);
    retry:
    gsmbyte = 0;
    uint8_t x = 0;
    //Search for *
    while(gsmbyte != '*')
    {
        gsmbyte = EUSARTG_Read();
        if(gsmflags.meerror)
        {
            goto offnet;
        }
    }
    gsmbyte = EUSARTG_Read(); //P
    gsmbyte = EUSARTG_Read(); //S
    gsmbyte = EUSARTG_Read(); //U
    if(gsmbyte != 'U')
    {
        goto retry;
    }
    while(gsmbyte != ':')
    {
        gsmbyte = EUSARTG_Read();
    }
    while(gsmbyte != '\n')
    {
        gsmbyte = EUSARTG_Read();
        gsmusd[x++] = gsmbyte;
    }
    //In case of DST message.
    delay_milli(5);


    x = 0x03;
    gsmtim[0] = '"';
    uint8_t i = 0x01;
    while(i < 0x09)
    {
        gsmtim[i] = gsmusd[x];
        gsmtim[i+1] = gsmusd[x+1];
        if(gsmusd[x+1] == ',')
        {
            gsmtim[i+1] = gsmusd[x];
            gsmtim[i] = '0';
            x--;
        }
        gsmtim[i+2] = '/';
        i = i + 3;
        x = x + 3;
    }
    gsmtim[i-1] = ',';
    
    
    while(i < 0x11)
    {
        gsmtim[i] = gsmusd[x];
        gsmtim[i+1] = gsmusd[x+1];
        if(gsmusd[x+1] == ',')
        {
            gsmtim[i+1] = gsmusd[x];
            gsmtim[i] = '0';
            x--;
        }
        gsmtim[i+2] = ':';
        i = i + 3;
        x = x + 3;
    }
    //This should take us to time zone dec i
    i--;
    x++;
    gsmtim[i] = gsmusd[x];
    gsmtim[i+1] = '0';
    gsmtim[i+2] = gsmusd[x+1];
    gsmtim[i+3] = '"';
    gsmtim[i+4] = '\r';
    gsmtim[i+5] = 0x00;
    offnet:
    gsm_msg((uint8_t*)netoff);
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)clockw);
    gsm_msg((uint8_t*)gsmtim);
    gsm_receive(1, gsmusd);
    if(gsmusd[0] != '0')
    {
        LATDbits.LATD0 = 0;
        abort();
    }
}
//Receive unsolicited messages for 16 seconds
//and return the number of newlines.
uint8_t gsm_unsolic(void)
{
    gsm_zerobuff(gsmusd, 0x80);
    uint8_t i = 1;
    uint16_t x = 0;
    uint8_t y = 0;
    resttim:
    TMR2_Initialize();
    TMR2_Start();
    while(!IFS0bits.T3IF && x < 0x200)
    {
        gsmusd[x] = gsm_Read();
        if(gsmusd[x] == '\n')
        {
            y++;
        }
        x++;
    }
    if(i > 0)
    {
        i--;
        goto resttim;
    }
    return y;
}

void gsm_receive(uint8_t noofline, uint8_t *messagebuf)
{
    uint8_t x = 0;
    gsmbyte = 0;
    while(noofline > 0x00)
    {
        gsmbyte = EUSARTG_Read();
        if(gsmflags.meerror)
        {
            break;
        }
        messagebuf[x] = gsmbyte;
        x++;
        if(gsmbyte == 0x0A || gsmbyte == 0x00)
        {
            noofline--;
        }
    }
    messagebuf[x] = 0;
 }

void gsm_txAT(void)
{
    gsm_transmit('A');
    gsm_transmit('T');
}

//Turn on the gsm unit and initialize the 3 second startup timer.
void gsm_on(void)
{
    LATDbits.LATD0 = 1;
//    IFS0CLR= 1 << _IFS0_T1IF_POSITION;
//    T1CONbits.ON = 1;
}

uint8_t gsm_Read(void)
{
    while(!U2STAbits.URXDA)
    {
        if(IFS0bits.T5IF)
        {
            break;
        }
    }

    
    if(1 == U2STAbits.OERR)
    {
        // EUSART2 error - restart

        U2STAbits.OERR = 0; 
    }

    return U2RXREG;
}

void gsm_off(void)
{
    LATDbits.LATD0 = 0;
}

void gsm_netwait(void)
{
    gsmflags.meerror = 0;
    gsmbyte = 0;
    uint8_t x = 0;
    while(gsmbyte != 'S')
    {
        gsmbyte = EUSARTG_Read();
        gsmusd[x++] = gsmbyte;
        if(gsmflags.meerror)
            break;
    }
    while(gsmbyte != '\n')
    {
        gsmbyte = EUSARTG_Read();
        gsmusd[x++] = gsmbyte;
        if(gsmflags.meerror)
            break;
    }
}

uint8_t EUSARTG_Read(void)
{
//    TRISCbits.TRISC3 = 1;
    uint32_t x = 0;
    while(!U2STAbits.URXDA && x < 0xFFFF)
    {
        if(x > 0xFFFFE)
        {
            gsmflags.meerror = 1;
            break;
        }
    }
//    TRISCbits.TRISC3 = 0;

    
    if(U2STAbits.OERR)
    {
        // EUSART2 error - restart

        U2STAbits.OERR = 0; 
    }

    return U2RXREG;
}


//PIR3bits.TX2IF -  EUSART2 Transmit Interrupt Flag bit
//1 = The EUSART2 transmit buffer, TX2REG, is empty (cleared by writing TX2REG)
//0 = The EUSART2 transmit buffer is full

//&& TX2STAbits.TXEN -  Transmit Enable bit SREN/CREN bits of RCxSTA (Register 27-2) override TXEN in Sync mode.
// 1 = Transmit enabled
// 0 = Transmit disabled

//TX2STAbits.TRMT -  Transmit Shift Register Status bit
// 1 = TSR empty TSR = Tx shift reg
// 0 = TSR full

//U2STAbits.URXDA -  EUSART2 Receive Interrupt Flag bit
//1 = The EUSART2 receive buffer, RC2REG, is full (cleared by reading RC2REG)
//0 = The EUSART2 receive buffer is empty

