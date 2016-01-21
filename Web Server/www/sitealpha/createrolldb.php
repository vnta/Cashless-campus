<?php


$con=mysqli_connect("localhost","root","","bill_db");
// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
ALTER TABLE bill AUTO_INCREMENT=12000;

ALTER TABLE bill ADD `Roll` INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY FIRST;



if (!mysqli_query($con,$sql))
  {
  die('Error: ' . mysqli_error($con));
  }


?>