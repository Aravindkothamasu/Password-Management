#include"header.h"
U32 putina[9],confirm[9],op=0,count=0;
U32 s1[12],s2[12],r1[12],r2[12];
U32 pwd[4][12];



/***************************************************************/
/*			Menu shows 									       */
/*						1.Forget Password				  	   */
/*						2.Enter Password (Enter Through Keypad)*/
void Menu(void)
{
abcd:
	lcd_cmd(0x1);
	lcd_string("1,Forget Password");
	lcd_cmd(0xc0);
	lcd_string("2,Enter Password");
	lcd_cmd(0x94);

	if((op = keyscan())<2)
	{		
		lcd_string("You Entered : ");
		lcd_data(op+49);
		tdelay_ms(500);
		(op==0) ? (reset(r1,r2)) : (enter()) ;	
	}																		    
	else 
	{
		lcd_string("Wrong Option");
		lcd_cmd(0xd4);
		lcd_string("Try again");
		tdelay_ms(2000);
		goto abcd;
	}
}


/*****************************************************************/
/*																 */
/*					For setting the password					 */


void set(U32 *a,U32 *b)
{				
	U32 k;
	if(count>=4)					//count = no.of times the password has set
	{
			lcd_cmd(0x1);
			lcd_string("4 times crossed ");//crossed 4 times
			lcd_cmd(0xc0);
			lcd_string("You can't set pwd");
			lcd_cmd(0x94);
			lcd_string("Program strucks");
			while(8);						//struck here, can't continue anymore
	}	
	Otp(1);									//OTP function
	tdelay_ms(2000);
asd:
	lcd_cmd(0x1);
	lcd_string("Entr new Pwd:");
	lcd_cmd(0xc0);
	input(a,12,2);							//Take the input 

	lcd_cmd(0x94);				
	lcd_string("Re-entr Pwd");				//Re-enter the password
	lcd_cmd(0xd4);
	input(b,12,4);							//Take the input
	
	
	tdelay_ms(500);
	lcd_cmd(0x1);						   //compare both the inputs
	if(!my_strcmp(a,b))
	{
		lcd_string("Pwd matched plz wait");
		lcd_cmd(0xc0);
		tdelay_ms(1000);
		lcd_string("check wth data bse");	  //Checking with Previous Passwords
		lcd_cmd(0x94);
		tdelay_ms(1700);
		lcd_cmd(1);
		for(k=0;k<count;k++)				   //loop represents no.of previous passwords assigned and checking into that
				if(my_strcmp(b,pwd[k])==0)	   //if any of that it is matching then,
				{	
					lcd_string("Pwd already used");
					lcd_cmd(0xc0);
					lcd_string(" Try New");
					tdelay_ms(4500);
					goto asd;
				}
		tdelay_ms(1000);
	}			
	else								//If Both are not matched then,
	{
		lcd_string("Pwd not mach Rentr");  //Error msg ,then goto again
		tdelay_ms(1000);
		goto asd;
	} 
	my_strcpy(a,pwd[count++]);			   //If it is matched then,add into data base.
//	lcd_cmd(0xd4);	 									
//	lcd_string("Setting Done");
//	tdelay_ms(2000);
	lcd_cmd(1);
}



/************************************************************/
/*												   			*/
/*					For Re-Setting Password					*/


void reset(U32 *r1,U32 *r2)
{					 //If you want to re-set password ,then confirm the date of birth
//	U32 i;
re:
	lcd_cmd(0x1);
	lcd_string("Enter DOB");		
	lcd_cmd(0xc0);
	input(confirm,8,2);				//Take the input DOB.
	lcd_cmd(0x94);
//	for(i=0;i<8;i++)
//		lcd_data(confirm[i]);
	tdelay_ms(1500);
	lcd_cmd(0xd4);
	if(!my_strcmp(confirm,putina))		//If it match returns 0 =  !0 true
		set(r1,r2);					    //set the password
	else								//Other wise Error message
	{	
		lcd_string("Wrong DOB Re-enter");		//Wrong date of birth
		tdelay_ms(700);
		goto re;								//goto starting
	}
		lcd_cmd(0xd4);	 									
		lcd_string("Setting Done");				//If every thing correct prints
		tdelay_ms(1500);
		login();								//login	function
}



/************************************************************/
/*												   			*/
/*					For Entering Password					*/
/*															*/

void enter(void)
{						//Enter a password that should match with the latest entered password.
	U32 ent[12];
again:
 	lcd_cmd(0x1);
	lcd_string("Enter Pwd :");
	lcd_cmd(0xc0);				//Take the i/p
	input(ent,12,2);
	lcd_cmd(0x94);
	tdelay_ms(900);
	lcd_cmd(1);
	if(my_strcmp(ent,pwd[count-1]))		//checking with latest password
	{
		tdelay_ms(500);
		lcd_string("Wrong Pwd Entr");	 //If it is fail
		tdelay_ms(1000);
		goto again;						 //doing from starting
	}
	else
		login();						 //if successfull login.
}



/************************************************************/
/*												   			*/
/*					Date of Birth function					*/
/*															*/


