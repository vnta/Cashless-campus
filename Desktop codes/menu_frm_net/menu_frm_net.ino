 int inc=0;
 if (c=="^")
 
 { while(c!="^")
 
  {
    coupon[inc].name= client.readStringUntil('#') ;
    coupon[inc].rate= client.readStringUntil('*') ;
    inc=inc+1;
  }
   
   
   
   
   
    noItems=menuFile.parseInt();   // parse doesnt read the next char (only peeks)
    menuFile.read();
    while(inc<noItems){
      coupon[inc].name=menuFile.readStringUntil(',');  // readuntil reads " , " also
      coupon[inc].rate=menuFile.parseInt();
      menuFile.read();
      coupon[inc].veg=menuFile.parseInt();
      menuFile.read();
      inc=inc+1;
    }
