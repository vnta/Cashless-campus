<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<HTML>
<HEAD>
	<title>
		Electronics - Henning Karlsen
	</title>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
	<META HTTP-EQUIV="CACHE-CONTROL" CONTENT="NO-CACHE">
	<META HTTP-EQUIV="PRAGMA" CONTENT="NO-CACHE">
</HEAD>

<body style="background-color: #FFFFFF;">

<pre>
<span style="color: #7E7E7E;">//&nbsp;UTFT_Analog_Clock&nbsp;(C)2010-2012&nbsp;Henning&nbsp;Karlsen</span>
<span style="color: #7E7E7E;">//&nbsp;web:&nbsp;http://www.henningkarlsen.com/electronics</span>
<span style="color: #7E7E7E;">//</span>
<span style="color: #7E7E7E;">//&nbsp;This&nbsp;program&nbsp;was&nbsp;made&nbsp;simply&nbsp;because&nbsp;I&nbsp;was&nbsp;bored.</span>
<span style="color: #7E7E7E;">//</span>
<span style="color: #7E7E7E;">//&nbsp;Hardware&nbsp;requirements:</span>
<span style="color: #7E7E7E;">//&nbsp;&nbsp;-&nbsp;Arduino&nbsp;Mega</span>
<span style="color: #7E7E7E;">//&nbsp;&nbsp;-&nbsp;Display&nbsp;module&nbsp;supported&nbsp;by&nbsp;UTFT</span>
<span style="color: #7E7E7E;">//&nbsp;&nbsp;-&nbsp;DS1307&nbsp;RTC</span>
<span style="color: #7E7E7E;">//&nbsp;&nbsp;-&nbsp;Some&nbsp;method&nbsp;of&nbsp;connecting&nbsp;the&nbsp;display&nbsp;module&nbsp;to&nbsp;the&nbsp;Arduino</span>
<span style="color: #7E7E7E;">//&nbsp;&nbsp;&nbsp;&nbsp;like&nbsp;the&nbsp;old&nbsp;ITDB02&nbsp;Mega&nbsp;Shield&nbsp;v1.1&nbsp;as&nbsp;it&nbsp;already&nbsp;contains</span>
<span style="color: #7E7E7E;">//&nbsp;&nbsp;&nbsp;&nbsp;the&nbsp;DS1307&nbsp;or&nbsp;the&nbsp;All&nbsp;in&nbsp;One&nbsp;Super&nbsp;Screw&nbsp;Shield&nbsp;from</span>
<span style="color: #7E7E7E;">//&nbsp;&nbsp;&nbsp;&nbsp;AquaLEDSource&nbsp;which&nbsp;also&nbsp;has&nbsp;everything&nbsp;you&nbsp;need&nbsp;on&nbsp;the</span>
<span style="color: #7E7E7E;">//&nbsp;&nbsp;&nbsp;&nbsp;shield.</span>
<span style="color: #7E7E7E;">//</span>
<span style="color: #7E7E7E;">//&nbsp;Software&nbsp;requirements:</span>
<span style="color: #7E7E7E;">//&nbsp;&nbsp;-&nbsp;UTFT&nbsp;library&nbsp;&nbsp;&nbsp;&nbsp;http://www.henningkarlsen.com/electronics/library.php?id=51</span>
<span style="color: #7E7E7E;">//&nbsp;&nbsp;-&nbsp;UTouch&nbsp;library&nbsp;&nbsp;http://www.henningkarlsen.com/electronics/library.php?id=55</span>
<span style="color: #7E7E7E;">//&nbsp;&nbsp;-&nbsp;DS1307&nbsp;library&nbsp;&nbsp;http://www.henningkarlsen.com/electronics/library.php?id=34</span>
<span style="color: #7E7E7E;">//</span>
<span style="color: #7E7E7E;">//&nbsp;This&nbsp;program&nbsp;should&nbsp;work&nbsp;on&nbsp;all&nbsp;the&nbsp;supported&nbsp;display&nbsp;modules</span>
<span style="color: #7E7E7E;">//&nbsp;from&nbsp;the&nbsp;2.4"&nbsp;ones&nbsp;and&nbsp;up&nbsp;to&nbsp;the&nbsp;5.0"&nbsp;ones,&nbsp;but&nbsp;keep&nbsp;in&nbsp;mind&nbsp;</span>
<span style="color: #7E7E7E;">//&nbsp;that&nbsp;this&nbsp;program&nbsp;was&nbsp;made&nbsp;to&nbsp;work&nbsp;on&nbsp;a&nbsp;320x240&nbsp;module,&nbsp;so&nbsp;it&nbsp;</span>
<span style="color: #7E7E7E;">//&nbsp;may&nbsp;look&nbsp;a&nbsp;little&nbsp;silly&nbsp;on&nbsp;larger&nbsp;displays.</span>
<span style="color: #7E7E7E;">//&nbsp;It&nbsp;will&nbsp;not&nbsp;work&nbsp;on&nbsp;the&nbsp;2.2"&nbsp;modules&nbsp;without&nbsp;modification&nbsp;as&nbsp;</span>
<span style="color: #7E7E7E;">//&nbsp;the&nbsp;resolution&nbsp;on&nbsp;those&nbsp;modules&nbsp;are&nbsp;too&nbsp;low.</span>
<span style="color: #7E7E7E;">//</span>
<span style="color: #7E7E7E;">//&nbsp;Default&nbsp;serial&nbsp;speed&nbsp;for&nbsp;this&nbsp;sketch&nbsp;is&nbsp;115200&nbsp;baud.</span>
<span style="color: #7E7E7E;">//</span>
<span style="color: #7E7E7E;">//&nbsp;You&nbsp;can&nbsp;buy&nbsp;the&nbsp;AquaLEDSource&nbsp;All&nbsp;in&nbsp;One&nbsp;Super&nbsp;Screw&nbsp;Shield&nbsp;here:</span>
<span style="color: #7E7E7E;">//&nbsp;English:&nbsp;&nbsp;&nbsp;&nbsp;http://www.aqualedsource.com/prods/screwshield.php</span>
<span style="color: #7E7E7E;">//&nbsp;Portuguese:&nbsp;http://www.aqualed-light.com/?sec=home&amp;id=1818</span>
<span style="color: #7E7E7E;">//</span>
<span style="color: #7E7E7E;">/**************************************************************************/</span>

