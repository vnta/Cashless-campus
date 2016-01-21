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
<span style="color: #CC6600;">void</span> serialClrScr()
{
&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (VT100_MODE)
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span> (<span style="color: #CC6600;">char</span>(27));
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span> (<span style="color: #006699;">"[2J"</span>);
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span> (<span style="color: #CC6600;">char</span>(27));
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span> (<span style="color: #006699;">"[H"</span>);
&nbsp;&nbsp;}
}

<span style="color: #CC6600;">boolean</span> serialValidateDate(<span style="color: #CC6600;">byte</span> d, <span style="color: #CC6600;">byte</span> m, <span style="color: #CC6600;">word</span> y)
{
&nbsp;&nbsp;<span style="color: #CC6600;">byte</span>    mArr[12] = {31,0,31,30,31,30,31,31,30,31,30,31};
&nbsp;&nbsp;<span style="color: #CC6600;">boolean</span> ok=<span style="color: #CC6600;">false</span>;
&nbsp;&nbsp;
&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (m==2)
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> ((y % 4)==0)
&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> ((d&gt;0) and (d&lt;=29))
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ok&nbsp;=&nbsp;<span style="color: #CC6600;">true</span>;
&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">else</span>
&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> ((d&gt;0) and (d&lt;=28))
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ok&nbsp;=&nbsp;<span style="color: #CC6600;">true</span>;
&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;}
&nbsp;&nbsp;<span style="color: #CC6600;">else</span>
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> ((d&gt;0) and (d&lt;=mArr[m-1]))
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ok&nbsp;=&nbsp;<span style="color: #CC6600;">true</span>;
&nbsp;&nbsp;}
&nbsp;&nbsp;
&nbsp;&nbsp;<span style="color: #CC6600;">return</span> ok;
}

<span style="color: #CC6600;">void</span> serialSendDOW(<span style="color: #CC6600;">byte</span> <span style="color: #CC6600;">dow</span>)
{
&nbsp;&nbsp;<span style="color: #CC6600;">char</span>* str[] = {<span style="color: #006699;">"Monday"</span>,<span style="color: #006699;">"Tuesday"</span>,<span style="color: #006699;">"Wednesday"</span>,<span style="color: #006699;">"Thursday"</span>,<span style="color: #006699;">"Friday"</span>,<span style="color: #006699;">"Saturday"</span>,<span style="color: #006699;">"Sunday"</span>};
&nbsp;&nbsp;
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(str[<span style="color: #CC6600;">dow</span>-1]);
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">", "</span>);
}

<span style="color: #CC6600;">void</span> serialSendMenu()
{
&nbsp;&nbsp;serialClrScr();
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span> (<span style="color: #006699;">"UTFT_Analog_Clock (C)2010-2012 Henning Karlsen"</span>);
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span> (<span style="color: #006699;">"----------------------------------------------"</span>);
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span> (<span style="color: #006699;">"T : Set time"</span>);
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span> (<span style="color: #006699;">"D : Set date"</span>);
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span> (<span style="color: #006699;">"R : Read current time and date"</span>);
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span> (<span style="color: #006699;">"? : Print menu"</span>);
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span> (<span style="color: #006699;">"Q : Quit Serial Mode"</span>);
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span> ();
}

