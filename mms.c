/* 
 * File:   mms.c
 * Author: Dave Plater
 *
 * Created on Sun 25 Feb 2024 14:59:17 SAST 
 */
#include "gsm.h"
/**/
uint8_t * srchbuf0;
uint8_t * srchbuf1;
uint8_t * srchbuf2;
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
            memset(gsmusd, NULL, 192); 
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
            Store_themms(Chan01_xpm, gsmmsg, mmsbyte2);
        }
    }
    goto repeatmms;
}

void parse_themms(void)//Format xpm for display
{
    uint16_t decim,wprc;
    uint16_t xy = 1;
    srchbuf0 = memchr(gsmmsg, ',', 32); //Look for the first comma
    srchbuf1 = memchr(srchbuf0 + 1, ':', 24); //Look for the colon after info
    credit = srchbuf1 - srchbuf0;
    credit++;
    memset(gsmusd, NULL, 192);
    srchbuf0 = memcpy(gsmusd, srchbuf0, credit); //Copy file info for FPM storage
    srchbuf0 = strstr(gsmusd, "chan");//"/* XPM */,chan1,R159.85:"
    srchbuf0 = srchbuf0 + 4; //Set at channel number
    channum = atoi(srchbuf0); // channum contains the channel number
    srchbuf0 = strstr(gsmusd, ",R");
    srchbuf0 = srchbuf0 + 2; //Set at price
    price = atoi(srchbuf0);//price section
    wprc = price / 100;
    decim = price % 100;
    
    price = sprintf(gsmusd, "Channel %d\nPrice R%.2d.%.2d.", channum, wprc, decim);
    xpmaddress = Chan01_xpm; // searchbufa stores the channels storage address
    while(xy < channum)
    {
        xpmaddress = xpmaddress + STORAGE_SIZE;
        xy++;
    }
    xy = 0;
    Store_themms((xpmaddress + BUF_SIZE), gsmusd, credit); //Finished storing the info
    srchbuf1 = strstr(gsmmsg, "\"BBBB");// indicates the start of the image
    srchbuf0 = strstr(srchbuf1, "B\","); //End of first pixel row
    csqval = srchbuf0 - srchbuf1; // The number of pixels in a row = the number of rows
    /* srchbuf1 = line start and srchbuf0 = end of line*/
    srchbuf2 = gsmmsg;
    while(xy < csqval)
    {
        srchbuf0 = strstr(srchbuf1, "\"B");// This is the start of the line
        srchbuf0++;//First pixel drop the "
        srchbuf1 = strstr(srchbuf0, "\",");//srchbuf1 contains the first pixel line end
        if(!srchbuf1)
        {
            srchbuf1 = strstr(srchbuf0, "\"}");
        }
        credit = srchbuf1 - srchbuf0;//This is the pixel row size
        memmove(srchbuf2, srchbuf0, (credit + 1));// Move one xpm line to gsmmsg beginning
        srchbuf2 = srchbuf2 + credit;
        srchbuf2[0] = 'E';
        srchbuf2++;
        srchbuf2[0] = NULL;
        srchbuf2[1] = NULL;
        srchbuf1 = srchbuf0 + credit + 1;
        xy++;
    }
    srchbuf2[0] = '\e';
}

void Test_pfm(void)
{
    mmsbyte2 = (strlen(mms_xpm)) + 2;
    srchbuf0 = memcpy(gsmmsg, mms_xpm, mmsbyte2);
    parse_themms();
    mmsbyte2 = strlen(gsmmsg);
    srchbuf1 = Chan01_xpm;
    srchbuf2 = gsmmsg + mmsbyte2;
    memset(srchbuf2, NULL, 129);
    Store_themms(srchbuf1, gsmmsg, mmsbyte2);
}

void Store_themms(uint32_t flashadd, uint8_t* flashsrc, uint16_t mmssize ) //mmssize stores the file size
{
    #if 1
    int8_t z;
    uint16_t tblocksz;
    uint16_t tblock = 0;
    uint32_t fflashadd;
    fflashadd = flashadd;
    srchbuf0 = flashsrc;
    tblocksz = mmssize / WRITE_FLASH_BLOCKSIZE;
    tblocksz++;  //Contains the number of blocks needed
    if(tblocksz > (BUF_SIZE / WRITE_FLASH_BLOCKSIZE)) //If file too big
    {
        tblocksz = (BUF_SIZE / WRITE_FLASH_BLOCKSIZE);//Truncate it.
    }
    while(tblock < tblocksz)
    {
        FLASH_EraseBlock(fflashadd);
        PIR7bits.NVMIF = 0;
        z = MyFLASH_WriteBlock(fflashadd, flashsrc);
        if(z == 0)
        {
            tblock++;
            fflashadd = fflashadd + WRITE_FLASH_BLOCKSIZE;
            flashsrc = flashsrc + WRITE_FLASH_BLOCKSIZE;
            
        }
    }
    #endif
}

bool MyFLASH_WriteBlock(uint32_t writeAddr, uint8_t *flashWrBufPtr)
{
    uint8_t i;
    uint8_t GIEBitValue = INTCONbits.GIE;
    
        // Block write sequence
    TBLPTRU = (uint8_t)((writeAddr & 0x00FF0000) >> 16);    // Load Table point register
    TBLPTRH = (uint8_t)((writeAddr & 0x0000FF00)>> 8);
    TBLPTRL = (uint8_t)(writeAddr & 0x000000FF);

    // Write block of data
    for (i=0; i<WRITE_FLASH_BLOCKSIZE; i++)
    {
        TABLAT = flashWrBufPtr[i];  // Load data byte

        if (i == (WRITE_FLASH_BLOCKSIZE-1))
        {
            asm("TBLWT*");
        }
        else
        {
            asm("TBLWT*+");
        }

        CLRWDT();
    }
    TBLPTRU = (uint8_t)((writeAddr & 0x00FF0000) >> 16);    // Load Table point register
    TBLPTRH = (uint8_t)((writeAddr & 0x0000FF00)>> 8);
    TBLPTRL = (uint8_t)(writeAddr & 0x000000FF);
    NVMCON1bits.NVMREG = 2;
    NVMCON1bits.WREN = 1;
	INTCONbits.GIE = 0; // Disable interrupts
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;  // Start program
    Nop();
    Nop();
    Nop();
    while(NVMCON1bits.WR);
    NVMCON1bits.WREN = 0;    // Disable writes to memory
    
    while(!PIR7bits.NVMIF);
    PIR7bits.NVMIF = 0;
	INTCONbits.GIE = GIEBitValue;   // Restore interrupt enable
    
    return (NVMCON1bits.WRERR);
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
    mmsbyte2++;
    gsmmsg[mmsbyte2] = 0x1A;//EOF
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
/**
 End of File
*/
