<?php
/* $timestamp = time();
 $w = date( "w", $timestamp);
 date_default_timezone_set('Asia/Calcutta');

if (date_default_timezone_get()) {
    echo 'date_default_timezone_set: ' . date_default_timezone_get() . '<br />';
}

if (ini_get('date.timezone')) {
    echo 'date.timezone: ' . ini_get('date.timezone');
}

$hourMin = date('H');
echo $hourMin;
 if (($w==0)&&(($hourMin>7)&&($hourMin<12))
 {
$con=mysqli_connect("localhost","root","","sunday_breakfast");
}
 if (($w==0)&&(($hourMin>12)&&($hourMin<7)
 {
$con=mysqli_connect("localhost","root","","sunday_lunch");
}
if (($w==0)&&(($hourMin>7)&&($hourMin<9)
 {
$con=mysqli_connect("localhost","root","","sunday_dinner");
}

 if (($w==1)&&(($hourMin>7)&&($hourMin<12))
 {
$con=mysqli_connect("localhost","root","","monday_breakfast");
}
 if (($w==1)&&(($hourMin>12)&&($hourMin<7)
 {
$con=mysqli_connect("localhost","root","","monday_lunch");
}
if (($w==1)&&(($hourMin>7)&&($hourMin<9)
 {
$con=mysqli_connect("localhost","root","","monday_dinner");
}

 if (($w==2)&&(($hourMin>7)&&($hourMin<12))
 {
$con=mysqli_connect("localhost","root","","tuesday_breakfast");
}
 if (($w==2)&&(($hourMin>12)&&($hourMin<7)
 {
$con=mysqli_connect("localhost","root","","tuesday_lunch");
}
if (($w==2)&&(($hourMin>7)&&($hourMin<9)
 {
$con=mysqli_connect("localhost","root","","tuesday_dinner");
}

 if (($w==3)&&(($hourMin>7)&&($hourMin<12))
 {
$con=mysqli_connect("localhost","root","","wednesday_breakfast");
}
 if (($w==3)&&(($hourMin>12)&&($hourMin<7)
 {
$con=mysqli_connect("localhost","root","","wednesday_lunch");
}
if (($w==3)&&(($hourMin>7)&&($hourMin<9)
 {
$con=mysqli_connect("localhost","root","","wednesday_dinner");
}

 if (($w==4)&&(($hourMin>7)&&($hourMin<12))
 {
$con=mysqli_connect("localhost","root","","thursday_breakfast");
}
 if (($w==4)&&(($hourMin>12)&&($hourMin<7)
 {
$con=mysqli_connect("localhost","root","","thursday_lunch");
}
if (($w==4)&&(($hourMin>7)&&($hourMin<9)
 {
$con=mysqli_connect("localhost","root","","thursday_dinner");
}

 if (($w==5)&&(($hourMin>7)&&($hourMin<12))
 {
$con=mysqli_connect("localhost","root","","friday_breakfast");
}
 if (($w==5)&&(($hourMin>12)&&($hourMin<7)
 {
$con=mysqli_connect("localhost","root","","friday_lunch");
}
if (($w==5)&&(($hourMin>7)&&($hourMin<9)
 {
$con=mysqli_connect("localhost","root","","friday_dinner");
}

 if (($w==6)&&(($hourMin>7)&&($hourMin<12))
 {
$con=mysqli_connect("localhost","root","","saturday_breakfast");
}
 if (($w==6)&&(($hourMin>12)&&($hourMin<7)
 {
$con=mysqli_connect("localhost","root","","saturday_lunch");
}
if (($w==6)&&(($hourMin>7)&&($hourMin<9)
 {
$con=mysqli_connect("localhost","root","","saturday_dinner");
}




*/

 $con=mysqli_connect("localhost","root","","final_db");

// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }

$result = mysqli_query($con,"SELECT * FROM coupon ORDER BY Coupon_price");
 echo "^";
while($row = mysqli_fetch_array($result))
  { 
  echo " ";
  echo  $row['Copon_name']  ;
  echo "#" . $row['Coupon_price'];
  echo "*";
  echo $row['veg'];
  
  } 
echo  "^"; 

mysqli_close($con);
?>