<span style="color: #7E7E7E;">//&nbsp;Enable&nbsp;(1)&nbsp;or&nbsp;disable&nbsp;(0)&nbsp;VT100&nbsp;terminal&nbsp;mode</span>
<span style="color: #7E7E7E;">//&nbsp;Enable&nbsp;this&nbsp;if&nbsp;your&nbsp;terminal&nbsp;program&nbsp;supports&nbsp;VT100&nbsp;control&nbsp;sequences.</span>
<span style="color: #7E7E7E;">//&nbsp;The&nbsp;Serial&nbsp;Monitor&nbsp;in&nbsp;the&nbsp;Arduino&nbsp;IDE&nbsp;does&nbsp;not&nbsp;support&nbsp;VT100&nbsp;control&nbsp;sequences.&nbsp;</span>
<span style="color: #7E7E7E;">//&nbsp;If&nbsp;using&nbsp;the&nbsp;Serial&nbsp;Monitor&nbsp;the&nbsp;line&nbsp;ending&nbsp;should&nbsp;be&nbsp;set&nbsp;to&nbsp;'No&nbsp;line&nbsp;ending'.</span>
#define&nbsp;VT100_MODE&nbsp;&nbsp;1

<span style="color: #7E7E7E;">//&nbsp;Enable&nbsp;or&nbsp;disable&nbsp;the&nbsp;use&nbsp;of&nbsp;the&nbsp;AquaLEDSource&nbsp;All&nbsp;in&nbsp;One&nbsp;Super&nbsp;Screw&nbsp;Shield</span>
<span style="color: #7E7E7E;">//&nbsp;Uncomment&nbsp;the&nbsp;following&nbsp;line&nbsp;if&nbsp;you&nbsp;are&nbsp;using&nbsp;this&nbsp;shield</span>
<span style="color: #7E7E7E;">//#define&nbsp;AQUALED_SHIELD&nbsp;1</span>

