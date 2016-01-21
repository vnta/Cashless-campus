<!DOCTYPE html>
<html>
<body>
<h1 style="font-family: snap itc;"><p style="color:goldenrod;">Alter Mess Menu </p></h1>


<h2><i><b><p style="color:navy;">TODAY'S MESS MENU </P></i></b></h2>
<br><br>
<a href="gotoedit.php"> <img src="up.jpg" > </a> 







<head>
	<title> Bill</title>
	<link href="styles.css" media="screen" rel="stylesheet" type="text/css" />
	</head>
		
<?php
$con=mysqli_connect("localhost","root","","final_db");
// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $i=0;

$result = mysqli_query($con,"SELECT * FROM coupon ORDER BY Coupon_price");

while($row = mysqli_fetch_array($result))
  {
  echo $row['Copon_name']  ;
  echo " " . $row['Coupon_price'];
  echo "<br>";
  $i=$i+1;
  }  
  echo $i;

mysqli_close($con);
?>


<br><br><br>
<form action="index.php" method="post">
<h2><b><p style="color:maroon;">Coupon_name: <input type="text" name="Name">
Coupon_price <input type="text" name="price">

<input type="submit" value="Add"></p></b></h2>
</form>




</body>
</html>