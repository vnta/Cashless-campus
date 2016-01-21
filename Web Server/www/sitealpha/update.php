<html>
<body>
<?php
$con=mysqli_connect("localhost","root","","final_db");
// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }

mysqli_query($con,"UPDATE coupon SET Coupon_price=$_POST[price]
WHERE Copon_name='$_POST[Name]'");

mysqli_close($con);
?>
<meta http-equiv="refresh" content="0; url=gotoedit.php"> 
</body>
</html>