#include&nbsp;&lt;<span style="color: #CC6600;">UTFT</span>.h&gt;
#include&nbsp;&lt;<span style="color: #CC6600;">DS1307</span>.h&gt;
#include&nbsp;&lt;<span style="color: #CC6600;">UTouch</span>.h&gt;

<span style="color: #7E7E7E;">//&nbsp;Declare&nbsp;which&nbsp;fonts&nbsp;we&nbsp;will&nbsp;be&nbsp;using</span>
extern&nbsp;uint8_t&nbsp;SmallFont[];
extern&nbsp;uint8_t&nbsp;BigFont[];

<span style="color: #CC6600;">UTFT</span>    myGLCD(<span style="color: #006699;">ITDB32S</span>,38,39,40,41);   <span style="color: #7E7E7E;">// Remember to change the model parameter to suit your display module!</span>
#ifndef&nbsp;AQUALED_SHIELD
&nbsp;&nbsp;<span style="color: #CC6600;">UTouch</span>  myTouch(6,5,4,3,2);
#else
&nbsp;&nbsp;<span style="color: #CC6600;">UTouch</span>  myTouch(62,63,64,65,66);
#endif

<span style="color: #7E7E7E;">//&nbsp;Init&nbsp;the&nbsp;DS1307</span>
<span style="color: #CC6600;">DS1307</span> rtc(20, 21);

<span style="color: #7E7E7E;">//&nbsp;Init&nbsp;a&nbsp;Time-data&nbsp;structure</span>
<span style="color: #CC6600;">Time</span>  t;

<span style="color: #CC6600;">int</span> clockCenterX=119;
<span style="color: #CC6600;">int</span> clockCenterY=119;
<span style="color: #CC6600;">int</span> oldsec=0;

<span style="color: #CC6600;">void</span> <span style="color: #CC6600;"><b>setup</b></span>()
{
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">InitLCD</span>();
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setFont</span>(BigFont);

&nbsp;&nbsp;myTouch.<span style="color: #CC6600;">InitTouch</span>();
&nbsp;&nbsp;myTouch.<span style="color: #CC6600;">setPrecision</span>(<span style="color: #006699;">PREC_HI</span>);

&nbsp;&nbsp;<span style="color: #7E7E7E;">// Set the clock to run-mode</span>
&nbsp;&nbsp;rtc.<span style="color: #CC6600;">halt</span>(<span style="color: #CC6600;">false</span>);
&nbsp;&nbsp;
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">begin</span>(115200);
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>(<span style="color: #006699;">"Send any character to enter serial mode..."</span>);
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>();
}

<span style="color: #CC6600;">void</span> drawDisplay()
{
&nbsp;&nbsp;<span style="color: #7E7E7E;">// Clear screen</span>
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">clrScr</span>();
&nbsp;&nbsp;
&nbsp;&nbsp;<span style="color: #7E7E7E;">// Draw Clockface</span>
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(0, 0, 255);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setBackColor</span>(0, 0, 0);
&nbsp;&nbsp;<span style="color: #CC6600;">for</span> (<span style="color: #CC6600;">int</span> i=0; i&lt;5; i++)
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawCircle</span>(clockCenterX, clockCenterY, 119-i);
&nbsp;&nbsp;}
&nbsp;&nbsp;<span style="color: #CC6600;">for</span> (<span style="color: #CC6600;">int</span> i=0; i&lt;5; i++)
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawCircle</span>(clockCenterX, clockCenterY, i);
&nbsp;&nbsp;}
&nbsp;&nbsp;
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(192, 192, 255);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"3"</span>, clockCenterX+92, clockCenterY-8);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"6"</span>, clockCenterX-8, clockCenterY+95);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"9"</span>, clockCenterX-109, clockCenterY-8);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"12"</span>, clockCenterX-16, clockCenterY-109);
&nbsp;&nbsp;<span style="color: #CC6600;">for</span> (<span style="color: #CC6600;">int</span> i=0; i&lt;12; i++)
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> ((i % 3)!=0)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;drawMark(i);
&nbsp;&nbsp;}&nbsp;&nbsp;
&nbsp;&nbsp;t&nbsp;=&nbsp;rtc.<span style="color: #CC6600;">getTime</span>();
&nbsp;&nbsp;drawMin(t.<span style="color: #CC6600;">min</span>);
&nbsp;&nbsp;drawHour(t.<span style="color: #CC6600;">hour</span>, t.<span style="color: #CC6600;">min</span>);
&nbsp;&nbsp;drawSec(t.<span style="color: #CC6600;">sec</span>);
&nbsp;&nbsp;oldsec=t.<span style="color: #CC6600;">sec</span>;

