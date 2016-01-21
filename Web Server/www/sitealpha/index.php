<html>
<body>
<?php
$con=mysqli_connect("localhost","root","","final_db");
// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
if (!(empty($_POST['Name'])))
{
$sql="INSERT INTO coupon (Copon_name, Coupon_price)
VALUES
('$_POST[Name]','$_POST[price]')";
echo "1 record added";


if (!mysqli_query($con,$sql))
  {
  die('Error: ' . mysqli_error($con));
  }
}

?>
<meta http-equiv="refresh" content="0; url=coupons.php"> 
</body>
</html>
