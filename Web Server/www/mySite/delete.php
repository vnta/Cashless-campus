<html>
<body>
<?php
$con=mysqli_connect("localhost","root","","final_db");
// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
mysqli_query($con,"DELETE FROM coupon WHERE Copon_name='$_POST[Name]'");

mysqli_close($con);
?>
<meta http-equiv="refresh" content="0; url=delete_item.php"> 
</body>
</html>