<?php

$con=mysqli_connect("localhost","root","","bill_db"); 
if (mysqli_connect_errno())

// Check connection
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
$sum=0;  
$value=$_GET['Roll'];
$result = mysqli_query($con,"SELECT * FROM bill
WHERE Roll='$value'");

if($row = mysqli_fetch_array($result))
  {
$sum=$row['Bill'];
 $sum=$sum+$_GET['Bill'];
  }
 

mysqli_query($con,"UPDATE bill SET Bill=$sum
WHERE Roll='$value'");

echo "1 record updated";
mysqli_close($con);
/*if (!mysqli_query($con,$result))
{
die('Error: ' . mysqli_error($con));
}*/


?>