void dob(void)
{
	U32 i;
qwert:
	tdelay_ms(2000);
	lcd_cmd(0x1);
	lcd_string("Enter DOB : ");
 	lcd_cmd(0xc0);
	lcd_string("Enter DD/MM/YYYY");
	lcd_cmd(0x94);
	for(i=0;i<8;i++)					  //scan 8 characters 2 (date) + 2 (mnth) + 4 (yr)
	{	
		if((putina[i]=keyscan()+48)>57)	  //if it otherthan ascii 0-9 enter loop
		{
			lcd_cmd(0xd4);
			lcd_string("Wrong i/p ");	  //error msg
			tdelay_ms(1500);
			goto qwert;					  //start again.
		}
		lcd_data(putina[i]);			  //if not print value
		if(i==1 || i==3)				  // print '/' after date,mnth
		{	tdelay_ms(50);
			lcd_data('/');	}		
	}
	putina[8]=0;						  // array last character is 0
	tdelay_ms(2000);
	lcd_cmd(1);							  //clear the screen
//	for(i=0;i<8;i++)
//		lcd_data(putina[i]);
	tdelay_ms(300);
	lcd_string("Plz wait setting...");
	tdelay_ms(1100);
}



/************************************************************/
/*												   			*/
/*						Input function						*/
/*															*/

void input(U32 *a,U32 len,U32 lin)		//array to store,length of array,line no. to print
{
	U32 i,flg=0;
	U8 li[5]={0,0x80,0xc0,0x94,0xd4};	
 	for(i=0;i<len;i++)
	{
		
		if( (a[i]=keyscan()) == 14)		 //checking for caps on (or) off
		{
				flg =!flg;				 //toggle the flag
				lcd_cmd(li[lin-1]+16);	 //to indicate caps on -off location
				(flg==1) ? lcd_data('C') : lcd_data(' '); //if on='C' off=' '
				lcd_cmd (li[lin]+i); 	  //after come to previous location
				i--;					  //decrement i.
				continue;				  //no need to go further in this case.
		}
		else if(a[i]==15)   			  //15 treated as '\n'
		{
			a[i] = 0;					  //assign no. as 0
			break;						  //come out of loop
		}
		else if(a[i]>9)				   	  //For a,b,c,d,e
			(flg == 1)?(a[i] += 55):(a[i] += 87);	//flg is 1 means caps ON ?  store in Caps : store in small
		else
			a[i] += 48;					//For 0 - 9				
		lcd_data(a[i]);					//print value
		tdelay_ms(700);					//after some delay repalce with '*'
		lcd_cmd(li[lin]+i);
		lcd_data('*');					//printing *
	}
}	



/************************************************************/
/*												   			*/
/*						OTP generation function				*/
/*															*/

void Otp(U32 num)
{
	static int a = 1234;		 //take a static value
	U8 c[4],d[4],i,b=0;			 //c is GSM,d is i/p from keypad
	U32 k;
again:
	k=1000,b=0;
//	uart0_tx_string("In OTP \r\n");
	a = a*10+num*10+(a/12)*3;									//some random expression
	a %= 10000;																//Should be < 10000
	for(i=0;i<4;i++)
	{
			c[i]=(a/k)-(b*10)+48;		   						//one by one into array GSM
			b = a/k;
			k /= 10;
	}
	 c[i] = 0;
	 send_msg(c);															//sending into GSM
	 lcd_cmd(0x1);
	 lcd_string("Enter OTP : ");
	 lcd_cmd(0xc0);
	 
	 for(i=0;i<4;i++)													//Recieving i/p loop
	 {
			lcd_data(d[i]=keyscan()+48);					//print character
			tdelay_ms(1000);	
			lcd_cmd(0xc0+i);											//for printing * on same place
			lcd_data('*');
	 }	  
	 
	 lcd_cmd(0x94);	
	 lcd_string("Plz wait ");									//plz wait.
	 lcd_cmd(0xd4);
	 for(i=0;i<4;i++)													//checking both true or not
			if(c[i] != d[i])												//if both not true error
			{
					lcd_string("Wrong OTP");
					tdelay_ms(1000);			 //start again.
					goto again;
			}
	lcd_string("OTP correct");
	tdelay_ms(3500);
}


/************************************************************/
/*												   																*/
/*					Initilization function													*/
/*																													*/


void inits()
{
	uart0_init(9600);							//uart
 	lcd_init();										//lcd 
	gsm_init();										//GSM 
	rtc_init();										//RTC
	set_time();										//set the time
	
	
	
	lcd_string(" *** Welcome to ***");				//initilization done.
	lcd_cmd(0xc0);
	lcd_string("   ** Password **");
	lcd_cmd(0x94);
	lcd_string("  ** Management **");
	tdelay_ms(5000);
	lcd_cmd(1);
}



/************************************************************/
/*												   			*/
/*						string copy function				*/
/*															*/
void my_strcpy(U32 *p,U32 *q )
{
		U32 i;
		for(i=0;p[i];i++)
			q[i] = p[i];
		q[i] = 0;
}



/************************************************************/
/*												   																*/
/*						string compare function												*/
/*																													*/

int my_strcmp(U32 *p,U32 *q)
{
 	U32 i;
	for(i=0;p[i];i++)
			if(p[i]!=q[i])
					return -1;
	if(p[i]==q[i])
		return 0;
	else 
		return -1;
}
