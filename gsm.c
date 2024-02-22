/* 
 * File:   gsm.c
 * Author: Dave Plater
 *
 * Created on September 26, 2018, 3:14 PM 
 */
#include "gsm.h"

//Wait for buffer empty
void gsm_waitx(void)
{
    TX1STAbits.TXEN = 1;
    while(!PIR3bits.TX1IF)
    {
    }
}
//Wait for buffer empty
void gsm_waitr(void)
{
    while(!PIR3bits.RC1IF)
    {
        
    }
}

void gsm_transmit(uint8_t txbyte)
{
    TX1STAbits.TXEN = 1;
    EUSARTG_Write(txbyte);
    while(!TX1STAbits.TRMT){}
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
    __uint24 msgbkup = msgadd;
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
void gsm_init(bool inittype)
{
    
    uint16_t x;
    uint8_t y;
    repeatoff:
    //led_switch(2); //Off
    gsm_zerobuff(gsmusd, 127); 
    y = gsm_on();
    ClrWdt();
    //led_switch(1);//RED
//    x = strstr(gsmusd, "RDY");
    if(y <= 4)                                                                                                                                                                                                                                      if(y == 0)
    {
        gsm_txAT();//Transmit AT\r to sync baud rate.
        gsm_transmit(0x0D);
        gsm_receive(1, gsmusm);
        gsm_msg("AT&F\r");
        x = Read_timeout1(gsmusd, 64);
        gsm_msg("AT&F0\r");
        x = Read_timeout1(gsmums, 64);
        gsm_msg("AT&V0\r");
        x = Read_timeout1(gsmmsg, 64);
        gsm_msg("AT&V\r");
        x = Read_timeout1(qrbuffer, 128);
        gsm_msg("AT&D0\r");
        gsm_receive(1, gsmusd);
        gsm_msg("AT+IPR=115200\r"); // 115200 or 57600 or 19200
//        gsm_msg("AT+IPR=0\r");
        gsm_receive(2, gsmusm);
        gsm_msg("AT&W0\r");
        gsm_receive(1, gsmums);
        asm("reset");
    }
    uint8_t *q;
    //Search for "+CPIN: NOT INSERTED"
    // void *memchr(const void *s, int c, size_t n);
    q = strstr(gsmusd, "+CFUN:"); // WARNING: The quote doesn't exist in the manual
    if(q)
    {
        if(!(memchr(q, '1', 10)))
        {
            asm("reset");
        }
    }
    else
    {
        goto repeatoff;
    }
        
//    gsmbyte = Read_timeout1(gsmusd);
    //gsm_unsolic(); //Populates gsmmsg
    errorecho:
    gsm_msg((uint8_t*)noecho);
    if(!inittype)
    {
        gsm_receive(1, gsmusd);
    }
    //
/*    uint8_t msgstr[24] = "AT+COPN\r";
    gsm_msg((uint8_t*)msgstr);
    gsmbyte = Read_timeout(gsmusd);
    gsm_msg((uint8_t*)"AT+CPOL?\r");
    gsmbyte = Read_timeout(gsmusd);
*/
    if(gsmflags.retransmit)
    {
        goto errorecho;
    }
    //led_switch(3); //LED toggle GREEN
	gsm_msg((uint8_t*)"AT+CREG=1\r");
	gsm_receive(1, gsmusm);
    ClrWdt();
    //led_switch(0); // Red = 1
	gsmwait:
    __delay_ms(2);
    //led_switch(3);
	gsm_msg((uint8_t*)"AT+CREG?\r");
	gsm_receive(2, gsmusd);
    q = strstr(gsmusd, "+CREG:");
    if(q)
    {
        if(!(memchr(q + 9, '1', 4)))
        {
            goto gsmwait;
        }
    }
    else
    {
        goto repeatoff;
    }
    //led_switch(2); //LED toggle GREEN
    uint8_t w = get_csq();
    if(w <= 0)
    {
        goto repeatoff;
    }
    if(w > 9)
    {
        //10 - 14, 15 - 19, 20 - 24 and >= 25
        LED4_SetHigh();
    }
    if(w > 14)
    {
        LED3_SetHigh();
    }
    if(w > 19)
    {
        LED2_SetHigh();
    }
    if(w > 24)
    {
        LED1_SetHigh();
    }
    
    gsm_msg((uint8_t*)tsoftid);
    gsm_receive(2, gsmusd);
    //led_switch(1);
}

uint8_t get_csq(void)
{
    uint8_t *m;
    gsm_msg((uint8_t*)"AT+CSQ\r");
	gsm_receive(2, gsmusd);
    m = strstr(gsmusd, "+CSQ:");
    if(m > 0)
    {
        m = m + sizeof("+CSQ:");
        csqval = atoi(m);
    }
    else
    {
        //led_switch(3); //Toggle led between green and red
        csqval = 0;
    }
    return (uint8_t)csqval;
}
/*
*  The RSSI values returned by the CSQ command is mapped to dBm value in the table below.
*  In the above example, rssi value of 25 corresponds to -63 dBm which implies an excellent signal condition.
Value 	RSSI dBm 	Condition
2 	-109 	Marginal
3 	-107 	Marginal
4 	-105 	Marginal
5 	-103 	Marginal
6 	-101 	Marginal
7 	-99 	Marginal
8 	-97 	Marginal
9 	-95 	Marginal 0 = 
10 	-93 	OK        0x0A 1010 0101
11 	-91 	OK        0x0B 1011
12 	-89 	OK        0x0C 1100
13 	-87 	OK        0x0D 1101
14 	-85 	OK        0x0E 1110
15 	-83 	Good      0x0F 1111
16 	-81 	Good      0x10 1 0000
17 	-79 	Good      0x11 1 0001
18 	-77 	Good      0x12 1 0010
19 	-75 	Good      0x13 1 0011
20 	-73 	Excellent 0x14 1 0100
21 	-71 	Excellent 0x15 1 0101
22 	-69 	Excellent 0x16 1 0110
23 	-67 	Excellent 0x17 1 0111
24 	-65 	Excellent 0x18 1 1000
 * 
25 	-63 	Excellent 0x19 1 1001
26 	-61 	Excellent
27 	-59 	Excellent
28 	-57 	Excellent  F
29 	-55 	Excellent
30 	-53 	Excellent
*/
//#if 0
/*    gsm_msg((uint8_t*)"AT+CANT?\r");
    Read_timeout1(gsmmsg, 64);
    gsm_msg((uint8_t*)"AT+CEGPRS=1,2\r");
    Read_timeout1(gsmmsg, 64);
    gsm_msg((uint8_t*)"AT+ECHARGE?\r");
    Read_timeout1(gsmmsg, 64);
    gsm_msg((uint8_t*)"AT+ECHARGE=1\r");
    Read_timeout1(gsmmsg, 64);
    gsm_msg((uint8_t*)"AT+ECHARGE=0\r");
    Read_timeout1(gsmmsg, 64);
    gsm_msg((uint8_t*)"AT+CBC\r");
    Read_timeout1(gsmmsg, 64);
    gsm_msg((uint8_t*)"AT+CBATCHK?\r");
    Read_timeout1(gsmmsg, 64);
    gsm_msg((uint8_t*)"AT+CBATCHK=1\r");
    Read_timeout1(gsmmsg, 64);
    gsm_msg((uint8_t*)"AT+CBATCHK=0\r");
    Read_timeout1(gsmmsg, 64);
    gsm_msg((uint8_t*)"AT+CBAND?\r");
    Read_timeout1(gsmmsg);
    gsm_msg((uint8_t*)"AT+CSDT?\r");//Switch on or off Detecting SIM Card
    Read_timeout1(gsmmsg);
    gsm_msg((uint8_t*)"AT+CGID\r");//Get SIM Card Group Identifier
    Read_timeout1(gsmmsg);
    gsm_msg((uint8_t*)"AT*CELLLOCK?\r");//*Set the List of ARFCN Which Needs to Be Locked - 

    Read_timeout1(gsmmsg);
    gsm_msg((uint8_t*)"AT+CSDT=0\r");// Don't detect sim
    Read_timeout1(gsmmsg);
    gsm_msg((uint8_t*)"AT+CSDT=1\r");//Detect sim
    Read_timeout1(gsmmsg);
    gsm_msg((uint8_t*)"AT+CSMINS?\r");//SIM Inserted Status Reporting
    Read_timeout1(gsmmsg);
    gsm_msg((uint8_t*)"AT+CSMINS=0\r");//Disable unsolicited result code
    Read_timeout1(gsmmsg);
    gsm_msg((uint8_t*)"AT+CSMINS=1\r");//Enable unsolicited result code
    Read_timeout1(gsmmsg);//AT+CANT
    gsm_msg((uint8_t*)"AT+CANT?\r");//Antenna Detecting
    Read_timeout1(gsmmsg);
    gsm_msg((uint8_t*)"AT+CNETSCAN\r");//Disable unsolicited result code
    Read_timeout1(gsmmsg);
    gsm_msg((uint8_t*)"AT+CSMINS=1\r");//Enable unsolicited result code
    Read_timeout1(gsmmsg);//AT+CANT*/
 //#endif
//Read until 3 second timeout for initialisation of network
//return message count
uint8_t Read_timeout1(uint8_t *msgadd, uint16_t lngmms)
{
    uint16_t v = 0;
    PIE3bits.RC1IE = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    TMR5_Initialize();
    T5CONbits.TMR5ON = 1;
    while(!PIR4bits.TMR5IF)
    {
        if(EUSART1_is_rx_ready())
        {
            PIR3bits.RC1IF = 0;
            msgadd[v] = EUSART1_Read();
            T5CONbits.TMR5ON = 0;
            TMR5_Initialize();
            T5CONbits.TMR5ON = 1;
            if(v < lngmms)
            {
                v++;
            }
            else
            {
                break;
            }
        }
    }
    PIE3bits.RC1IE = 0;
    INTCONbits.GIEH = 0;
    INTCONbits.GIEL = 0;
    msgadd[v] = 0;
    return v;
}
void Read_SMS(void)
{
    //led_switch(2);
    Read_Service();
 //   base64_encode("22d3cf4f-db05-4609-9773-2312375b4523:", (idx_t) 37, base64buf, (idx_t) 58);
    __delay_ms(500);
    gsm_msg(smstxt);//AT+CMGF=1 set text sms
    gsm_receive(1, gsmtim);
    gsm_msg(smsdel);//"AT+CMGDA=\"DEL ALL\"\r"
    gsm_receive(1, gsmtim);
//    price_set();
    gsmflags.msgavl = 0;
    PIE3bits.RC1IE = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    //led_switch(2); //off
    while(SERVICE_PORT)
    {
        int_sms_notify();
    }
    PIE3bits.RC1IE = 0;
    uint8_t k = 0;
    while(!k)
    {
        uint8_t z = Long_Press();
        switch(z)
        {
            case 3 : k = 1;
            break;
            case 2 : channel = 0;
            dispense_test();
            k = 1;
            break;
            case 1 : k = 0;
            continue;
        }
    }
}
/*
    gsm_msg(smstxt);
    gsm_receive(1, gsmmsg);
    
    gsm_msg(smsdel);
    gsm_receive(1, gsmmsg);
    
    gsm_getbalance();
    
    gsm_msg(smslst);
    gsm_receive(1,gsmmsg);
    
    gsm_msg(smdqry);
    gsm_receive(1, gsmmsg);
    
    gsm_msg(engqry);
    gsm_receive(2, gsmmsg);
    
    gsm_msg(netoff);
    gsm_receive(2, gsmmsg);
   
    gsm_msg(facres);
    gsm_receive(1, gsmmsg);
    goto gsminit;
    asm("nop");
*/
/*+CMGR: "REC UNREAD","+27820098372","","22/07/19,15:29:07+08"
ùòèdc££KEY = 22d3cf4f-db05-4609-9773-2312375b4523:.Sent from 27766520007 from the my Vodacom app.Get 20 free sms per day.
0*/

int int_sms_notify(void)
{
    
    uint8_t* x;
    int y = 0;
    ClrWdt();
    if(EUSART1_is_rx_ready())
    {
        if(gsmflags.msgavl) //Retrieve the message if set
        {
            gsmflags.msgavl = 0;
            y = gsmint_receive(gsmmsg);
            if(y > 0)//if y > 0 then something has been received
            {
                y = 0;
                PIE3bits.RC1IE = 0;
                ClrWdt();
                //led_switch(0); //Green = price store
                x = strstr(gsmmsg, "Setup,");// check for price set message
                if(!x)//Not a setup message, check for merchant key
                {
                    x = strstr(gsmmsg, "KEY = ");
                    if(!x)// Not a merchant key either, delete and wait.
                    {
                        x = strstr(gsmmsg, "MID = ");
                        if(x)
                        {
                            //led_switch(1); //Red =  merchant id stored
                            store_mid();
                            while(SERVICE_PORT)
                            {
                                ClrWdt();
                                //led_switch(3);
                            }
                        }
                        //led_switch(2); //off
                        gsm_msg(smsdel);//"AT+CMGDA=\"DEL ALL\"\r"
                        gsm_receive(1, gsmtim);
                        PIE3bits.RC1IE = 1;
                    }
                    else// is a merchant key
                    {
                        //led_switch(1); //Red =  merchant key stored
                        store_merchkey();
                        while(SERVICE_PORT)
                        {
                            ClrWdt();
                        }
                        gsm_msg(smsdel);//"AT+CMGDA=\"DEL ALL\"\r"
                        gsm_receive(1, gsmtim);
                        __delay_ms(1000);
                        PIE3bits.RC1IE = 1;
                    }
                }
                else //Is a price set message
                {
                    
                    price_set();
                    gsm_msg(smsdel);//"AT+CMGDA=\"DEL ALL\"\r"
                    gsm_receive(1, gsmtim);
                    __delay_ms(1000);
                    PIE3bits.RC1IE = 1;
                }
            }
        /*
         * +CMGR: "REC UNREAD","+27766520007","Dave Plater","22/06/21,15:58:15+08"
         * Setup, 1=50,2=43,3=40,4=30,5=20,6=10,7=15,8=25..0
         * Setup, 1=0975,2=0975,3=1250,4=1190..
         */
        }
        else //Wait for unsolicited notification
        {
            ClrWdt();
            y = gsmint_receive(gsmusd);
            if(!y)
            {
                y = strstr(gsmusd, "+CMTI"); //Make sure it's an sms notification
            }
        }
        //led_switch(2) ;       
    }
    if(y > 0)
    {
        gsm_msg("AT+CMGR=1\r");// 
        gsmflags.msgavl = 1;
    }
}

int gsmint_receive( uint8_t messagebuf[] )
{
    //TMR3 PIR4bits.TMR3IF T3CONbits.TMR3ON = 1;
    TMR3_Initialize();
    T3CONbits.TMR3ON = 1;
    gsmflags.meerror = 0;
    int x = 0;
    gsmbyte = 0;
    while(!PIR4bits.TMR3IF)// If no data for 10mS then message receive complete
    {
        if(EUSART1_is_rx_ready()) //Receive buffer data present
        {
            gsmbyte = EUSART1_Read();
            messagebuf[x] = gsmbyte;
            x++;
            TMR3_Initialize();
            T3CONbits.TMR3ON = 1;
        }
    }
    T3CONbits.TMR3ON = 0;
    x++;
    messagebuf[x] = 0;
    return x;
}

void gsm_receive(uint8_t noofline, uint8_t messagebuf[])
{
    gsmflags.meerror = 0;
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
  //  x++;
    messagebuf[x] = 0;
}

void gsm_txAT(void)
{
    gsm_transmit('A');
    gsm_transmit('T');
}

//Turn on or off the gsm unit and initialize the 3 second startup timer.
/*#define PWR_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define PWR_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
*/
uint8_t gsm_on(void)
{
    rgsm_on:
    gsm_msg("AT+CPOWD=0\n");
    delay_10mS(400);//delay 4 seconds after power down
    ClrWdt();
    PWR_LAT = 0;
    One_Second();//Hold PWR low for 1 second is actually 1.49 seconds
    ClrWdt();
    PWR_LAT = 1;
    uint8_t x = Read_timeout1(gsmusd, 128);
//    gsm_receive(10, gsmusd);
    return x;
}

void One_Second(void)
{
    T1CONbits.TMR1ON = 0;
    TMR1_Initialize();
    TMR1_WriteTimer(19036);//TMR1 1 sec = 0x86E8 = 34536; 19036 = 0x4A5C
    T1CONbits.TMR1ON = 1;
    while(!PIR4bits.TMR1IF){}
    T1CONbits.TMR1ON = 0;
    PIR4bits.TMR1IF = 0;
}

uint8_t gsm_Read(void)
{
    TMR6_Initialize();
    T6CONbits.TMR6ON = 1;
    while(!PIR3bits.RC1IF)
    {
        if(PIR4bits.TMR6IF)
        {
            TMR6_Stop();
            PIR4bits.TMR6IF = 0;
            gsmflags.meerror = 1;
            break;
        }
    }

    
    if(1 == RC1STAbits.OERR)
    {
        // EUSART1 error - restart

        RC1STAbits.CREN = 0; 
        RC1STAbits.CREN = 1; 
    }

    return RC1REG;
}

void gsm_off(void)
{
    gsm_msg("AT+CPOWD=0\n");
    __delay_ms(500);
}

void gsm_netwait(void)
{
    gsmbyte = 0;
    uint8_t x = 0;
    while(gsmbyte != 'S')
    {
        gsmbyte = EUSARTG_Read();
        gsmmsg[x++] = gsmbyte;
    }
    while(gsmbyte != '\n')
    {
        gsmbyte = EUSARTG_Read();
        gsmmsg[x++] = gsmbyte;
    }
}

uint8_t EUSARTG_Read(void)
{
/*    long long d = 0;//1048575 loops timeout
    gsmflags.retransmit = 0;//    TRISCbits.TRISC3 = 1;*/
    while(!PIR3bits.RC1IF/* && d <= 0xFFFFFF*/)
    {
    /*    d++;
        if(d >= 0xFFFFFF)
        {
            gsmflags.retransmit = 1; //Timeout happened
            return 0;
        }*/
    }
//    TRISCbits.TRISC3 = 0;

    
    if(RC1STAbits.OERR)
    {
        // EUSART1 error - restart

        RC1STAbits.CREN = 0; 
        RC1STAbits.CREN = 1; 
    }
    return RC1REG;
}

void EUSARTG_Write(uint8_t txData)
{
    while(0 == PIR3bits.TX1IF)
    {
    }

    TX1REG = txData;    // Write the data byte to the USART.
}

bool delay_10mS(uint16_t count)
{
    TMR3_Initialize();
    T3CONbits.TMR3ON = 1;
    PIR4bits.TMR3IF = 0;
    while(count > 0)
    {
        if(PIR4bits.TMR3IF)
        {
            count--;
            T3CONbits.TMR3ON = 0;
            TMR3_Initialize();
            T3CONbits.TMR3ON = 1;
            PIR4bits.TMR3IF = 0;
        }
    }
    return 1;
}

uint8_t Read_timeout2(uint8_t *msgadd,uint16_t lngmms ) //10ms timeout with interrupt read
{
    uint16_t v = 0;
    PIE3bits.RC1IE = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    TMR5_Initialize();
    TMR5_WriteTimer(0x1CF3);//15 second timeout
    T5CONbits.TMR5ON = 1;
    while(!PIR4bits.TMR5IF)
    {
        if(EUSART1_is_rx_ready())
        {
            PIR3bits.RC1IF = 0;
            msgadd[v] = EUSART1_Read();
            T5CONbits.TMR5ON = 0;
            TMR5_Initialize();
            TMR5_WriteTimer(0x1CF3);//15 second timeout
            T5CONbits.TMR5ON = 1;
            if(v < lngmms)
            {
                v++;
            }
            else
            {
                break;
            }
        }
    }
    PIE3bits.RC1IE = 0;
    INTCONbits.GIEH = 0;
    INTCONbits.GIEL = 0;
    msgadd[v] = 0;
    return v;
}

/*"AT+CMMSCURL=\"mmsc.monternet.com\""
 OK
 AT+CMMSCID=1
 AT+CMMSPROTO="10.0.0.172",80
  AT+SAPBR=3,1,"Contype","GPRS"
 AT+SAPBR=3,1,"APN","CMWAP"
 AT+SAPBR=1,1
 AT+SAPBR=2,1
+SAPBR: 1,1,"10.89.193.1"
OK
 +CMTI: "SM",3,"MMS PUSH"*/
//DAILYASAP50
void Get_mms(void)
{
    mms_init();
    gsm_msg("AT+CMGD=1,4\r");
    gsm_receive(1, gsmusd);
    repeatmms:
    while(SERVICE_GetValue())
    {
        csqval = Read_timeout1(gsmusd, 64);// look for +CMTI: "SM",3,"MMS PUSH"
        if(csqval > 6)
        {
            srchbuf0 = strstr(gsmusd, "+CMTI: ");
            if(!srchbuf0)
            {
                break;
            }
            mmsbyte = *(srchbuf0 + 8);//mmsbyte now contains the index
            gsm_msg("AT+CMMSRDPUSH=1\r");
            csqval = Read_timeout1(gsmusd, 383);
            srchbuf0 = strstr(gsmusd, "+CMMSRDPUSH:");
            if(srchbuf0)
            {
                credit = strlen(srchbuf0);
                srchbuf1 = memchr(srchbuf0, 0x20, credit);
                mmsbyte = atoi(srchbuf1 + 1); //mmsbyte now contains the message index
            }
/* +CMTI: "SM",1,"MMS PUSH",2,1 use "PUSH," to get index
   +CMTI: "SM",2,"MMS PUSH",2,2 Search 
+CMMSRECV: "+27766520007","2024-02-17,12:29:39","",2023
1,"smil.xml",10,242
2,"text_0.txt",4,168*/
            memset(gsmusd, NULL, 383); 
            sprintf(gsmums, "AT+CMMSRECV=%d\r", mmsbyte); //This takes 10 seconds maybe more
            gsm_msg(gsmums);
            csqval = Read_timeout2(gsmusd, 383);//<fileIndex,name,type,filesize>
            srchbuf0 = strstr(gsmusd, "+CMMSRECV:");
            if(srchbuf0)
            {
                srchbuf1 = strrchr(srchbuf0, ','); //Search for the last comma
                srchbuf1++;
                mmsbyte2 = atoi(srchbuf1); //mmsbyte now contains the file size to be used with read
            }
            credit = csqval;
            memset(gsmmsg, NULL, 2048);
            sprintf(gsmums, "AT+CMMSREAD=%d\r", mmsbyte);
            gsm_msg(gsmums);
            Read_themms(gsmmsg, mmsbyte2);
            Store_themms(mmsbyte2);
        }
    }
    goto repeatmms;
}

void Store_themms(uint16_t mmssize)
{
    int8_t z;
    flashadd = Chan01_xpm;
    while(flashadd <= Chan01_xpm + mmssize)
    {
        z = FLASH_WriteBlock(flashadd, srchbuf0);
        if(z)
        {
            flashadd = Chan01_xpm + WRITE_FLASH_BLOCKSIZE;
        }
    }
}

void Read_themms(uint8_t* messbuf, uint16_t mmssize)
{
    uint16_t mmscnt = 0;
    PIE3bits.RC1IE = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    TMR3_Initialize();
    T3CONbits.TMR3ON = 1;
    PIR4bits.TMR3IF = 0;
    while(EUSART1_is_rx_ready() == false)
    {
        if(PIR4bits.TMR3IF)
        {
            TMR3_Initialize();
            T3CONbits.TMR3ON = 1;
            PIR4bits.TMR3IF = 0;
            mmscnt++;
            if(mmscnt > 5000)
            {
                break;
            }
        }
    }
    mmscnt = 0;
    while(!PIR4bits.TMR3IF)
    {
        if(EUSART1_is_rx_ready())
        {
            gsmbyte = EUSART1_Read();
            TMR3_Initialize();
            T3CONbits.TMR3ON = 1;
            PIR4bits.TMR3IF = 0;
            PIR3bits.RC1IF = 0;
            if(gsmbyte != NULL)
            {
                gsmmsg[mmscnt++] = gsmbyte;
            }
        }
    }
    T3CONbits.TMR3ON = 0;
    PIE3bits.RC1IE = 0;// mmscnt   = total file size including header
    INTCONbits.GIEH = 0;//mmsbyte2 = actual data size so mmscnt - mmsbyte2 = header size
    INTCONbits.GIEL = 0;//add header size to gsmmsg and move to gsmmsg
    srchbuf0 = strstr(gsmmsg, "/* XPM */");
    srchbuf1 = memmove(gsmmsg, srchbuf0, mmscnt);
    srchbuf0 = gsmmsg + mmsbyte2 + 1;
    csqval = mmscnt - mmsbyte2;
    memset(srchbuf0, NULL, csqval);
}

void convert_mms(void) //Remove message header and any null characters in the body
{
    srchbuf0 = memchr(gsmmsg, NULL, 64);//Locate first null character
    srchbuf1 = memmove(gsmmsg, srchbuf0, mmsbyte2);//overwrite file header
    mmsbyte = mmsbyte2;
    uint16_t mmscnt = 0;
    uint16_t gmmscnt = 0;
    while(mmscnt < mmsbyte2)
    {
        gsmbyte = gsmmsg[mmscnt++];
        if(gsmbyte != 0)
        {
            gsmmsg[gmmscnt++];
        }
    }
}
/*
 2,"<sender>","<subject>","<transaction>","<location>","<time>",<class>,<size>
 2,"+27766520007","","0049010999012402111316431254001","http://10.114.3.139:8080/was/00490109990124021113164312540
 
 */
void mms_init(void)
{
    gsm_msg("AT+CMMSINIT\r");
    gsm_receive(1, gsmusd);
    gsm_msg("AT+CMMSCURL=\"http://mmsc.vodacom4me.co.za\"\r");
    gsm_receive(1, gsmusd);
    gsm_msg("AT+CMMSCID=1\r");
    gsm_receive(1, gsmusd);
    gsm_msg("AT+CMMSPROTO=\"196.6.128.13\",8080\r");
    gsm_receive(1, gsmusd);
    gsm_msg("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r");
    gsm_receive(1, gsmusd);
    gsm_msg("AT+SAPBR=3,1,\"APN\",\"mms.vodacom.net\"\r");
    gsm_receive(1, gsmusd);
    gsm_msg("AT+SAPBR=1,1\r");
    gsm_receive(1, gsmusd);
    gsm_msg("AT+SAPBR=2,1\r"); //+SAPBR: 1,1,"196.6.128.13" OK
    gsm_receive(2, gsmusd);
    gsm_msg("AT+CMMSEDIT=0\r");
    gsm_receive(1, gsmtim);
}
//PIR3bits.TX1IF -  EUSART1 Transmit Interrupt Flag bit
//1 = The EUSART1 transmit buffer, TX1REG, is empty (cleared by writing TX1REG)
//0 = The EUSART1 transmit buffer is full

//&& TX1STAbits.TXEN -  Transmit Enable bit SREN/CREN bits of RCxSTA (Register 27-2) override TXEN in Sync mode.
// 1 = Transmit enabled
// 0 = Transmit disabled

//TX1STAbits.TRMT -  Transmit Shift Register Status bit
// 1 = TSR empty TSR = Tx shift reg
// 0 = TSR full

//PIR3bits.RC1IF -  EUSART1 Receive Interrupt Flag bit
//1 = The EUSART1 receive buffer, RC1REG, is full (cleared by reading RC1REG)
//0 = The EUSART1 receive buffer is empty