<span style="color: #CC6600;">void</span> serialSetTime()
{
&nbsp;&nbsp;<span style="color: #CC6600;">char</span> buf[6];
&nbsp;&nbsp;<span style="color: #CC6600;">char</span> tmp;
&nbsp;&nbsp;<span style="color: #CC6600;">int</span>  cnt=0;
&nbsp;&nbsp;<span style="color: #CC6600;">int</span>  h,m,s;
&nbsp;&nbsp;
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"Enter time in 24-hour format [hhmmss]: "</span>);
&nbsp;&nbsp;<span style="color: #CC6600;">while</span> (cnt&lt;6)
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">while</span>(<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">available</span>()==0) {};
&nbsp;&nbsp;&nbsp;&nbsp;tmp&nbsp;=&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">read</span>();
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> ((tmp&gt;=<span style="color: #006699;">'0'</span>) and (tmp&lt;=<span style="color: #006699;">'9'</span>))
&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;buf[cnt]=tmp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cnt++;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(tmp);
&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;}
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>();
&nbsp;&nbsp;h&nbsp;=&nbsp;((buf[0]-<span style="color: #006699;">'0'</span>)*10) + (buf[1]-<span style="color: #006699;">'0'</span>);
&nbsp;&nbsp;m&nbsp;=&nbsp;((buf[2]-<span style="color: #006699;">'0'</span>)*10) + (buf[3]-<span style="color: #006699;">'0'</span>);
&nbsp;&nbsp;s&nbsp;=&nbsp;((buf[4]-<span style="color: #006699;">'0'</span>)*10) + (buf[5]-<span style="color: #006699;">'0'</span>);
&nbsp;&nbsp;<span style="color: #CC6600;">if</span> ((h&gt;23) or (m&gt;59) or (s&gt;59))
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>(<span style="color: #006699;">"ERROR: Invalid time"</span>);
&nbsp;&nbsp;<span style="color: #CC6600;">else</span>
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;rtc.<span style="color: #CC6600;">setTime</span>(h,m,s);
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"New time set to "</span>);
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (h&lt;10)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"0"</span>);
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(h,<span style="color: #006699;">DEC</span>);
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">":"</span>);
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (m&lt;10)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"0"</span>);
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(m,<span style="color: #006699;">DEC</span>);
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">":"</span>);
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (s&lt;10)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"0"</span>);
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(s,<span style="color: #006699;">DEC</span>);
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>(<span style="color: #006699;">"..."</span>);
&nbsp;&nbsp;}
}

