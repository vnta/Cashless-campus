 
$count=0;
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
 /*echo $row['Copon_name']  ;
  echo " " . $row['Coupon_price'];
  echo "<br>";*/
  $count=$count+1;
 }
 while($do<$count)
{
    <form action="checkbox-form.php" method="post">
       $result<br />
    <input type="checkbox" name="$row['Copon_name']" value="Delete" />
      $do=$do+1;
	  </form>


mysqli_close($con);

?>
}

 