&nbsp;&nbsp;<span style="color: #7E7E7E;">// Draw calendar</span>
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(255, 255, 255);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">fillRoundRect</span>(240, 0, 319, 85);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(0, 0, 0);
&nbsp;&nbsp;<span style="color: #CC6600;">for</span> (<span style="color: #CC6600;">int</span> i=0; i&lt;7; i++)
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(249+(i*10), 0, 248+(i*10), 3);
&nbsp;&nbsp;&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(250+(i*10), 0, 249+(i*10), 3);
&nbsp;&nbsp;&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(251+(i*10), 0, 250+(i*10), 3);
&nbsp;&nbsp;}

&nbsp;&nbsp;<span style="color: #7E7E7E;">// Draw SET button</span>
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(64, 64, 128);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">fillRoundRect</span>(260, 200, 319, 239);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(255, 255, 255);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawRoundRect</span>(260, 200, 319, 239);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setBackColor</span>(64, 64, 128);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"SET"</span>, 266, 212);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setBackColor</span>(0, 0, 0);
}

<span style="color: #CC6600;">void</span> drawMark(<span style="color: #CC6600;">int</span> h)
{
&nbsp;&nbsp;<span style="color: #CC6600;">float</span> x1, y1, x2, y2;
&nbsp;&nbsp;
&nbsp;&nbsp;h=h*30;
&nbsp;&nbsp;h=h+270;
&nbsp;&nbsp;
&nbsp;&nbsp;x1=110*<span style="color: #CC6600;">cos</span>(h*0.0175);
&nbsp;&nbsp;y1=110*<span style="color: #CC6600;">sin</span>(h*0.0175);
&nbsp;&nbsp;x2=100*<span style="color: #CC6600;">cos</span>(h*0.0175);
&nbsp;&nbsp;y2=100*<span style="color: #CC6600;">sin</span>(h*0.0175);
&nbsp;&nbsp;
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x1+clockCenterX, y1+clockCenterY, x2+clockCenterX, y2+clockCenterY);
}

<span style="color: #CC6600;">void</span> drawSec(<span style="color: #CC6600;">int</span> s)
{
&nbsp;&nbsp;<span style="color: #CC6600;">float</span> x1, y1, x2, y2;
&nbsp;&nbsp;<span style="color: #CC6600;">int</span> ps = s-1;
&nbsp;&nbsp;
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(0, 0, 0);
&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (ps==-1)
&nbsp;&nbsp;&nbsp;&nbsp;ps=59;
&nbsp;&nbsp;ps=ps*6;
&nbsp;&nbsp;ps=ps+270;
&nbsp;&nbsp;
&nbsp;&nbsp;x1=95*<span style="color: #CC6600;">cos</span>(ps*0.0175);
&nbsp;&nbsp;y1=95*<span style="color: #CC6600;">sin</span>(ps*0.0175);
&nbsp;&nbsp;x2=80*<span style="color: #CC6600;">cos</span>(ps*0.0175);
&nbsp;&nbsp;y2=80*<span style="color: #CC6600;">sin</span>(ps*0.0175);
&nbsp;&nbsp;
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x1+clockCenterX, y1+clockCenterY, x2+clockCenterX, y2+clockCenterY);

