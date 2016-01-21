<html>
<body>
<?php
$con=mysqli_connect("localhost","root","","final_db");
// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }

$result = mysqli_query($con,"SELECT * FROM coupon ORDER BY Coupon_price");

while($row = mysqli_fetch_array($result))
  {
  echo $row['Copon_name']  ;
  echo " " . $row['Coupon_price'];
  echo "<br>";
  }

mysqli_close($con);

?>



<form action="update.php" method="post">
Coupon_name: <input type="text" name="Name">
Coupon_price <input type="text" name="price">
<input type="submit" value="Update">
</form>
</body>
</html>
