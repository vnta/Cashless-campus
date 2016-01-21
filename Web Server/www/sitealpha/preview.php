<?php
$con=mysqli_connect("localhost","root","","bill_db");
// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }

$result = mysqli_query($con,"SELECT * FROM bill ORDER BY Roll");

while($row = mysqli_fetch_array($result))
  {
  echo $row['Roll']  ;
  echo " " . $row['Bill'];
  echo "<br>";
  }

mysqli_close($con);

?>