&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(255, 0, 0);
&nbsp;&nbsp;s=s*6;
&nbsp;&nbsp;s=s+270;
&nbsp;&nbsp;
&nbsp;&nbsp;x1=95*<span style="color: #CC6600;">cos</span>(s*0.0175);
&nbsp;&nbsp;y1=95*<span style="color: #CC6600;">sin</span>(s*0.0175);
&nbsp;&nbsp;x2=80*<span style="color: #CC6600;">cos</span>(s*0.0175);
&nbsp;&nbsp;y2=80*<span style="color: #CC6600;">sin</span>(s*0.0175);
&nbsp;&nbsp;
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x1+clockCenterX, y1+clockCenterY, x2+clockCenterX, y2+clockCenterY);
}

<span style="color: #CC6600;">void</span> drawMin(<span style="color: #CC6600;">int</span> m)
{
&nbsp;&nbsp;<span style="color: #CC6600;">float</span> x1, y1, x2, y2, x3, y3, x4, y4;
&nbsp;&nbsp;<span style="color: #CC6600;">int</span> pm = m-1;
&nbsp;&nbsp;
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(0, 0, 0);
&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (pm==-1)
&nbsp;&nbsp;&nbsp;&nbsp;pm=59;
&nbsp;&nbsp;pm=pm*6;
&nbsp;&nbsp;pm=pm+270;
&nbsp;&nbsp;
&nbsp;&nbsp;x1=80*<span style="color: #CC6600;">cos</span>(pm*0.0175);
&nbsp;&nbsp;y1=80*<span style="color: #CC6600;">sin</span>(pm*0.0175);
&nbsp;&nbsp;x2=5*<span style="color: #CC6600;">cos</span>(pm*0.0175);
&nbsp;&nbsp;y2=5*<span style="color: #CC6600;">sin</span>(pm*0.0175);
&nbsp;&nbsp;x3=30*<span style="color: #CC6600;">cos</span>((pm+4)*0.0175);
&nbsp;&nbsp;y3=30*<span style="color: #CC6600;">sin</span>((pm+4)*0.0175);
&nbsp;&nbsp;x4=30*<span style="color: #CC6600;">cos</span>((pm-4)*0.0175);
&nbsp;&nbsp;y4=30*<span style="color: #CC6600;">sin</span>((pm-4)*0.0175);
&nbsp;&nbsp;
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x1+clockCenterX, y1+clockCenterY, x3+clockCenterX, y3+clockCenterY);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x3+clockCenterX, y3+clockCenterY, x2+clockCenterX, y2+clockCenterY);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x2+clockCenterX, y2+clockCenterY, x4+clockCenterX, y4+clockCenterY);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x4+clockCenterX, y4+clockCenterY, x1+clockCenterX, y1+clockCenterY);

&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(0, 255, 0);
&nbsp;&nbsp;m=m*6;
&nbsp;&nbsp;m=m+270;
&nbsp;&nbsp;
&nbsp;&nbsp;x1=80*<span style="color: #CC6600;">cos</span>(m*0.0175);
&nbsp;&nbsp;y1=80*<span style="color: #CC6600;">sin</span>(m*0.0175);
&nbsp;&nbsp;x2=5*<span style="color: #CC6600;">cos</span>(m*0.0175);
&nbsp;&nbsp;y2=5*<span style="color: #CC6600;">sin</span>(m*0.0175);
&nbsp;&nbsp;x3=30*<span style="color: #CC6600;">cos</span>((m+4)*0.0175);
&nbsp;&nbsp;y3=30*<span style="color: #CC6600;">sin</span>((m+4)*0.0175);
&nbsp;&nbsp;x4=30*<span style="color: #CC6600;">cos</span>((m-4)*0.0175);
&nbsp;&nbsp;y4=30*<span style="color: #CC6600;">sin</span>((m-4)*0.0175);
&nbsp;&nbsp;
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x1+clockCenterX, y1+clockCenterY, x3+clockCenterX, y3+clockCenterY);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x3+clockCenterX, y3+clockCenterY, x2+clockCenterX, y2+clockCenterY);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x2+clockCenterX, y2+clockCenterY, x4+clockCenterX, y4+clockCenterY);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x4+clockCenterX, y4+clockCenterY, x1+clockCenterX, y1+clockCenterY);
}

