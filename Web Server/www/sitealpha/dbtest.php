<?php
/*$con=mysqli_connect("localhost","root","");
// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }

// Create database
$sql="CREATE DATABASE saturday";
if (mysqli_query($con,$sql))
  {
  echo "Database saturday created successfully";
  }
else
  {
  echo "Error creating database: " . mysqli_error($con);
  }
 */
 $con=mysqli_connect("localhost","root","","saturday");
// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }

// Create table
$sql="CREATE TABLE coupon(Copon_name CHAR(30),Coupon_price CHAR(30))";

// Execute query
if (mysqli_query($con,$sql))
  {
  echo "Tables created successfully";
  }
else
  {
  echo "Error creating table: " . mysqli_error($con);
  }
 
?>