<span style="color: #CC6600;">void</span> serialSetDate()
{
&nbsp;&nbsp;<span style="color: #CC6600;">char</span> buf[8];
&nbsp;&nbsp;<span style="color: #CC6600;">char</span> tmp;
&nbsp;&nbsp;<span style="color: #CC6600;">int</span>  cnt=0;
&nbsp;&nbsp;<span style="color: #CC6600;">int</span>  d,m,y;
&nbsp;&nbsp;
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"Enter date [ddmmyyyy]: "</span>);
&nbsp;&nbsp;<span style="color: #CC6600;">while</span> (cnt&lt;8)
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">while</span>(<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">available</span>()==0) {};
&nbsp;&nbsp;&nbsp;&nbsp;tmp&nbsp;=&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">read</span>();
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> ((tmp&gt;=<span style="color: #006699;">'0'</span>) and (tmp&lt;=<span style="color: #006699;">'9'</span>))
&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;buf[cnt]=tmp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cnt++;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(tmp);
&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;}
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>();
&nbsp;&nbsp;d&nbsp;=&nbsp;((buf[0]-<span style="color: #006699;">'0'</span>)*10) + (buf[1]-<span style="color: #006699;">'0'</span>);
&nbsp;&nbsp;m&nbsp;=&nbsp;((buf[2]-<span style="color: #006699;">'0'</span>)*10) + (buf[3]-<span style="color: #006699;">'0'</span>);
&nbsp;&nbsp;y&nbsp;=&nbsp;((buf[4]-<span style="color: #006699;">'0'</span>)*1000) + ((buf[5]-<span style="color: #006699;">'0'</span>)*100) + ((buf[6]-<span style="color: #006699;">'0'</span>)*10) + (buf[7]-<span style="color: #006699;">'0'</span>);
&nbsp;&nbsp;<span style="color: #CC6600;">if</span> ((y&lt;2000) or (y&gt;2099))
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>(<span style="color: #006699;">"ERROR: Invalid time"</span>);
&nbsp;&nbsp;<span style="color: #CC6600;">else</span>
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> ((m&lt;1) or (m&gt;12))
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>(<span style="color: #006699;">"ERROR: Invalid time"</span>);
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">else</span>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (!serialValidateDate(d,m,y))
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>(<span style="color: #006699;">"ERROR: Invalid time"</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">else</span>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;rtc.<span style="color: #CC6600;">setDate</span>(d,m,y);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;rtc.<span style="color: #CC6600;">setDOW</span>(calcDOW(d,m,y));
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"New date set to "</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;serialSendDOW(calcDOW(d,m,y));
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (d&lt;10)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"0"</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(d,<span style="color: #006699;">DEC</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"."</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (m&lt;10)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"0"</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(m,<span style="color: #006699;">DEC</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"."</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(y,<span style="color: #006699;">DEC</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>(<span style="color: #006699;">"..."</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}
}

<span style="color: #CC6600;">void</span> serialReadTimeDate()
{
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"Time: "</span>);
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>(rtc.<span style="color: #CC6600;">getTimeStr</span>());
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"Date: "</span>);
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(rtc.<span style="color: #CC6600;">getDOWStr</span>(<span style="color: #006699;">FORMAT_SHORT</span>));
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">", "</span>);
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>(rtc.<span style="color: #CC6600;">getDateStr</span>());
}

<span style="color: #CC6600;">void</span> serialMode()
{
&nbsp;&nbsp;<span style="color: #CC6600;">boolean</span> quitMode = <span style="color: #CC6600;">false</span>;
&nbsp;&nbsp;<span style="color: #CC6600;">char</span>    cmd;
&nbsp;&nbsp;
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">clrScr</span>();
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setFont</span>(BigFont);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setColor</span>(255,255,255);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">setBackColor</span>(0,0,0);
&nbsp;&nbsp;myGLCD.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"SERIAL MODE"</span>, <span style="color: #006699;">CENTER</span>, (myGLCD.<span style="color: #CC6600;">getDisplayYSize</span>()/2)-8);
&nbsp;&nbsp;
&nbsp;&nbsp;<span style="color: #CC6600;">while</span> (<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">available</span>()&gt;0)
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">read</span>();
&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;serialSendMenu();
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span> (<span style="color: #006699;">"&gt; "</span>);
&nbsp;&nbsp;
&nbsp;&nbsp;<span style="color: #CC6600;">while</span> (quitMode==<span style="color: #CC6600;">false</span>)
&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">available</span>()&gt;0)
&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cmd&nbsp;=&nbsp;uCase(<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">read</span>());
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>(cmd);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">switch</span> (cmd)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">case</span> <span style="color: #006699;">'T'</span>: serialSetTime();
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">break</span>;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">case</span> <span style="color: #006699;">'D'</span>: serialSetDate();
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">break</span>;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">case</span> <span style="color: #006699;">'R'</span>: serialReadTimeDate();
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">break</span>;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">case</span> <span style="color: #006699;">'?'</span>: serialSendMenu();
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">break</span>;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">case</span> <span style="color: #006699;">'Q'</span>: <span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>(<span style="color: #006699;">"Exiting serial mode..."</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>();
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;quitMode&nbsp;=&nbsp;<span style="color: #CC6600;">true</span>;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">break</span>;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">default</span>:  <span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>(<span style="color: #006699;">"ERROR: Unknown command"</span>);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">break</span>;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;">if</span> (quitMode==<span style="color: #CC6600;">false</span>)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">print</span>(<span style="color: #006699;">"&gt; "</span>);
&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;}
&nbsp;&nbsp;<span style="color: #CC6600;">while</span> (<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">available</span>()&gt;0)
&nbsp;&nbsp;&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">read</span>();
&nbsp;&nbsp;drawDisplay();
&nbsp;&nbsp;printDate();
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>(<span style="color: #006699;">"Send any character to enter serial mode again..."</span>);
&nbsp;&nbsp;<span style="color: #CC6600;"><b>Serial</b></span>.<span style="color: #CC6600;">println</span>();
}



</pre>
</body>
</html>