<span style="color: #CC6600;">void</span> drawHour(<span style="color: #CC6600;">int</span> h, <span style="color: #CC6600;">int</span> m)
{
&nbsp;&nbsp;<span style="color: #CC6600;">float</span> x1, y1, x2, y2, x3, y3, x4, y4;
&nbsp;&nbsp;<span style="color: #CC6600;">int</span> ph = h;
&nbsp;&nbsp;
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(0, 0, 0);
&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (m==0)
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;ph=((ph-1)*30)+((m+59)/2);
&nbsp;&nbsp;}
&nbsp;&nbsp;<span style="color: #CC6600;">else</span>
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;ph=(ph*30)+((m-1)/2);
&nbsp;&nbsp;}
&nbsp;&nbsp;ph=ph+270;
&nbsp;&nbsp;
&nbsp;&nbsp;x1=60*<span style="color: #CC6600;">cos</span>(ph*0.0175);
&nbsp;&nbsp;y1=60*<span style="color: #CC6600;">sin</span>(ph*0.0175);
&nbsp;&nbsp;x2=5*<span style="color: #CC6600;">cos</span>(ph*0.0175);
&nbsp;&nbsp;y2=5*<span style="color: #CC6600;">sin</span>(ph*0.0175);
&nbsp;&nbsp;x3=20*<span style="color: #CC6600;">cos</span>((ph+5)*0.0175);
&nbsp;&nbsp;y3=20*<span style="color: #CC6600;">sin</span>((ph+5)*0.0175);
&nbsp;&nbsp;x4=20*<span style="color: #CC6600;">cos</span>((ph-5)*0.0175);
&nbsp;&nbsp;y4=20*<span style="color: #CC6600;">sin</span>((ph-5)*0.0175);
&nbsp;&nbsp;
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x1+clockCenterX, y1+clockCenterY, x3+clockCenterX, y3+clockCenterY);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x3+clockCenterX, y3+clockCenterY, x2+clockCenterX, y2+clockCenterY);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x2+clockCenterX, y2+clockCenterY, x4+clockCenterX, y4+clockCenterY);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x4+clockCenterX, y4+clockCenterY, x1+clockCenterX, y1+clockCenterY);

&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(255, 255, 0);
&nbsp;&nbsp;h=(h*30)+(m/2);
&nbsp;&nbsp;h=h+270;
&nbsp;&nbsp;
&nbsp;&nbsp;x1=60*<span style="color: #CC6600;">cos</span>(h*0.0175);
&nbsp;&nbsp;y1=60*<span style="color: #CC6600;">sin</span>(h*0.0175);
&nbsp;&nbsp;x2=5*<span style="color: #CC6600;">cos</span>(h*0.0175);
&nbsp;&nbsp;y2=5*<span style="color: #CC6600;">sin</span>(h*0.0175);
&nbsp;&nbsp;x3=20*<span style="color: #CC6600;">cos</span>((h+5)*0.0175);
&nbsp;&nbsp;y3=20*<span style="color: #CC6600;">sin</span>((h+5)*0.0175);
&nbsp;&nbsp;x4=20*<span style="color: #CC6600;">cos</span>((h-5)*0.0175);
&nbsp;&nbsp;y4=20*<span style="color: #CC6600;">sin</span>((h-5)*0.0175);
&nbsp;&nbsp;
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x1+clockCenterX, y1+clockCenterY, x3+clockCenterX, y3+clockCenterY);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x3+clockCenterX, y3+clockCenterY, x2+clockCenterX, y2+clockCenterY);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x2+clockCenterX, y2+clockCenterY, x4+clockCenterX, y4+clockCenterY);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawLine</span>(x4+clockCenterX, y4+clockCenterY, x1+clockCenterX, y1+clockCenterY);
}

<span style="color: #CC6600;">void</span> printDate()
{
&nbsp;&nbsp;<span style="color: #CC6600;">Time</span> t_temp;
&nbsp;&nbsp;
&nbsp;&nbsp;t_temp&nbsp;=&nbsp;rtc.<span style="color: #CC6600;">getTime</span>();
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setFont</span>(BigFont);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(0, 0, 0);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setBackColor</span>(255, 255, 255);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">print</span>(rtc.<span style="color: #CC6600;">getDOWStr</span>(<span style="color: #006699;">FORMAT_SHORT</span>), 256, 8);
&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (t_temp.<span style="color: #CC6600;">date</span>&lt;10)
&nbsp;&nbsp;&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">printNumI</span>(t_temp.<span style="color: #CC6600;">date</span>, 272, 28);
&nbsp;&nbsp;<span style="color: #CC6600;">else</span>
&nbsp;&nbsp;&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">printNumI</span>(t_temp.<span style="color: #CC6600;">date</span>, 264, 28);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">print</span>(rtc.<span style="color: #CC6600;">getMonthStr</span>(<span style="color: #006699;">FORMAT_SHORT</span>), 256, 48);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">printNumI</span>(t_temp.<span style="color: #CC6600;">year</span>, 248, 65);
}

<span style="color: #CC6600;">void</span> clearDate()
{
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(255, 255, 255);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">fillRect</span>(248, 8, 312, 81);
}

<span style="color: #CC6600;">void</span> <span style="color: #CC6600;"><b>loop</b></span>()
{
&nbsp;&nbsp;<span style="color: #CC6600;">int</span> x, y;
&nbsp;&nbsp;
&nbsp;&nbsp;t&nbsp;=&nbsp;rtc.<span style="color: #CC6600;">getTime</span>();
&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (t.<span style="color: #CC6600;">date</span>==0)
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;setClock();
&nbsp;&nbsp;}
&nbsp;&nbsp;<span style="color: #CC6600;">else</span>
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;drawDisplay();
&nbsp;&nbsp;&nbsp;&nbsp;printDate();
&nbsp;&nbsp;}
&nbsp;&nbsp;
&nbsp;&nbsp;t&nbsp;=&nbsp;rtc.<span style="color: #CC6600;">getTime</span>();
&nbsp;&nbsp;
&nbsp;&nbsp;<span style="color: #CC6600;">while</span> (<span style="color: #CC6600;">true</span>)
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">available</span>()&gt;0)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;serialMode();
&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (oldsec!=t.<span style="color: #CC6600;">sec</span>)
&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> ((t.<span style="color: #CC6600;">sec</span>==0) and (t.<span style="color: #CC6600;">min</span>==0) and (t.<span style="color: #CC6600;">hour</span>==0))
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;clearDate();
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;printDate();
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (t.<span style="color: #CC6600;">sec</span>==0)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;drawMin(t.<span style="color: #CC6600;">min</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;drawHour(t.<span style="color: #CC6600;">hour</span>, t.<span style="color: #CC6600;">min</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;drawSec(t.<span style="color: #CC6600;">sec</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;oldsec=t.<span style="color: #CC6600;">sec</span>;
&nbsp;&nbsp;&nbsp;&nbsp;}

&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (myTouch.<span style="color: #CC6600;">dataAvailable</span>())
&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;myTouch.<span style="color: #CC6600;">read</span>();
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;x=myTouch.<span style="color: #CC6600;">getX</span>();
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;y=myTouch.<span style="color: #CC6600;">getY</span>();
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (((y&gt;=200) &amp;&amp; (y&lt;=239)) &amp;&amp; ((x&gt;=260) &amp;&amp; (x&lt;=319)))
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span> (255, 0, 0);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">drawRoundRect</span>(260, 200, 319, 239);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;setClock();
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">delay</span>(10);
&nbsp;&nbsp;&nbsp;&nbsp;t&nbsp;=&nbsp;rtc.<span style="color: #CC6600;">getTime</span>();
&nbsp;&nbsp;}
}


</pre>
</body>
</html>
